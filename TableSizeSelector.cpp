/*
* The MIT License (MIT)
*
* Copyright (c) 2015 Dmitry Ivanov
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#include "TableSizeSelector.h"
#include <QPainter>
#include <QMouseEvent>
#include <QToolTip>

#define MAX_ROWS (10)
#define MAX_COLUMNS (20)

TableSizeSelector::TableSizeSelector(QWidget * parent) :
    QWidget(parent),
    m_currentRow(-1),
    m_currentColumn(-1),
    m_rowHeight(0),
    m_columnWidth(0),
    m_rect()
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setMouseTracking(true);

    QFontMetrics fontMetrics(font());
    m_rowHeight = fontMetrics.height() + 2;
    m_columnWidth = fontMetrics.width("  ") + 3;

    m_rect.setHeight(m_rowHeight * MAX_ROWS);
    m_rect.setWidth(m_columnWidth * MAX_COLUMNS);
}

void TableSizeSelector::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    // Fill background
    painter.fillRect(m_rect, palette().brush(QPalette::Base));

    // Fill current selection area (if any)
    if ((m_currentRow >= 0) && (m_currentColumn >= 0))
    {
        QRectF selectionRect;
        selectionRect.setHeight(m_currentRow * m_rowHeight);
        selectionRect.setWidth(m_currentColumn * m_columnWidth);
        painter.fillRect(selectionRect, palette().brush(QPalette::Highlight));
    }

    QPen pen = painter.pen();
    pen.setWidthF(0.7);
    painter.setPen(pen);

    // Drawing rows grid
    for(int i = 0; i <= MAX_ROWS; ++i) {
        double verticalPos = i * m_rowHeight;
        painter.drawLine(QPointF(0.0, verticalPos), QPointF(m_rect.width(), verticalPos));
    }

    // Drawing columns grid
    for(int i = 0; i <= MAX_COLUMNS; ++i) {
        double horizontalPos = i * m_columnWidth;
        painter.drawLine(QPointF(horizontalPos, 0.0), QPointF(horizontalPos, m_rect.height()));
    }
}

void TableSizeSelector::mouseMoveEvent(QMouseEvent * event)
{
    m_currentRow = static_cast<int>(event->y() / m_rowHeight) + 1;
    m_currentColumn = static_cast<int>(event->x() / m_columnWidth) + 1;
    QToolTip::showText(event->globalPos(), QString::number(m_currentRow) + "x" + QString::number(m_currentColumn));
    repaint();
}

void TableSizeSelector::mouseReleaseEvent(QMouseEvent * event)
{
    if (m_rect.contains(event->pos())) {
        emit tableSizeSelected(m_currentRow, m_currentColumn);
    }

    QWidget::mouseReleaseEvent(event);
}

void TableSizeSelector::enterEvent(QEvent *event)
{
    QWidget::enterEvent(event);
    repaint();
}

void TableSizeSelector::leaveEvent(QEvent * event)
{
    QWidget::leaveEvent(event);

    m_currentRow = -1;
    m_currentColumn = -1;
    repaint();
}

QSize TableSizeSelector::sizeHint() const
{
    QSize size;
    size.setHeight(static_cast<int>(m_rect.height()) + 1);
    size.setWidth(static_cast<int>(m_rect.width()) + 1);
    return size;
}
