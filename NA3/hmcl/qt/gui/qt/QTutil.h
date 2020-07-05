// package facsanadu.gui.qt;



// // QT utility functions
class QTutil
{

 /**
  * Return a widget with a label to the left of it
  */
 static QLayout withLabel(String s, QWidget w);
 
 /**
  * Return a widget with a label to the right of it
  */
 static QLayout withLabel(String s, QWidget w, String sRight);

 /**
  * Place widget within a titled frame
  */
 static QWidget withinTitledFrame(String title, QWidget w);

 /**
  * Place layout within a titled frame
  */
 static QWidget withinTitledFrame(String title, QLayout layout);

 /**
  * Convert QT date to Java date
  */
 static Date convertToJavaDate(QDate qd, QTime qt);
 
 static QDate convertToQDate(Calendar calendar);

 static QFileDialog.Filter buildFileDialogSupportedFormatsFilter(String fileType, Collection<String> formatsList);

 /**
  * Request an open-file dialog
  * 
  * @param parent  Qt widget parent
  * @param title   What to ask the user
  * @param filter  Filter for the files
  * @return        The file, or null if none opened
  */
 static File openFileDialog(QWidget parent, String title, Filter filter);

 /**
  * Open multiple files dialog. Never returns null
  */
 static Collection<File> openFilesDialog(QWidget parent, String title, Filter filter);

 /**
  * Request a save-file dialog
  * 
  * @param parent       Qt widget parent
  * @param title        What to ask the user
  * @param suggestName  Suggested name of file, or null
  * @param filter       Filter for the files
  * @return             The file, or null if none opened
  */
 static File saveFileDialog(QWidget parent, String title, String suggestName, String defaultSuffix, QFileDialog.Filter filter);

 static File saveFileDialog(QWidget parent, String title, Filter filter);

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
 static File openExistingDirectoryDialog(QWidget parent, String title, String acceptText);

 static Filter getAllFilesFilter();

 static List<String> getSupportedImageFormats();

 /**
  * Executes the QApplication::exec() method, which has different names in different versions of QTJambi, using reflection
  * 
  * @return The value from QApplication::exec()
  */
 static int execStaticQApplication();

 static String formatDateTime(long t);

 static QLayout layoutHorizontal(QWidget... widgets);

 static QLayout layoutVertical(Object... widgets);  

 static void showNotice(final QWidget parent, final String text);

 static void printError(final QWidget parent, final String text);
 

 static boolean checkIsSigned(boolean isSigned, QWidget parent);

 /**
  * Fit number of rows
  */
 static void setProperHeightOfTable(QTableView listTables);

 static QValidator getLabstoryIdvalidator(QObject parent);
 
 static boolean showOkCancel(String title);
 
 static boolean showYesNo(String title);

 static boolean addingKey(QMouseEvent event);

 /**
  * Create a read-only list item
  */
 static QTableWidgetItem createReadOnlyItem(QString s);

};
