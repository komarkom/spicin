#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QStandardItemModel"
#include "QStandardItem"

#include "MObjectInv.h"

MainWindow::MainWindow(QWidget *parent, dataprovider *dp) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dp = new dataprovider();
    dp->init();
    dp->insertTestData();
    QList<MObjectInv> lst11 = dp->dbSelectObj(dp->_getDatabase());
    ui->ErrorFrame->hide();
    ui->listFrame->hide();
    ui->objFrame->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QStandardItemModel setMyModel(QString type)
{

}

void MainWindow::on_realEstateButton_clicked()
{
    ui->listFrame->show();
    ui->ErrorFrame->hide();
    ui->objFrame->hide();
    dp = new dataprovider();
    QList<MObjectInv> Objlst = dp->dbSelectObj(dp->_getDatabase());
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;
    QStringList horizontalHeader;
    horizontalHeader.append("Номер");
    horizontalHeader.append("Адрес");
    horizontalHeader.append("Название");
    horizontalHeader.append("Тип");
    model->setHorizontalHeaderLabels(horizontalHeader);

    int i = 0;
    foreach (MObjectInv ol, Objlst) {
       if(ol.Subtype == QString("Здание")){
       item = new QStandardItem(QString::number(ol.InvNumber));
       model->setItem(i, 0, item);
       item = new QStandardItem(QString(ol.Address));
       model->setItem(i, 1, item);
       item = new QStandardItem(QString(ol.Name));
       model->setItem(i, 2, item);
       item = new QStandardItem(QString(ol.Subtype));
       model->setItem(i, 3, item);
       i++;
       }
    }
    ui->listObjView->setModel(model);
    connect(ui->listObjView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));

}

void MainWindow::onTableClicked(const QModelIndex &index)
{
    if (index.isValid() && index.column() == 0) {
        int _invNumber = index.data().toInt();
        ui->listFrame->hide();
        ui->objFrame->show();
        dp = new dataprovider();
        QList<MObjectInv> Objlst = dp->dbSelectObj(dp->_getDatabase());
        QStandardItemModel *model = new QStandardItemModel;
        QStandardItem *item;
        QStringList verticalHeader;
        verticalHeader.append("Номер");
        verticalHeader.append("Адрес");
        verticalHeader.append("Название");
        verticalHeader.append("Тип");
        verticalHeader.append("Владелец");
        verticalHeader.append("Дата");
        verticalHeader.append("Объект КН");
        verticalHeader.append("Начальная стоимость");
        verticalHeader.append("Рыночная стоимость");
        verticalHeader.append("В эксплуатации");
        QStringList horizontalHeader;
        horizontalHeader.append("Значение");
        horizontalHeader.append("Ошибка");
        horizontalHeader.append("Коментарий");
        model->setVerticalHeaderLabels(verticalHeader);
        model->setHorizontalHeaderLabels(horizontalHeader);

        foreach (MObjectInv ol, Objlst) {
           if(ol.InvNumber == _invNumber)
           {
               item = new QStandardItem(QString::number(ol.InvNumber));
               model->setItem(0, item);
               item = new QStandardItem(QString(ol.Address));
               model->setItem(1, item);
               item = new QStandardItem(QString(ol.Name));
               model->setItem(2, item);
               item = new QStandardItem(QString(ol.Subtype));
               model->setItem(3, item);
               item = new QStandardItem(QString(ol.ManagingManComp));
               model->setItem(4, item);
               item = new QStandardItem(QString(ol.StartupDate));
               model->setItem(5, item);
               item = new QStandardItem(QString(ol.OKN));
               model->setItem(6, item);
               item = new QStandardItem(QString(QString::number(ol.BookValueRur)));
               model->setItem(7, item);
               item = new QStandardItem(QString(QString::number(ol.MarketBalance)));
               model->setItem(8, item);
               item = new QStandardItem(QString(QString::number(ol.IsUsed)));
               model->setItem(9, item);
            }
        }
        ui->objView->setModel(model);
        connect(ui->objView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onErrorFieldClicked(const QModelIndex &)));
    }
}

void MainWindow::onErrorFieldClicked(const QModelIndex &index)
{
    if (index.isValid() && index.column() == 1)
    {
        QStandardItemModel *model = new QStandardItemModel;
        QStandardItem *item;

        item = new QStandardItem(QString("x"));
        item->setBackground(QBrush(QColor(23,45,123)));
        model->setItem(index.row(),2, item);
        ui->objView->setModel(model);
    }
}

void MainWindow::on_movablesButton_clicked()
{
    ui->listFrame->show();
    ui->ErrorFrame->hide();
    ui->objFrame->hide();
    dp = new dataprovider();
    QList<MObjectInv> Objlst = dp->dbSelectObj(dp->_getDatabase());
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;
    QStringList horizontalHeader;
    horizontalHeader.append("Номер");
    horizontalHeader.append("Адрес");
    horizontalHeader.append("Название");
    horizontalHeader.append("Тип");
    model->setHorizontalHeaderLabels(horizontalHeader);

    int i = 0;
    foreach (MObjectInv ol, Objlst) {
       if(ol.Subtype == QString("Движимое")){
       item = new QStandardItem(QString::number(ol.InvNumber));
       model->setItem(i, 0, item);
       item = new QStandardItem(QString(ol.Address));
       model->setItem(i, 1, item);
       item = new QStandardItem(QString(ol.Name));
       model->setItem(i, 2, item);
       item = new QStandardItem(QString(ol.Subtype));
       model->setItem(i, 3, item);
       i++;
       }
    }
    ui->listObjView->setModel(model);
    }

void MainWindow::on_errorButton_clicked()
{
    ui->ErrorFrame->show();
    ui->listFrame->hide();
    ui->objFrame->hide();
    dp = new dataprovider();
    QList<MError> erlst = dp->dbSelectErr(dp->_getDatabase());
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;
    QStringList horizontalHeader;
    horizontalHeader.append("Номер объекта");
    horizontalHeader.append("Поле");
    horizontalHeader.append("Коментарий");
    model->setHorizontalHeaderLabels(horizontalHeader);

    int i = 0;
    foreach (MError er, erlst) {

       item = new QStandardItem(QString::number(er.ObjNumber));
       model->setItem(i, 0, item);
       item = new QStandardItem(QString::number(er.FieldName));
       model->setItem(i, 1, item);
       item = new QStandardItem(QString(er.Comment));
       model->setItem(i, 2, item);
       i++;
       }

    ui->errorTableView->setModel(model);
}



