
// // license___here

#include "ViewRenderer.h"

#include "ViewSettings.h"
#include "Histogram.h"
#include "ViewTransform.h"

#include "../data/ChannelInfo.h"
#include "../data/Dataset.h"

#include "../gates/GatingResult.h"

#include "../gates/gate-info.h"

#include "gate/GateRenderer.h"
#include "gate/GateRendererManager.h"


#include <QtMath>


// package facsanadu.gui.view;


/**
 * 
 * Renderer of one view
 * 
 * @author Johan Henriksson
 *
 */
int ViewRenderer::labelOffset = 15;

void ViewRenderer::renderData(ViewSettings* viewsettings, Dataset* segment,
  GatingResult* gr, ViewTransform* trans, QPainter& pm, int rendermax)
{
 if(viewsettings->isHistogram())
  renderHistogram(viewsettings, segment, gr, trans, pm);

 else
  renderXY(viewsettings, segment, gr, trans, pm, rendermax);
}
 
void ViewRenderer::renderGates(ViewSettings* viewsettings, Dataset* segment,
  GatingResult* gr, ViewTransform* trans, QPainter& pm, 
  LinkedList<GateHandle*> handles, int rendermax)
{
 Q_UNUSED(gr)
 Q_UNUSED(rendermax)
 Q_UNUSED(segment)

 //Draw all gates
 drawgatesRecursive(pm, trans, viewsettings->gate(), viewsettings, handles);
}
 
 
 
 /**
 * Render histogram
 * @param handles 
 */
void ViewRenderer::renderHistogram(ViewSettings* viewsettings, Dataset* segment, GatingResult* gr, ViewTransform* trans, QPainter& pm)
{
 QList<ChannelInfo*> chans = segment->getChannelInfo();
 //Headache - for scaling, here it would make more sense to scale by the output histograms rather than just datasize
 
 Histogram* h = viewsettings->computeHistogram(segment, gr); //better if this was only once!
 
 pm.setPen(QPen(QColor::fromRgb(0,0,0)));
 pm.setBrush(QBrush(Qt::gray));

 double magicConstant = 0.2 * qSqrt(h->getNumBins()) * viewsettings->zoomY();

 double binw = 1.0/(h->getNumBins() + 1);
 for(int i = 0; i < h->getNumBins(); i++)
 { 
  double frac = h->getFrac(i);
  int x1 = trans->mapGeneralToScreenX(i * binw);
  int x2 = trans->mapGeneralToScreenX((i+1) * binw);
  int y1 = trans->mapGeneralToScreenY(0); 
  int y2 = trans->mapGeneralToScreenY(frac * magicConstant); //here is the problem
  pm.drawRect(QRect(x1, y1, x2 - x1, y2 - y1));
 }

 //Draw boundary
 QString labelX = chans.at( viewsettings->indexX() )->formatName();
 QString labelY = "Fraction";
 drawHeaderLines(pm, trans, labelX, labelY);
 
 //Draw all gates
// drawgatesRecursive(pm, trans, viewsettings->gate, viewsettings, handles);
}

 /**
 * Draw scatter plot
 */
void ViewRenderer::renderXY(ViewSettings* viewsettings, Dataset* ds,
  GatingResult* gr, ViewTransform* trans, QPainter& pm, int rendermax)
{
 QList<ChannelInfo*> chans = ds->getChannelInfo();

 QList<Gate*> listgates = gr->getIdGates();

 QVector<int> colr(listgates.size());
 QVector<int> colg(listgates.size());
 QVector<int> colb(listgates.size());

// int colr[]=new int[listgates.size()];
// int colg[]=new int[listgates.size()];
// int colb[]=new int[listgates.size()];

 for(int i=0; i<listgates.size(); i++)
 {
  Gate* g = listgates.at(i);
  if(g != nullptr)
  {
   GateColor c ( g->color() );
   colr[i] = c.r();
   colg[i] = c.g(); 
   colb[i] = c.b();
  }
 }
 
 QPen pen(QColor::fromRgb(0,0,255));
 pen.setWidth(2);
 pm.setPen(pen);

 QColor thecol; //=new QColor();
 QList<int> accepted = gr->getAcceptedFromGate(viewsettings->gate() );
 if(! accepted.isEmpty())
 {
  for(int i=0; i<accepted.size() && i < rendermax; ++i)
  {
   int ind = accepted.at(i);
   double chanX;
   double chanY;

//  chanX=viewsettings->transformation.transform(ds, ind, viewsettings->indexX);
//  chanY=viewsettings->transformation.transform(ds, ind, viewsettings->indexY);
   chanX = ds->getAsFloatCompensated(ind, viewsettings->indexX() );
   chanY = ds->getAsFloatCompensated(ind, viewsettings->indexY() );
  
   int x = trans->mapFcsToScreenX(chanX);
   int y = trans->mapFcsToScreenY(chanY);

   int colid = gr->getGateIntIDForObs(ind);

  //TODO //note: there are some nasty cases when i can be outside range. race condition!
   if(colid < colr.length())
     thecol.setRgb(colr[colid], colg[colid], colb[colid]); 

//  else
//   System.out.println("warning race condition: id out of range "+colid+", has up to "+colr.length);

   pen.setColor(thecol);
   pm.setPen(pen);
   pm.drawPoint(x, y);  
  }
 }
 else
  {}  //System.out.println("gating not done yet");
 
 
 //Draw boundary
 QString labelX = chans.at(viewsettings->indexX() )->formatName();
 QString labelY = chans.at(viewsettings->indexY() )->formatName();
 drawHeaderLines(pm, trans, labelX, labelY);
}


/**
 * Draw things surrounding graph
 */
void ViewRenderer::drawHeaderLines(QPainter& pm, ViewTransform* trans, 
  QString labelX, QString labelY)
{
 //Draw labels
 QFontMetrics fm = pm.fontMetrics();
 pm.setPen(QColor::fromRgb(0,0,0));
 pm.drawText( (trans->getTotalWidth() - fm.boundingRect(labelX).width()) / 2, 
  trans->getTotalHeight() - labelOffset, labelX);
 pm.save();
 pm.translate(labelOffset, 
   (trans->getTotalHeight() + fm.boundingRect(labelY).width()) / 2);
 pm.rotate(-90);
 pm.drawText(0, 0, labelY);
 pm.restore();

 //Draw lines
 pm.setPen(QColor::fromRgb(0,0,0));
 int off2 = 5;

 pm.drawLine(
  trans->graphOffsetXY(), off2, 
  trans->graphOffsetXY(), trans->getTotalHeight() - trans->graphOffsetXY() );

 pm.drawLine(
  trans->graphOffsetXY(), trans->getTotalHeight() - trans->graphOffsetXY(), 
  trans->getTotalWidth() - off2, 
  trans->getTotalHeight() - trans->graphOffsetXY() );

}

 /**
 * Draw all gates recursively
 */
void ViewRenderer::drawgatesRecursive(QPainter& pm, ViewTransform* trans, 
  Gate* parent, ViewSettings* viewsettings, LinkedList<GateHandle*> handles)
{
 for(Gate* g : parent->children() )
 {
  pm.setPen(QColor::fromRgb(255,0,0));
  pm.setBrush(QBrush(Qt::transparent));
  GateRenderer* rend = GateRendererManager::getGateRenderer(g);
  rend->render(g, pm, trans, viewsettings, handles);
  drawgatesRecursive(pm, trans, g, viewsettings, handles);
 }
}


