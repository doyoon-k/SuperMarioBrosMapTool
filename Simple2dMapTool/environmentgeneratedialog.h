#ifndef ENVIRONMENTGENERATEDIALOG_H
#define ENVIRONMENTGENERATEDIALOG_H

#include <QDialog>

namespace Ui {
class EnvironmentGenerateDialog;
}

class EnvironmentGenerateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EnvironmentGenerateDialog(QWidget *parent = nullptr);
    ~EnvironmentGenerateDialog();

private:
    Ui::EnvironmentGenerateDialog *ui;
};

#endif // ENVIRONMENTGENERATEDIALOG_H
