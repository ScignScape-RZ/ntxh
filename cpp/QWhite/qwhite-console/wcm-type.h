
#ifndef WCM_TYPE__H
#define WCM_TYPE__H

#include "accessors.h"

#include "flags.h"

#include <QString>
#include <QList>
#include <QDate>

class QWhite_Column_Set;
class WCM_Hyponode;
class WCM_Type;


class WCM_Type
{
 QString name_;
 quint32 id_;
 quint8 precycle_length_;
 quint16 cell_block_size_;

public:

 ACCESSORS(QString ,name)
 ACCESSORS(quint32 ,id)
 ACCESSORS(quint8 ,precycle_length)
 ACCESSORS(quint16 ,cell_block_size)

 WCM_Type();
};

#endif
