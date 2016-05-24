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

#ifndef TABLE_SIZE_SELECTOR_H
#define TABLE_SIZE_SELECTOR_H

#include <QWidget>

class TableSizeSelector : public QWidget
{
    Q_OBJECT
public:
    explicit TableSizeSelector(QWidget * parent = 0);

Q_SIGNALS:
    void tableSizeSelected(int rows, int columns);

private:
    virtual void paintEvent(QPaintEvent * event);

    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);

    virtual void enterEvent(QEvent * event);
    virtual void leaveEvent(QEvent * event);

    virtual QSize sizeHint() const;

private:
    int         m_currentRow;
    int         m_currentColumn;
    double      m_rowHeight;
    double      m_columnWidth;
    QRectF      m_rect;
};

#endif // TABLE_SIZE_SELECTOR_H
