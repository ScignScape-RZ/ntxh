
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

//class TXH_UDP_Deprel_Callbacks;
//class TXH_UDP_Word_Pair;
//class TXH_UDP_Word_Group;

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

// QVector<NTXH_UDP_Word_Pos> word_poss_;
// QList<NTXH_UDP_Word_Pair*> pairs_;
// QMap<NTXH_UDP_Word_Pos*, QMap<QString, NTXH_UDP_Word_Group*>> groups_map_;
// QMap<QPair<QString, NTXH_UDP_Word_Pos*>, NTXH_UDP_Word_Group*> dwg_groups_map_;
// QVector<NTXH_UDP_Word_Group*> dwg_groups_;

 QVector<NTXH_UDP_SXP_Rel_Pair> sxp_vector_;
 QVector<QPair<QString, int>> sxp_texts_;
 QString sxp_text_;

 QString latex_out_file_;
 QString corpus_name_;

// NTXH_UDP_Word_Group* get_group(QString k, NTXH_UDP_Word_Pos* dgw);

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

 //?static void init_callbacks(NTXH_UDP_Deprel_Callbacks& cbs);

 void init_pairs();
//? void init_groups(const NTXH_UDP_Deprel_Callbacks& cbs);

 QString get_dep_by_word(QString qw, int which = 0);
 int get_id_by_word(QString qw, int which = 0);

// NTXH_UDP_Word_Pos* normalize_deps(QMap<QString, QList<NTXH_UDP_Word_Pos*>>& m);
// NTXH_UDP_Word_Pos* guess_dock_parents(const NTXH_UDP_Deprel_Callbacks& cbs);
// void resolve_parent_claims();
// NTXH_UDP_Word_Pos* get_usubject(NTXH_UDP_Word_Pos* dgw);
// QList<NTXH_UDP_Word_Pos*> get_uadv(NTXH_UDP_Word_Pos* dgw,
//    QMap<NTXH_UDP_Word_Pos*, QList<NTXH_UDP_Word_Pos*>>& advs);
// QList<NTXH_UDP_Word_Pos*> get_uadj(NTXH_UDP_Word_Pos* dgw);
// NTXH_UDP_Word_Pos* get_udeprel(NTXH_UDP_Word_Pos* dgw, QString dp);
// NTXH_UDP_Word_Pos* get_udeprel(NTXH_UDP_Word_Pos* dgw, const QSet<QString>& dps);
// QList<NTXH_UDP_Word_Pos*> get_udeprels(NTXH_UDP_Word_Pos* dgw, const QSet<QString>& dps);

// QString to_vstring(NTXH_UDP_Word_Pos* dgw);
// QString get_pos_tag(NTXH_UDP_Word_Pos* dgw);
// QString get_udeprel(NTXH_UDP_Word_Pos* dgw);

// TXH_UDP_Word_Pos* get_uhead(TXH_UDP_Word_Pos* dgw);

// TXH_UDP_Word_Group* check_init_group(QString k, TXH_UDP_Word_Pos* dgw, TXH_UDP_Word_Pos* hdgw);

// TXH_UDP_Word_Group* check_init_adv_group(TXH_UDP_Word_Pos* dgw, TXH_UDP_Word_Pos* hdgw);
// TXH_UDP_Word_Group* check_init_adj_group(TXH_UDP_Word_Pos* dgw, TXH_UDP_Word_Pos* hdgw);
// TXH_UDP_Word_Group* check_init_verb_group(TXH_UDP_Word_Pos* dgw, TXH_UDP_Word_Pos* hdgw);

// void init_adj_group_rep(TXH_UDP_Word_Group& dwgg);
// void init_adv_group_rep(TXH_UDP_Word_Group& dwgg);
// void init_verb_group_rep(TXH_UDP_Word_Group& dwgg);
// TXH_UDP_Word_Pos* check_default_init_group_rep(TXH_UDP_Word_Group& dwgg);

// TXH_UDP_Word_Pos* get_adv_rep(TXH_UDP_Word_Pos* dgw);
// TXH_UDP_Word_Pos* get_rep(QString k, TXH_UDP_Word_Pos* dgw);

 void init_group_reps();

// TXH_UDP_Word_Pos* find_group_rep_not_of_kind(QString k, TXH_UDP_Word_Pos* dgw);
// TXH_UDP_Word_Group* find_group_of_kind(QString k, TXH_UDP_Word_Pos* dgw);
// TXH_UDP_Word_Pos* find_group_rep_of_kind(QString k, TXH_UDP_Word_Pos* dgw);

// void internal_resolve_adj_group(TXH_UDP_Word_Pos* dgw, TXH_UDP_Word_Pos* hdgw);
// void resolve_internal_group_parents();
// void resolve_internal_group_parents(TXH_UDP_Word_Group& dwgg);
// void default_resolve_internal_group_parents(TXH_UDP_Word_Group& dwgg, bool left_assoc);
// void verb_resolve_internal_group_parents(TXH_UDP_Word_Group& dwgg);
// void set_as_parent(TXH_UDP_Word_Pos* c, TXH_UDP_Word_Pos* p,
//   int lvl, int pos);

// void set_as_group_indirect_parent(QString ck, TXH_UDP_Word_Pos* c, QString pk, TXH_UDP_Word_Pos* p,
//   int lvl, int pos);

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

// static void scan_sxp(const QVector<TXH_UDP_SXP_Rel_Pair>& qvec);

 static void parse_sxp(QString sxp, QVector<NTXH_UDP_SXP_Rel_Pair>& qvec,
   QVector<QPair<QString, int>>& sxp_texts);

// void set_verb_to_subject(int v, int s, int lvl);
// int get_adj(int n);


};


#endif
