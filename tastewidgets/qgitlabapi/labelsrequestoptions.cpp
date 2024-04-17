#include "labelsrequestoptions.h"

#include "urlcomposer.h"

#include <QMap>
#include <QVariant>

using namespace gitlab;

QUrlQuery LabelsRequestOptions::urlQuery() const
{
    QMap<QString, QVariant> data;
    if (!mSearch.isEmpty()) {
        data["search"] = mSearch;
    }

    if (mWith_counts) {
        data["with_counts"] = mWith_counts;
    }

    if (mPage > 0) {
        data["page"] = mPage;
    } else {
        data["page"] = 1;
    }

    return UrlComposer::setQuery(data);
}
