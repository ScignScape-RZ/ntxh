
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "ngml-sdi-document.h"

#include "ngml-sdi-element.h"
#include "ngml-sdi-page.h"

#include "ntxh-parser/ntxh-document.h"

#include "global-types.h"

#include "textio.h"

USING_KANS(TextIO)

#include <QDir>

typedef NTXH_Graph::hypernode_type hypernode_type;

NGML_SDI_Document::NGML_SDI_Document(QString path, QString folder)
  :  path_(path), folder_(folder), global_base_line_skip_(12)
{
}

NGML_SDI_Page* NGML_SDI_Document::get_page(u4 page)
{
 NGML_SDI_Page* result = pages_.value(page - 1);
 if(!result)
 {
  result = new NGML_SDI_Page(page);
  if(page >= pages_.size())
    pages_.resize(page);
  pages_[page - 1] = result;
 }
 return result;  
}

void NGML_SDI_Document::parse_element_start_hypernode(NTXH_Graph& g, hypernode_type* hn)
{
 NGML_SDI_Element* nsel = new NGML_SDI_Element();
 g.get_sfsr(hn, {{2,10}}, [this, nsel](QVector<QPair<QString, void*>>& prs)
 {
  //:n:1 :i:2 :o:3 :c:4 :r:5 :k:6 :p:8 :x:9 :y:10 :b:7 ;
  u4 id = prs[0].first.toInt();
  nsel->set_id(id);
  this->open_elements_[{"NGML_SDI_Element", id}] = nsel;

  nsel->set_kind(prs[4].first);

  u4 start_x = prs[7].first.toInt();
  u4 start_y = prs[8].first.toInt();
  if(prs[5].first.isEmpty())
    start_y -= (u4) this->global_base_line_skip_;    

  nsel->set_start_x(start_x);
  nsel->set_start_y(start_y);
 
  u4 pg = prs[6].first.toInt();
  NGML_SDI_Page* page = this->get_page(pg);
  page->add_page_element(nsel);   
 });

// qDebug() << "parse_element_start_hypernode()";
}

void NGML_SDI_Document::parse_element_end_hypernode(NTXH_Graph& g, hypernode_type* hn)
{
 g.get_sfsr(hn, {{2,6}}, [this](QVector<QPair<QString, void*>>& prs)
 {
  //:i:2 :o:3 :p:4 :x:5 :y:6 ;
  u4 id = prs[0].first.toInt();

  void* pv = this->open_elements_.value({"NGML_SDI_Element", id});
  if(!pv)
    return;
  NGML_SDI_Element* nsel = static_cast<NGML_SDI_Element*>(pv);
  u4 end_x = prs[3].first.toInt();
  u4 end_y = prs[4].first.toInt();
  nsel->set_end_x(end_x);
  nsel->set_end_y(end_y);
 });
// qDebug() << "parse_element_end_hypernode()";
}

void NGML_SDI_Document::parse_paragraph_start_hypernode(NTXH_Graph& g, hypernode_type* hn)
{
 qDebug() << "parse_paragraph_start_hypernode()";
}

void NGML_SDI_Document::parse_paragraph_end_hypernode(NTXH_Graph& g, hypernode_type* hn)
{
 qDebug() << "parse_paragraph_end_hypernode()";
}

void NGML_SDI_Document::parse_info_hypernode(NTXH_Graph& g, hypernode_type* hn)
{
 qDebug() << "parse_info_hypernode()";
}


void NGML_SDI_Document::parse()
{
 QMap<QString, void(NGML_SDI_Document::*)(NTXH_Graph& g, hypernode_type*)> methods {
  {"Info", &NGML_SDI_Document::parse_info_hypernode},

  {"Paragraph:Start",
    &NGML_SDI_Document::parse_paragraph_start_hypernode},

  {"Paragraph:End",
    &NGML_SDI_Document::parse_paragraph_end_hypernode},

  {"Element:Start",
    &NGML_SDI_Document::parse_element_start_hypernode},

  {"Element:End",
    &NGML_SDI_Document::parse_element_end_hypernode},

//"Sentence:Start"
//"Sentence:End"
//"Sentence:Start"
//"Sentence:End"
//"Paragraph:End"
 };

 NTXH_Document doc(path_);

 doc.parse();

 typedef NTXH_Graph::hypernode_type hypernode_type;

 NTXH_Graph& g = *doc.graph();
 const QVector<hypernode_type*>& v = g.hypernodes();

 u4 i = 0;

// u8 bls = 12; // default ... 

 for(hypernode_type* h : v)
 {
//  QString name;
  g.get_sf(h, 1, [this, &methods, &g, h](QPair<QString, void*>& pr)
  {
   auto it = methods.find(pr.first);
   if(it != methods.end())
   {
    (this->**it)(g, h);
   }
  });

//  g.get_sf(h, 2, [](QPair<QString, void*>& pr)
//  {
//   sent.set_corpus_name(pr.first);
//  });

#ifdef HIDE
  g.get_sf(h, 3, [](QPair<QString, void*>& pr)
  {
//   sent.set_sxp_text(pr.first);
  });

  g.get_sf(h, 4, [](QPair<QString, void*>& pr)
  {
//   sent.set_latex_out_file(pr.first);
  });

  g.get_sf(h, 5, [](QPair<QString, void*>& pr)
  {
//   qts << pr.first << "\n\n";
  });
#endif
 } 

 output_pages();
}

void NGML_SDI_Document::output_pages()
{
 QDir qd(folder_);
 for(NGML_SDI_Page* page : pages_)
 {
  QString fn = QString::number(page->number());
  fn.prepend('p');
  fn.append(".txt");
  fn = qd.absoluteFilePath(fn);
  save_file(fn, "OK");
 }
}


