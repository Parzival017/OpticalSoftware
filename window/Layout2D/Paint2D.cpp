#include "Paint2D.h"

#define R 40

Paint2D::Paint2D(QWidget *parent) : QGraphicsView(parent)
{
    //binding scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 0, 0);
    setScene(scene);
    qDebug() << this->size();
    //disable scrollbar
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Paint2D::wheelEvent(QWheelEvent *event)
{
    if (QApplication::keyboardModifiers() == Qt::ControlModifier) {
#if (QT_VERSION >= QT_VERSION_CHECK(5,12,0))
        QPoint viewP = event->position().toPoint();
        QPointF oldP = mapToScene(viewP);
        if(event->angleDelta().y() < 0)
            scale(0.9, 0.9);
        else
            scale(1/0.9, 1/0.9);
#else
        QPoint viewP = event->pos();
        QPointF oldP = mapToScene(viewP);
        if(event->delta() < 0)
            scale(0.9, 0.9);
        else
            scale(1/0.9, 1/0.9);
#endif
        scene->setSceneRect(mapToScene(rect()).boundingRect());
        QPointF disPointF = mapToScene(viewP) - oldP;
        scene->setSceneRect(scene->sceneRect().x()-disPointF.x(),\
                            scene->sceneRect().y()-disPointF.y(),\
                            scene->sceneRect().width(),\
                            scene->sceneRect().height());
        scene->update();
        return ;
    }
    QGraphicsView::wheelEvent(event);
}

void Paint2D::mousePressEvent(QMouseEvent *event)
{
    isMousePressed = true;
    m_lastPointF = event->pos();
    QGraphicsView::mousePressEvent(event);
}

void Paint2D::mouseMoveEvent(QMouseEvent *event)
{
    if(isMousePressed)
    {
        QPointF disPointF = event->pos() - m_lastPointF;
        m_lastPointF = event->pos();
        scene->setSceneRect(scene->sceneRect().x() - disPointF.x() * \
                            scene->sceneRect().width() / 1200.0,     \
                            scene->sceneRect().y() - disPointF.y() * \
                            scene->sceneRect().height() / 1200.0,    \
                            scene->sceneRect().width(),              \
                            scene->sceneRect().height());
        scene->update();
    }
    QGraphicsView::mouseMoveEvent(event);
}

void Paint2D::mouseReleaseEvent(QMouseEvent *event)
{
    isMousePressed = false;
    QGraphicsView::mouseReleaseEvent(event);
}

void Paint2D::Demo()
{
    QGraphicsEllipseItem *elli = new QGraphicsEllipseItem\
            (QRectF(100, 100, 100, 100));
    elli->setPen(QPen(QColor(0,0,0,50),10));
    elli->setBrush(QBrush(QColor(255,235,205,255)));
    scene->addItem(elli);
}

QGraphicsScene *Paint2D::getscene()
{
    return scene;
}

Paint2D::~Paint2D()
{

}

void Paint2D::draw_system(Obj *sys) {
    int size = sys->getSurfaceSize();
    double x = 0;
    QVector<QPointF> upperPoints;
    for (int i = 0; i < size; i++) {
        Standard sur = sys->getSurface(i);
        x = x + sur.d;
        upperPoints.append(drawSurface_withReturn(sys->getSurface(i), x));
    }
    for (int j= 1; j < size; j+=2 ){
        drawEdge(upperPoints[j-1],upperPoints[j]);
    }
}

void Paint2D::drawEdge(QPointF upperPoint1,QPointF upperPoint2){
    qreal x1 = upperPoint1.x(),x2 = upperPoint2.x();
    qreal y1 = upperPoint1.y(),y2 = upperPoint2.y();
    qreal greater_x,greater_y,lower_x,lower_y;
   if(y1>y2){
       greater_x = x1;
       greater_y = y1;
       lower_x = x2;
       lower_y = y2;
   }else{
       greater_x = x2;
       greater_y = y2;
       lower_x = x1;
       lower_y = y1;
   }
   QPainterPath path;
   path.moveTo(lower_x, lower_y);
   path.lineTo(QPointF(lower_x,greater_y));
   path.lineTo(QPointF(greater_x,greater_y));

   path.moveTo(lower_x, -lower_y);
   path.lineTo(QPointF(lower_x,-greater_y));
   path.lineTo(QPointF(greater_x,-greater_y));
   QGraphicsItem *graph = new QGraphicsPathItem(path);
   scene->addItem(graph);
}

void Paint2D::drawSurface(Standard sur, const double x) {
    double semiD = sur.D;
    double radiu = sur.r;
    qreal spanAngle = qAsin((qreal)semiD / radiu) / M_PI * 180;
    QRectF r = QRectF(x, -radiu, 2 * radiu, 2 * radiu);
    QPainterPath path;
    path.moveTo(x, 0);
    path.arcTo(r, 180, spanAngle);
    path.moveTo(x, 0);
    path.arcTo(r, 180, -spanAngle);
    QGraphicsItem *graph = new QGraphicsPathItem(path);
    scene->addItem(graph);
}

QPointF Paint2D::drawSurface_withReturn(Standard sur, const double x){
    double semiD = sur.D;
    double radiu = sur.r;
    qreal spanAngle = qAsin((qreal)semiD / radiu) / M_PI * 180;
    QRectF r = QRectF(x, -radiu, 2 * radiu, 2 * radiu);
    QPainterPath path;
    path.moveTo(x, 0);
    path.arcTo(r, 180, spanAngle);
    QPointF upper = path.currentPosition();
    path.moveTo(x, 0);
    path.arcTo(r, 180, -spanAngle);
    QGraphicsItem *graph = new QGraphicsPathItem(path);
    scene->addItem(graph);
    return upper;
}
