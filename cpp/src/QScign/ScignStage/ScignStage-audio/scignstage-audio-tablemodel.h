
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SCIGNSTAGE_AUDIO_TABLEMODEL__H
#define SCIGNSTAGE_AUDIO_TABLEMODEL__H

#include <QObject>

#include <QMetaType>

#include <QList>

#include <QPoint>

#include <QDialog>
#include <QAbstractTableModel>

#include <functional>

#include "accessors.h"
#include "qsns.h"

#include "nav-protocols/nav-audio-1d-panel.h"

#include "global-types.h"

#include "kans.h"


//QSNS_(ScignStage)
//_QSNS(ScignStage)
//?namespace QScign { namespace ScignStage {



class ScignStage_Audio_TableModel : public QAbstractTableModel
{
 Q_OBJECT

 std::function<void(u4*,QVariant&)> get_data_callback_;


public:

 QVariant data(const QModelIndex& index,
   int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
// , columnCount(), and data().


 ACCESSORS(MACRO_PASTE(std::function<void(u4*,QVariant&)>) ,get_data_callback)

 int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE
 {
  return 0;
 }

 int columnCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE
 {
  return 0;
 }


 ScignStage_Audio_TableModel();

 ~ScignStage_Audio_TableModel();


Q_SIGNALS:

public Q_SLOTS:


};

//_QSNS(ScignStage)


#endif  // SCIGNSTAGE_AUDIO_TABLEMODEL__H


