#include "charactergeneratedialog.h"
#include "ui_charactergeneratedialog.h"
#include "mainwindow.h"

CharacterGenerateDialog::CharacterGenerateDialog(QWidget *parent,MapScreen* pMapScreen,QGraphicsScene* pMapScene) :
    QDialog(parent),
    p_mapScene(pMapScene),
    p_mapScreen(pMapScreen),
    ui(new Ui::CharacterGenerateDialog)
{
    ui->setupUi(this);
}

CharacterGenerateDialog::~CharacterGenerateDialog()
{
    delete ui;
}

void CharacterGenerateDialog::on_character_Generate_pushButton_clicked()
{
    characterType = ui->character_Type_listWidget->currentItem()->text();
    QVector<QGraphicsItem*>& vTmpItems = p_mapScreen->getvTmpItems();
    qreal scale = p_mapScreen->getAccumulatedScale();
    QPen pen(Qt::black);
    int one_block_length = MainWindow::one_block_length;

    QGraphicsItem* item;
    if(characterType == "Mario")
    {
        item = p_mapScene->addRect(0,0,one_block_length,one_block_length);
    }
    else if(characterType == "Goomba")
    {
        item = p_mapScene->addRect(0,0,one_block_length,one_block_length);
    }
    else if(characterType == "Green Koopa Troopa")
    {
        item = p_mapScene->addRect(0,0,one_block_length,one_block_length*2);
    }
    else if(characterType == "Red Koopa Troopa")
    {
        item = p_mapScene->addRect(0,0,one_block_length,one_block_length*2);
    }

    item->setScale(scale);
    item->setPos(0,0);
    vTmpItems.push_back(item);

    p_mapScreen->setTmpItemType(characters,characterType);
    this->close();
}
