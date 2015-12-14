#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QStandardItemModel"
#include "QStandardItem"

#include "MObjectInv.h"
#include "utils.h"


MainWindow::MainWindow(QWidget *parent, dataprovider *dp) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dp = new dataprovider();
    dp->init();
    dp->insertTestData();

    ui->ErrorFrame->hide();
    ui->listFrame->hide();
    ui->objFrame->show();
    connect(ui->objView, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(onErrorFieldClicked(const QModelIndex &)));
    connect(ui->listObjView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_realEstateButton_clicked()
{
    ui->listFrame->show();
    ui->ErrorFrame->hide();
    ui->objFrame->hide();

    QStandardItemModel *model = new QStandardItemModel;
    dp = new dataprovider();
    Utils::prepareDataList(dp, model, "Здание");
    ui->listObjView->setModel(model);
}

void MainWindow::onTableClicked(const QModelIndex &index)
{
    if (index.isValid() && index.column() == 0) {
        int _invNumber = index.data().toInt();
        ui->listFrame->hide();
        ui->objFrame->show();
        dp = new dataprovider();
        QStandardItemModel *model = new QStandardItemModel;
        Utils::prepareDataObj(dp, model,_invNumber);
        ui->objView->setModel(model);
     }
}

void MainWindow::onErrorFieldClicked(const QModelIndex &index)
{
    if (index.isValid() && index.column() == 1)
    {
        QModelIndex in = ui->objView->model()->index(0,0);
        int _invNumber = in.data().toInt();

        if(index.data().toString().isNull() || index.data().toString().isEmpty())
        {
            dp->insertVal(MError(_invNumber, index.row(), "x"));
        }
        else
        {
            dp->deleteobject(MError(_invNumber, index.row(), ""));
        }

        dp = new dataprovider();
        QStandardItemModel *model = new QStandardItemModel;
        Utils::prepareDataObj(dp, model,_invNumber);
        ui->objView->setModel(model);
    }
}

void MainWindow::on_movablesButton_clicked()
{
    ui->listFrame->show();
    ui->ErrorFrame->hide();
    ui->objFrame->hide();
    QStandardItemModel *model = new QStandardItemModel;
    dp = new dataprovider();
    Utils::prepareDataList(dp, model, "Движимое");
    ui->listObjView->setModel(model);

}

void MainWindow::on_errorButton_clicked()
{
    ui->ErrorFrame->show();
    ui->listFrame->hide();
    ui->objFrame->hide();
    dp = new dataprovider();
    QStandardItemModel *model = new QStandardItemModel;
    Utils::prepareDataError(dp,model);
    ui->errorTableView->setModel(model);


}



