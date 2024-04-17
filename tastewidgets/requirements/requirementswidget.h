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

#include "checkedfilterproxymodel.h"
#include "issuetextproxymodel.h"
#include "tagfilterproxymodel.h"

#include <QItemSelection>
#include <QPointer>
#include <QSortFilterProxyModel>
#include <QToolButton>
#include <QWidget>

class QHeaderView;

namespace Ui {
class RequirementsWidget;
}

namespace ive {
class InterfaceDocument;
}

namespace tracecommon {
class WidgetBar;
}

namespace requirement {
class RequirementsManager;
class RequirementsModelBase;

class RequirementsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RequirementsWidget(QWidget *parent = nullptr);
    ~RequirementsWidget();

    /*!
     * The manager to load/save the requirements from the data source (gitlab)
     */
    void setManager(RequirementsManager *manager);
    /*!
     * Model for the QTableView to show the requirements
     */
    void setModel(requirement::RequirementsModelBase *model);

    /*!
     * Returns the URL to fetch the requirements from
     */
    QUrl url() const;
    /*!
     * \brief RequirementsWidget::setUrl sets the url to fetch the requirements from
     * \param url
     */
    void setUrl(const QUrl &url);
    /*!
     * \brief RequirementsWidget::token Returns the token to authenticate for fetching the requirements
     */
    QString token() const;
    /*!
     * \brief RequirementsWidget::setToken sets the Token to authenticate for fetching the requirements
     * \param token
     */
    void setToken(const QString &token);

    /*!
     * A pointer to the table header, so the column geometry can be saved/restored
     */
    QHeaderView *horizontalTableHeader() const;

protected Q_SLOTS:
    void setLoginData();
    void updateServerStatus();
    void updateProjectReady();
    void openIssueLink(const QModelIndex &index);
    void toggleShowUsedRequirements();
    void requestRequirements();
    void showNewRequirementDialog() const;
    void removeRequirement();
    void modelSelectionChanged(const QItemSelection &selected, const QItemSelection &);
    void fillTagBar(const QStringList &tags);

Q_SIGNALS:
    void requirementSelected(QString RequirementID, bool checked);
    void requirementsUrlChanged(QString requirementsUrl);
    void requirementsCredentialsChanged(QUrl url, QString token);

protected:
    QString m_requirementsUrl;

private:
    bool tagButtonExists(const QString &tag) const;
    void onChangeOfCredentials();

    Ui::RequirementsWidget *ui;
    QList<QToolButton *> m_tagButtons;
    tracecommon::WidgetBar *m_widgetBar;
    QPointer<RequirementsManager> m_reqManager;
    QPointer<requirement::RequirementsModelBase> m_model;
    tracecommon::IssueTextProxyModel m_textFilterModel;
    tracecommon::TagFilterProxyModel m_tagFilterModel;
    CheckedFilterProxyModel m_checkedModel;
};

}
