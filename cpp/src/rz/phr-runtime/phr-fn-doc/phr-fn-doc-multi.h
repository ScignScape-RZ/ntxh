
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_FN_DOC_MULTI__H
#define PHR_FN_DOC_MULTI__H


#include "kans.h"

#include "phaon-ir/types/phr-universal-class.h"

#include <QString>
#include <QObject>
#include <QList>
#include <QPair>

KANS_(Phaon)

class PHR_Env;
class PHR_Fn_Doc;
class PHR_Type_Object;

class PHR_Fn_Doc_Multi : public QObject, public PHR_Universal_Class
{
 Q_OBJECT

 PHR_Fn_Doc* fnd_;

 QList<QPair<QString, PHR_Type_Object>> fns_;

public:

 PHR_Fn_Doc_Multi();

 PHR_Fn_Doc_Multi(const PHR_Fn_Doc_Multi& rhs);

 ~PHR_Fn_Doc_Multi();

 Q_INVOKABLE void read(QString fn);
 Q_INVOKABLE void init(PHR_Env* penv);

 Q_INVOKABLE void kph_gen_multi(QString path);

};

_KANS(Phaon)

USING_KANS(Phaon)

Q_DECLARE_METATYPE(PHR_Fn_Doc_Multi)
Q_DECLARE_METATYPE(PHR_Fn_Doc_Multi*)

#endif //PHR_FN_DOC_MULTI__H
