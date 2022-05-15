#include "LensDataEditor.h"
#include "ui_LensDataEditor.h"
#include <QDebug>
#include <QMessageBox>

LensDataEditor::LensDataEditor(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::LensDataEditor) {
    ui->setupUi(this);
    connect(ui->actionInsert_Surface, &QAction::triggered, this, &LensDataEditor::insert_row);
    connect(ui->actionDelete_Surface, &QAction::triggered, this, &LensDataEditor::delete_row);
    connect(ui->tableWidget, &QTableWidget::doubleClicked, this, &LensDataEditor::double_clicked);
    connect(ui->tableWidget, &QTableWidget::itemChanged, this, &LensDataEditor::update_system);
    connect(ui->tableWidget, &QTableWidget::itemSelectionChanged, this, &LensDataEditor::histroy_record);
    //仅能单选
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //隔行变色
    ui->tableWidget->setAlternatingRowColors(true);
    model = ui->tableWidget->model();
}

void LensDataEditor::insert_row() {
    int row = ui->tableWidget->currentRow() + 1;
    QTableWidgetItem *it = ui->tableWidget->verticalHeaderItem(row - 1);
    QString head_str = (it == NULL) ? "" : it->text();
    if (head_str != "IMA") {
        insertSem = 1;
        ui->tableWidget->insertRow(row);
        init_row(row);
        if (row <= STO_index)
            STO_index++;
        else
            row--;
        system->addSurface(row);
        insertSem = 0;
    }
    //    system->log();
}

void LensDataEditor::delete_row() {
    int row = ui->tableWidget->currentRow();
    QTableWidgetItem *it = ui->tableWidget->verticalHeaderItem(row);
    QString head_str = (it == NULL) ? "" : it->text();
    if (head_str != "OBJ" && head_str != "STO" && head_str != "IMA") {
        ui->tableWidget->removeRow(row);
        if (row < STO_index)
            STO_index--;
        else
            row--;
        system->delSurface(row);
    }
    //    system->log();
}

void LensDataEditor::histroy_record() {
    QTableWidgetItem *it = ui->tableWidget->currentItem();
    histroyString = (it == NULL) ? "" : it->text();
    //    qDebug() << histroyString;
}

void LensDataEditor::update_system(QTableWidgetItem *item) {
    if (insertSem)
        return;
    int col = item->column();
    int row = item->row();
    if (row == STO_index)
        return;
    QString head_str = ui->tableWidget->horizontalHeaderItem(col)->text();
    bool isnum;
    double num = item->text().toDouble(&isnum);
    //    qDebug() << isnum << num;
    if (head_str == QString("曲率半径")) {
        if (!isnum)
            goto input_error;
        system->setSurface_radiu((row < STO_index) ? row : row - 1, num);
    } else if (head_str == QString("厚度")) {
        if (!isnum)
            goto input_error;
        system->setSurface_thick((row < STO_index) ? row : row - 1, num);
    } else if (head_str == QString("玻璃")) {
        //TODO::
        if (item->text() != "Air") {
            QMessageBox::warning(this, "error", "玻璃库还在开发中，咕咕咕");
            item->setText(histroyString);
            return;
        }
    } else if (head_str == QString("半直径")) {
        if (!isnum)
            goto input_error;
        system->setSurface_semiD((row < STO_index) ? row : row - 1, num);
    } else if (head_str == QString("圆锥系数")) {
        if (!isnum)
            goto input_error;
        system->setSurface_conic((row < STO_index) ? row : row - 1, num);
    }
    histroyString = item->text();
    //    system->log();
    //    qDebug() << "---";
    return;
input_error:
    QMessageBox::warning(this, "error", "数据错误");
    item->setText(histroyString);
    return;
}

void LensDataEditor::double_clicked(const QModelIndex &index) {
    if (index.column() == 0) {
        SurfaceProperties dailog;
        dailog.exec();
        model->setData(index, dailog.getType());
    }
    //TODO::
}

void LensDataEditor::init_row(int rowIndex, QString TypeStr, QString RadiuStr, QString ThickStr, QString BoliStr, QString DiamStr, QString ConiStr, QString RefStr) {
    int col = ui->tableWidget->columnCount();
    for (int i = 0; i < col; i++) {
        QString head_str = ui->tableWidget->horizontalHeaderItem(i)->text();
        QTableWidgetItem *item = new QTableWidgetItem;
        if (head_str == QString("表面类型")) {
            item->setText(TypeStr);
            item->setFlags(item->flags() & (~Qt::ItemIsEditable)); //设置不可编辑
        } else if (head_str == QString("曲率半径")) {
            item->setText(RadiuStr);
        } else if (head_str == QString("厚度")) {
            item->setText(ThickStr);
        } else if (head_str == QString("玻璃")) {
            item->setText(BoliStr);
        } else if (head_str == QString("半直径")) {
            item->setText(DiamStr);
        } else if (head_str == QString("折射率")) {
            item->setText(RefStr);
            item->setFlags(item->flags() & (~Qt::ItemIsEditable)); //设置不可编辑
        } else if (head_str == QString("圆锥系数")) {
            item->setText(ConiStr);
        }
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(rowIndex, i, item);
    }
}

LensDataEditor::~LensDataEditor() { delete ui; }

QAbstractItemModel *LensDataEditor::get_data() {
    return ui->tableWidget->model();
}
