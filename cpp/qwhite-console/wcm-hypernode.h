
#ifndef WCM_HYPERNODE__H
#define WCM_HYPERNODE__H

#include "accessors.h"

#include <QString>
#include <QList>
#include <QDate>

#include <functional>

class QWhite_Column_Set;
class WCM_Hyponode;
class WCM_Type;




class WCM_Hypernode
{
 QVector<WCM_Hyponode*> hyponodes_;

 WCM_Type* wcm_type_;

 QMap<quint32, QString>* indexed_column_map_;

public:

 ACCESSORS__RGET(QVector<WCM_Hyponode*> ,hyponodes)
 ACCESSORS(WCM_Type* ,wcm_type)
// ACCESSORS__GET(PASTE_EXPRESSION(QMap<quint32, QString*>)* ,indexed_column_map)
// ACCESSORS__SET(PASTE_EXPRESSION(QMap<quint32, QString*>)* ,indexed_column_map)

 ACCESSORS(MACRO_PASTE(QMap<quint32, QString>)* ,indexed_column_map)

 WCM_Hypernode();

 void supply_data(QByteArray& qba, QWhite_Column_Set& columns);
 void absorb_data(const QByteArray& qba, QWhite_Column_Set& columns);

 void add_hyponode(WCM_Hyponode* who);
 void add_hyponodes(QList<WCM_Hyponode*> whos);

 void each_hyponode(std::function<void(WCM_Hypernode&, WCM_Hyponode&, quint32)>);
 void each_hyponode(std::function<void(WCM_Hyponode&, quint32)>);
 void each_hyponode(std::function<void(WCM_Hypernode&, WCM_Hyponode&)>);
 void each_hyponode(std::function<void(WCM_Hyponode&)>);

 QString check_column(quint32 index);


};

#endif
