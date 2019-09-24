#include "environmentgeneratedialog.h"
#include "ui_environmentgeneratedialog.h"

EnvironmentGenerateDialog::EnvironmentGenerateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnvironmentGenerateDialog)
{
    ui->setupUi(this);
}

EnvironmentGenerateDialog::~EnvironmentGenerateDialog()
{
    delete ui;
}
