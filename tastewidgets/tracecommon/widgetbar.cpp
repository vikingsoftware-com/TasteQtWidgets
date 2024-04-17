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

#include "widgetbar.h"

#include "ui_widgetbar.h"

#include <QHBoxLayout>
#include <QScrollBar>

namespace tracecommon {

WidgetBar::WidgetBar(QWidget *parent)
    : QScrollArea(parent)
    , ui(new Ui::WidgetBar)
{
    ui->setupUi(this);
    auto layout = new QHBoxLayout();
    setWidget(new QWidget);
    widget()->setLayout(layout);
    widget()->setContentsMargins(2, 0, 2, 0);
    widget()->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    auto widgetContentMargins = layout->contentsMargins();
    widget()->setContentsMargins(widgetContentMargins.left(), 0, widgetContentMargins.right(), 0);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    auto layoutContentMargins = layout->contentsMargins();
    auto contentMargins = contentsMargins();
    setContentsMargins(contentMargins.left(), 1, contentMargins.right(), 1);
    layout->setContentsMargins(layoutContentMargins.left(), 0, layoutContentMargins.right(), 0);
    layout->setSizeConstraint(QLayout::SetFixedSize);
}

WidgetBar::~WidgetBar()
{
    delete ui;
}

/*!
 * \brief WidgetBar::addWidget adds widget `w` to the WidgetBar's widget layout
 * \param w is any QWidget based widget.
 */
void WidgetBar::addWidget(QWidget *w)
{
    widget()->layout()->addWidget(w);
}

}
