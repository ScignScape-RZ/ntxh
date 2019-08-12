
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DATASET__H
#define DATASET__H

#include "phaong/phaong.h"
#include "phaong/phaong-types.h"

#include "qring/qring-file-structure.h"


#include "kans.h"
#include "accessors.h"

#include <QVector>
#include <QString>
#include <QMap>

#define PASTE_EXPRESSION(...) __VA_ARGS__


KANS_(DSM)

class Language_Sample;
class Language_Sample_Group;

class Dataset :  public QRing_File_Structure
{
 QString file_;
 QString pdf_path_;
 QString subdocument_kind_;

 QVector<Language_Sample*> samples_;

// QVector<int> chapter_pages_;
 QVector<Language_Sample_Group*> groups_;

 QStringList issues_;
 QStringList forms_;

 QVector<QPair<QPair<QString, int>, QPair<int, int>>> subdocuments_;

public:

 Dataset(QString root_folder = QString());//QString file);

 ACCESSORS__RGET(QVector<Language_Sample*> ,samples)
 ACCESSORS__RGET(QVector<Language_Sample_Group*> ,groups)

 ACCESSORS__RGET(QStringList ,issues)
// ACCESSORS__RGET(QStringList ,forms)

 ACCESSORS(QString ,file)
 ACCESSORS(QString ,pdf_path)
 ACCESSORS(QString ,subdocument_kind)

 ACCESSORS__RGET(PASTE_EXPRESSION(QVector<QPair<QPair<QString, int>,
    QPair<int, int>>>) ,subdocuments)


 void save_raw_file(QString text, int page, int num);
 void parse_to_samples(QString text, int page, int num, phaong<pg_t>& phg);

 void save_to_file();
 void get_serialization(QString& text, QString& gtext);

 void load_from_file(QString path);
 void save_to_file(QString path);

 void save_to_file_udp();
 void save_to_file_udp(QString path, QString upath, QString ppath);


};


_KANS(DSM)

#endif // DATASET__H
