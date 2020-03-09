
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "ngml-sdi-document.h"

#include "ntxh-parser/ntxh-document.h"

#include "global-types.h"

NGML_SDI_Document::NGML_SDI_Document(QString path)
  :  path_(path)
{
}

void NGML_SDI_Document::parse()
{
 NTXH_Document doc(path_);

 doc.parse();

 typedef NTXH_Graph::hypernode_type hypernode_type;

 NTXH_Graph& g = *doc.graph();
 const QVector<hypernode_type*>& v = g.hypernodes();

 u4 i = 0;

 u8 bls = 12; // default ... 

 for(hypernode_type* h : v)
 {
//  QString name;
  g.get_sf(h, 1, [&bls](QPair<QString, void*>& pr)
  {
   QString name = pr.first;
   qDebug() << name;   

//   QString b = pr.first;
//   if(b.endsWith("pt")
//     b.chop(2);
//   bls=b.toLongLong();
  });

  g.get_sf(h, 2, [](QPair<QString, void*>& pr)
  {
//   sent.set_corpus_name(pr.first);
  });

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
