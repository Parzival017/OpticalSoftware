#include "spotwidget.h"
#include "ui_spotwidget.h"

SpotWidget::SpotWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpotWidget)
{
    ui->setupUi(this);
    paint = new Paint2D(this);
    ui->verticalLayout->addWidget(paint);
    paint->getscene()->setSceneRect(paint->mapToScene(rect()).boundingRect());
}


void drawgrid(){
//    QRectF r = QRectF(-100,100,200,200);
//    QPainterPath path;
//    path.moveTo(-100, -100);

//    QGraphicsItem *graph = new QGraphicsPathItem(path);
//    scene->addItem(graph);
}

SpotWidget::~SpotWidget()
{
    delete ui;
}
