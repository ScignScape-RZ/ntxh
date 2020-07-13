
// // license___here_h


#ifndef ViewToolChoice__H
#define ViewToolChoice__H


// package facsanadu.gui.view.tool;

// import facsanadu.gui.view.ViewWidget;

// // Currently selected tool
//enum 

class ViewTool;
class ViewWidget;

class ViewToolChoice
{

public:

 enum Enum {
   SELECT, RECT, POLY, ELLIPSE, RANGE
 };

 static ViewTool* getTool(ViewWidget* w, Enum e);
};


#endif // __H
 


