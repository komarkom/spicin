#ifndef MERROR_H
#define MERROR_H
#include <QString>

class MError
{
public:
    MError(int _ObjNumber,int _FieldName, QString _Comment);

    int ObjNumber;
    int FieldName;
    QString Comment;
};

#endif // MERROR_H
