
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "ngml-sdi-document.h"

#include "ntxh-parser/ntxh-document.h"


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

 int i = 0;

 for(hypernode_type* h : v)
 {
  g.get_sf(h, 1, [](QPair<QString, void*>& pr)
  {
//   sent.set_id(pr.first.toInt());
  });

  g.get_sf(h, 2, [](QPair<QString, void*>& pr)
  {
//   sent.set_corpus_name(pr.first);
  });

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
 } 

}
