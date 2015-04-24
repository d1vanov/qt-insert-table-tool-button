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

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (!QIcon::hasThemeIcon("insert-table")) {
        ui->insertTableToolButton->setIcon(QIcon(":/table.png"));
    }
    QObject::connect(ui->insertTableToolButton, SIGNAL(createdTable(int,int,double,bool)),
                     this, SLOT(onInsertTable(int,int,double,bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onInsertTable(int rows, int columns, double width, bool relative)
{
    qDebug() << "Insert table: rows = " << rows << ", columns = " << columns
             << ", width = " << width << ", relative = " << (relative ? "true" : "false");

    QTextCursor cursor = ui->textEdit->textCursor();

    QTextTableFormat tableFormat;
    QVector<QTextLength> columnWidthConstraints;
    columnWidthConstraints.reserve(columns);
    double averageColumnWidth = width / columns;

    if (relative)
    {
        for(int i = 0; i < columns; ++i) {
            QTextLength textLength(QTextLength::PercentageLength, averageColumnWidth);
            columnWidthConstraints.push_back(textLength);
        }
    }
    else
    {
        for(int i = 0; i < columns; ++i) {
            QTextLength textLength(QTextLength::FixedLength, averageColumnWidth);
            columnWidthConstraints.push_back(textLength);
        }
    }

    tableFormat.setColumnWidthConstraints(columnWidthConstraints);

    Q_UNUSED(cursor.insertTable(rows, columns, tableFormat));
}
