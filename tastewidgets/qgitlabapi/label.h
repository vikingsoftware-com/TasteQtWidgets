#pragma once

#include "QGitlabAPI_global.h"

#include <QColor>
#include <QJsonObject>
#include <QString>

namespace gitlab {

class QGITLABAPI_EXPORT Label
{
public:
    Label(const QJsonObject &label);

    int mLabelId;
    QString mName;
    QString mDescription;
    QColor mColor;
};

}
