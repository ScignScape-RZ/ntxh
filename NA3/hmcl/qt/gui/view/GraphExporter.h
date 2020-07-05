// package facsanadu.gui.view;


// // Export graphs to files
class GraphExporter
{
 /**
  * Split selected according to parameters, then save
  */
 static void render(File f, FacsanaduProject proj, LinkedList<Dataset> listds, LinkedList<ViewSettings> listviews, 
   boolean splitDS, boolean splitView, int onew, int oneh);

 /**
  * Render everything to one image
  */
 static void render(File f, FacsanaduProject proj, List<Dataset> listds, List<ViewSettings> listviews, int onew, int oneh);

};
