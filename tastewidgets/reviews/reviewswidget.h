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

#include "issuetextproxymodel.h"
#include "tagfilterproxymodel.h"

#include <QList>
#include <QPointer>
#include <QToolButton>
#include <QWidget>

class QHeaderView;
namespace tracecommon {
class WidgetBar;
}

namespace reviews {

class Review;
class ReviewsModelBase;
class ReviewsManager;

namespace Ui {
class ReviewsWidget;
}

/*!
 * Widget for listing all reviews
 */
class ReviewsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReviewsWidget(QWidget *parent = nullptr);
    ~ReviewsWidget();

    /*!
     * Hides the create/remove review button
     * \param show when set to false, the buttons are hidden
     */
    void showButtons(bool show);

    void setManager(ReviewsManager *manager);
    void setModel(ReviewsModelBase *model);

    /*!
     * Returns the URL to fetch the reviews from
     */
    QUrl url() const;
    /*!
     * Sets the url to fetch the requirements from
     */
    virtual void setUrl(const QUrl &url);
    /*!
     * Returns the token to authenticate for fetching the reviews
     */
    QString token() const;
    /*!
     * Sets the Token to authenticate for fetching the requirements
     */
    virtual void setToken(const QString &token);

    /*!
     * A pointer to the table header, so the column geometry can be saved/restored
     */
    QHeaderView *horizontalTableHeader() const;

public Q_SLOTS:
    void setLoginData();
    void updateServerStatus();
    void updateProjectReady();

Q_SIGNALS:
    void reviewsUrlChanged(QUrl reviewsUrl);
    void reviewsCredentialsChanged(QUrl url, QString token);
    void reviewAdded(const Review &review);
    void reviewRemoved(const QString &reviewId);

protected Q_SLOTS:
    void onChangeOfCredentials();
    void requestReviews();
    void openIssueLink(const QModelIndex &index);
    void showNewReviewDialog() const;
    void removeReview();
    void fillTagBar(const QStringList &tags);

protected:
    bool tagButtonExists(const QString &tag) const;

    Ui::ReviewsWidget *ui;
    QList<QToolButton *> m_tagButtons;
    tracecommon::WidgetBar *m_widgetBar;
    QPointer<ReviewsManager> m_reviewsManager;
    QPointer<ReviewsModelBase> m_model;
    tracecommon::IssueTextProxyModel m_textFilterModel;
    tracecommon::TagFilterProxyModel m_tagFilterModel;
};

} // namespace reviews
