
// // license___here

#include "QTutil.h"


// package facsanadu.gui.qt;



// // QT utility functions

QLayout QTutil::withLabel(String s, QWidget w)
  {
  QHBoxLayout layout=new QHBoxLayout();
  QLabel l=new QLabel(s);
  l.setSizePolicy(Policy.Fixed, Policy.Fixed);
  layout.addWidget(l);
  layout.addWidget(w);
  layout.setSpacing(0);
  layout.setMargin(0);

  return layout;
  }

 
 /**
  * Return a widget with a label to the right of it
  */
QLayout QTutil::withLabel(String s, QWidget w, String sRight)
  {
  QHBoxLayout layout=new QHBoxLayout();
  if(s!=null)
   {
   QLabel lLeft=new QLabel(s);
   lLeft.setSizePolicy(Policy.Minimum, Policy.Minimum);
   layout.addWidget(lLeft);
   }
  layout.addWidget(w);
  if(sRight!=null)
   {
   QLabel lRight=new QLabel(sRight);
   lRight.setSizePolicy(Policy.Minimum, Policy.Minimum);
   layout.addWidget(lRight);
   }
  return layout;
  }


 /**
  * Place widget within a titled frame
  */
QWidget QTutil::withinTitledFrame(String title, QWidget w)
  {
  QVBoxLayout layout=new QVBoxLayout();
  layout.addWidget(w);
  layout.setMargin(0);
  return QTutil.withinTitledFrame(title,layout);
  }

 /**
  * Place layout within a titled frame
  */
QWidget QTutil::withinTitledFrame(String title, QLayout layout)
  {
  QGroupBox b=new QGroupBox(title);
  b.setLayout(layout);
  return b;
  }

 /**
  * Convert QT date to Java date
  */
Date QTutil::convertToJavaDate(QDate qd, QTime qt)
  {
  Calendar c=Calendar.getInstance();
  c.clear();
  c.set(qd.year(), qd.month()-1, qd.day());    // check day!

  if(qt!=null)
   {
   c.set(Calendar.HOUR, qt.hour());
   c.set(Calendar.MINUTE, qt.minute());
   c.set(Calendar.SECOND, qt.second());
   c.set(Calendar.MILLISECOND, 0);
   }
  return c.getTime();
  }
 
QDate QTutil::convertToQDate(Calendar calendar)
  {
  return new QDate(calendar.get(Calendar.YEAR), calendar.get(Calendar.MONTH)+1, calendar.get(Calendar.DAY_OF_MONTH));
  }
 
 


QFileDialog.Filter QTutil::buildFileDialogSupportedFormatsFilter(String fileType, Collection<String> formatsList)
  {
  String formats="";
  for(String arr:formatsList)
   {
   if(!formats.equals(""))
    formats+=" ";
   formats+="*."+arr;
   }
  return new QFileDialog.Filter(fileType+" ("+formats+")");
  }


 /**
  * Request an open-file dialog
  * 
  * @param parent  Qt widget parent
  * @param title   What to ask the user
  * @param filter  Filter for the files
  * @return        The file, or null if none opened
  */
File QTutil::openFileDialog(QWidget parent, String title, Filter filter)
  {
    String fileName = QFileDialog.getOpenFileName(parent, title, lastQtDir, filter);
    if(!fileName.equals(""))
     {
     File f=new File(fileName);
     lastQtDir=f.getParentFile().getAbsolutePath();
     return f;
     }
    else
     return null;
  }

 /**
  * Open multiple files dialog. Never returns null
  */
Collection<File> QTutil::openFilesDialog(QWidget parent, String title, Filter filter)
  {
    List<String> fileName = QFileDialog.getOpenFileNames(parent, title, lastQtDir, filter);
    if(!fileName.isEmpty())
     {
     List<File> fs=new LinkedList<File>();
     for(String f:fileName)
      {
      File tf=new File(f);
      fs.add(tf);
       lastQtDir=tf.getParentFile().getAbsolutePath();
      }
     return fs;
     }
    else
     return new LinkedList<File>();
  }

 /**
  * Request a save-file dialog
  * 
  * @param parent       Qt widget parent
  * @param title        What to ask the user
  * @param suggestName  Suggested name of file, or null
  * @param filter       Filter for the files
  * @return             The file, or null if none opened
  */
File QTutil::saveFileDialog(QWidget parent, String title, String suggestName, String defaultSuffix, QFileDialog.Filter filter)
  {
  QFileDialog dia=new QFileDialog(parent, title, lastQtDir);
  dia.setFilter(filter.filter);
  if(defaultSuffix!=null)
   dia.setDefaultSuffix(defaultSuffix);  
  if(suggestName!=null)
   dia.selectFile(suggestName);
  dia.setAcceptMode(AcceptMode.AcceptSave);
  if(dia.exec()==0)
   return null;
  if(dia.selectedFiles().isEmpty())
   return null;
  
  String fileName = dia.selectedFiles().iterator().next();
    if(!fileName.equals(""))
     {
     File f=new File(fileName);
     lastQtDir=f.getParentFile().getAbsolutePath();
     return f;
     }
    else
     return null;
  }

File QTutil::saveFileDialog(QWidget parent, String title, Filter filter)
  {
  return saveFileDialog(parent, title, null, null, filter);
  }
 /**
  * Last directory where a file was opened from
  */
// privateQString lastQtDir="";

 /**
  * Open dialog for selecting an existing directory
  * @param parent  QT widget parent
  * @param title   Title to show
  * @return        Directory if selected, otherwise null
  */
File QTutil::openExistingDirectoryDialog(QWidget parent, String title, String acceptText)
  {
  QFileDialog dia=new QFileDialog(parent, title, lastQtDir);
  if(acceptText!=null)
   dia.setLabelText(DialogLabel.Accept, acceptText);
  if(dia.exec()!=0)
//    String fileName = QFileDialog.getExistingDirectory(parent, title, lastQtDir);
//    if(!fileName.equals(""))
     {
//     File f=new File(fileName);
     File f=new File(dia.selectedFiles().iterator().next());
     lastQtDir=f.getAbsolutePath();
     return f;
     }
    else
     return null;
  }


Filter QTutil::getAllFilesFilter()
  {
  return new QFileDialog.Filter(QCoreApplication.translate("labstory","Files")+" (*.*)");
  }


List<String> QTutil::getSupportedImageFormats()
  {
  LinkedList<String> formats=new LinkedList<String>();
  for(QByteArray arr:QImageReader.supportedImageFormats())
   formats.add(arr.toString());
  return formats;
  }


 /**
  * Executes the QApplication::exec() method, which has different names in different versions of QTJambi, using reflection
  * 
  * @return The value from QApplication::exec()
  */
int QTutil::execStaticQApplication()
  {
  //New name
  try
   {
   Method method=QApplication.class.getDeclaredMethod("execStatic");
   return (Integer)method.invoke(null);
   }
  catch (Exception e){}
  
  //Old name
  try
   {
   Method method=QCoreApplication.class.getDeclaredMethod("exec");
   return (Integer)method.invoke(null);
   }
  catch (Exception e){}
  
  throw new RuntimeException("Could not find anymethod in QApplication to perform exec()"); 
  }


QString QTutil::formatDateTime(long t)
  {
  DateFormat df=new SimpleDateFormat("yyyy-MM-dd kk:mm");
  return df.format(t);
  }


QLayout QTutil::layoutHorizontal(QWidget... widgets)
  {
  QHBoxLayout layout=new QHBoxLayout();
  for(QWidget w:widgets)
   layout.addWidget(w);
  return layout;
  }

QLayout QTutil::layoutVertical(Object... widgets)
  {
  QVBoxLayout layout=new QVBoxLayout();
  for(Object w:widgets)
   {
   if(w instanceof QWidget)
    layout.addWidget((QWidget)w);
   else if(w instanceof QLayout)
    layout.addLayout((QLayout)w);
   else
    throw new RuntimeException("Neither widget nor layout");
   }
  return layout;
  }
 

void QTutil::showNotice(final QWidget parent, final String text)
  {
  QMessageBox.information(parent, QtProgramInfo.programName, text);
  }

 
void QTutil::printError(final QWidget parent, final String text)
  {
  QApplication.invokeAndWait(new Runnable()
   {
    void run()
    {
    QMessageBox.critical(parent, QtProgramInfo.programName, text);
    }
   });
  }
 

bool QTutil::checkIsSigned(boolean isSigned, QWidget parent)
  {
  if(isSigned)
   {
   QMessageBox.critical(parent, QtProgramInfo.programName, QCoreApplication.translate(
     "qtutil","The object has been signed and cannot be modified"));
   return true;
   }
  else
   return false;
  }
 

 /**
  * Fit number of rows
  */
void QTutil::setProperHeightOfTable(QTableView listTables)
  {
  int nNumRows = listTables.model().rowCount();
  int nRowHeight = listTables.rowHeight(0);
  int nTableHeight = (nNumRows * nRowHeight) + listTables.horizontalHeader().height() + 2*listTables.frameWidth();
  if(nTableHeight>300)
   nTableHeight=300;  
  listTables.setMinimumHeight(nTableHeight);
  listTables.setMaximumHeight(nTableHeight);
  }


QValidator QTutil::getLabstoryIdvalidator(QObject parent)
  {
  //Do NOT use the constructor(regexp), windows qt bug!
  QRegExpValidator validator=new QRegExpValidator(parent);
  validator.setRegExp(new QRegExp("[abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890]*"));
  return validator;
  }
 
 
bool QTutil::showOkCancel(String title)
  {
  QMessageBox msgBox=new QMessageBox();
  msgBox.setText(title);
  msgBox.setStandardButtons(StandardButton.Ok, StandardButton.Cancel);
  msgBox.setDefaultButton(StandardButton.Ok);
  int ret = msgBox.exec();
  return ret==StandardButton.Ok.value();
  }
 
bool QTutil::showYesNo(String title)
  {
  QMessageBox msgBox=new QMessageBox();
  msgBox.setText(title);
  msgBox.setStandardButtons(StandardButton.Yes, StandardButton.No);
  msgBox.setDefaultButton(StandardButton.Yes);
  int ret = msgBox.exec();
  return ret==StandardButton.Yes.value();
  }


bool QTutil::addingKey(QMouseEvent event)
  {
  return event.modifiers().isSet(KeyboardModifier.ShiftModifier) || event.modifiers().isSet(KeyboardModifier.ControlModifier);
  }

 /**
  * Create a read-only list item
  */
QTableWidgetItem QTutil::createReadOnlyItem(String s)
  {
  QTableWidgetItem it=new QTableWidgetItem(s);
  it.setFlags(new ItemFlags(ItemFlag.ItemIsSelectable, ItemFlag.ItemIsEnabled));
  return it;
  }

