#include "blockgeneratedialog.h"
#include "ui_blockgeneratedialog.h"
#include "mapscreen.h"
#include "mainwindow.h"
#include "block.h"
#include "constants.h"
#include <QGraphicsScene>
#include <QDebug>

BlockGenerateDialog::BlockGenerateDialog(QWidget *parent,MapScreen* pMapScreen,QGraphicsScene* pMapScene) :
    QDialog(parent),
    ui(new Ui::BlockGenerateDialog),
    p_mapScreen(pMapScreen),
    p_mapScene(pMapScene)
{
    ui->setupUi(this);
}

BlockGenerateDialog::~BlockGenerateDialog()
{
    delete ui;

}

void BlockGenerateDialog::on_generate_PushButton_clicked()
{
   blockType = ui->block_Type_List_Widget->currentItem()->text();
   int row = ui->row_SpinBox->value();
   int col = ui->column_SpinBox->value();

   QVector<QGraphicsItem*>& vtmpItems = p_mapScreen->getvTmpItems();
   qreal scale = p_mapScreen->getAccumulatedScale();
   QPen blackPen(Qt::black);
   int one_block_length = MainWindow::one_block_length;
//   int half_block_length = MainWindow::half_block_length;

   for(int i = 0; i<row;i++)
   {
      for(int j = 0; j<col;j++)
      {
          int x = j*one_block_length;
          int y = i*one_block_length;

          QGraphicsItem* item = p_mapScene->addRect(0,0,one_block_length,one_block_length,blackPen);
          item->setScale(scale);
          item->setPos(x*scale,y*scale);
          vtmpItems.push_back(item);
      }
   }
   p_mapScreen->setTmpItemType(block,blockType);
   this->close();
}
