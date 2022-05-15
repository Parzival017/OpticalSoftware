#ifndef LENSDATAEDITOR_H
#define LENSDATAEDITOR_H

#include <QMainWindow>
#include <QTableWidget>

#include <config.h>
#include <system/system.h>
#include "SurfaceProperties.h"

namespace Ui {
class LensDataEditor;
}

class LensDataEditor : public QMainWindow {
    Q_OBJECT

public:
    explicit LensDataEditor(QWidget *parent = nullptr);
    ~LensDataEditor();
    QAbstractItemModel *get_data();
#if defined(USE_OLD_SYSTEM)
    void bind_system(OpticalSystem *sys) { system = sys; };
#elif defined(USE_NEW_SYSTEM)
    void bind_system(Obj *sys) { system = sys; };
#endif

private:
    Ui::LensDataEditor *ui;
    QAbstractItemModel *model;
    QString histroyString = "";
    int STO_index = 1;
    bool insertSem = 0; //信号量

#if defined(USE_OLD_SYSTEM)
    OpticalSystem *system = nullptr;
#elif defined(USE_NEW_SYSTEM)
    Obj *system = nullptr;
#endif

    void insert_row();
    void delete_row();
    void histroy_record();
    void update_system(QTableWidgetItem *item);
    void double_clicked(const QModelIndex &index);
    void init_row(int rowIndex, QString TypeStr = "标准面",
                  QString RadiuStr = "inf", QString ThickStr = "0",
                  QString BoliStr = "Air", QString DiamStr = "0",
                  QString ConiStr = "0", QString RefStr = "1");
};

#endif // LENSDATAEDITOR_H
