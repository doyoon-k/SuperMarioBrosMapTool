#pragma once
#ifndef BLOCKGENERATEDIALOG_H
#define BLOCKGENERATEDIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include "mapscreen.h"

namespace Ui {
class BlockGenerateDialog;
}

class BlockGenerateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BlockGenerateDialog(QWidget *parent = nullptr,MapScreen* pMapScreen = nullptr,QGraphicsScene* pMapScene = nullptr);
    ~BlockGenerateDialog();

private slots:
    void on_generate_PushButton_clicked();
private:
    Ui::BlockGenerateDialog *ui;
    MapScreen* p_mapScreen;
    QGraphicsScene* p_mapScene;
    QString blockType;
};

#endif // BLOCKGENERATEDIALOG_H
