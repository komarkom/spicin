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
    setWindowTitle("ПК \"Инвентаризация имущества\"");

    connect(ui->objView, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(onErrorFieldClicked(const QModelIndex &)));
    connect(ui->listObjView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));
    on_statButton_clicked();

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
    ui->staticticframe->hide();
    QStandardItemModel *model = new QStandardItemModel;
    dp = new dataprovider();
    Utils::prepareDataList(dp, model, "Здание");
    ui->listObjView->setModel(model);
    ui->listObjView->resizeColumnsToContents();
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
    ui->staticticframe->hide();
    QStandardItemModel *model = new QStandardItemModel;
    dp = new dataprovider();
    Utils::prepareDataList(dp, model, "Движимое");
    ui->listObjView->setModel(model);
    ui->listObjView->resizeColumnsToContents();
}

void MainWindow::on_errorButton_clicked()
{
    ui->ErrorFrame->show();
    ui->listFrame->hide();
    ui->objFrame->hide();
    ui->staticticframe->hide();
    dp = new dataprovider();
    QStandardItemModel *model = new QStandardItemModel;
    Utils::prepareDataError(dp,model);
    ui->errorTableView->setModel(model);
}




void MainWindow::on_statButton_clicked()
{
    ui->ErrorFrame->hide();
    ui->listFrame->hide();
    ui->objFrame->hide();
    ui->staticticframe->show();
    //        QCPBars *regen = new QCPBars(ui->widget_2->xAxis, ui->widget_2->yAxis);
    //        QCPBars *nuclear = new QCPBars(ui->widget_2->xAxis, ui->widget_2->yAxis);
            QCPBars *fossil = new QCPBars(ui->widget_2->xAxis, ui->widget_2->yAxis);
            // set names and colors:
            QPen pen;
            pen.setWidthF(1.2);
            fossil->setName("Fossil fuels");
            pen.setColor(QColor(255, 131, 0));
            fossil->setPen(pen);
            fossil->setBrush(QColor(255, 131, 0, 50));

            // prepare x axis with country labels:
            QVector<double> ticks;
            QVector<QString> labels;
            ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 ;
            labels << "Номер" << "Адрес" << "Наименование" << "Тип" << "Владелец" << "Дата" << "Объект КН" << "Начальная стоимость" << "Рыночная стоимость" << "Используется";
            ui->widget_2->xAxis->setAutoTicks(false);
            ui->widget_2->xAxis->setAutoTickLabels(false);
            ui->widget_2->xAxis->setTickVector(ticks);
            ui->widget_2->xAxis->setTickVectorLabels(labels);
            ui->widget_2->xAxis->setTickLabelRotation(60);
            ui->widget_2->xAxis->setSubTickCount(0);
            ui->widget_2->xAxis->setTickLength(0, 4);
            ui->widget_2->xAxis->grid()->setVisible(true);
            ui->widget_2->xAxis->setRange(0, 8);

            // prepare y axis:
            ui->widget_2->yAxis->setRange(0, 12.1);
            ui->widget_2->yAxis->setPadding(5); // a bit more space to the left border
            ui->widget_2->yAxis->setLabel("Количество ошибок по типам полей в объектах инвентаризации");
            ui->widget_2->yAxis->grid()->setSubGridVisible(true);
            QPen gridPen;
            gridPen.setStyle(Qt::SolidLine);
            gridPen.setColor(QColor(0, 0, 0, 25));
            ui->widget_2->yAxis->grid()->setPen(gridPen);
            gridPen.setStyle(Qt::DotLine);
            ui->widget_2->yAxis->grid()->setSubGridPen(gridPen);

            // Add data:
            QVector<double> fossilData;
            fossilData  << 0.86*10.5 << 0.83*5.5 << 0.84*5.5 << 0.52*5.8 << 0.89*5.2 << 0.90*4.2 << 0.67*11.2 << 8 << 5 << 3;

            fossil->setData(ticks, fossilData);


            // setup legend:
            ui->widget_2->legend->setVisible(true);
            ui->widget_2->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
            ui->widget_2->legend->setBrush(QColor(255, 255, 255, 200));
            QPen legendPen;
            legendPen.setColor(QColor(130, 130, 130, 200));
            ui->widget_2->legend->setBorderPen(legendPen);
            QFont legendFont = font();
            legendFont.setPointSize(10);
            ui->widget_2->legend->setFont(legendFont);
            ui->widget_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
