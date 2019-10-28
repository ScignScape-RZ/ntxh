
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "scignstage-audio-tablemodel.h"

#include "styles.h"




#include <QApplication>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QButtonGroup>
#include <QScrollArea>
#include <QFileDialog>
#include <QTabWidget>
#include <QSplitter>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QGroupBox>

#include <QDirIterator>

#include <QPlainTextEdit>
#include <QTextStream>

#include <QtMultimedia/QMediaPlayer>

#include <QPainter>
#include <QPushButton>
#include <QLabel>

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QTableWidget>
#include <QGraphicsPixmapItem>

#include <QMessageBox>
#include <QDebug>
#include <QClipboard>

#include <QProcess>

#include <QGraphicsView>
#include <QScrollArea>
#include <QTcpServer>
#include <QNetworkAccessManager>

#include <QHeaderView>

#include <QMenu>
#include <QAction>

#include <QListWidget>

//#include "dsmain/test-series.h"
//#include "dsmain/test-sample.h"
//#include "dsmain/audio-sample.h"
//#include "dsmain/assessment-scores-average.h"

#include "xpdf-bridge.h"

//#include "dsmain/test-sentence.h"

//#include "PhaonLib/phaon-runner.h"

//#include "kauvir-phaon/kph-command-package.h"

//#include "kauvir-code-model/kcm-channel-group.h"
//#include "kauvir-code-model/kauvir-code-model.h"

#include "textio.h"

USING_KANS(TextIO)

//USING_KANS(Phaon)

//USING_QSNS(ScignStage)


ScignStage_Audio_TableModel::ScignStage_Audio_TableModel(u1 nc, u1 nr)
  :  number_of_columns_(nc), number_of_rows_(nr)
{
}

QVariant ScignStage_Audio_TableModel::headerData(int section,
  Qt::Orientation orientation, int role) const
{
 if(role != Qt::DisplayRole)
   return {};
 if(orientation == Qt::Vertical)
   return section + 1;
 QString def = QString("?%1").arg(section);
 return headers_.value(section, def);
}


ScignStage_Audio_TableModel::~ScignStage_Audio_TableModel()
{
}

QVariant ScignStage_Audio_TableModel::data(const QModelIndex& index,
  int role) const
{
 if(!get_data_callback_)
   return {};

 QVariant result;
 int r = index.row();
 int c = index.column();

 u4 args [3] = {(u4) r, (u4) c, (u4) role};

 get_data_callback_(args, result);

 return result;
}
