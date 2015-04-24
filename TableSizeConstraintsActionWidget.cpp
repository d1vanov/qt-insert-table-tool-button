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

#include "TableSizeConstraintsActionWidget.h"
#include <QHBoxLayout>
#include <QDoubleSpinBox>
#include <QComboBox>

TableSizeConstraintsActionWidget::TableSizeConstraintsActionWidget(QWidget * parent) :
    QWidgetAction(parent),
    m_currentWidth(400.0),
    m_currentWidthTypeIsRelative(false)
{
    QWidget * layoutContainer = new QWidget(parent);

    QHBoxLayout * layout = new QHBoxLayout(layoutContainer);

    QDoubleSpinBox * widthSpinBox = new QDoubleSpinBox(layoutContainer);
    widthSpinBox->setMinimum(1.0);
    widthSpinBox->setMaximum(2000.0);
    widthSpinBox->setDecimals(2);
    widthSpinBox->setValue(m_currentWidth);

    QComboBox * widthTypeComboBox = new QComboBox(layoutContainer);
    widthTypeComboBox->addItem("pixels");
    widthTypeComboBox->addItem("%");
    widthTypeComboBox->setCurrentIndex(m_currentWidthTypeIsRelative ? 1 : 0);

    layout->addWidget(widthSpinBox);
    layout->addWidget(widthTypeComboBox);

    layoutContainer->setLayout(layout);
    setDefaultWidget(layoutContainer);

    QObject::connect(widthSpinBox, SIGNAL(valueChanged(double)), this, SLOT(onWidthChange(double)));
    QObject::connect(widthTypeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(onWidthTypeChange(QString)));
}

double TableSizeConstraintsActionWidget::width() const
{
    return m_currentWidth;
}

bool TableSizeConstraintsActionWidget::isRelative() const
{
    return m_currentWidthTypeIsRelative;
}

void TableSizeConstraintsActionWidget::onWidthChange(double width)
{
    m_currentWidth = width;
    emit chosenTableWidthConstraints(m_currentWidth, m_currentWidthTypeIsRelative);
}

void TableSizeConstraintsActionWidget::onWidthTypeChange(QString widthType)
{
    if (widthType == "%") {
        m_currentWidthTypeIsRelative = true;
    }
    else {
        m_currentWidthTypeIsRelative = false;
    }

    emit chosenTableWidthConstraints(m_currentWidth, m_currentWidthTypeIsRelative);
}
