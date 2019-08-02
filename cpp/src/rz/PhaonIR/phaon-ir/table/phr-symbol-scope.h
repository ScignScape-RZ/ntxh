
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_SYMBOL_SCOPE__H
#define PHR_SYMBOL_SCOPE__H


#include "kans.h"

#include <QString>
#include <QMap>

#include "accessors.h"

#include "phr-function-vector.h"

KANS_(Phaon)


class PHR_Namespace;
class PHR_Runtime_Scope;
class PHR_Function;

class PHR_Symbol_Scope
{
protected:
 PHR_Runtime_Scope* runtime_scope_;

public:

 PHR_Symbol_Scope(PHR_Runtime_Scope* runtime_scope);

 void add_function(QString name, PHR_Function& phf);

 ACCESSORS(PHR_Runtime_Scope* ,runtime_scope)


};

_KANS(Phaon)


#endif //PHR_SYMBOL_SCOPE__H
