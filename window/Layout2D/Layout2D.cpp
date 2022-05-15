#include "Layout2D.h"
#include "ui_Layout2D.h"

Layout2D::Layout2D(QWidget *parent) : QMainWindow(parent), ui(new Ui::Layout2D)
{
    ui->setupUi(this);
    connect(ui->menu_2, &QMenu::triggered, this, [=]() {
        //非模态对话框
        QDialog *dlg2 = new QDialog(this);
        dlg2->setVisible(true);
        dlg2->resize(800, 600);
        dlg2->setAttribute(Qt::WA_DeleteOnClose); //设置属性(防止内存泄漏,一旦关掉即释放dlg2)
        dlg2->show();
    });
    paint = new Paint2D(this);
    ui->verticalLayout->addWidget(paint);
    paint->getscene()->setSceneRect(paint->mapToScene(rect()).boundingRect());
}

void Layout2D::draw_system(Obj *sys) {
    paint->draw_system(sys);
}

Layout2D::~Layout2D()
{
    delete ui;
}
