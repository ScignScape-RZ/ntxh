
// // license___here

#include "ColorSet.h"


// package facsanadu.gui.colors;


// //

ColorSet::ColorSet()
{
 colors_ = new LinkedList<GateColor>();

}

static ColorSet colorset = new ColorSet();


void ColorSet::parseStandardColors() throws IOException
{
 BufferedReader br=new BufferedReader(new InputStreamReader
   (ColorSet.class.getResourceAsStream("commoncolors.txt")));

 QString line;
 while((line=br.readLine())!=null)
 {
  GateColor c=new GateColor();
  c.r=Integer.parseInt(line.substring(1,1+2),16);
  c.g=Integer.parseInt(line.substring(3,3+2),16);
  c.b=Integer.parseInt(line.substring(5,5+2),16);
  colors.add(c);
 }
 br.close();
}

GateColor ColorSet::get(int curcol)
{
 return colors.get(curcol);
}

int ColorSet::size()
{
 return colors.size();
}



GateColor ColorSet::getRandomColor()
{
 return new GateColor(colors.get((int)(Math.random()*colors.size())));
}

GateColor ColorSet::getUnusedColor(HashSet<GateColor> colset)
{
 for(GateColor c:colors)
 {
  if(!colset.contains(c))
    return c;
  //Fallback - any random color
 }
 return new GateColor(
  (int)(Math.random()*255), 
  (int)(Math.random()*255), 
  (int)(Math.random()*255));
}


