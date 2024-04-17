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

#pragma once

#include "issuesmanager.h"
#include "requirement.h"

#include <memory>

namespace requirement {

/*!
 * The RequirementsManager is responsible to communicate to the server/storage that handles the requirments for
 * components
 */
class RequirementsManager : public tracecommon::IssuesManager
{
    Q_OBJECT

public:
    RequirementsManager(REPO_TYPE repoType = tracecommon::IssuesManager::REPO_TYPE::GITLAB, QObject *parent = nullptr);
    ~RequirementsManager();

    /*!
     * \brief Makes a request to retrieve all the requirements
     * \return Returns true if there's a pending request otherwise false.
     */
    bool requestAllRequirements();
    /*!
     * \brief Makes a request to create requirement
     * \param title The title of the requirement
     * \param reqIfId The ID of the requirement (Not be confused with the Gitlab issue ID)
     * \param description The requiement's description
     * \param testMethod The test method of the requirement
     * \return Returns true if there's a pending request otherwise false.
     */
    bool createRequirement(
            const QString &title, const QString &reqIfId, const QString &description, const QString &testMethod) const;
    /*!
     * \brief Removes a requirement
     * \param requirement Instance of the requirement object to be removed
     * \return Returns true if there's a pending request otherwise false.
     */
    bool removeRequirement(const Requirement &requirement) const;

Q_SIGNALS:
    /*!
     * \brief This signal marks the start of the requirements fetching
     */
    void startingFetchingRequirements();
    /*!
     * \brief This signal marks the end of the requirements fetching
     */
    void fetchingRequirementsEnded();
    /*!
     * \brief This signal carries the list of requirements fetched from Gitlab server
     */
    void listOfRequirements(const QList<requirement::Requirement> &);
    /*!
     * \brief This signal is triggered when a Requirement is created
     */
    void requirementAdded();
    /*!
     * \brief This signal is triggered when a Requirement is closed
     */
    void requirementClosed();

private:
    class RequirementsManagerPrivate;
    std::unique_ptr<RequirementsManagerPrivate> d;
};

}
