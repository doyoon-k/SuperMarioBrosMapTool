#ifndef ITEMGENERATEDIALOG_H
#define ITEMGENERATEDIALOG_H

#include <QDialog>
#include "mapscreen.h"
#include <QGraphicsScene>

namespace Ui {
class ItemGenerateDialog;
}

class ItemGenerateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ItemGenerateDialog(QWidget *parent = nullptr,MapScreen* pMapScreen = nullptr,QGraphicsScene* pMapScene = nullptr);
    ~ItemGenerateDialog();

private slots:
    void on_item_generate_pushButton_clicked();

private:
    Ui::ItemGenerateDialog *ui;
    MapScreen* p_mapScreen;
    QGraphicsScene* p_mapScene;
    QString itemType;
};

#endif // ITEMGENERATEDIALOG_H
