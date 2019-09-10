#include "mapscreen.h"
#include "ui_mapscreen.h"
#include <QPainter>

MapScreen::MapScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapScreen)
{
    ui->setupUi(this);
}

MapScreen::~MapScreen()
{
    delete ui;
}

void MapScreen::MapScreen::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawLine(this->x,this->y,this->x+this->width,this->y+this->height);
}
