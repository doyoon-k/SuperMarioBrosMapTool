#ifndef ENVIRONMENTGENERATEDIALOG_H
#define ENVIRONMENTGENERATEDIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include "mapscreen.h"

namespace Ui {
class EnvironmentGenerateDialog;
}

class EnvironmentGenerateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EnvironmentGenerateDialog(QWidget *parent = nullptr,MapScreen* pMapScreen = nullptr,QGraphicsScene* pMapScene = nullptr);
    ~EnvironmentGenerateDialog();

private slots:
    void on_generate_pushButton_clicked();

private:
    Ui::EnvironmentGenerateDialog *ui;
    MapScreen* p_mapScreen;
    QGraphicsScene* p_mapScene;
    QString environmentType;
};

#endif // ENVIRONMENTGENERATEDIALOG_H
