#include "label.h"

using namespace gitlab;

Label::Label(const QJsonObject &label)
{
    mLabelId = label["id"].toInt();
    mName = label["name"].toString();
    mDescription = label["description"].toString();
    mColor = QColor(label["color"].toString());
}
