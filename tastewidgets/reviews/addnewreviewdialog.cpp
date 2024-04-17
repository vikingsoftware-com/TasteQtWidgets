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

#include "addnewreviewdialog.h"

#include "reviewsmodelbase.h"
#include "ui_addnewreviewdialog.h"

#include <QPushButton>

namespace reviews {

AddNewReviewDialog::AddNewReviewDialog(ReviewsModelBase *model, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddNewReviewDialog)
    , m_model(model)
{
    ui->setupUi(this);

    ui->gridLayout->setVerticalSpacing(10);
    auto sizePolicy = ui->notUniqueIDLabel->sizePolicy();
    sizePolicy.setRetainSizeWhenHidden(true);
    ui->notUniqueIDLabel->setSizePolicy(sizePolicy);
    ui->notUniqueIDLabel->setVisible(false);
    connect(ui->titleLineEdit, &QLineEdit::textChanged, this, &AddNewReviewDialog::updateOkButton);
    connect(ui->idLineEdit, &QLineEdit::textChanged, this, &AddNewReviewDialog::updateOkButton);
    updateOkButton();
}

AddNewReviewDialog::~AddNewReviewDialog()
{
    delete ui;
}

/*!
 * Returns the title of the review.
 * A title is mandatory to add a review
 */
QString AddNewReviewDialog::title() const
{
    return ui->titleLineEdit->text();
}

/*!
 * Contains the main content of the review
 */
QString AddNewReviewDialog::description() const
{
    return ui->descriptionTextEdit->toPlainText();
}

/*!
 * Returns the ID of the review.
 * An ID is mandatory to add a review
 */
QString AddNewReviewDialog::reviewId() const
{
    return ui->idLineEdit->text();
}

/*!
 * Reviews are classified by different methods. There is always only one test method.
 */
QString AddNewReviewDialog::testMethod() const
{
    return ui->methodBox->currentText();
}

void AddNewReviewDialog::updateOkButton()
{
    QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    if (!okButton) {
        return;
    }

    bool reviewIdExists = m_model->reviewIDExists(ui->idLineEdit->text());
    ui->notUniqueIDLabel->setVisible(reviewIdExists);
    okButton->setDisabled(ui->titleLineEdit->text().isEmpty() || ui->idLineEdit->text().isEmpty() || reviewIdExists);
}

} // namespace review
