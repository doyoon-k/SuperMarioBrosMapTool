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
    p_bgImgObject(new QImage)
{
    ui->setupUi(this);
    p_mapScene = new QGraphicsScene(this);

    //must set scene rect boundary...
    ui->graphicsView->setScene(p_mapScene);
    ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);

    vBlocks.reserve(200);
    vTmpItems.reserve(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QGraphicsScene *MainWindow::getGraphicsScene() const
{
    return p_mapScene;
}

QVector<QGraphicsItem*> &MainWindow::getvTmpItems()
{
    return vTmpItems;
}

QVector<Block *> &MainWindow::getvBlocks()
{
    return vBlocks;
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

    p_bgImgObject->load(imgPath);
    QPixmap imgPixmap;
    imgPixmap = QPixmap::fromImage(*p_bgImgObject);

    //if the image already exists,
    if(p_bgImage != nullptr)
    {
        p_mapScene->removeItem(p_bgImage);
    }
    //add loaded background pixmap and set QGraphicPixmapItem.
    p_bgImage = p_mapScene->addPixmap(imgPixmap);
    p_bgImage->setOpacity(0.5);
    p_mapScene->setSceneRect(0,0,imgPixmap.width(),imgPixmap.height());
}

void MainWindow::on_background_OnOff_Button_clicked()
{
    if(p_bgImage == nullptr)
        return;

    if(p_bgImage->isVisible() == true)
    {
        p_bgImage->hide();
    }
    else
    {
        p_bgImage->show();
    }
}

void MainWindow::MainWindow::wheelEvent(QWheelEvent *event)
{
    if(p_bgImage == nullptr)
        return;
    qreal width = p_bgImage->boundingRect().width();
    qreal height = p_bgImage->boundingRect().height();

    p_bgImage->setScale(p_bgImage->scale()+event->delta()/100.0);
    qreal bgImgScale = p_bgImage->scale();

    p_mapScene->setSceneRect(0,0,width*bgImgScale,height*bgImgScale);
}



void MainWindow::on_addBlock_Button_clicked()
{
    if(p_bgImage == nullptr)
    {
        QMessageBox::information(this,"Background is not set.","You need to set the background first!");
        return;
    }
    p_blockGenerateDialog = new BlockGenerateDialog(this);
    p_blockGenerateDialog->setWindowTitle("Block Generator");
    p_blockGenerateDialog->setModal(true);
    p_blockGenerateDialog->show();
}

void MainWindow::MainWindow::mouseMoveEvent(QMouseEvent *event)
{

}
