#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dataprovider.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, dataprovider *dp = 0);
    ~MainWindow();

private slots:
    void on_realEstateButton_clicked();

    void on_movablesButton_clicked();

    void on_errorButton_clicked();

    void onTableClicked(const QModelIndex &index);
    void onErrorFieldClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    dataprovider *dp;
};

#endif // MAINWINDOW_H
