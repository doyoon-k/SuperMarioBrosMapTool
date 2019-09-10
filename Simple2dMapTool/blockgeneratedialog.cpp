#include "blockgeneratedialog.h"
#include "ui_blockgeneratedialog.h"
#include "mainwindow.h"
#include "block.h"
#include <QGraphicsScene>

BlockGenerateDialog::BlockGenerateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlockGenerateDialog)
{
    ui->setupUi(this);
}

BlockGenerateDialog::~BlockGenerateDialog()
{
    delete ui;
}

void BlockGenerateDialog::on_generate_PushButton_clicked()
{
   QString blockType = ui->block_Type_List_Widget->currentItem()->text();
   int row = ui->row_SpinBox->value();
   int col = ui->row_SpinBox->value();
   QString itemType;


   MainWindow* mw = reinterpret_cast<MainWindow*>(parentWidget());

   if(mw== nullptr)
       return;

   QGraphicsScene* scene = mw->getGraphicsScene();
   QVector<QGraphicsItem*>& vtmpItems = mw->getvTmpItems();
   QPen blackPen(Qt::black);
   int one_block_length = MainWindow::one_block_length;

   for(int i = 0; i<row;i++)
   {
      for(int j = 0; j<col;j++)
      {
         vtmpItems.push_back(scene->addRect(row*one_block_length,col*one_block_length,one_block_length,one_block_length,blackPen));
      }
   }

}
