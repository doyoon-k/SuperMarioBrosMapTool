#include "itemgeneratedialog.h"
#include "ui_itemgeneratedialog.h"
#include "mainwindow.h"
#include "constants.h"

ItemGenerateDialog::ItemGenerateDialog(QWidget *parent, MapScreen *pMapScreen, QGraphicsScene *pMapScene)
    :QDialog(parent),
      ui(new Ui::ItemGenerateDialog),
      p_mapScreen(pMapScreen),
      p_mapScene(pMapScene)
{
    ui->setupUi(this);
}

ItemGenerateDialog::~ItemGenerateDialog()
{
    delete ui;
}

void ItemGenerateDialog::on_item_generate_pushButton_clicked()
{
    itemType = ui->item_Type_listWidget->currentItem()->text();
    QVector<QGraphicsItem*>& vTmpItems = p_mapScreen->getvTmpItems();
    qreal scale = p_mapScreen->getAccumulatedScale();
    QPen blockPen(Qt::black);
    int one_block_length = MainWindow::one_block_length;

    QGraphicsItem* item = p_mapScene->addRect(0,0,one_block_length,one_block_length);
    item->setScale(scale);
    item->setPos(0,0);
    vTmpItems.push_back(item);

    p_mapScreen->setTmpItemType(CURRENT_TMP_ITEM::item,itemType);
    this->close();
}
