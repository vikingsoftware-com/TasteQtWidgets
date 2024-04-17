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

#include "reviewsmodelbase.h"

#include "reviewsmanager.h"

using namespace tracecommon;

namespace reviews {

ReviewsModelBase::ReviewsModelBase(ReviewsManager *manager, QObject *parent)
    : TraceCommonModelBase(parent)
    , m_manager(manager)
{
    if (m_manager != nullptr) {
        connect(m_manager, &ReviewsManager::listOfReviews, this, &ReviewsModelBase::addReviews);
        connect(m_manager, &ReviewsManager::startingFetchingReviews, this, &ReviewsModelBase::clearReviews);
    }
}

void ReviewsModelBase::clearReviews()
{
    setReviews({});
}

/*!
 * Replaces the set of existing reviews with the given one
 */
void ReviewsModelBase::setReviews(const QList<Review> &reviews)
{
    beginResetModel();
    m_reviews = reviews;
    endResetModel();
}

/*!
 * Appends the given \a reviews to the existing ones
 */
void ReviewsModelBase::addReviews(const QList<Review> &reviews)
{
    beginInsertRows(QModelIndex(), m_reviews.size(), m_reviews.size() + reviews.size() - 1);
    m_reviews.append(reviews);
    endInsertRows();
}

QVariant ReviewsModelBase::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case REVIEW_ID:
            return tr("ID");
        case TITLE:
            return tr("Title");
        case AUTHOR:
            return tr("Author");
        case CRITICALITY:
            return tr("Criticality");
        }
    }

    return {};
}

int ReviewsModelBase::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return m_reviews.size();
}

int ReviewsModelBase::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant ReviewsModelBase::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_reviews.size()) {
        return QVariant();
    }

    switch (role) {
    case TraceCommonModelBase::IssueLinkRole:
        return m_reviews[index.row()].m_link;
    case Qt::DisplayRole: {
        switch (index.column()) {
        case REVIEW_ID:
            return m_reviews[index.row()].m_id;
        case TITLE:
            return m_reviews[index.row()].m_longName;
        case AUTHOR:
            return m_reviews[index.row()].m_author;
        case CRITICALITY:
            return m_reviews[index.row()].criticality();
        }
        break;
    }
    case Qt::ToolTipRole:
        return m_reviews[index.row()].m_description;
    case TraceCommonModelBase::IssueIdRole:
        return m_reviews[index.row()].m_issueID;
    case TraceCommonModelBase::TagsRole:
        return m_reviews[index.row()].m_tags;
    case TraceCommonModelBase::DetailDescriptionRole:
        return m_reviews[index.row()].m_description;
    case TraceCommonModelBase::TitleRole:
        return m_reviews[index.row()].m_longName;
    case TraceCommonModelBase::AuthorRole:
        return m_reviews[index.row()].m_author;
    case ReviewIdRole:
        return m_reviews[index.row()].m_id;
    }

    return QVariant();
}

Review ReviewsModelBase::reviewFromIndex(const QModelIndex &idx) const
{
    int issueID = idx.data(ReviewsModelBase::IssueIdRole).toInt();
    for (const auto &review : m_reviews) {
        if (review.m_issueID == issueID) {
            return review;
        }
    }
    return Review();
}

bool ReviewsModelBase::reviewIDExists(const QString &revID) const
{
    return std::any_of(
            m_reviews.begin(), m_reviews.end(), [revID](const Review &review) { return review.m_id == revID; });
}

} // namespace requirement
