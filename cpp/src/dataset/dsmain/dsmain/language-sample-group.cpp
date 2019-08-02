
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "language-sample-group.h"

#include "language-sample.h"

#include <QDebug>

#include "textio.h"

#include <QTextStream>

#include "ntxh-builder/ntxh-builder.h"

USING_KANS(DSM)
USING_KANS(HGDMCore)

USING_KANS(TextIO)

Language_Sample_Group::Language_Sample_Group(int id)
  :  id_(id), page_(0), section_num_(0), start_num_(0), end_num_(0)
{

}

QString Language_Sample_Group::get_form()
{
 if(classification_.isEmpty())
 {
  if(isEmpty())
    return "Text";
  return first()->get_form();
 }
 int index = classification_.indexOf(':');
 if(index == -1)
 {
  return classification_;
 }
 return classification_.left(index);
}

QString Language_Sample_Group::get_issue()
{
 if(classification_.isEmpty())
 {
  if(isEmpty())
    return "(N_A)";
  return first()->get_issue();
 }
 int index = classification_.indexOf(':');
 if(index == -1)
 {
  return "(N_A)";
 }
 return classification_.mid(index + 1);
}


void Language_Sample_Group::serialize(QTextStream& qts)
{
 NTXH_Builder ntb(qts);
 ntb.enter("SG");
 ntb.nsf("i", id_);

 ntb.el();
 for(Language_Sample* ls : *this)
 {
  ls->serialize(qts);
  ntb.array_append();
  ntb.el();
 }
 ntb.el();


 ntb.nsf("s", page_, start_num_, end_num_);

 ntb.leave();
 ntb.top_append();

 ntb.el();
}

QString Language_Sample_Group::get_main_archival_or_text()
{
 if(isEmpty())
   return QString();
 return first()->archival_or_text();
}

QString Language_Sample_Group::get_main_pre()
{
 if(isEmpty())
   return QString();
 return first()->pre();
}

QString Language_Sample_Group::get_main_post()
{
 if(isEmpty())
   return QString();
 return first()->post();
}

QString Language_Sample_Group::get_main_text()
{
 if(isEmpty())
   return QString();
 return first()->text();
}


void Language_Sample_Group::serialize_samples_to_file(
  QVector<Language_Sample_Group*>& lsgs, QString file)
{
// QString text;
// QTextStream qts(&text);
}

