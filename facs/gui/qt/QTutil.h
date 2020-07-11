
// // license___here_h


#ifndef QTutil__H
#define QTutil__H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLayout>
#include <QFile>
#include <QDate>
#include <QValidator>

// package facsanadu.gui.qt;



// // QT utility functions
class QTutil
{
public:

 /**
  * Return a widget with a label to the left of it
  */
 static QLayout* withLabel(QString s, QWidget* w);
 
 /**
  * Return a widget with a label to the right of it
  */
 static QLayout* withLabel(QString s, QWidget* w, QString sRight);

 /**
  * Place widget within a titled frame
  */
 static QWidget* withinTitledFrame(QString title, QWidget& w);

 /**
  * Place layout within a titled frame
  */
 static QWidget* withinTitledFrame(QString title, QLayout& layout);

 /**
  * Convert QT date to Java date
  */
// static Date convertToJavaDate(QDate qd, QTime qt);
 
// static QDate convertToQDate(Calendar calendar);

// static QFileDialog.Filter buildFileDialogSupportedFormatsFilter(String fileType, Collection<String> formatsList);

 /**
  * Request an open-file dialog
  * 
  * @param parent  Qt widget parent
  * @param title   What to ask the user
  * @param filter  Filter for the files
  * @return        The file, or null if none opened
  */
 static QFile openFileDialog(QWidget parent, QString title, QString filter); //Filter filter

 /**
  * Open multiple files dialog. Never returns null
  */
 static QList<QFile> openFilesDialog(QWidget parent, QString title, QString filter);

 /**
  * Request a save-file dialog
  * 
  * @param parent       Qt widget parent
  * @param title        What to ask the user
  * @param suggestName  Suggested name of file, or null
  * @param filter       Filter for the files
  * @return             The file, or null if none opened
  */
//? static QFile saveFileDialog(QWidget parent, QString title, QString suggestName, String defaultSuffix, QFileDialog.Filter filter);

//? static File saveFileDialog(QWidget parent, String title, Filter filter);

 /**
  * Last directory where a file was opened from
  */
 //private static String lastQtDir="";

 /**
  * Open dialog for selecting an existing directory
  * @param parent  QT widget parent
  * @param title   Title to show
  * @return        Directory if selected, otherwise null
  */
 static QFile openExistingDirectoryDialog(QWidget parent, QString title, QString acceptText);

//? static Filter getAllFilesFilter();

 static QList<QString> getSupportedImageFormats();

 /**
  * Executes the QApplication::exec() method, which has different names in different versions of QTJambi, using reflection
  * 
  * @return The value from QApplication::exec()
  */
 static int execStaticQApplication();

 static QString formatDateTime(long t);

 static QLayout* //QLayout 
   layoutHorizontal(QList<QObject*> widgets);

 static QLayout* //QLayout
   layoutVertical(QList<QObject*> widgets);  

 static void showNotice(const QWidget& parent, const QString text);

 static void printError(const QWidget& parent, const QString text);
 

 static bool checkIsSigned(bool isSigned, QWidget& parent);

 /**
  * Fit number of rows
  */
 static void setProperHeightOfTable(QTableView& listTables);

 static QIntValidator // QValidator
   getLabstoryIdvalidator(QObject& parent);
 
 static bool showOkCancel(QString title);
 
 static bool showYesNo(QString title);

 static bool addingKey(QMouseEvent* event);

 /**
  * Create a read-only list item
  */
 static QTableWidgetItem* createReadOnlyItem(QString s);

};

#endif // __H
 

