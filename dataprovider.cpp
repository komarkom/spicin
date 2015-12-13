#include "dataprovider.h"

dataprovider::dataprovider()
{

}

void dataprovider::init(QString dbName)
{
    dataBase = QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName(dbName);
    if (!dataBase.open()) {
        throw 0;
    }
    if (!dataBase.tables().contains(QLatin1String("MObjectInv"))) {
        QSqlQuery a_query(dataBase);
        QString str = "CREATE TABLE MObjectInv ("
                "InvNumber integer PRIMARY KEY NOT NULL, "
                "Address VARCHAR(255), "
                "Name VARCHAR(255), "
                "Subtype VARCHAR(255), "
                "ManagingManComp VARCHAR(255), "
                "StartupDate VARCHAR(255), "
                "OKN VARCHAR(255)"
                "TotalArea integer, "
                "MarketBalance integer, "
                "IsUsed integer, "
                ");";
        bool b = a_query.exec(str);
        if (!b) {
            throw 1;
        }
    }
    if (!dataBase.tables().contains(QLatin1String("MError"))) {
        QSqlQuery a_query(dataBase);
        QString str = "CREATE TABLE MError ("
                "ObjNumber integer PRIMARY KEY NOT NULL, "
                "FieldName integer, "
                "Comment VARCHAR(255), "
                ");";
        bool b = a_query.exec(str);
        if (!b) {
            throw 2;
        }
    }
}


void dataprovider::insertVal(MObjectInv e)
{
    QSqlQuery q(dataBase);
    q.prepare("INSERT INTO MObjectInv (InvNumber, Address,Name,"
              "Subtype,ManagingManComp,StartupDate, OKN,TotalArea, MarketBalance, IsUsed)"
              " VALUES(:InvNumber, :Address, :Name,"
              ":Subtype, :ManagingManComp, :StartupDate, :OKN, :TotalArea, :MarketBalance, :IsUsed)");
    q.bindValue(":InvNumber", e.InvNumber);
    q.bindValue(":Address", e.Address);
    q.bindValue(":Name", e.Name);
    q.bindValue(":Subtype", e.Subtype);
    q.bindValue(":ManagingManComp", e.ManagingManComp);
    q.bindValue(":StartupDate", e.StartupDate);
    q.bindValue(":OKN", e.OKN);
    q.bindValue(":TotalArea", e.BookValueRur);
    q.bindValue(":MarketBalance", e.MarketBalance);
    q.bindValue(":IsUsed", e.IsUsed);
    if (!q.exec()) {
        QSqlError err = q.lastError();
        QString errText = err.text();
        return;
    }
}

void dataprovider::insertVal(MError e)
{
    QSqlQuery q(dataBase);
    q.prepare("INSERT INTO MError (ObjNumber, FieldName, Comment)"
              " VALUES(:ObjNumber, :FieldName, :Comment)");
    q.bindValue(":ObjNumber", e.ObjNumber);
    q.bindValue(":FieldName", e.FieldName);
    q.bindValue(":Comment", e.Comment);
    if (!q.exec()) {
        QSqlError err = q.lastError();
        QString errText = err.text();
        return;
    }
}

QList<MObjectInv> dataprovider::dbSelectObj (QSqlDatabase db) {
    QSqlQuery q(db);

    q.prepare("SELECT * FROM MObjectInv");
    if (!q.exec()) {
        return QList<MObjectInv>();
    }
    QList<MObjectInv> lst;
    while (q.next()) {
        int invNumber = q.value(0).toInt();
        QString Address = q.value(1).toString();
        QString Name = q.value(2).toString();
        QString Subtype = q.value(3).toString();
        QString ManagingManComp = q.value(4).toString();
        QString StartupDate = q.value(5).toString();
        QString OKN = q.value(6).toString();
        int BookValueRur = q.value(7).toInt();
        int MarketBalance = q.value(8).toInt();
        int IsUsed = q.value(9).toInt();
        MObjectInv s(invNumber, Address, Name, Subtype, ManagingManComp,
                     StartupDate, OKN, BookValueRur, MarketBalance, IsUsed);
        lst.append(s);
    }
    return lst;
}
QList<MError> dataprovider::dbSelectErr (QSqlDatabase db) {
    QSqlQuery q(db);

    q.prepare("SELECT * FROM MError");
    if (!q.exec()) {
        return QList<MError>();
    }
    QList<MError> lst;
    while (q.next()) {
        int ObjNumber = q.value(0).toInt();
        int FieldName = q.value(1).toInt();
        QString Comment = q.value(2).toString();

        MError s(ObjNumber, FieldName, Comment);
        lst.append(s);
    }
    return lst;
}

QString dataprovider::close(QString dbName)
{
   QString cN = dataBase.connectionName();
   dataBase.close();
   return cN;
}

QSqlDatabase dataprovider::_getDatabase()
{
    return dataBase;
}
