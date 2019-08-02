
//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "application-config-model.h"

#include <QDebug>

#include "kans.h"

#include "textio.h"

USING_KANS(TextIO)

USING_KANS(DSM)


Application_Config_Model::Application_Config_Model()
 : usrl_(User_Levels::N_A), insert_text_{{
     { "xpdf",
      {{{"external/xpdf/xpdf"},
       {"USING_XPDF"},
       {} }}},

     { "xx",
      {{{"external/xpdf/xpdf-console"},
       {},
       {} }}},

     { "ro",
      {{{"dataset/ro-info/ro-info-console"},
         {},
         {} }}},

     { "ppc",
      {{{"dataset/pdf-pull/pdf-pull-console"},
         {},
         {} }}},

    { "udp",
      {{{"external/udpipe/udpipe", "hgdm/ntxh-udp/ntxh-udp",
         "hgdm/ntxh-udp/ntxh-udp-console"},
      {"USING_UDP"},
      {} }}},

    { "kdmi",
      {{
       {
        "dataset/ds-kdmi/ds-kdmi",
        "dataset/ds-kdmi/ds-kdmi-console",
        "dataset/ds-kdmi/kdmi-bridge",
        "dataset/ds-kdmi/kdmi-bridge-console",
        },
      {},
       {} }}},

    { "kph",
      {{
       {
        "rz/tests-phr/kauvir-phaon-console",
        "rz/tests-phr/kph-tcp-console",
       },

       {"USING_KPH"},
       {} }}},

    { "kph-gen",
      {{
       {
        "rz/phr-runtime/phr-env",
        "rz/phr-runtime/phr-fn-doc",
        "rz/PhaonLib/phr-command-runtime",

        "rz/tests-phr/kph-generator",
        "rz/PhaonLib/phr-direct-eval",

        "rz/tests-phr/kph-generator-console",
        "rz/tests-phr/kph-multigen-console",
       },
      {"USING_KPH_GEN"},
       {} }}},

    { "config",
      {{
       {
        "dataset/config/config-dialog-console",
       },
      {"USING_CONFIG_DIALOG"},
       {} }}},

    { "lex-pair",
      {{
       {
        "QScign/LexPair/lexpair",
        "QScign/LexPair/lexpair-console",
       },
      {"USING_LEXPAIR"},
       {} }}},

    { "charm",
      {{
       {
        "hgdm/charm/charm-lib",
        "hgdm/charm/charm-lib-console",
       },
      {},
       {} }}},

    { "charm",
      {{
       {
        "rz/rz-kauvir/rz-graph-core",
        "rz/rz-kauvir/rz-graph-token",
       },
       {},
      {} }}},

 }}
{


}

void Application_Config_Model::parse_config_code(QString cc)
{
 if(cc.startsWith("gen_test__"))
 {
  gen_test_ = ".gen.txt";
  cc = cc.mid(10);
 }

 qDebug() << cc;
 int index = cc.indexOf('-');

 int ul = cc.mid(index + 1).toInt();
 cc = cc.left(index);

 usrl_ = (User_Levels) ul;

 if(cc.contains("xq"))
 {
  insert_text_["xpdf"][0].pri_libs.append(
    QString("libqtpng libqtfreetyped").split(' '));
 }
 else if(cc.contains("xs"))
 {
  insert_text_["xpdf"][0].pri_libs.append(
    QString("png freetype").split(' '));
 }
 else
   insert_text_.remove("xpdf");

 if(!cc.contains("xx"))
 {
  insert_text_.remove("xx");
 }

 if(!cc.contains('k'))
 {
  insert_text_.remove("kph");
 }

 if(!cc.contains('g'))
 {
  insert_text_.remove("kph-gen");
 }

 if(!cc.contains('z'))
 {
  insert_text_.remove("rz");
 }

 if(!cc.contains('d'))
 {
  insert_text_.remove("kdmi");
 }

 if(!cc.contains('c'))
 {
  insert_text_.remove("config");
 }

 if(!cc.contains('r'))
 {
  insert_text_.remove("ro");
 }


 if(!cc.contains('p'))
 {
  insert_text_.remove("ppc");
 }

 if(!cc.contains('u'))
 {
  insert_text_.remove("udp");
 }

 if(!cc.contains('l'))
 {
  insert_text_.remove("lex-pair");
 }

 if(!cc.contains('m'))
 {
  insert_text_.remove("charm");
 }

 for(QPair<QString, QString> pr : QList<QPair<QString, QString>>{

 {"", "hgdm/ntxh/ntxh"},
 {"", "hgdm/ntxh/ntxh-parser"},
 {"", "hgdm/ntxh/ntxh-builder"},

 {"", "QScign/QRing/qring"},

 {"", "dataset/ro-info/ro-info"},
 {"", "dataset/config/config-dialog"},
 {"", "dataset/dsmain/dsmain"},
 {"", "dataset/pdf-pull/pdf-pull"},

 {"kdmi", "*"},

 {"ppc", "*"},
 {"ro", "*"},
 {"udp", "*"},
 {"xpdf", "*"},

 {"", "rz/PhaonIR/phaon-ir"},
 {"", "rz/PhaonLib/phaon-lib"},

 {"", "QScign/ScignStage/ScignStage-ling"},
 {"lex-pair", "*"},
 {"config", "*"},
 {"charm", "*"},


 {"xx", "*"},

 {"", "dataset/application-model/application-model"},

 {"kph", "dataset/application-model/application-model-test-dialog"},
 {"kph", "dataset/application-model/amtd-console"},

 {"kph-gen", "*"},

 {"", "dataset/dsmain/_run__dsmain-console"},
 })
 if(pr.first.isEmpty() || insert_text_.contains(pr.first))
   subdirs_.push_back(pr);
}

void Application_Config_Model::reset(QStringList files, QString name_supplement)
{
 for(QString f : files)
 {
  QString text;
  load_file(f + name_supplement, text);
  save_file(f, text);
 }
}

QPair<int, int> Application_Config_Model::find_insert_indices(QString qs,
  QString locator,
  QString end_locator)
{
 int index = qs.indexOf(locator);
 if(index == -1)
  return {-1, -1};
 index += locator.size();
 int end = qs.indexOf(end_locator, index);
 if(end == -1)
   return {index, -1};
 return {index, end - index};
}

QString Application_Config_Model::insert_to_defines(QString file_path, QString& result)
{
 load_file(file_path, result);

 QString locator = "\n//__CUSTOM_DEFINES__//\n\n";
 QString end_locator = "\n\n//__END_INSERT__//\n";

 QPair<int, int> ii = find_insert_indices(result, locator, end_locator);

 if(ii.second == -1)
   return file_path + ".err.txt";

 QString insert;

 QMapIterator<QString, QList<Gen_Targets>> it(insert_text_);

 while(it.hasNext())
 {
  it.next();
  for(QString def : it.value()[0].defines)
  {
   insert += QString("#define %1\n").arg(def);
  }
 }

 result.replace(ii.first, ii.second, insert);

 return file_path + gen_test_;
}

QString Application_Config_Model::insert_to_unibuild(QString file_path, QString& result)
{
 load_file(file_path, result);

 QString locator = "\n#__CHOICE_SUBDIRS__#\n\n";
 QString end_locator = "\n\n#__END_INSERT__#\n";
 QPair<int, int> ii = find_insert_indices(result, locator, end_locator);
 if(ii.second == -1)
   return file_path + ".err.txt";

 QString insert = "SUBDIRS = \\\n";

 for(QPair<QString, QString> pr : subdirs_)
 {
  if(pr.first.isEmpty())
    insert += QString("  %1 \\\n").arg(pr.second);
  else if(pr.second == "*")
    for(QString qs : insert_text_[pr.first][0].subdirs)
      insert += QString("  %1 \\\n").arg(qs);
  else
    insert += QString("  %1 \\\n").arg(pr.second);
 }

 result.replace(ii.first, ii.second, insert);

 return file_path + gen_test_;
}

QString Application_Config_Model::insert_to_choices(QString file_path, QString& result)
{
 load_file(file_path, result);

 QString locator = "\n#__CHOICE_FEATURES__#\n\n";
 QString end_locator = "\n\n#__END_INSERT__#\n";
 QPair<int, int> ii = find_insert_indices(result, locator, end_locator);
 if(ii.second == -1)
   return file_path + ".err.txt";

 QString insert = QString("CHOICE_FEATURES = %1").arg(insert_text_.isEmpty()?
    "none" : insert_text_.keys().join(' '));

 result.replace(ii.first, ii.second, insert);

 return file_path + gen_test_;
}

void Application_Config_Model::insert_to_custom_libs(const QMap<QString, QString>& files,
  QMap<QString, QString>& result)
{
 QMapIterator<QString, QString> it(files);

 while(it.hasNext())
 {
  it.next();

  QString k = it.key();
  QString fn = it.value();
  QString c = load_file(fn);

  QString locator = "\n#__CUSTOM_LIBS__#\n\n";
  QString end_locator = "\n\n#__END_INSERT__#\n";
  QPair<int, int> ii = find_insert_indices(c, locator, end_locator);

  if(ii.second == -1)
  {
   result[fn + ".err.txt"] = c;
   continue;
  }

  QString libs;

  if(insert_text_.contains(k))
  {
   for(QString lib : insert_text_[k][0].pri_libs)
   {
    libs += QString(" -l%1 ").arg(lib);
   }
   QString insert;
   if(!libs.isEmpty())
     insert = QString("LIBS += %1").arg(libs);
   c.replace(ii.first, ii.second, insert);
  }

  result[fn + gen_test_] = c;
 }
}
