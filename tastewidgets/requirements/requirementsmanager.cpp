/*
   Copyright (C) 2023 European Space Agency - <maxime.perrotin@esa.int>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public License
along with this program. If not, see <https://www.gnu.org/licenses/lgpl-2.1.html>.
*/

#include "requirementsmanager.h"

#include "gitlab/gitlabrequirements.h"
#include "issuerequestoptions.h"
#include "issuesmanagerprivate.h"
#include "qgitlabclient.h"

#include <QDir>

namespace requirement {

struct RequirementsManager::RequirementsManagerPrivate : public tracecommon::IssuesManagerPrivate {
    RequirementsManagerPrivate(RequirementsManager::REPO_TYPE rType)
        : IssuesManagerPrivate(rType)
    {
        switch (repoType) {
        case REPO_TYPE::GITLAB:
            gitlabRequirements = std::make_unique<requirement::GitLabRequirements>();
        }
    }

    std::unique_ptr<requirement::GitLabRequirements> gitlabRequirements;
};

RequirementsManager::RequirementsManager(REPO_TYPE repoType, QObject *parent)
    : tracecommon::IssuesManager(parent)
    , d(std::make_unique<RequirementsManagerPrivate>(repoType))
{
    init(d.get());
    switch (d->repoType) {
    case (REPO_TYPE::GITLAB): {
        connect(d->gitlabClient.get(), &gitlab::QGitlabClient::listOfIssues, d->gitlabRequirements.get(),
                &requirement::GitLabRequirements::listOfIssues);
        connect(d->gitlabClient.get(), &gitlab::QGitlabClient::issueCreated, this,
                &RequirementsManager::requirementAdded);
        connect(d->gitlabClient.get(), &gitlab::QGitlabClient::issueClosed, this,
                &RequirementsManager::requirementClosed);
        connect(d->gitlabClient.get(), &gitlab::QGitlabClient::issueFetchingDone, this,
                &RequirementsManager::fetchingRequirementsEnded);
        connect(d->gitlabClient.get(), &gitlab::QGitlabClient::listOfLabels, this, [this](QList<gitlab::Label> labels) {
            m_tagsBuffer.append(GitLabRequirements::tagsFromLabels(labels));
        });
        connect(d->gitlabRequirements.get(), &requirement::GitLabRequirements::listOfRequirements, this,
                &RequirementsManager::listOfRequirements);
        break;
    }
    default:
        qDebug() << "unknown repository type";
    }
}

RequirementsManager::~RequirementsManager() { }

/*!
 * Starts a request to load all requirements from the server. The requirements will be delivered by the
 * listOfRequirements signal.
 * \return Returns true when everything went well.
 */
bool RequirementsManager::requestAllRequirements()
{
    switch (d->repoType) {
    case (REPO_TYPE::GITLAB): {
        gitlab::IssueRequestOptions options;
        options.mProjectID = m_projectID;
        options.mLabels = { k_requirementsTypeLabel };
        const bool wasBusy = d->gitlabClient->requestIssues(options);
        if (wasBusy) {
            return false;
        }
        Q_EMIT startingFetchingRequirements();
        return true;
    }
    default:
        qDebug() << "unknown repository type";
    }
    return false;
}

/*!
 * Creates a new requirement on the server
 * \param title The title of the requirement
 * \param reqIfId The ID of that requirement
 * \param description The content of the requirements
 * \param testMethod The selected class of testing
 * \return Returns true when everything went well.
 */
bool RequirementsManager::createRequirement(
        const QString &title, const QString &reqIfId, const QString &description, const QString &testMethod) const
{
    switch (d->repoType) {
    case (REPO_TYPE::GITLAB): {
        const QString descr = QString("#reqid %1\n\n%2").arg(reqIfId, description);
        QStringList labels = { k_requirementsTypeLabel, testMethod };
        const bool wasBusy = d->gitlabClient->createIssue(m_projectID, title, descr, labels);
        return !wasBusy;
    }
    default:
        qDebug() << "unknown repository type";
    }
    return false;
}

bool RequirementsManager::removeRequirement(const Requirement &requirement) const
{
    switch (d->repoType) {
    case (REPO_TYPE::GITLAB): {
        const bool wasBusy = d->gitlabClient->closeIssue(m_projectID, requirement.m_issueID);
        return !wasBusy;
    }
    default:
        qDebug() << "unknown repository type";
    }
    return false;
}

}
