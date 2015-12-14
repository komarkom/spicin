#ifndef UTILS_H
#define UTILS_H
#include "QString"
#include "QStandardItemModel"
#include "QStandardItem"

#include "MObjectInv.h"
#include "dataprovider.h"

class Utils
{
public:
    Utils();
    static QString getFieldName(int n)
        {
            switch (n) {
            case 0:
                return "Инвентаризационный номер";
                break;
            case 1:
                return "Адрес";
                break;
            case 2:
                return "Наименование";
                break;
            case 3:
                return "Тип";
                break;
            case 4:
                return "Владелец";
                break;
            case 5:
                return "Дата";
                break;
            case 6:
                return "Объект КН";
                break;
            case 7:
                return "Начальная стоимость";
                break;
            case 8:
                return "Рыночная стоимость";
                break;
            case 9:
                return "Используется";
                break;
            default:
                return "";
                break;
            }
        }
    static void prepareDataList(dataprovider *dp, QStandardItemModel *model, QString type)
    {
        QList<MObjectInv> Objlst = dp->dbSelectObj(dp->_getDatabase());

        QStandardItem *item;
        QStringList horizontalHeader;
        horizontalHeader.append("Номер");
        horizontalHeader.append("Адрес");
        horizontalHeader.append("Название");
        horizontalHeader.append("Тип");
        model->setHorizontalHeaderLabels(horizontalHeader);

        int i = 0;
        foreach (MObjectInv ol, Objlst) {
           if(ol.Subtype == QString(type)){
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
    }
    static void prepareDataObj(dataprovider *dp, QStandardItemModel *model, int _invNumber)
    {
        QList<MObjectInv> Objlst = dp->dbSelectObj(dp->_getDatabase());
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
        QList<MError> erLst = dp->dbSelectErr(dp->_getDatabase());
        foreach (MError er , erLst) {
            if(er.ObjNumber == _invNumber)
            {
                item = new QStandardItem(QString("x"));
                item->setBackground(QBrush(QColor(1,0,0)));
                model->setItem(er.FieldName, 1, item);
            }
        }
    }
    static void prepareDataError(dataprovider *dp, QStandardItemModel *model)
    {
        QList<MError> erlst = dp->dbSelectErr(dp->_getDatabase());
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
           item = new QStandardItem(Utils::getFieldName(er.FieldName));
           model->setItem(i, 1, item);
           item = new QStandardItem(QString(er.Comment));
           model->setItem(i, 2, item);
           i++;
           }

    }
};

#endif // UTILS_H
