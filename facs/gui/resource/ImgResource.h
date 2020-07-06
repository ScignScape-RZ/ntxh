
// // license___here_h

#ifndef ImgResource__H
#define ImgResource__H

#include <QLabel>
#include <QPixmap>
#include <QByteArray>
#include <QDataStream>

// package facsanadu.gui.resource;


/**
 * Common icons. By loading them once, memory is conserved
 * 
 * @author Johan Henriksson
 *
 */
class ImgResource
{
 static QPixmap getIcon(QString name);

public:

 /**
  * Read a stream into a byte array
  */

// static QByteArray readStreamIntoArray(InputStream is); // throws IOException;
 
 static QByteArray readStreamIntoArray(QDataStream& qds); // throws IOException;


 /**
  * Get an icon as a resource - this will work even if the icons are embedded into the jar file
  */

 static QPixmap imgWindowIcon; //= getIcon("programIcon.png");

 static QPixmap moveRight; //=getIcon("tango-go-next.png");
 static QPixmap moveLeft; //=getIcon("tango-go-previous.png");

 static QPixmap moveUp; //=getIcon("tango-go-up.png");
 static QPixmap moveDown; //=getIcon("tango-go-down.png");

 static QPixmap icon_delete; //=getIcon("tango-trash.png");

 static QPixmap gateEllipse; //=getIcon("fugue-shape-ellipse.png");
 static QPixmap gateRect; //=getIcon("fugue-shape-rect.png");
 static QPixmap gatePolygon; //=getIcon("fugue-shape-polygon.png");
 static QPixmap gateRange; //=getIcon("shape-interval.png");
 static QPixmap gateSelect; //=getIcon("drawSelect.png");
 
 static void setWindowIcon(QWidget* w);
 static QLabel label(QPixmap p);
 
};

#endif // __H


