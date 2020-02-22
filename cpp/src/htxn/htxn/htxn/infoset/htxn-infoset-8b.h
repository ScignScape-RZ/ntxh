
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef HTXN_INFOSET_8B__H
#define HTXN_INFOSET_8B__H

#include "accessors.h"

#include "global-types.h"

#include "flags.h"

#include "kans.h"

#include <QString>
#include <QList>
#include <QDate>

#include <functional>


class QTextStream;

KANS_(HTXN)

class Glyph_Layer_8b;
class HTXN_Document_8b;

class HTXN_Infoset_8b 
{ 
 HTXN_Document_8b* htxn_document_;

public:

 HTXN_Infoset_8b(HTXN_Document_8b* htxn_document);
};



_KANS(HTXN)

#endif // HTXN_INFOSET_8B__H
