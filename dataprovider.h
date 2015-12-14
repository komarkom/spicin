#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <QtSql>
#include "MObjectInv.h"
#include "merror.h"

class dataprovider
{
public:
    dataprovider();
    void init(QString dbName="db_name.sqlite");
    void insertVal(MObjectInv e);
    void insertVal(MError e);
    int insertTestData();
    QList<MObjectInv> dbSelectObj (QSqlDatabase db);
    QList<MError> dbSelectErr (QSqlDatabase db);
    void deleteobject(MError e);
    QString close(QString dbName="db_name.sqlite");
    QSqlDatabase _getDatabase();
private:
    QSqlDatabase dataBase;
    QString dbName;
};

#endif // DATAPROVIDER_H
