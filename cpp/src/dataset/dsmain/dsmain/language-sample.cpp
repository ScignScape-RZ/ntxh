
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
  :  text_(text), group_(group), id_(0), page_(0)
{
}

QString Language_Sample::archival_or_text()
{
 if(archival_.isEmpty())
   return text_;
 return archival_;
}

QString Language_Sample::parse_classification(QString key)
{
 static QMap<QString, QString> static_map{{
   {{"txt"}, {"Text"}},
   {{"dlg"}, {"Dialog"}},
   {{"par"}, {"Paragraph"}},
   {{"syn"}, {"Syntax"}},
   {{"sem"}, {"Semantics"}},
   {{"pra"}, {"Pragmatics"}},
   {{"amb"}, {"Ambiguity"}},
   {{"sco"}, {"Scope"}},
   {{"lex"}, {"Lexical"}},
   {{"ref"}, {"Reference"}},
   {{"idi"}, {"Idiomatic"}},
   {{"log"}, {"Logic"}},

                                          }};

 if(static_map.contains(key))
   return static_map.value(key);
}


QString Language_Sample::get_form()
{
 if(classification_.isEmpty())
   return "Text";
 int index = classification_.indexOf(':');
 if(index == -1)
 {
  return "Text";
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
  return classification_;
 }
 return classification_.mid(index + 1);
}

void Language_Sample::clean(QString& qs)
{
 qs.replace("'", " '");
 qs.replace(".", " .");
 qs.replace("!", " !");
 qs.replace("?", " ?");
 qs.replace("(", " (");
 qs.replace(")", " )");
 qs.replace(")", " )");
 qs.replace("---{}", " - ");
 qs.replace(";", " ;");
 qs.replace(":", " :");
}

void Language_Sample::serialize_udp(int gid, QTextStream& qts, QString& udp)
{
 NTXH_Builder ntb(qts);
 ntb.enter("SI");
 ntb.sf("i", QString::number(id_));
 ntb.msf("t", text_);

 udp = QString("# sent_id = %1-%2").arg(gid).arg(id_);

 QString aot = archival_or_text().simplified();
 clean(aot);
 QStringList qsl = aot.split(' ');

 int i = 0;
 for(QString w : qsl)
 {
  ++i;
  udp += QString("\n%1\t%2\t_\t_\t_\t_\t_\t_\t_\t_").arg(i).arg(w);
 }

 ntb.msf("u", udp);

 ntb.leave();
 ntb.el();
}

void Language_Sample::serialize(QTextStream& qts)
{
 NTXH_Builder ntb(qts);
 ntb.enter("SI");

 if(!latex_label_.isEmpty())
 {
  ntb.sf("x", latex_label_);
 }
 ntb.msf("t", text_);

 ntb.leave();
}
