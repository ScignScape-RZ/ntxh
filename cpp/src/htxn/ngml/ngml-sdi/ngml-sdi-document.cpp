
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

#include "quazip/quazip.h"
#include "quazip/quazipfile.h"

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

  // //  assume that everything is in pts for now ...
  QString sx = prs[7].first;
  if(sx.endsWith("pt"))
    sx.chop(2);

  QString sy = prs[8].first;
  if(sy.endsWith("pt"))
    sy.chop(2);

  u4 start_x = (int) sx.toDouble();
  u4 start_y = (int) sy.toDouble();

  if(prs[5].first.isEmpty())
    start_y -= (u4) this->global_base_line_skip_;
  else
  {
   QString b = prs[5].first;
   if(b.endsWith("pt"))
     b.chop(2);
   start_y -= (int) b.toDouble();
  }    


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

  // //  assume that everything is in pts for now ...
  QString ex = prs[3].first;
  if(ex.endsWith("pt"))
    ex.chop(2);

  QString ey = prs[4].first;
  if(ey.endsWith("pt"))
    ey.chop(2);

  u4 end_x = (int) ex.toDouble();
  u4 end_y = (int) ey.toDouble();
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

 QList<QPair<QString, QPair<QString, QString>>> files;

 for(NGML_SDI_Page* page : pages_)
 {
  QString fn = QString::number(page->number());
  fn.prepend('p');
  fn.append(".txt");
  QString ffn = qd.absoluteFilePath(fn);
  QString contents;
  page->write(contents);
  save_file(ffn, contents);
  files.push_back({ffn, {qd.dirName() + "/" + fn, fn}});
 }

 QuaZip zip(folder_ + ".sdi.zip");
 zip.setFileNameCodec("IBM866");

 if (!zip.open(QuaZip::mdCreate)) 
 {
  qDebug() << "Zip open failed ...";
 }

 QFile inFile;
 QuaZipFile outFile(&zip);
 
 char c;
 int j = 0;
 
 for(QPair<QString, QPair<QString, QString>> pr : files)
 {
  qDebug() << "PR: " << pr;

  inFile.setFileName(pr.first);
  if (!inFile.open(QIODevice::ReadOnly))
  {  
   qDebug() << "Infile open failed ...";
   continue;
  }

  QuaZipNewInfo qni = QuaZipNewInfo(pr.second.first, pr.second.second);
  //qni.setPermissions(QFileDevice::ReadOther);
  qni.setFilePermissions(pr.first);

  if (!outFile.open(QIODevice::WriteOnly, qni))
  {
   qDebug() << "Outfile open failed ...";
   continue; 
  }
 
//  qni.setPermissions(QFileDevice::ReadOther);
  //qni.setFilePermissions(pr.first);

  while (inFile.getChar(&c))
    outFile.putChar(c);
 
  if (outFile.getZipError() != ZIP_OK)
  {
   qDebug() << "Outfile write failed ...";   
   continue;
  }
  outFile.close();
 
  if (outFile.getZipError() != ZIP_OK)
  {
   qDebug() << "Outfile close failed ...";   
   continue; 
  }

  inFile.close();
 }
 
 zip.close();
 
 if (zip.getZipError() != 0)
   qDebug() << "Zip failed ...";

 QString new_path = folder_ + "/../../test/" + qd.dirName() + ".sdi.zip";
 QString unzip_path = folder_ + "/../../test/test";

 qDebug() << new_path;

 if(QFile::exists(new_path))
 {
   QFile::remove(new_path);
 }

 qDebug() << "Copying ... " << folder_ + ".sdi.zip" << " to " << new_path;

 QFile::copy(folder_ + ".sdi.zip", new_path); 

 check_read_page(new_path, unzip_path, qd.dirName(), 1);
}

NGML_SDI_Page* NGML_SDI_Document::check_read_page(QString zip_file_path, 
  QString unzip_path, QString unzip_folder_name, u4 page_number)
{
 check_unzip_folder(zip_file_path, unzip_path, unzip_folder_name);
 QDir dir(*unzip_folder_);
 QString path = dir.absoluteFilePath(QString("p%1.txt").arg(page_number));
 NGML_SDI_Page* result = new NGML_SDI_Page(page_number);
 load_file(path, [result](QString& line) -> u8
 {
  if(line.isEmpty())
    return 0;
  QStringList nums = line.simplified().split(' ');
  if(nums.length() < 6)
    return 1; // malformed; stop reading
  result->read_page_element_from_strings(nums);   
 });

 return result;
 //qDebug() << "Text: " << text;
}

void NGML_SDI_Document::check_unzip_folder(QString zip_file_path, 
  QString unzip_path, QString unzip_folder_name)
{
 if(unzip_folder_)
   return;

 QDir dir(unzip_path);
 dir.mkdir(unzip_folder_name);
 unzip_folder_ = new QString(dir.absoluteFilePath(unzip_folder_name));

//? qDebug() << "UZ: " << dir.absolutePath();
//? if (!dir.exists())
//?   dir.mkpath(".");

 QuaZip zip(zip_file_path);

 if (!zip.open(QuaZip::mdUnzip)) 
 {
  qWarning("testRead(): zip.open(): %d", zip.getZipError());
  return;
 }

 zip.setFileNameCodec("IBM866");

 qWarning("%d entries\n", zip.getEntriesCount());
 qWarning("Global comment: %s\n", zip.getComment().toLocal8Bit().constData());

 QuaZipFileInfo info;

 QuaZipFile file(&zip);

 QFile out;
 QString name;
 char c;
 for (bool more = zip.goToFirstFile(); more; more = zip.goToNextFile()) 
 {
  if (!zip.getCurrentFileInfo(&info)) 
  {
   qWarning("testRead(): getCurrentFileInfo(): %d\n", zip.getZipError());
  }
//?  if (!singleFileName.isEmpty())
//?    if (!info.name.contains(singleFileName))
//?      continue;

  if (!file.open(QIODevice::ReadOnly)) 
  {
   qWarning("testRead(): file.open(): %d", file.getZipError());
   return;
  }

  name = QString("%1/%2").arg(unzip_path).arg(file.getActualFileName());

  qDebug() << "Name: " << name;

  if (file.getZipError() != UNZ_OK) 
  {
   qWarning("testRead(): file.getFileName(): %d", file.getZipError());
   return;
  }

  //out.setFileName("out/" + name);
  out.setFileName(name);

  // this will fail if "name" contains subdirectories, but we don't mind that
  if(!out.open(QIODevice::WriteOnly))
    qDebug() << "Out failed ...";
  // Slow like hell (on GNU/Linux at least), but it is not my fault.
  // Not ZIP/UNZIP package's fault either.
  // The slowest thing here is out.putChar(c).
  while (file.getChar(&c)) out.putChar(c);

  out.close();

  if (file.getZipError() != UNZ_OK) 
  {
   qWarning("testRead(): file.getFileName(): %d", file.getZipError());
   return;
  }

  if (!file.atEnd()) 
  {
   qWarning("testRead(): read all but not EOF");
   return;
  }

  file.close();

  if (file.getZipError() != UNZ_OK) 
  { 
   qWarning("testRead(): file.close(): %d", file.getZipError());
   return;
  }
 }

 zip.close();

 if (zip.getZipError() != UNZ_OK) 
 {
  qWarning("testRead(): zip.close(): %d", zip.getZipError());
  return;
 }

}

