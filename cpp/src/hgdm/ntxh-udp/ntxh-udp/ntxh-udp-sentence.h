
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef NTXH_UDP_SENTENCE__H
#define NTXH_UDP_SENTENCE__H


#include "udpipe/udpipe.h"

//#include "dygred-word-pos.h"

#include <QVector>

#include "accessors.h"

class QTextStream;

struct NTXH_UDP_SXP_Rel
{
 QString chief;
 int which;
 int index;
 int unw;
 int max_unw;
 int pos;
 int sxp_index;
};

struct NTXH_UDP_SXP_Rel_Pair
{
 QString text;
 int which;
 int index;
 int sxp_index;
 NTXH_UDP_SXP_Rel rel;
};

class NTXH_UDP_Sentence
{
 quint16 id_;

 sentence* udp_sentence_;

 QVector<NTXH_UDP_SXP_Rel_Pair> sxp_vector_;
 QVector<QPair<QString, int>> sxp_texts_;
 QString sxp_text_;

 QString latex_out_file_;
 QString corpus_name_;

public:

 enum Join_Field_Codes {
   Text, UPOS, XPOS
 };

 explicit NTXH_UDP_Sentence(sentence* udp_sentence = nullptr);


 ACCESSORS__RGET(QVector<NTXH_UDP_SXP_Rel_Pair> ,sxp_vector)
 ACCESSORS(QString ,sxp_text)
 ACCESSORS(QString ,latex_out_file)
 ACCESSORS(QString ,corpus_name)
 ACCESSORS(quint16 ,id)
 ACCESSORS(sentence* ,udp_sentence)

 void init_pairs();

 QString get_dep_by_word(QString qw, int which = 0);
 int get_id_by_word(QString qw, int which = 0);

 void init_group_reps();

 void report_text();
 void report_text(QTextStream& qts);

 void join_text(QTextStream& qts, QString sep, QString end, Join_Field_Codes j = Join_Field_Codes::Text);
 void join_sxp_text(QTextStream& qts,
   QString sep, QString end, Join_Field_Codes j = Join_Field_Codes::Text);

 void write_edges(QTextStream& qts, QString templat, QString rtemplat);
 void write_sxp_edges(QTextStream& qts,
   QString templat, QString rtemplat, int root_num = 1);

 void check_comments();

 void write_latex(QTextStream& qts);

 void parse_sxp(QString sxp);
 void check_parse_sxp();

 static void parse_sxp(QString sxp, QVector<NTXH_UDP_SXP_Rel_Pair>& qvec,
   QVector<QPair<QString, int>>& sxp_texts);

};


#endif
