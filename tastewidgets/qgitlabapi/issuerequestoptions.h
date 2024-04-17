#pragma once

#include "requestoptions.h"

#include <QList>
#include <QMap>
#include <QStringList>
#include <QVariant>

namespace gitlab {

/**
 * @brief The IssueRequestOptions class holds all options for fetching issue data
 * For more documentation see https://docs.gitlab.com/ee/api/issues.html
 */
class IssueRequestOptions : public RequestOptions
{
public:
    QString mAssignee; /// If not empty, only issues assigned to that assignee (username) are fetched
    QString mAuthor; /// If not empty, only issues assigned to that assignee with that username are fetched
    QList<int> mIids; /// If not empty, return only the issues having the given iids (unique IDs for the whole server)
    QStringList mLabels; /// Comma-separated list of label names, issues must have all labels to be returned. None lists
                         /// all issues with no labels. Any lists all issues with at least one label. No+Label
                         /// (Deprecated) lists all issues with no labels. Predefined names are case-insensitive.
                         ///
    QString mScope = "all"; /// Return issues for the given scope: "created_by_me", "assigned_to_me" or "all".
    QString mState = "opened"; /// Return "all" issues or just those that are "opened" or "closed"

    /**
     * @brief queryData Creates query data for the URL
     */
    QUrlQuery urlQuery() const override;
};

}
