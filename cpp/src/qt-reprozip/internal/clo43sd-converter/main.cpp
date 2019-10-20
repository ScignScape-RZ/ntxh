
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include <QDebug>

//#include "patient.h"

//#include "whitedb.h"

#include <QCoreApplication>

#include <QDataStream>

#include "global-types.h"

#include "withs.h"

#include <QMap>
#include <QStringList>

#include <QProcess>

#include "base32.h"

#include "textio.h"

#include "npy/cnpy.h"

USING_KANS(TextIO)

QString convert(QString dir, QString ndir, QString file, QString py_file)
{
 QString py = QString(R"(
import numpy
a = numpy.load("%1/%2.npy", allow_pickle=True, encoding='latin1')
numpy.save("%3/%2.2.npy", a, fix_imports=True))").arg(dir).arg(file).arg(ndir);

 save_file(py_file, py);

 QProcess proc;
 QString cmd = QString("python3 %1").arg(py_file);
 proc.execute(cmd);

 return QString("%1/%2.2.npy").arg(ndir).arg(file);
}

void phconvert (QString sp, QString mf, QString lf, QString phdir)
{
 QFileInfo mqfi(mf);
 std::string mfilename = mf.toStdString();

 QFileInfo lqfi(lf);
 std::string lfilename = lf.toStdString();

 QString mbn = mqfi.completeBaseName();
 if(mbn.endsWith(".2"))
   mbn.chop(2);

 QString lbn = lqfi.completeBaseName();
 if(lbn.endsWith(".2"))
   lbn.chop(2);


 QString mph_file = QString("%1/ph-%2.ntxh").arg(phdir).arg(mbn);
 QString lph_file = QString("%1/ph-%2.ntxh").arg(phdir).arg(lbn);

 cnpy::NpyArray marr = cnpy::npy_load(mfilename);
 std::vector<double> mds = marr.as_vec<double>();

 int mnfs = marr.shape[0];
 int mdim = marr.shape[1];

 cnpy::NpyArray larr = cnpy::npy_load(lfilename);
 std::vector<double> lds = larr.as_vec<double>();

 int lnfs = larr.shape[0];
 int ldim = larr.shape[1];

 int c = 0;

 QString contents;

 QTextStream qts(&contents);

 qts << QString(R"(
!/ MFSS_Coefficients

$sp: %1
$n: %2
$d: %3
$s.
)").arg(sp).arg(mnfs).arg(mdim);

 for(int i = 0; i < mnfs; ++i)
 {
  for(int j = 0; j < mdim; ++j)
  {
   double d = mds[c];
   ++c;
   qts << d << "\n";
  }
  qts << "\n";
 }
 qts << "\n.\n";

 qts << "\n\n/!\n";
 save_file(mph_file, contents);

 qts << QString(R"(
!/ Log_Coefficients

$sp: %1
$n: %2
$d: %3
$s.
)").arg(sp).arg(lnfs).arg(ldim);

 for(int i = 0; i < lnfs; ++i)
 {
  for(int j = 0; j < ldim; ++j)
  {
   double d = lds[c];
   ++c;
   qts << d << "\n";
  }
  qts << "\n";
 }
 qts << "\n.\n";

 qts << "\n\n/!\n";
 save_file(lph_file, contents);
}


int main(int argc, char *argv[])
{
 QMap<QString, QStringList> args;
// QString enc;
 QStringRef enc;

 QString arg1;

 if(argc > 1)
   arg1 = QString::fromLatin1(argv[1]);

// qDebug() << arg1;

 if(arg1.startsWith("qmap="))
 {
 // enc = arg1.midRef(6);
  enc = arg1.midRef(5);
 }


 if(!enc.isEmpty())
 {
  QByteArray qba;
  base32_decode_qstringref(enc, qba);
  QDataStream qds(qba);
  qds >> args;

  qDebug() << args;
 }

 QString pytemp = QT_REPROZIP_BIN_FOLDER "/temp.py";
 qDebug() << pytemp;

 args = {
  {"abbr", {"AMRE"} },
 };

 QString sp = args["abbr"].first();
 QString root = args["root"].first();
 QString filename = args["name"].first();
 QString phfolder = args["phf"].first();
 QString mdir = root + "/mfcc";
 QString mndir = root + "/mfcc-py2";
 QString ldir = root + "/logmelspec";
 QString lndir = root + "/log-py2";
 QString mbn = filename + ".mfcc";
 QString lbn = filename + ".logmelspec";

// QString mdir = "/home/nlevisrael/hypergr/ntxh/external/data/clo43sd/CLO-43SD/mfcc";
// QString mndir = "/home/nlevisrael/hypergr/ntxh/external/data/clo43sd/CLO-43SD/mfcc-py2";
// QString mbn = "AMRE2330536360101.mfcc";

// QString ldir = "/home/nlevisrael/hypergr/ntxh/external/data/clo43sd/CLO-43SD/logmelspec";
// QString lndir = "/home/nlevisrael/hypergr/ntxh/external/data/clo43sd/CLO-43SD/log-py2";
// QString lbn = "AMRE2330536360101.logmelspec";

// QString sp = "AMRE";
 QString mc = convert(mdir, mndir, mbn, pytemp);
 QString lc = convert(ldir, lndir, lbn, pytemp);

 phconvert(sp, mc, lc, "/home/nlevisrael/hypergr/ntxh/external/data/clo43sd/CLO-43SD/ph");

 return 0;
}
