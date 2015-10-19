#include "TableSettingsDialog.h"
#include "ui_TableSettingsDialog.h"

TableSettingsDialog::TableSettingsDialog(QWidget * parent) :
    QDialog(parent),
    ui(new Ui::TableSettingsDialog)
{
    ui->setupUi(this);

    ui->warningLine->clear();
    ui->warningLine->setHidden(true);

    QComboBox * pTableWidthModeComboBox = ui->tableWidthModeComboBox;
    pTableWidthModeComboBox->addItem(QObject::tr("pixels"));
    pTableWidthModeComboBox->addItem(QObject::tr("% of page width"));
    pTableWidthModeComboBox->setCurrentIndex(1);

    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(onOkButtonPressed()));
    QObject::connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(onCancelButtonPressed()));
}

TableSettingsDialog::~TableSettingsDialog()
{
    delete ui;
}

int TableSettingsDialog::numRows() const
{
    return m_numRows;
}

int TableSettingsDialog::numColumns() const
{
    return m_numColumns;
}

double TableSettingsDialog::tableWidth() const
{
    return m_tableWidth;
}

bool TableSettingsDialog::relativeWidth() const
{
    return m_relativeWidth;
}

void TableSettingsDialog::onOkButtonPressed()
{
    QString error;
    bool res = verifySettings(error);
    if (!res) {
        ui->warningLine->setText(QString("<font color=red>") + error + QString("</font>"));
        ui->warningLine->setHidden(false);
        return;
    }

    if (!ui->warningLine->isHidden()) {
        ui->warningLine->clear();
        ui->warningLine->setHidden(true);
    }

    m_numRows = static_cast<int>(ui->numRowsSpinBox->value());
    m_numColumns = static_cast<int>(ui->numColumnsSpinBox->value());
    m_tableWidth = ui->tableWidthDoubleSpinBox->value();
    m_relativeWidth = checkRelativeWidth();

    accept();
}

void TableSettingsDialog::onCancelButtonPressed()
{
    reject();
}

bool TableSettingsDialog::verifySettings(QString & error) const
{
    int numRows = ui->numRowsSpinBox->value();
    if ((numRows < 1) || (numRows > 30)) {
        error = QObject::tr("Number of rows should be between 1 and 30");
        return false;
    }

    int numColumns = ui->numColumnsSpinBox->value();
    if ((numColumns < 1) || (numColumns > 30)) {
        error = QObject::tr("Number of columns should be between 1 and 30");
        return false;
    }

    double tableWidth = ui->tableWidthDoubleSpinBox->value();
    int intTableWidth = static_cast<int>(tableWidth);

    bool tableRelativeWidth = checkRelativeWidth();
    if (tableRelativeWidth)
    {
        if ((intTableWidth < 1) || (intTableWidth > 100)) {
            error = QObject::tr("Relative table width should be between 1 and 100");
            return false;
        }
    }
    else
    {
        if ((intTableWidth < 1) || (intTableWidth > 999999999)) {
            error = QObject::tr("Bad table width in pixels number");
            return false;
        }
    }

    return true;
}

bool TableSettingsDialog::checkRelativeWidth() const
{
    int comboBoxValueIndex = ui->tableWidthModeComboBox->currentIndex();
    return (comboBoxValueIndex == 1);
}
