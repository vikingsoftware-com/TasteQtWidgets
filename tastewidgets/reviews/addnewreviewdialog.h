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

#include <QDialog>

namespace reviews {

namespace Ui {
class AddNewReviewDialog;
}

class ReviewsModelBase;

class AddNewReviewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewReviewDialog(reviews::ReviewsModelBase *model, QWidget *parent = nullptr);
    ~AddNewReviewDialog();
    QString title() const;
    QString description() const;
    QString reviewId() const;
    QString testMethod() const;

private:
    void updateOkButton();

    Ui::AddNewReviewDialog *ui = nullptr;
    ReviewsModelBase *m_model = nullptr;
};

} // namespace review
