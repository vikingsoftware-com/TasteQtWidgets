/*
   Copyright (C) 2024 European Space Agency - <maxime.perrotin@esa.int>

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

#include "review.h"

#include <QObject>

namespace reviews {

/*!
 * Returns the criticality / test method of the review.
 */
QString Review::criticality() const
{
    if (m_tags.contains("minor", Qt::CaseInsensitive)) {
        return QObject::tr("minor");
    }
    if (m_tags.contains("major", Qt::CaseInsensitive)) {
        return QObject::tr("major");
    }
    if (m_tags.contains("editorial", Qt::CaseInsensitive)) {
        return QObject::tr("editorial");
    }

    return QObject::tr("default");
}

bool Review::isValid() const
{
    return !m_id.isEmpty() && !m_longName.isEmpty();
}

bool Review::operator==(const Review &other) const
{
    return (m_id == other.m_id) && (m_longName == other.m_longName) && (m_description == other.m_description)
            && (m_author == other.m_author) && (m_issueID == other.m_issueID) && (m_tags == other.m_tags)
            && (m_link == other.m_link);
}

} // namespace reviews
