
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_SCOPE_SYSTEM__H
#define PHR_SCOPE_SYSTEM__H

#include "kans.h"


#include "accessors.h"

#include <QtGlobal>
#include <QQueue>

#include <QMap>


#include "phr-runtime-scope.h"

KANS_(Phaon)

class PHR_Runtime_Scope;

class PHR_Scope_System
{
 PHR_Runtime_Scope* current_scope_;
 QQueue<PHR_Runtime_Scope*> phr_scope_queue_;

public:

 PHR_Scope_System();

 ACCESSORS(PHR_Runtime_Scope* ,current_scope)
 ACCESSORS__RGET(QQueue<PHR_Runtime_Scope*> ,phr_scope_queue)

 quint64 find_value_from_current_scope(QString key, PHR_Type** rty = nullptr);

 PHR_Type* get_type_for_symbol_name(QString sym);
};

_KANS(Phaon)

#endif //PHR_SCOPE_SYSTEM__H

