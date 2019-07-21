
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "language-sample.h"

#include "language-sample-group.h"

#include "phaong/phaong-types.h"

#include <QDebug>
#include <QTextStream>

#include "textio.h"

#include "ntxh-builder/ntxh-builder.h"


USING_KANS(DSM)
USING_KANS(HGDMCore)
USING_KANS(TextIO)



Language_Sample::Language_Sample(Language_Sample_Group* group, QString text)
  :  text_(text), group_(group)
{
// phg.new_hypernode(this, 6, {"Language_Sample", nullptr});

// {
//  int phaong_data_index = 0;
//  phg.PHAONG_DATA(QString ,text);
//  phg.PHAONG_DATA(QString ,source_title);
//  phg.PHAONG_DATA(int ,index);
//  phg.PHAONG_DATA(QString ,sub_index);
//  phg.PHAONG_DATA(int ,chapter);
//  phg.PHAONG_DATA(int ,page);
// }

}

QString Language_Sample::get_form()
{
 if(classification_.isEmpty())
   return "Text";
 int index = classification_.indexOf(':');
 if(index == -1)
 {
  return classification_;
 }
 return classification_.left(index);
}

QString Language_Sample::get_issue()
{
 if(classification_.isEmpty())
   return "(N_A)";
 int index = classification_.indexOf(':');
 if(index == -1)
 {
  return "(N_A)";
 }
 return classification_.mid(index + 1);
}

void Language_Sample::serialize(QTextStream& qts)
{
 NTXH_Builder ntb(qts);
 ntb.enter("SE");

 if(!latex_label_.isEmpty())
 {
  ntb.sf("x", latex_label_);
 }
 ntb.msf("t", text_);

 ntb.leave();

 qts << "!/ SE";

}

//int Language_Sample::get_group_id()
//{
// if(group_)
// {
//  return group_->id();
// }
// return 0;
//}

