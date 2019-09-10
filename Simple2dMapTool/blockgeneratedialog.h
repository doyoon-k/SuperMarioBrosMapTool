#ifndef BLOCKGENERATEDIALOG_H
#define BLOCKGENERATEDIALOG_H

#include <QDialog>

namespace Ui {
class BlockGenerateDialog;
}

class BlockGenerateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BlockGenerateDialog(QWidget *parent = nullptr);
    ~BlockGenerateDialog();

private slots:
    void on_generate_PushButton_clicked();
private:
    Ui::BlockGenerateDialog *ui;
};

#endif // BLOCKGENERATEDIALOG_H
