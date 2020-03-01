
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "mosaic-menubar.h"

#include <QPainter>
#include <QWidgetAction>
#include <QScreen>


Mosaic_Menubar::Mosaic_Menubar() : QMenuBar()
{

}

void Mosaic_Menubar::use_default_stylesheet(QString name)
{
 setStyleSheet(QString(R"(#%1{
    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                      stop:0 white, stop:1 darkgray);
    spacing: 3px; /* spacing between menu bar items */
   }

  #%1::item:selected {
    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                      stop:0 yellow, stop:1 darkgray);
  }

  #%1::separator {
     height: 2px;
    background: lightblue;
    margin-left: 10px;
    margin-right: 5px;  }
  )").arg(name));

}

void Mosaic_Menubar::add_to_style_sheet(QString sheet)
{
 setStyleSheet(styleSheet().append(sheet));
}

void Mosaic_Menubar::handle_screenshot(int target_window_id)
{
 QDir qd;
 qd.cdUp();
 QString path = qd.filePath("ScreenShot");
 handle_screenshot(path, target_window_id); 
}


void Mosaic_Menubar::handle_screenshot(QString path, int target_window_id)
{
 QScreen* screen = QGuiApplication::primaryScreen();
 if (!screen)
   return;
 QApplication::beep();
  //int target_window_id  = dlg.winId();

 QTimer::singleShot(10000, [=]
 {
  QPixmap pixmap = screen->grabWindow(target_window_id );
  qDebug() << "Saving to path: " << path;

  QFile file(path);
  if(file.open(QIODevice::WriteOnly))
  {
   pixmap.save(&file, "PNG");
  }
 });
}

void* Mosaic_Menubar::get_action_data(QAction* qa, QString key)
{
 if(QMap<QString, void*>* qm = (QMap<QString, void*>*) qa->data().value<void*>())
 {
  auto it = qm->find(key);
  if(it != qm->end())
    return *it;
 }
 return nullptr;
}

void Mosaic_Menubar::add_action_data(QAction* qa, QString key, void* value)
{
 if(QMap<QString, void*>* qm = (QMap<QString, void*>*) qa->data().value<void*>())
   qm->insert(key, value);
 else
   qa->setData(qVariantFromValue((void*)new QMap<QString, void*>{{key, value}}));
}

// // mosaic
QWidgetAction* Mosaic_Menubar::add_text_separator(QString text, QWidget* parent)
{
 if(!parent)
   parent = this;
 QLabel* lbl = new QLabel(text, parent);
 //?lbl->setMinimumWidth(10); //_this->minimumWidth() - 4);
 QWidgetAction* result = new QWidgetAction(parent);
 result->setDefaultWidget(lbl);
 result->setProperty("menu-separator", true);
 addAction(result); 
 return result;
}


void Mosaic_Menubar::paintEvent(QPaintEvent *e){

     QStyleOption opt;
     opt.init(this);
     QPainter p1(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p1, this);

//return;

    QPainter p(this);
    QRegion emptyArea(rect());

    // Draw the items
    for (int i = 0; i < actions().size(); ++i) {
        QAction* action = actions().at(i);
        QRect adjustedActionRect = this->actionGeometry(action);

        // Fill by the magic color the selected item
        if (action->property("mosaic") == true)
        {
//void* gat_action_data(QAction* qa, QString key);
         if(QLinearGradient* qlg = (QLinearGradient*) get_action_data(action, "QLinearGradient"))
           p.fillRect(adjustedActionRect, *qlg);
         else if(QColor* qc = (QColor*) get_action_data(action, "QColor"))
           p.fillRect(adjustedActionRect, *qc);          
        }

        // Fill by the magic color the selected item
        if (action->property("menu-separator") == true)
        {
         QRect qr(adjustedActionRect.x(), 
           adjustedActionRect.y() + 5, 1, 10);
//         qDebug() << "...";
//         adjustedActionRect.adjust(0, 0, 10, 10);
         p.fillRect(qr, QColor(70,70,70));
         continue;
        }

//        if (i == 2)
//            p.fillRect(adjustedActionRect, QColor(255,0,0));


        // Draw all the other stuff (text, special background..)
        if (adjustedActionRect.isEmpty() || !action->isVisible())
            continue;
        if(!e->rect().intersects(adjustedActionRect))
            continue;

        emptyArea -= adjustedActionRect;
        QStyleOptionMenuItem opt;
        initStyleOption(&opt, action);
        opt.rect = adjustedActionRect;
        style()->drawControl(QStyle::CE_MenuBarItem, &opt, &p, this);
    }

     //draw border
    if(int fw = style()->pixelMetric(QStyle::PM_MenuBarPanelWidth, 0, this)) {
        QRegion borderReg;
        borderReg += QRect(0, 0, fw, height()); //left
        borderReg += QRect(width()-fw, 0, fw, height()); //right
        borderReg += QRect(0, 0, width(), fw); //top
        borderReg += QRect(0, height()-fw, width(), fw); //bottom
        p.setClipRegion(borderReg);
        emptyArea -= borderReg;
        QStyleOptionFrame frame;
        frame.rect = rect();
        frame.palette = palette();
        frame.state = QStyle::State_None;
        frame.lineWidth = style()->pixelMetric(QStyle::PM_MenuBarPanelWidth);
        frame.midLineWidth = 0;
        style()->drawPrimitive(QStyle::PE_PanelMenuBar, &frame, &p, this);
    }
    p.setClipRegion(emptyArea);
    QStyleOptionMenuItem menuOpt;
    menuOpt.palette = palette();
    menuOpt.state = QStyle::State_None;
    menuOpt.menuItemType = QStyleOptionMenuItem::EmptyArea;
    menuOpt.checkType = QStyleOptionMenuItem::NotCheckable;
    menuOpt.rect = rect();
    menuOpt.menuRect = rect();
style()->drawControl(QStyle::CE_MenuBarEmptyArea, &menuOpt, &p, this);
}

