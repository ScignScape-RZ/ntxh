

// // license___here_h


#ifndef ViewRenderer__H
#define ViewRenderer__H


// package facsanadu.gui.view;


/**
 * 
 * Renderer of one view
 * 
 * @author Johan Henriksson
 *
 */
class ViewRenderer
{
 static int labelOffset; // =15;
  
 /**
  * Render histogram
  * @param handles 
  */
 static void renderHistogram(ViewSettings viewsettings, Dataset segment, GatingResult gr, ViewTransform trans, QPainter pm);

 /**
  * Draw scatter plot
  */
 static void renderXY(ViewSettings viewsettings, Dataset ds, GatingResult gr, ViewTransform trans, QPainter pm,
   int rendermax);
 
 /**
  * Draw things surrounding graph
  */
 static void drawHeaderLines(QPainter pm, ViewTransform trans, String labelX, String labelY);

 /**
  * Draw all gates recursively
  */
 static void drawgatesRecursive(QPainter pm, ViewTransform trans, Gate parent, ViewSettings viewsettings, LinkedList<GateHandle> handles);
 
public: 
 /**
  * Render view to device
  */
  static void renderData(ViewSettings viewsettings, Dataset segment, GatingResult gr,   ViewTransform trans, QPainter pm, int rendermax);
 
 static void renderGates(ViewSettings viewsettings, Dataset segment, GatingResult gr, ViewTransform trans, QPainter pm, LinkedList<GateHandle> handles, int rendermax);
};

#endif // __H
 



