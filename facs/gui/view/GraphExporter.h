
// // license___here_h


#ifndef GraphExporter__H
#define GraphExporter__H

#include <QFile>

// // temp
#include<QList>
#define LinkedList QList

// package facsanadu.gui.view;

class FacsanaduProject;
class Dataset;
class ViewSettings;


// // Export graphs to files
class GraphExporter
{

public:

 /**
  * Split selected according to parameters, then save
  */
 static void render(QFile& qf, FacsanaduProject* proj, LinkedList<Dataset*> listds, LinkedList<ViewSettings*> listviews, 
   bool splitDS, bool splitView, int onew, int oneh);

 /**
  * Render everything to one image
  */
 static void render(QFile& f, FacsanaduProject* proj, QList<Dataset*> listds, QList<ViewSettings*> listviews, int onew, int oneh);

};

#endif // __H
 

