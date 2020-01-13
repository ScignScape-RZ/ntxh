
#include "rz-ngml/kernel/document/rz-ngml-document.h"

#include "rz-ngml/output/rz-ngml-output-html.h"
#include "rz-ngml/output/rz-ngml-output-latex.h"
#include "rz-ngml/output/rz-ngml-output-htxn.h"

#include "rz-ngml/output/rz-ngml-output-xml.h"

#include "rz-ngml/kernel/document/rz-ngml-folder.h"

#include "rzns.h"

#include <QRegularExpression>

// //
//#include <QDomDocument>
//#include <QDomElement>
//#include <QDomNode>


USING_RZNS(NGML)

#define DEFAULT_DIRECTORY "/home/nlevisrael/hypergr/ntxh/ar/htxn/ngml"

//#include <QApplication>
//#include <QFileDialog>
#include <QDebug>


int main(int argc, char* argv[])
{
// QApplication qapp(argc, argv);

// QString folder = QFileDialog::getExistingDirectory(nullptr,
//   "Select Folder"
//   " (needs /ngml subfolder)",
//   DEFAULT_DIRECTORY);

 NGML_Document ndoc; //(DEFAULT_DIRECTORY "/t1.ngml");
 ndoc.load_and_parse(DEFAULT_DIRECTORY "/t1.ngml");

 NGML_Output_HTXN noh(ndoc);
 noh.export_htxne();

 noh.write_latex_out(DEFAULT_DIRECTORY "/t1.ngml.htxne.tex");

//? QFile file(DEFAULT_DIRECTORY "/t1.ngml.htxne");
//? if(file.open(QIODevice::WriteOnly | QIODevice::Text))
//? {
//?  doc.write_latex_out(file); 
//? }


// NGML_Folder ngf(folder + "/ngml");
// ngf.convert_all_files(folder, folder + "/khif");

 return 0;
}


