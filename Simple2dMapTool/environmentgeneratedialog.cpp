#include "environmentgeneratedialog.h"
#include "ui_environmentgeneratedialog.h"
#include "mainwindow.h"

EnvironmentGenerateDialog::EnvironmentGenerateDialog(QWidget *parent,MapScreen* pMapScreen,QGraphicsScene* pMapScene) :
    QDialog(parent),
    ui(new Ui::EnvironmentGenerateDialog), 
    p_mapScreen(pMapScreen),
    p_mapScene(pMapScene)
{
    ui->setupUi(this);
}

EnvironmentGenerateDialog::~EnvironmentGenerateDialog()
{
    delete ui;
}

void EnvironmentGenerateDialog::on_generate_pushButton_clicked()
{
    environmentType = ui->environment_List_listWidget->currentItem()->text();
    QVector<QGraphicsItem*>& vTmpItems = p_mapScreen->getvTmpItems();
    qreal scale = p_mapScreen->getAccumulatedScale();
    QPen pen(Qt::black);
    int one_block_length = MainWindow::one_block_length;

    QGraphicsItem* item;
    if(environmentType == "Pirhana Plant Pipe")
    {
        item = p_mapScene->addRect(0,0,one_block_length*2.0,one_block_length*4.0);
    }
    else if(environmentType == "Pipe Head(Horizontal)")
    {
        item = p_mapScene->addRect(0,0,one_block_length*2.0,one_block_length);
    }
    else if(environmentType == "Pipe Head(Vertical)")
    {
        item = p_mapScene->addRect(0,0,one_block_length,one_block_length*2.0);
    }
    else if(environmentType == "Pipe Body(Horizontal)")
    {
        item = p_mapScene->addRect(0,0,one_block_length*2.0,one_block_length);
    }
    else if(environmentType == "Pipe Body(Vertical)")
    {
        item = p_mapScene->addRect(0,0,one_block_length,one_block_length*2.0);
    }
    else if(environmentType == "Flag")
    {
        item = p_mapScene->addRect(0,0,one_block_length*3.0,one_block_length*10.0);
    }
    else if(environmentType == "Cloud1")
    {
        item = p_mapScene->addRect(0,0,one_block_length*2.0,one_block_length*2.0);
    }
    else if(environmentType == "Cloud2")
    {
        item = p_mapScene->addRect(0,0,one_block_length*3.0,one_block_length*2.0);
    }
    else if(environmentType == "Cloud3")
    {
        item = p_mapScene->addRect(0,0,one_block_length*4.0,one_block_length*2.0);
    }
    else if(environmentType == "Bush1")
    {
        item = p_mapScene->addRect(0,0,one_block_length*2.0,one_block_length);
    }
    else if(environmentType == "Bush2")
    {
        item = p_mapScene->addRect(0,0,one_block_length*3.0,one_block_length);
    }
    else if(environmentType == "Bush3")
    {
        item = p_mapScene->addRect(0,0,one_block_length*4.0,one_block_length);
    }
    else if(environmentType == "Castle")
    {
        item = p_mapScene->addRect(0,0,one_block_length*5.0,one_block_length*5.0);
    }
    else if(environmentType == "Lift")
    {
        item = p_mapScene->addRect(0,0,one_block_length*3,one_block_length);
    }

    item->setScale(scale);
    item->setPos(0,0);
    vTmpItems.push_back(item);

    p_mapScreen->setTmpItemType(environments,environmentType);
    this->close();
}
