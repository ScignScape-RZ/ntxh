
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef LANGUAGE_SAMPLE_GROUP__H
#define LANGUAGE_SAMPLE_GROUP__H

#include "kans.h"
#include "accessors.h"

#include <QVector>
#include <QString>

class QTextStream;

KANS_(DSM)

class Language_Sample;

class Language_Sample_Group : public QVector<Language_Sample*>
{
 int id_;
 int page_;

 int section_num_;
 int start_num_;
 int end_num_;

 QString classification_;

 QString text_id_;


public:

 Language_Sample_Group(int id);


 ACCESSORS(int ,id)
 ACCESSORS(int ,page)

 ACCESSORS(int ,section_num)

 ACCESSORS(int ,start_num)
 ACCESSORS(int ,end_num)
 ACCESSORS(QString ,classification)
 ACCESSORS(QString ,text_id)

 void serialize(QTextStream& qts);

 static void serialize_samples_to_file(QVector<Language_Sample_Group*>& lsgs, QString file);

 QString get_main_text();
 QString get_main_archival_or_text();
 QString get_main_pre();
 QString get_main_post();

 QString get_form();
 QString get_issue();


};


_KANS(DSM)

#endif // LANGUAGE_SAMPLE_GROUP__H
