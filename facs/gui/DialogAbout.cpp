
// // license___here

#include "DialogAbout.h"

#include <QTextEdit>

#include "resource/ImgResource.h"
#include "QtProgramInfo.h"


//package facsanadu.gui;

#define connect_this(x, y, z) connect(y, &x, \
   this, &DialogAbout::z);


DialogAbout::DialogAbout()
{
 QTextEdit* textedit = new QTextEdit(linebreaksAsBR(QtProgramInfo::licenseText));
 textedit->setReadOnly(true);

 QPushButton* bOk = new QPushButton("OK");
 bOk->setDefault(true);
 
 QVBoxLayout* vlayout = new QVBoxLayout();
 vlayout->addWidget(new QLabel(
   "<b>" + QtProgramInfo::programName + " " + "</b> " +tr("version") + 
   " " + QtProgramInfo::getVersionString() + 
   " by Johan Henriksson et al<br/>"));

 vlayout->addWidget(textedit);
 vlayout->addWidget(bOk);
 setLayout(vlayout);

 setMinimumSize(500, 300);
 
 setModal(true);
 setWindowTitle(QtProgramInfo::programName + " - "+ tr("About"));
 ImgResource::setWindowIcon(this);
 
 // bOk.clicked.connect(this,"actionOK()");

 connect_this(QPushButton ::clicked ,bOk ,actionOK)
 
 setVisible(true);
}
	
void DialogAbout::actionOK()
{
 close();
}
	
QString DialogAbout::linebreaksAsBR(QString s)
{
 return s.replace("\n","<br/>");
}

