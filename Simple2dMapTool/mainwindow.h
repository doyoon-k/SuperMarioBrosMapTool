#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QGraphicsItem>
#include "blockgeneratedialog.h"
#include "itemgeneratedialog.h"
#include "charactergeneratedialog.h"
#include "environmentgeneratedialog.h"
#include "block.h"
#include "constants.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void testFunc();
    void testFunc2();
    const static int one_block_length = 16;
    const static int half_block_length = one_block_length/2;
    QGraphicsScene* getGraphicsScene()const;
private slots:
    void on_set_Background_Button_clicked();
    void on_background_OnOff_Button_clicked();
    void on_addBlock_Button_clicked();

    void on_add_Item_pushButton_clicked();

    void on_add_Character_pushButton_clicked();

    void on_add_Environment_pushButton_clicked();

    void on_save_Map_Button_clicked();

private:
    Ui::MainWindow *ui;
    BlockGenerateDialog* p_blockGenerateDialog = nullptr;
    ItemGenerateDialog* p_ItemGenerateDialog = nullptr;
    CharacterGenerateDialog* p_characterGenerateDialog = nullptr;
    EnvironmentGenerateDialog* p_environmentGenerateDialog = nullptr;
    QGraphicsScene* p_mapScene = nullptr;
};

#endif // MAINWINDOW_H
