
// // license___here_h


#ifndef ColorSet__H
#define ColorSet__H


// package facsanadu.gui.colors;


// // Set of colors
class ColorSet
{
 LinkedList<GateColor> colors_; //= new LinkedList<GateColor>();
 
 static ColorSet colorset_; //= new ColorSet();
 
/*
 static
  {
  try
   {
   colorset.parseStandardColors();
   }
  catch (IOException e)
   {
   e.printStackTrace();
   }
  }
*/
 
 void parseStandardColors() throws IOException;

 GateColor get(int curcol);

 int size();

 GateColor getRandomColor();

 GateColor getUnusedColor(HashSet<GateColor> colset);

};

#endif // __H
 

