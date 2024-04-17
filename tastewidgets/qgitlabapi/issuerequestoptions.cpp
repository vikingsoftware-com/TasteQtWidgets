#include "issuerequestoptions.h"

#include "urlcomposer.h"

using namespace gitlab;

QUrlQuery IssueRequestOptions::urlQuery() const
{
    QMap<QString, QVariant> data;
    if (!mAssignee.isEmpty()) {
        data["assignee_username"] = mAssignee;
    }
    if (!mAuthor.isEmpty()) {
        data["author_username"] = mAuthor;
    }
    if (!mIids.isEmpty()) {
        data["assignee_username"] = QVariant::fromValue<QList<int>>(mIids);
    }
    if (mPage > 0) {
        data["page"] = mPage;
    } else {
        data["page"] = 1;
    }
    if (!mScope.isEmpty()) {
        data["scope"] = mScope;
    }
    if (!mState.isEmpty()) {
        data["state"] = mState;
    }
    if (!mLabels.isEmpty()) {
        data["labels"] = mLabels.join(",");
    }

    // Set the maximum number of issues being returned for this single request (gitlab max is 100)
    data["per_page"] = 80;

    return UrlComposer::setQuery(data);
}
