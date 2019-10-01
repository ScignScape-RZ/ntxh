
#include "wcm-hyponode.h"

#include <QDataStream>
#include <QIODevice>
#include <QMetaType>

#include "qwhite/qwhite-column-set.h"

WCM_Hyponode::WCM_Hyponode()
{

}

quint64 WCM_Hyponode::defers_to_wg() const
{
 static int mt = QMetaType::type("QVarDBValue");
 if(qt_encoding_.userType() == mt)
 {
  QVarDBValue qvdbv = qt_encoding_.value<QVarDBValue>();
  if(qvdbv.code == 1)
    return qvdbv.code;
 }
 return 0;
}

void WCM_Hyponode::set_wgdb_encoding(wg_enc wgdb_encoding)
{
 static QVarDBValue qvdbv {1};
 wgdb_encoding_ = wgdb_encoding;
 qt_encoding_.setValue(qvdbv);
}

