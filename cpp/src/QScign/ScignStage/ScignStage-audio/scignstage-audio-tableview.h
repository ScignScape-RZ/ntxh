
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SCIGNSTAGE_AUDIO_TABLEVIEW__H
#define SCIGNSTAGE_AUDIO_TABLEVIEW__H

#include <QObject>

#include <QMetaType>

#include <QList>

#include <QPoint>

#include <QDialog>
#include <QTableView>

#include <functional>

#include "accessors.h"
#include "qsns.h"

#include "nav-protocols/nav-audio-1d-panel.h"

#include <functional>

#include "kans.h"


//QSNS_(ScignStage)
//_QSNS(ScignStage)
//?namespace QScign { namespace ScignStage {



class ScignStage_Audio_TableView : public QTableView
{

 Q_OBJECT

public:



 ScignStage_Audio_TableView();

 ~ScignStage_Audio_TableView();


Q_SIGNALS:

public Q_SLOTS:


};

//_QSNS(ScignStage)


#endif  // SCIGNSTAGE_AUDIO_TABLEVIEW__H


