
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef HTXN_INFOSET_RANGE__H
#define HTXN_INFOSET_RANGE__H

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
class HTXN_Node_Detail;

class HTXN_Infoset_Range 
{ 
 u4 enter_;
 u4 leave_;

 u4 layer_id_;

 void* input_data_;

 HTXN_Node_Detail* node_detail_;

 QString classifier_;

public:

 HTXN_Infoset_Range(u4 enter, u4 leave, u4 layer_id);
 HTXN_Infoset_Range(QString cl, u4 enter, u4 leave, u4 layer_id);

 ACCESSORS(u4 ,enter)
 ACCESSORS(u4 ,leave)
 ACCESSORS(u4 ,layer_id)
 ACCESSORS(void* ,input_data)
 ACCESSORS(HTXN_Node_Detail* ,node_detail)
 ACCESSORS(QString ,classifier)

 template<typename T>
 T* input_data_as()
 {
  return (T*) input_data_;
 }

};



_KANS(HTXN)

#endif // HTXN_INFOSET_RANGE__H
