
// // license___here

#include "ImgResource.h"


// package facsanadu.gui.resource;


/**
 * Common icons. By loading them once, memory is conserved
 * 
 * @author Johan Henriksson
 *
 */

byte[] ImgResource::readStreamIntoArray(InputStream is) throws IOException
{
 if(is==null)
   throw new IOException("Inputstream is null");
 byte[] arr=LabnoteUtil.readStreamToArray(is);
 is.close();
 return arr;
}

static QPixmap ImgResource::getIcon(String name)
{
 try 
 {
  QPixmap pm=new QPixmap();
  pm.loadFromData(readStreamIntoArray(ImgResource.class.getResourceAsStream(name)));
  return pm;
 }  
 catch (IOException e) 
 {
  System.err.println("Unable to read "+name+" "+e.getMessage());
  return nullptr;
 }
}


QPixmap ImgResource::imgWindowIcon= getIcon("programIcon.png");

QPixmap ImgResource::moveRight=getIcon("tango-go-next.png");
QPixmap ImgResource::moveLeft=getIcon("tango-go-previous.png");

QPixmap ImgResource::moveUp=getIcon("tango-go-up.png");
QPixmap ImgResource::moveDown=getIcon("tango-go-down.png");

QPixmap ImgResource::icon_delete=getIcon("tango-trash.png");

QPixmap ImgResource::gateEllipse=getIcon("fugue-shape-ellipse.png");
QPixmap ImgResource::gateRect=getIcon("fugue-shape-rect.png");
QPixmap ImgResource::gatePolygon=getIcon("fugue-shape-polygon.png");
QPixmap ImgResource::gateRange=getIcon("shape-interval.png");
QPixmap ImgResource::gateSelect=getIcon("drawSelect.png");


void ImgResource::setWindowIcon(QWidget w)
{
 w.setWindowIcon(new QIcon(imgWindowIcon));
}

QLabel ImgResource::label(QPixmap p)
{
 QLabel lab=new QLabel();
 lab.setPixmap(p);
 return lab;
}

