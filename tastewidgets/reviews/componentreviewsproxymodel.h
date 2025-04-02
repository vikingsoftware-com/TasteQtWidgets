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

#pragma once

#include "reviewsmodelbase.h"

namespace reviews {

/*!
 * Model to show the reviews of one single component.
 * The reviews of the component are set by /see setAcceptableIds
 */
class ComponentReviewsProxyModel : public reviews::ReviewsModelBase
{
public:
    explicit ComponentReviewsProxyModel(reviews::ReviewsManager *manager, QObject *parent = nullptr);

    /*!
     * Limits the reviews to only those reviews that have on of the given ids
     */
    void setAcceptableIds(const QStringList &ids);
    /*!
     * \brief setReviews If reviews are empty all reviews are set, otherwise original reviews are filtered.
     * \param reviews
     */
    void setReviews(const QList<reviews::Review> &reviews) override;
    void addReviews(const QList<reviews::Review> &reviews) override;

    bool reviewIDExists(const QString &revID) const override;

protected:
    QStringList m_ids;
    QList<reviews::Review> m_originalReviews;
};

} // namespace reviews
