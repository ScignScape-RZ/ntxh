
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dataset.h"

#include "language-sample.h"

#include "language-sample-group.h"

#include "phaong/phaong.h"
#include "phaong/phaong-types.h"


//#include "relae-phaon/kernel/graph/relae-phaon-node.h"
//#include "relae-phaon/kernel/frame/relae-phaon-frame.h"
//#include "relae-phaon/kernel/query/relae-phaon-query.h"
//#include "relae-phaon/kernel/graph/relae-phaon-graph.h"
//#include "ds-relae-phaon/rph-document.h"


#include "ntxh-parser/ntxh-document.h"

#include "textio.h"

#include <QDateTime>


USING_KANS(DSM)
USING_KANS(TextIO)

Dataset::Dataset() 
{
//
 forms_ = QStringList{{"Text", "Dialog", "Intonation", "Fragment", "Paragraph"}};
 issues_ = QStringList{{"Ambiguity", "Context", "Logic",
            "Scope", "Polarity", "Belief", "Syntax", "Semantics", "Pragmatics",
            "Convention", "Idioms", "Lexical", "Idiomatic", "Reference",
 "Ontological", //"Rhetoric"
 }};
}

bool check(QPair<QString, void*>& pr)
{
 if(pr.first.isEmpty())
   return pr.second;
 return true;
};

void Dataset::save_to_file(QString path)
{
 Language_Sample_Group::serialize_samples_to_file(groups_, path);
}

void Dataset::save_to_file()
{
 save_to_file(file_ + ".out.txt");
}

void Dataset::save_to_file_udp()
{
 save_to_file_udp(file_ + ".udp.ntxh", file_ + ".conllu", file_ + ".pre.txt");
}

void Dataset::save_to_file_udp(QString path, QString upath, QString ppath)
{
 QFile outfile(path);
 if (!outfile.open(QIODevice::WriteOnly | QIODevice::Text))
   return;
 QTextStream outstream(&outfile);

 QFile uo(upath);
 if (!uo.open(QIODevice::WriteOnly | QIODevice::Text))
   return;
 QTextStream uos(&uo);

 QFile po(ppath);
 if (!po.open(QIODevice::WriteOnly | QIODevice::Text))
   return;
 QTextStream pos(&po);

 for(Language_Sample_Group* g : groups_)
 {
  for(Language_Sample* ls : *g)
  {
   QString u;
   ls->serialize_udp(g->id(), outstream, u);
   uos << u;
   uos << "\n\n";
   QString aot = ls->archival_or_text().simplified();
   Language_Sample::clean(aot);
   pos << aot << "\n";
  }
 }

 outfile.close();
 uo.close();
 po.close();
}

void Dataset::load_from_file(QString path)
{
 file_ = path;

 NTXH_Document doc(path);

 doc.parse();

 typedef NTXH_Graph::hypernode_type hypernode_type;

 NTXH_Graph& g = *doc.graph();
// const QVector<hypernode_type*>& v = g.hypernodes();


// RPH_Graph::hypernode_type* hn = doc.graph()->hypernodes()[0];

 QVector<NTXH_Graph::hypernode_type*>& hns = doc.top_level_hypernodes();

 groups_.resize(hns.size());

 int count = 0;

 std::transform(hns.begin(), hns.end(), groups_.begin(), [&count,&doc](NTXH_Graph::hypernode_type* hn)
 {
  ++count;
  Language_Sample_Group* result = new Language_Sample_Group(count);

//  doc.graph()->get_sfs(hn, {1,2,3}, [result](QVector<QPair<QString, void*>>& prs)

  doc.graph()->get_sfsr(hn, {{1,3}}, [result](QVector<QPair<QString, void*>>& prs)
  {
   QVector<quint16> nums = {0,0,0};
   std::transform(prs.begin(), prs.end(), nums.begin(), [](QPair<QString, void*>& pr)
   {
    return pr.first.toInt();
   });
   result->set_id(nums[0]);
//   result->set_start_num(nums[1]);
//   result->set_end_num(nums[2]);
   result->set_page(nums[1]);
   result->set_section_num(nums[2]);

  });

  doc.graph()->all_afs(hn, [&doc, result](QPair<QString, void*>& pr)
  {
   NTXH_Graph::hypernode_type* ihn = (NTXH_Graph::hypernode_type*) pr.second;
   if(ihn)
   {
    Language_Sample* ls = nullptr;
    doc.graph()->get_sfsr(ihn, {{1,10}}, [result, &ls](QVector<QPair<QString, void*>>& prs)
    {
     {QPair<QString, void*>& ipr = prs[3];
      if(check(ipr))
        ls = new Language_Sample(result, ipr.first);}
     {QPair<QString, void*>& ipr = prs[0];
      if(check(ipr))
        ls->set_id(ipr.first.toInt());}
     {QPair<QString, void*>& ipr = prs[1];
      if(check(ipr))
        ls->set_page(ipr.first.toInt());}
     {QPair<QString, void*>& ipr = prs[2];
      if(check(ipr))
        ls->set_latex_label(ipr.first);}
     {QPair<QString, void*>& ipr = prs[4];
      if(check(ipr))
        ls->set_udp_source(ipr.first);}
     {QPair<QString, void*>& ipr = prs[5];
      if(check(ipr))
        ls->set_udp_label(ipr.first);}
     {QPair<QString, void*>& ipr = prs[6];
      if(check(ipr))
        ls->set_pre(ipr.first);}
     {QPair<QString, void*>& ipr = prs[7];
      if(check(ipr))
        ls->set_post(ipr.first);}
     {QPair<QString, void*>& ipr = prs[8];
      if(check(ipr))
        ls->set_archival(ipr.first);}
     {QPair<QString, void*>& ipr = prs[9];
      if(check(ipr))
        ls->set_classification(ipr.first);}
    });

//    doc.graph()->get_sf(ihn, 4, [result, &ls](QPair<QString, void*>& ipr)
//    {
//     ls = new Language_Sample(result, ipr.first);
//    });

//    doc.graph()->get_sf(ihn, 3, [ls](QPair<QString, void*>& ipr)
//    {
//     if(check(ipr))
//       ls->set_latex_label(ipr.first);
//    });

//    doc.graph()->get_sf(ihn, 1, [ls](QPair<QString, void*>& ipr)
//    {
//     if(check(ipr))
//       ls->set_id(ipr.first.toInt());
//    });

//    doc.graph()->get_sf(ihn, 2, [ls](QPair<QString, void*>& ipr)
//    {
//     if(check(ipr))
//       ls->set_page(ipr.first.toInt());
//    });

    result->push_back(ls);
   }
  });

  return result;
 });
}


void Dataset::save_raw_file(QString text, int page, int num)
{
 QString dt = QDateTime::currentDateTime().toString("dd-MM-yy--hh-mm");
 QString path = QString("%1.%2.%3.%4.txt").arg(file_)
   .arg(page).arg(num).arg(dt);
 save_file(path, text);
}

void Dataset::get_serialization(QString& text, QString& gtext)
{
 for(Language_Sample* samp : samples_)
 {
  //?text += samp->get_serialization() + "\n";
 }

 int rgc = 0;
 for(Language_Sample_Group* g : groups_)
 {
  //?gtext += g->get_serialization(rgc);
 }


// QMap<int, Language_Sample_Group*> gm;
// int sz = groups_.size();
// QMapIterator<QString, Language_Sample_Group*> it(groups_);
// while(it.hasNext())
// {
//  it.next();
//  Language_Sample_Group* g = it.value();
//  int id = g->id();
//  gm[id] = g;
// }

// for(int i = 0; i < sz; ++i)
// {
//  Language_Sample_Group* g = gm[i + 1];
//  gtext += g->get_serialization();
// }


}

//void Dataset::save_to_file()
//{
// QString text;
// QString gtext;
// get_serialization(text, gtext);
// QString dt = QDateTime::currentDateTime().toString("dd-MM-yy--hh-mm");
// QString path = QString("%1.%2.txt").arg(file_).arg(dt);
// save_file(path, text);

// QString gpath = QString("%1.%2.g.txt").arg(file_).arg(dt);
// save_file(gpath, gtext);

//}

void Dataset::parse_to_samples(QString text, int page,
  int num, phaong<pg_t>& phg)
{
#ifdef HIDE

 int current_page = page;
 int current_index = num;
 QString current_sub_index;

 QStringList qsl = text.split("\n");
 for(QString qs : qsl)
 {
  if(qs.isEmpty())
    continue;
  if(qs.startsWith('@'))
  {
   current_page = qs.mid(1).toInt();
   continue;
  }
  if(qs.startsWith('#'))
  {
   current_index = qs.mid(1).toInt();
   continue;
  }
  if(qs.size() < 3)
    continue;
  if( (qs[1] == '.') || (qs[1] == ')') )
  {
   current_sub_index = qs[0];
   qs = qs.mid(2);
  }
  else if( (qs[2] == '.') || (qs[2] == ')') )
  {
   current_sub_index = qs.left(2);
   qs = qs.mid(3);
  }
  else if( (qs[3] == '.') || (qs[3] == ')') )
  {
   current_sub_index = qs.left(3);
   qs = qs.mid(4);
  }
  Language_Sample* samp = new Language_Sample(qs.simplified(), phg);
  samp->set_page(current_page);
  samp->set_index(current_index);
  samp->set_sub_index(current_sub_index);
  samp->set_chapter(get_chapter_number_from_page(current_page));

  samples_.push_back(samp);
 }
#endif // HIDE
}