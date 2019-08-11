
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef LANGUAGE_SAMPLE__H
#define LANGUAGE_SAMPLE__H


#include "phaong/phaong.h"
#include "phaong/phaong-types.h"


#include "kans.h"
#include "accessors.h"

#include <QVector>
#include <QString>

class QTextStream;


KANS_(DSM)

class Language_Sample_Group;

class Language_Sample
{
 quint32 id_;
 QString text_;
 QString latex_label_;

 Language_Sample_Group* group_;
 QString classification_;
 quint32 page_;

 QString udp_source_;
 QString udp_label_;

 QString pre_;
 QString post_;

 QString archival_;

 QString subindex_;
 QString speaker_;
 QString annotation_mark_;
 QString alternate_;

public:

 Language_Sample(Language_Sample_Group* group, QString text);

 ACCESSORS(QString ,text)
 ACCESSORS(QString ,latex_label)
 ACCESSORS(QString ,classification)
 ACCESSORS(quint32 ,id)
 ACCESSORS(quint32 ,page)

 ACCESSORS(QString ,udp_label)
 ACCESSORS(QString ,udp_source)

 ACCESSORS(QString ,pre)
 ACCESSORS(QString ,post)
 ACCESSORS(QString ,archival)


 ACCESSORS(QString ,subindex)
 ACCESSORS(QString ,speaker)
 ACCESSORS(QString ,annotation_mark)
 ACCESSORS(QString ,alternate)

 ACCESSORS(Language_Sample_Group* ,group)

 QString get_form();
 QString get_issue();

 static void clean(QString& qs);

 QString parse_classification(QString key);

 void serialize(QTextStream& qts);
 void serialize_udp(int gid, QTextStream& qts, QString& udp);

 QString archival_or_text();

};


_KANS(DSM)

#endif // LANGUAGE_SAMPLE__H
