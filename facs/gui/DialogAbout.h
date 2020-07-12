
// // license___here_h


#ifndef DialogAbout__H
#define DialogAbout__H


#include <QDialog>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QCheckBox>
#include <QPushButton>



// package facsanadu.gui;


class DialogAbout : public QDialog
{
//? Q_OBJECT

public:

 DialogAbout();
 
 static QString linebreaksAsBR(QString s);

//?Q_SIGNALS:

 // // Action: OK
 void actionOK();

};

#endif // __H
 



