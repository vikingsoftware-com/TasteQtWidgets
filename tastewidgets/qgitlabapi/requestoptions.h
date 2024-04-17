#pragma once

#include <QUrlQuery>

namespace gitlab {

class RequestOptions
{
public:
    int mPage = 1; /// Number of the page to fetch. See pagination of gitlab API
    int mProjectID = -1;
    /**
     * @brief queryData Creates query data for the URL
     */
    virtual QUrlQuery urlQuery() const = 0;
};

}
