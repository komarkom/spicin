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

    dp->init();
    MObjectInv mObj(12,"Здесь", "Build", "realEstete", "nws", "121212", "y", 12,12,1);
    dp->insertVal(mObj);
    ui->ErrorFrame->hide();
    ui->realEstateFrame->show();
    ui->movableFrame->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_realEstateButton_clicked()
{
    ui->realEstateFrame->show();
    ui->movableFrame->hide();
    ui->ErrorFrame->hide();

}

void MainWindow::on_movablesButton_clicked()
{
    ui->movableFrame->show();
    ui->ErrorFrame->hide();
    ui->realEstateFrame->hide();
        QStandardItemModel *model = new QStandardItemModel;
        QStandardItem *item;

        //Заголовки столбцов
        QStringList horizontalHeader;
        horizontalHeader.append("Первый");
        horizontalHeader.append("Второй");
        horizontalHeader.append("Третий");
        horizontalHeader.append("Четвертый");

        //Заголовки строк
        QStringList verticalHeader;
        verticalHeader.append("Ряд 1");
        verticalHeader.append("Ряд 2");

        model->setHorizontalHeaderLabels(horizontalHeader);
        model->setVerticalHeaderLabels(verticalHeader);

        //Первый ряд
        item = new QStandardItem(QString("0"));
        model->setItem(0, 0, item);

        item = new QStandardItem(QString("1"));
        model->setItem(0, 1, item);

        item = new QStandardItem(QString("2"));
        model->setItem(0, 2, item);

        item = new QStandardItem(QString("3"));
        model->setItem(0, 3, item);

        //Второй ряд
        item = new QStandardItem(QString("4"));
        model->setItem(1, 0, item);

        item = new QStandardItem(QString("5"));
        model->setItem(1, 1, item);

        item = new QStandardItem(QString("6"));
        model->setItem(1, 2, item);

        item = new QStandardItem(QString("7"));
        model->setItem(1, 3, item);

        ui->movableTableView->setModel(model);

//        ui->tableView->resizeRowsToContents();
//        ui->tableView->resizeColumnsToContents();
}

void MainWindow::on_errorButton_clicked()
{
    ui->ErrorFrame->show();
    ui->movableFrame->hide();
    ui->realEstateFrame->hide();
}
