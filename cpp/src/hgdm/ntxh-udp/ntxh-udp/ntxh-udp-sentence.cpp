
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "ntxh-udp-sentence.h"

#include <QDebug>
#include <QTextStream>

#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QStack>

NTXH_UDP_Sentence::NTXH_UDP_Sentence(sentence* udp_sentence)
  : udp_sentence_(udp_sentence)
{

}

void NTXH_UDP_Sentence::report_text(QTextStream& qts)
{
// // // todo ...
// QString rep;
// for(word w : udp_sentence_->words)
// {
// }
// qts << rep << "\n";
}

void NTXH_UDP_Sentence::write_sxp_edges(QTextStream& qts,
  QString templat, QString rtemplat, int root_num)
{
 qts << rtemplat.arg(root_num).arg("root");

 for(NTXH_UDP_SXP_Rel_Pair& pr : sxp_vector_)
 {
  QString rel = QString("%1%2").arg(pr.rel.unw).arg(pr.rel.pos);
  qts << templat.arg(pr.rel.sxp_index).arg(pr.sxp_index).arg(rel);
 }
}


void NTXH_UDP_Sentence::write_edges(QTextStream& qts, QString templat, QString rtemplat)
{
 for(word w : udp_sentence_->words)
 {
  if(w.id == 0)
    continue;

  int h = w.head;

  if(h > 0)
    qts << templat.arg(w.id).arg(h).arg(QString::fromStdString(w.deprel));
  else if(h == 0)
    qts << rtemplat.arg(w.id).arg(QString::fromStdString(w.deprel));
 }
}

void NTXH_UDP_Sentence::join_sxp_text(QTextStream& qts,
  QString sep, QString end, Join_Field_Codes j)
{
 int i = 0;
 int max = sxp_texts_.size();
 for(QPair<QString, int>& pr : sxp_texts_)
 {
  ++i;
  word w = udp_sentence_->words[pr.second];

  QString text;

  switch (j)
  {
  case Join_Field_Codes::Text:
   text = pr.first;
   break;
  case Join_Field_Codes::UPOS:
   text = QString::fromStdString(w.upostag);
   break;
  case Join_Field_Codes::XPOS:
   text = QString::fromStdString(w.xpostag);
   break;
  }

  text.replace("$", "\\$");
  text.replace("->", "{\\arrwhich}");

  if(i == max)
    qts << text << end;
  else
    qts << text << sep;
 }
}

void NTXH_UDP_Sentence::join_text(QTextStream& qts, QString sep, QString end, Join_Field_Codes j)
{
 int max = udp_sentence_->words.size() - 1;
 for(word w : udp_sentence_->words)
 {
  if(w.id == 0)
    continue;
  QString text;

  switch (j)
  {
  case Join_Field_Codes::Text:
   //?text = wp.text();
   text = QString::fromStdString(w.form);
   break;
  case Join_Field_Codes::UPOS:
   text = QString::fromStdString(w.upostag);
   break;
  case Join_Field_Codes::XPOS:
   text = QString::fromStdString(w.xpostag);
   break;
  }

  text.replace("$", "\\$");

  if(w.id == max)
    qts << text << end;
  else
    qts << text << sep;
 }
}


void NTXH_UDP_Sentence::report_text()
{
// // // todo ...
// QString rep;
// for(word w : udp_sentence_->words)
// {
// }
// qDebug() << rep;
}

int NTXH_UDP_Sentence::get_id_by_word(QString qw, int which)
{
 int count = 0;
 for(word w : udp_sentence_->words)
 {
  if(w.form == qw.toStdString())
  {
   if(which == 0)
     return w.id;
   ++count;
   if(count == which)
     return w.id;
  }
 }
 return 0;
}

QString NTXH_UDP_Sentence::get_dep_by_word(QString qw, int which)
{
 int count = 0;
 for(word w : udp_sentence_->words)
 {
  if(w.form == qw.toStdString())
  {
   if(count == which)
     return QString::fromStdString(w.deprel);
   ++count;
  }
 }
 return QString();
}


void NTXH_UDP_Sentence::write_latex(QTextStream& qts)
{
 qts << "\n\\begin{dependency}\n\\begin{deptext}\n";

 join_text(qts, " \\& ", " \\\\");
 qts << "\n";
 join_text(qts, " \\& ", " \\\\", NTXH_UDP_Sentence::Join_Field_Codes::UPOS);
 qts << "\n";
 join_text(qts, " \\& ", " \\\\", NTXH_UDP_Sentence::Join_Field_Codes::XPOS);
 qts << "\n\\end{deptext}\n\n";

 write_edges(qts, "\\depedge{%1}{%2}{%3}\n", "\\deproot{%1}{%2}\n");

 qts << "\n\n\\end{dependency}\n";

 QString sx = sxp_text_;
 if(!sx.isEmpty())
 {
  sx.replace("$", "\\$");
  sx.replace("->", "{\\arrwhich}");

  qts << "\n" << sx << "\n";


  qts << "\n\\begin{dependency}\n\\begin{deptext}\n";

  join_sxp_text(qts, " \\& ", " \\\\");
  qts << "\n";
  join_sxp_text(qts, " \\& ", " \\\\", NTXH_UDP_Sentence::Join_Field_Codes::UPOS);
  qts << "\n";
  join_sxp_text(qts, " \\& ", " \\\\", NTXH_UDP_Sentence::Join_Field_Codes::XPOS);

  qts << "\n\\end{deptext}\n\n";

  write_sxp_edges(qts, "\\depedge[edge below]{%1}{%2}{%3}\n",
    "\\deproot[edge below]{%1}{%2}\n");
  qts << "\n\n\\end{dependency}\n";

 }
}

void NTXH_UDP_Sentence::check_comments()
{
 for(std::string c : udp_sentence_->comments)
 {
  QString qs = QString::fromStdString(c);
  if(qs.startsWith("#sxp:"))
  {
   sxp_text_ = qs.mid(5).trimmed();
   parse_sxp(sxp_text_);
  }
  if(qs.startsWith("#ltx:"))
  {
   latex_out_file_ = qs.mid(5).trimmed();
  }
 }
}

void NTXH_UDP_Sentence::parse_sxp(QString sxp, QVector<NTXH_UDP_SXP_Rel_Pair>& qvec,
  QVector<QPair<QString, int>>& sxp_texts)
{
 QRegularExpression rx = QRegularExpression("(\\(|\\)|[^()\\s]+|\\s+)");
 int pos = 0;

 int opc = 0;
 int cpc = 0;

 QMap<QString, int> counts;

 QStack<int> pos_stack;

 NTXH_UDP_SXP_Rel current_ch = {QString(), 0, 0, 0, 0, 0, 0};
 QStack<NTXH_UDP_SXP_Rel> ch_stack;

 while(pos < sxp.length())
 {
  QRegularExpressionMatch rxm = rx.match(sxp, pos);
  if(!rxm.hasMatch())
   break;
  QString qs = rxm.captured();
  pos += qs.length();
  qs = qs.trimmed();
  if(!qs.isEmpty())
  {
   if(qs == '(')
   {
    ++opc;
    continue;
   }
   else if(qs == ')')
   {
    ++cpc;
    continue;
   }
   else if(qs.trimmed().isEmpty())
     continue;

   int which = 0;
   if(qs.endsWith("->@"))
   {
    qs.chop(3);
    which = ++counts[qs];
   }
   else
   {
    ++counts[qs];
   }

   sxp_texts.push_back({qs, which});

   if(cpc > 0)
   {
    int unw = current_ch.unw;
//?    int max = current_ch.max_unw;
    for(int i = 0; i < cpc; ++i)
    {
     current_ch = ch_stack.pop();
    }
    unw = current_ch.unw;
    ++current_ch.pos;
    if(opc == 0)
    {
     qDebug() << QString("\n%1 : %2 (%3-%4)").
        arg(current_ch.chief).arg(qs).arg(current_ch.unw).arg(current_ch.pos);
     qvec.push_back({qs, which, 0, sxp_texts.size(), current_ch});
     ++current_ch.pos;
    }
   }
   if(opc > 0)
   {
    if(!current_ch.chief.isEmpty())
    {
     qDebug() << QString("\n%1 : %2 (%3-%4)").
        arg(current_ch.chief).arg(qs).arg(current_ch.unw).arg(current_ch.pos);
     qvec.push_back({qs, which, 0, sxp_texts.size(), current_ch});
    }
    ch_stack.push(current_ch);
    if(opc > 1)
    {
     for(int i = opc; i > 1; --i)
     {
      ch_stack.push({qs, which, 0, i, opc, 0, sxp_texts.size()});
     }
    }
    current_ch = {qs, which, 0, 1, opc, 1, sxp_texts.size()};
    opc = 0;
    cpc = 0;
   }
   else if(cpc > 0)
   {
    cpc = 0;
    continue;
   }
   else
   {
    qDebug() << QString("\n%1 : %2 (%3-%4)").
       arg(current_ch.chief).arg(qs).arg(current_ch.unw).arg(current_ch.pos);
    qvec.push_back({qs, which, 0, sxp_texts.size(), current_ch});
    ++current_ch.pos;
   }
  }
 }
}

void NTXH_UDP_Sentence::check_parse_sxp()
{
 if(!sxp_text_.isEmpty())
   parse_sxp(sxp_text_);
}


void NTXH_UDP_Sentence::parse_sxp(QString sxp)
{
 parse_sxp(sxp, sxp_vector_, sxp_texts_);
 for(NTXH_UDP_SXP_Rel_Pair& pr : sxp_vector_)
 {
  int i1 = get_id_by_word(pr.text, pr.which);
  int i2 = get_id_by_word(pr.rel.chief, pr.rel.which);
  pr.index = i1;
  pr.rel.index = i2;
 }

 for(QPair<QString, int>& pr : sxp_texts_)
 {
  int id = get_id_by_word(pr.first, pr.second);
  if(pr.second > 0)
    pr.first += QString("->%1").arg(pr.second);
  pr.second = id;
 }
}

