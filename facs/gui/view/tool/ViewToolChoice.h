
// // license___here_h


#ifndef ViewToolChoice__H
#define ViewToolChoice__H


// package facsanadu.gui.view.tool;

// import facsanadu.gui.view.ViewWidget;

/**
 * 
 * Currently selected tool
 * 
 * @author Johan Henriksson
 *
 */
enum class ViewToolChoice
{
 SELECT, RECT, POLY, ELLIPSE, RANGE;
};
 

ViewTool getTool(ViewWidget w, ViewToolChoice t);


#endif // __H
 


