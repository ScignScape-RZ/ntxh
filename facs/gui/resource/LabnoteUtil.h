
// // license___here_h


#ifndef LabnoteUtil__H
#define LabnoteUtil__H



// package facsanadu.gui.resource;

// // Johan Henriksson
class LabnoteUtil
{
 /**
  * E-mail regexp 
  */
 static Pattern rfc2822;

public:

  /**
   * Copy file from one location to another
   */
 static void copy(File src, File dst) throws IOException;

  /**
   * Read file into memory
   */
 static byte[] readFileToArray(File src) throws IOException;

 /**
  * Read file into string
  */
 static QString readFileToString(File src) throws IOException;

 /**
  * Read stream into an array
  */
 static byte[] readStreamToArray(InputStream is) throws IOException
  
 /**
  * Read the XML content from a file
  */
 static Document readXML(File filename) throws IOException, JDOMException;

 static Document readXML(InputStream is) throws IOException, JDOMException;
  
  /**
   * Write XML-document to disk
   */
 static void writeXmlData(Document doc, File file) throws IOException;

  /**
   * Write XML-document to stream
   */
 static void writeXmlData(Document doc, OutputStream os) throws IOException;

  /**
   * Delete directory or file recursively
   */
 static void deleteRecursive(File f) throws IOException;

 
 /**
  * Check if an email address is valid
  */
 static bool isEmailValid(String email);

 /**
  * Figure out file extension. Return as .foo or as "" if none
  */
 static String getFileExt(File f);

 /**
  * Put value within <name></name> and return XML element
  */
 static Element elementWithValue(String name, String value);

 /**
  * Store content of input stream to a file. The stream is closed afterwards
  */
 static void streamToFile(InputStream is, File file) throws IOException;

 /**
  * Transfer the content from one stream to another
  */
 static void streamToStream(InputStream is, OutputStream os) throws IOException;
 
 static void streamToStream(InputStream is, OutputStream os, long tot) throws IOException;
 /**
  * Format the size of a document to make it human-readable
  */
 static String formatFileSize(long size);

 /**
  * Write string into file
  */
 static void writeStringToFile(File f, String s) throws IOException;

 /**
  * Convert array to UTF8 string
  */
 static String arrayToUTF8string(byte[] arr);

 /**
  * Primitive bubble sort, O(n^2)
  */
 static <E> void bubbleSort(ArrayList<E> list, Comparator<E> comp);
 
 /**
  * Read UTF8 string from stream (assuming to read all of the stream)
  */
 static String readStreamToString(InputStream is) throws IOException;

 static <E> String commaSeparateLowlevel(Collection<E> list);
 
 static <E> String commaSeparateOrNone(Collection<E> list);
 
 static <E,F> String commaSeparate(Map<E,F> list);

 static bool equalsNull(Object value, Object value2);

 /**
  * Format a duration, in ms
  */
 static QString formatDuration(long duration);

 /**
  * Write a string. An integer followed by the string
  */
 static void writeString(DataOutputStream os, String s) throws IOException;

 /**
  * Write a string. An integer followed by the string. Check that the string is of length <=n
  */
 static void writeStringN(DataOutputStream os, String s, int n) throws IOException;

 /**
  * Read string from writers. Throw an error if the string is longer than n
  */
 static QString readStringN(DataInputStream is, int n) throws IOException;

 /**
  * Read string from the writers
  */
 static QString readString(DataInputStream is) throws IOException;

 static <E> void writeCollection(DataOutputStream dos, Collection<E> set) throws IOException;

 static Collection<String> readCollection(DataInputStream is, int len) throws IOException;

 /**
  * Check if two maps are equal to another, with equals() on both keys and values
  */
 static <E,F> bool deepMapEquals(Map<E, F> map, Map<E, F> map2);

 static bool equalApprox(float x1, float x12);

 static int compareInt(int a, int b);

 static Long parseDuration(String text);

};

#endif // __H
 



