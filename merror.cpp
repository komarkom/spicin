#include "merror.h"

MError::MError(int _ObjNumber,int _FieldName, QString _Comment)
{
    this->ObjNumber = _ObjNumber;
    this->FieldName = _FieldName;
    this->Comment = _Comment;
}
