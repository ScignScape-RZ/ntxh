
#include "rz-ngml/kernel/document/rz-ngml-document.h"

#include "rz-ngml/output/rz-ngml-output-html.h"
#include "rz-ngml/output/rz-ngml-output-latex.h"
#include "rz-ngml/output/rz-ngml-output-khif.h"
#include "rz-ngml/kernel/document/rz-ngml-folder.h"

#include <QMapIterator>

#include <QRegularExpression>

USING_RZNS(NGML)



#define DEFAULT_DIRECTORY  "../.."


#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QMap>


struct mi_pair
{
 mi_pair(int x, int y)
 {
  qDebug() << ( (x < y)? "Ok": "No");
 }
};

void f(int x, int y,
 mi_pair pr)
{

}

void f(int x, int y) throw (int)
{
 if(y < x)
  throw y - x;
 f(x, y, mi_pair(x, y));
}

typedef void (*test) (int, int);

int main(int argc, char* argv[])
{
 test tt = &f;
 (*tt)(5, 6);

 QString dir;
 {
  QApplication qapp(argc, argv);
  dir = QFileDialog::getExistingDirectory(nullptr, "Choose Folder", DEFAULT_DIRECTORY);
 }

 NGML_Folder folder(dir);
 folder.convert_to_latex();

}

