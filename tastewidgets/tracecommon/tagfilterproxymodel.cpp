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

#include "tagfilterproxymodel.h"

#include "tracecommonmodelbase.h"

namespace tracecommon {

TagFilterProxyModel::TagFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel { parent }
{
}

/*!
 * Add one more tag to be accepted
 */
void TagFilterProxyModel::addTag(const QString &tag)
{
    if (m_tags.contains(tag)) {
        return;
    }
    m_tags.append(tag);
    invalidate();
}

/*!
 * Remove one tag from the list of accepted ones.
 * If all tags are removed, the filter shows all data
 */
void TagFilterProxyModel::removeTag(const QString &tag)
{
    m_tags.removeAll(tag);
    invalidate();
}

bool TagFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourcParent) const
{
    if (m_tags.isEmpty()) {
        return true;
    }

    QModelIndex idx = sourceModel()->index(sourceRow, filterKeyColumn(), sourcParent);
    const QStringList tags = idx.data(TraceCommonModelBase::TagsRole).toStringList();

    for (const QString &tag : m_tags) {
        if (tags.contains(tag)) {
            return true;
        }
    }
    return false;
}

} // namespace tracecommon
