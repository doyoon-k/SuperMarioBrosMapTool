#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    p_mapScene(new QGraphicsScene)
{
    ui->setupUi(this);
    ui->mapScreen->set_p_mw(this);
    //must set scene rect boundary...
    ui->mapScreen->setScene(p_mapScene);
    ui->mapScreen->set_p_MapScene(p_mapScene);
    ui->mapScreen->setAlignment(Qt::AlignTop|Qt::AlignLeft);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QGraphicsScene *MainWindow::getGraphicsScene() const
{
    return p_mapScene;
}

void MainWindow::on_set_Background_Button_clicked()
{
    //open file explorer to select the image file.
    QString imgPath = QFileDialog::getOpenFileName(this,"Choose an image file to open.","C://","JPEG(*.jpg *.jpeg);;PNG (*.png)");

    if(imgPath == nullptr)
    {
        qDebug()<<"no file selected!";
        return;
    }

    QImage*& imgObj = ui->mapScreen->getBackgroundImageObject();
    imgObj->load(imgPath);

    QPixmap imgPixmap;
    imgPixmap = QPixmap::fromImage(*imgObj);

    QGraphicsPixmapItem*& bgImgItem = ui->mapScreen->getBackgroundPixmapItem();

    //if the image already exists,
    if(bgImgItem != nullptr)
    {
        p_mapScene->removeItem(bgImgItem);
    }
    //add loaded background pixmap and set QGraphicPixmapItem.
    bgImgItem = p_mapScene->addPixmap(imgPixmap);
    bgImgItem->setOpacity(0.4);
    p_mapScene->setSceneRect(0,0,imgPixmap.width(),imgPixmap.height());
}

void MainWindow::on_background_OnOff_Button_clicked()
{
    QGraphicsItem* bgImgItem = ui->mapScreen->getBackgroundPixmapItem();
    if(bgImgItem == nullptr)
        return;

    if(bgImgItem->isVisible() == true)
    {
        bgImgItem->hide();
    }
    else
    {
        bgImgItem->show();
    }
    qDebug()<<"!";
}

void MainWindow::on_addBlock_Button_clicked()
{
    QGraphicsPixmapItem* p_bgImage = ui->mapScreen->getBackgroundPixmapItem();
    if(p_bgImage == nullptr)
    {
        QMessageBox::information(this,"Background is not set.","You need to set the background first!");
        return;
    }
    p_blockGenerateDialog = new BlockGenerateDialog(this,ui->mapScreen,p_mapScene);
    p_blockGenerateDialog->setWindowTitle("Block Generator");
    p_blockGenerateDialog->setModal(true);
    p_blockGenerateDialog->show();
}

void MainWindow::on_add_Item_pushButton_clicked()
{
    QGraphicsPixmapItem* p_bgImage = ui->mapScreen->getBackgroundPixmapItem();
    if(p_bgImage == nullptr)
    {
        QMessageBox::information(this,"Background is not set.","You need to set the background first!");
        return;
    }
    p_ItemGenerateDialog = new ItemGenerateDialog(this,ui->mapScreen,p_mapScene);
    p_ItemGenerateDialog->setWindowTitle("Item Generator");
    p_ItemGenerateDialog->setModal(true);
    p_ItemGenerateDialog->show();
}

void MainWindow::on_add_Character_pushButton_clicked()
{
    QGraphicsPixmapItem* p_bgImage = ui->mapScreen->getBackgroundPixmapItem();
    if(p_bgImage == nullptr)
    {
        QMessageBox::information(this,"Background is not set.","You need to set the background first!");
        return;
    }
    p_characterGenerateDialog = new CharacterGenerateDialog(this,ui->mapScreen,p_mapScene);
    p_characterGenerateDialog->setWindowTitle("Character Generator");
    p_characterGenerateDialog->setModal(true);
    p_characterGenerateDialog->show();

}
