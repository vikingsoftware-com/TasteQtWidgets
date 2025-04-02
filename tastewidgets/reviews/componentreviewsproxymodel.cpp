/*
   Copyright (C) 2024 European Space Agency - <maxime.perrotin@esa.int>
                                                                                \
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.
                                                                                \
This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.
                                                                                \
You should have received a copy of the GNU Library General Public License
along with this program. If not, see <https://www.gnu.org/licenses/lgpl-2.1.html>.
*/

#include "componentreviewsproxymodel.h"

#include "reviewsmodelbase.h"

namespace reviews {

ComponentReviewsProxyModel::ComponentReviewsProxyModel(reviews::ReviewsManager *manager, QObject *parent)
    : reviews::ReviewsModelBase { manager, parent }
{
}

void ComponentReviewsProxyModel::setAcceptableIds(const QStringList &ids)
{
    m_ids = ids;
    setReviews(m_originalReviews);
}

void ComponentReviewsProxyModel::setReviews(const QList<reviews::Review> &reviews)
{
    beginResetModel();
    m_originalReviews = reviews;
    m_reviews.clear();
    if (m_ids.isEmpty()) {
        m_reviews = m_originalReviews;
    } else {
        for (const reviews::Review &review : m_originalReviews) {
            if (m_ids.contains(review.m_id)) {
                m_reviews.append(review);
            }
        }
    }
    endResetModel();
}

void ComponentReviewsProxyModel::addReviews(const QList<reviews::Review> &reviews)
{
    beginResetModel();
    m_originalReviews.append(reviews);
    if (m_ids.isEmpty()) {
        m_reviews = m_originalReviews;
    } else {
        for (const reviews::Review &review : reviews) {
            if (m_ids.contains(review.m_id) && !m_reviews.contains(review)) {
                m_reviews.append(review);
            }
        }
    }
    endResetModel();
}

bool ComponentReviewsProxyModel::reviewIDExists(const QString &revID) const
{
    return std::any_of(m_originalReviews.begin(), m_originalReviews.end(),
            [revID](const reviews::Review &review) { return review.m_id == revID; });
}

} // namespace reviews
