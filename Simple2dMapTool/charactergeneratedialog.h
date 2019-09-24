#ifndef CHARACTERGENERATEDIALOG_H
#define CHARACTERGENERATEDIALOG_H

#include <QDialog>
#include "mapscreen.h"
#include <QGraphicsScene>

namespace Ui {
class CharacterGenerateDialog;
}

class CharacterGenerateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CharacterGenerateDialog(QWidget *parent = nullptr,MapScreen* pMapScreen = nullptr,QGraphicsScene* pMapScene = nullptr);
    ~CharacterGenerateDialog();

private slots:
    void on_character_Generate_pushButton_clicked();

private:
    Ui::CharacterGenerateDialog *ui;
    MapScreen* p_mapScreen;
    QGraphicsScene* p_mapScene;
    QString characterType;
};

#endif // CHARACTERGENERATEDIALOG_H
