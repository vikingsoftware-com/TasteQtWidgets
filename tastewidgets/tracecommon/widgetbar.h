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

#pragma once

#include <QScrollArea>

namespace tracecommon {

namespace Ui {
class WidgetBar;
}

/*!
 * \brief This is horizontally scrollable widget bar
 *
 *  This class is used to provide a display bar of any QWidget based
 *  item in a horizontal  disposition. The member `addWidget` is used to insert
 *  new items in the widget bar.
 *
 *  The inserted items are lined up horizontally. A scrollbar is automatically enabled
 *  when the number of items are bigger than viewport of the WidgetBar.
 *  The Vertical scrolling has been disabled.
 *
 *  The widget consist in a scrollarea with a central widget that acts as a placeholder for
 *  a horizontal layout that  contains the inserted items.
 *
 */
class WidgetBar : public QScrollArea
{
    Q_OBJECT

public:
    explicit WidgetBar(QWidget *parent = nullptr);
    ~WidgetBar();
    void addWidget(QWidget *w);

private:
    Ui::WidgetBar *ui;
};

}
