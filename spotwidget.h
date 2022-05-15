#ifndef SPOTWIDGET_H
#define SPOTWIDGET_H

#include <QMainWindow>
#include <window/Layout2D/Paint2D.h>

namespace Ui {
class SpotWidget;
}
//点列图
class SpotWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpotWidget(QWidget *parent = nullptr);
    ~SpotWidget();
    void drawgrid();            //绘制方格线

private:
    Ui::SpotWidget *ui;
    Paint2D *paint;
};

#endif // SPOTWIDGET_H
