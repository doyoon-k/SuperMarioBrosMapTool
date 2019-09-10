#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QGraphicsItem>
#include "blockgeneratedialog.h"
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

    const static int one_block_length = 16;
    QGraphicsScene* getGraphicsScene()const;
    QVector<Block*>& getvBlocks();
    QVector<QGraphicsItem*>& getvTmpItems();
private slots:
    void on_set_Background_Button_clicked();
    void on_background_OnOff_Button_clicked();
    void on_addBlock_Button_clicked();

    void MainWindow::wheelEvent(QWheelEvent *event);
    void MainWindow::mouseMoveEvent(QMouseEvent *event);
private:
    Ui::MainWindow *ui;
    BlockGenerateDialog* p_blockGenerateDialog = nullptr;
    QGraphicsScene* p_mapScene = nullptr;
    QGraphicsPixmapItem* p_bgImage = nullptr;
    QImage* p_bgImgObject;
    QVector<Block*> vBlocks;
    QVector<QGraphicsItem*> vTmpItems;
};

#endif // MAINWINDOW_H
