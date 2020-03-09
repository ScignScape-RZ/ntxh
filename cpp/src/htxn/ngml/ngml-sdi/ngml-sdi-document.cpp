
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "ngml-sdi-document.h"

#include "ntxh-parser/ntxh-document.h"

#include "global-types.h"

typedef NTXH_Graph::hypernode_type hypernode_type;

NGML_SDI_Document::NGML_SDI_Document(QString path)
  :  path_(path), global_base_line_skip_(12)
{
}

void NGML_SDI_Document::parse_paragraph_start_hypernode(const NTXH_Graph& g, hypernode_type* h)
{
 qDebug() << "parse_paragraph_start_hypernode()";
}

void NGML_SDI_Document::parse_paragraph_end_hypernode(const NTXH_Graph& g, hypernode_type* h)
{
 qDebug() << "parse_paragraph_end_hypernode()";
}

void NGML_SDI_Document::parse_info_hypernode(const NTXH_Graph& g, hypernode_type* h)
{
 qDebug() << "parse_info_hypernode()";
}


void NGML_SDI_Document::parse()
{
 QMap<QString, void(NGML_SDI_Document::*)(const NTXH_Graph&, hypernode_type*)> methods {
  {"Info", &NGML_SDI_Document::parse_info_hypernode},
  {"Paragraph:Start",
    &NGML_SDI_Document::parse_paragraph_start_hypernode},
  {"Paragraph:End",
    &NGML_SDI_Document::parse_paragraph_end_hypernode},
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
  g.get_sf(h, 1, [this, &methods, g, h](QPair<QString, void*>& pr)
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

}
