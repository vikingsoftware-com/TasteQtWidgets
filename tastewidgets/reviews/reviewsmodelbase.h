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
along with this program. If not, see
<https://www.gnu.org/licenses/lgpl-2.1.html>.
*/

#pragma once

#include "review.h"
#include "tracecommonmodelbase.h"

#include <QList>
#include <QPointer>

namespace reviews {

class ReviewsManager;

/*!
 * \brief Base model to hold reviews for a Qt view
 */
class ReviewsModelBase : public tracecommon::TraceCommonModelBase
{
    Q_OBJECT

public:
    enum RoleNames
    {
        ReviewIdRole = tracecommon::TraceCommonModelBase::UserRole + 1,
    };

    enum HEADER_SECTIONS
    {
        REVIEW_ID = 0,
        TITLE,
        AUTHOR,
        CRITICALITY,
    };

    explicit ReviewsModelBase(ReviewsManager *manager, QObject *parent = nullptr);

    /*!
     * \brief Empties the list of reviews of the model
     */
    virtual void clearReviews();

    /*!
     * \brief Sets the list of reviews in the model
     * \param reviews All reviews in that model
     */
    virtual void setReviews(const QList<Review> &reviews);
    /*!
     * \brief Append reviews to the existing reviews in the model
     * \param reviews Reviews to add to the model
     */
    virtual void addReviews(const QList<Review> &reviews);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Review reviewFromIndex(const QModelIndex &idx) const;

    /*!
     * \brief Check if a review ID already exists in the model
     * \param revID The ID of the review
     * \return True if the review exists in the model
     */
    virtual bool reviewIDExists(const QString &revID) const;

protected:
    QList<Review> m_reviews;
    QPointer<ReviewsManager> m_manager;
};

} // namespace requirement
