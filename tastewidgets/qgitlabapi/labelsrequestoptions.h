#pragma once

#include "requestoptions.h"
namespace gitlab {

class LabelsRequestOptions : public RequestOptions
{
public:
    QString mSearch; /// Keyword to filter labels by
    bool mWith_counts = false; /// Whether or not to include issue and merge request counts
    /**
     * @brief queryData Creates query data for the URL
     */
    QUrlQuery urlQuery() const override;
};
}
