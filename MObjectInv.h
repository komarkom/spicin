#ifndef MOBJECTINV_H
#define MOBJECTINV_H
#include <QString>


class MObjectInv
{
public:
    MObjectInv(int _InvNumber, QString _Address, QString _Name,
               QString _Subtype, QString _ManagingManComp,
               QString _StartupDate, QString _OKN, int _BookValueRur,
               int _MarketBalance, int _IsUsed)
    {
        this->InvNumber = _InvNumber;
        this->Address = _Address;
        this->Name = _Name;
        this->Subtype = _Subtype;
        this->ManagingManComp = _ManagingManComp;
        this->StartupDate = _StartupDate;
        this->OKN =_OKN;
        this->BookValueRur = _BookValueRur;
        this->MarketBalance = _MarketBalance;
        this->IsUsed = _IsUsed;
    }

public:
    int InvNumber;
    QString Address;
    QString Name;
    QString Subtype;

    QString ManagingManComp;

    QString StartupDate;

    QString OKN;

    int BookValueRur;
    int MarketBalance;
    int IsUsed;
};



#endif // MOBJECTINV_H
