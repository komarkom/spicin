#include <QString>
#include <QtTest>
#include "utils.h"
#include "MObjectInv.h"
#include "merror.h"
#include "dataprovider.h"

class MUTest : public QObject
{
    Q_OBJECT

public:
    MUTest();

private Q_SLOTS:
    void testRandom();
    void testGetName();
    void testCreateMObjInv();
    void testCreateMError();
    void testDbInsert();
    void testDbSelect();
};

MUTest::MUTest()
{

}

void MUTest::testGetName()
{
    QVERIFY("Адрес" == Utils::getFieldName(1));
}

void MUTest::testCreateMObjInv()
{
    MObjectInv m = MObjectInv(133,"","Такой вот объект","","","","",17648, 93242,1);
    QVERIFY("Такой вот объект" == m.Name);
}

void MUTest::testCreateMError()
{
    MError m = MError(34,4,"Хреновенько");
    QVERIFY("Хреновенько" == m.Comment);
}

void MUTest::testDbInsert()
{
    QFile("test_db.sqlite").remove();
    dataprovider* dp = new dataprovider();
    dp->init("test_db.sqlite");
    MError m(34,4,"Хреновенько");
    dp->insertVal(m);
    QList<MError> errs = dp->dbSelectErr(dp->_getDatabase());
    QCOMPARE(errs.size(), 1);
    QString connectionName = dp->close();
    delete dp;
    QSqlDatabase::removeDatabase(connectionName);
}

void MUTest::testDbSelect()
{

    QFile("test_db.sqlite").remove();
    dataprovider* dp = new dataprovider();
    dp->init("test_db.sqlite");
    MError m(34,4,"Хорошо");
    dp->insertVal(m);
    QList<MError> errs = dp->dbSelectErr(dp->_getDatabase());
    MError err = errs.at(0);
    QString loadedText = err.Comment;
    QCOMPARE(loadedText, QString("Хорошо"));

    QString connectionName = dp->close();
    delete dp;
    QSqlDatabase::removeDatabase(connectionName);
}

void MUTest::testRandom()
{
    QVERIFY(qrand() != qrand());
}

QTEST_APPLESS_MAIN(MUTest)

#include "tst_mutest.moc"
