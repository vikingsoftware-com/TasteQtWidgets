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

#include "issuetextproxymodel.h"

#include "tracecommonmodelbase.h"

namespace tracecommon {

IssueTextProxyModel::IssueTextProxyModel(QObject *parent)
    : QSortFilterProxyModel { parent }
{
}

bool IssueTextProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QRegularExpression expression = filterRegularExpression();

    const QModelIndex idx = sourceModel()->index(sourceRow, 0, sourceParent);

    const QString detail = idx.data(TraceCommonModelBase::DetailDescriptionRole).toString();
    QRegularExpressionMatch match = expression.match(detail);
    if (match.hasMatch()) {
        return true;
    }
    const QString title = idx.data(TraceCommonModelBase::TitleRole).toString();
    match = expression.match(title);
    if (match.hasMatch()) {
        return true;
    }

    const QString author = idx.data(TraceCommonModelBase::AuthorRole).toString();
    match = expression.match(author);
    return match.hasMatch();
}

} // namespace requirement
