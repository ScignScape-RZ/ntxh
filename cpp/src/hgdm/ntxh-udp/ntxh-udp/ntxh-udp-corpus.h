
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef NTXH_UDP_CORPUS__H
#define NTXH_UDP_CORPUS__H


#include "ntxh-udp-sentence.h"

#include <QVector>

#include "qring/qring-file-structure.h"

class QTextStream;

class NTXH_UDP_Corpus : public QVector<NTXH_UDP_Sentence>,
  public QRing_File_Structure
{

public:

 NTXH_UDP_Corpus(QString root_folder);

 int detokenize(QString outfile);

 void report_sentence_texts();

 void report_sentence_texts(QTextStream& qts);

 void init_sentences();
 void check_comments();
 void check_write_latex();


};


#endif
