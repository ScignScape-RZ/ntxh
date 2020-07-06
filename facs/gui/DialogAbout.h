
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
 public DialogAbout();
 
 // // Action: OK
 public void actionOK();

 public static String linebreaksAsBR(QString s);
};

#endif // __H
 



