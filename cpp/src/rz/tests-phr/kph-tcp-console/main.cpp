
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "kph-generator/kph-generator.h"

#include "phaon-ir/channel/phr-channel-group.h"

#include "phaon-ir/phr-code-model.h"

#include "phr-direct-eval/phr-direct-eval.h"

#include "phaon-ir/runtime/phr-command-package.h"

#include "phaon-lib/phr-runner.h"

#include "relae-graph/relae-caon-ptr.h"

#include "phr-env/phr-env.h"
#include "phr-fn-doc/phr-fn-doc.h"

#include "test-functions.h"

#include <QObject>

#include "kans.h"

#include "phaon-ir/phaon-ir.h"
#include "phaon-ir/channel/phr-channel-system.h"

extern void default_phr_startup(PhaonIR& phr);

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QCoreApplication>
#include <QDateTime>

#include "kans.h"

USING_KANS(Phaon)


void init_qba(QByteArray& qba)
{
 PHR_Channel_System pcs;

 PhaonIR phr(&pcs);

 default_phr_startup(phr);

 PHR_Command_Package pcp(phr.channel_system(), phr.type_system());
 pcp.parse_from_file( DEFAULT_KPH_FOLDER "/dataset/raw/t1.kph" );

 pcp.supply_data(qba);

 qba.append("<//>");

 QByteArray pre = "<<>>kph@";
 quint64 ms = QDateTime::currentMSecsSinceEpoch();
 pre.append(QByteArray::number(ms));
 pre.append(':');
 qba.prepend(pre);

}

int main_via_socket(int argc, char* argv[])
{
 QCoreApplication app(argc, argv);
 QByteArray qba;

 init_qba(qba);

 QTcpSocket* tcpSocket = new QTcpSocket;
 int port = 18261; // // r z 1

 tcpSocket->connectToHost("Localhost", port);

 QObject::connect(tcpSocket, &QNetworkReply::readyRead,
  [tcpSocket, &app, &qba]()
 {
  QString result = QString::fromLatin1( tcpSocket->readAll() );
  if(result == "OK")
  {
   tcpSocket->write(qba);
  }
  else if(result == "END")
  {
   qDebug() << "OK\n";
   tcpSocket->disconnectFromHost();
   tcpSocket->deleteLater();
   app.exit();
  }
  else
  {
   qDebug() << "Unexpected response: " << result << "\n";
   tcpSocket->disconnectFromHost();
   tcpSocket->deleteLater();
   app.exit();
  }
 });

 return app.exec();
}

int main_via_qnam(int argc, char* argv[])
{
 QCoreApplication app(argc, argv);
 QByteArray qba;

 init_qba(qba);

 QNetworkAccessManager qnam;

 int port = 18261; // // r z 1
 QString addr = QString("http://localhost:%1/").arg(port);

 QNetworkRequest req;

 req.setUrl( QUrl(addr) );
 req.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");

 QNetworkReply* reply = qnam.post(req, qba);

 QObject::connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
  [reply, &app](QNetworkReply::NetworkError code)
 {
  if(code != QNetworkReply::RemoteHostClosedError)
  {
   qDebug() << "Unexpected error: " << code << "\n";
  }
  else
  {
   qDebug() << "OK\n";
  }
  reply->deleteLater();
  app.exit();
 });

 return app.exec();
}


int main(int argc, char* argv[])
{
 // choose one ...
 // // return main_via_socket(argc, argv);
 return main_via_qnam(argc, argv);
}

