
//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <QApplication>
#include <QGraphicsView>

#include <QList>
#include <QDebug>

#include <QMessageBox>

#include <QMenu>

#include <QGraphicsItem>

#include <QScreen>
#include <QTimer>
#include <QTime>

#include <QImage>

#include <QApplication>
#include <QDesktopWidget>

#include <QFileDialog>

#include "defines.h"

#include "ScignStage-ling/ScignStage-ling-dialog.h"

#include "ScignStage-ling/xpdf-bridge.h"

#ifdef USING_LEXPAIR
#include "lexpair/lexpair-dialog.h"
#endif // USING_LEXPAIR

#include "dsmain/language-sample.h"

#include "dsmain/language-sample-group.h"

#include "dsmain/dataset.h"

#ifdef USING_KPH
#include "phaon-ir/phr-code-model.h"
#include "phaon-lib/phr-runner.h"
#include "phr-direct-eval/phr-direct-eval.h"
#include "phaon-ir/table/phr-symbol-scope.h"
#include "phaon-ir/table/phr-channel-group-table.h"
#include "phaon-ir/scopes/phr-runtime-scope.h"
#include "phaon-ir/scopes/phr-scope-system.h"
extern void init_test_functions(PhaonIR& phr, PHR_Code_Model& pcm,
  PHR_Channel_Group_Table& table, PHR_Symbol_Scope& pss);
#endif // USING_KPH

#include "application-model/application-model.h"


#ifdef USING_CONFIG_DIALOG
#include "application-model/application-config-model.h"
#include "application-model/application-model.h"
#include "config-dialog/config-dialog.h"
#endif


#include "kans.h"

#include "textio.h"

USING_KANS(TextIO)

#ifdef USING_KPH
USING_KANS(Phaon)
#endif

//?USING_QSNS(ScignStage)

#ifdef USING_CONFIG_DIALOG
void launch_config_dialog(Config_Dialog*& dlg, QWidget* parent)
{
 if(!dlg)
 {
  dlg = new Config_Dialog(parent);
 }

 dlg->set_reset_callback([]()
 {
  Application_Config_Model::reset(
  {
   DEFINES_SRC_FOLDER "/UNIBUILD-custom_defines.h",
   CHOICES_PRI_FOLDER "/UNIBUILD-custom_choices.pri",
   UNIBUILD_PRI_FOLDER "/build-custom.pro",
   CUSTOM_LIBS_PRI_FOLDER "/_xpdf.pri",
   CUSTOM_LIBS_PRI_FOLDER "/_kph.pri",
   CUSTOM_LIBS_PRI_FOLDER "/_ss3d.pri",
  }, ".reset");
 });

 dlg->set_proceed_callback([&dlg](QString qs)
 {
  qDebug() << qs;

  Application_Config_Model acm;
  acm.parse_config_code(qs);
  {
   QString result;
   QString f = acm.insert_to_defines(DEFINES_SRC_FOLDER "/UNIBUILD-custom_defines.h", result);
   save_file(f, result);
  }

  {
   QString result;
   QString f = acm.insert_to_choices(CHOICES_PRI_FOLDER "/UNIBUILD-custom_choices.pri", result);
   save_file(f, result);
  }

  {
   QString result;
   QString f = acm.insert_to_unibuild(UNIBUILD_PRI_FOLDER "/build-custom.pro", result);
   save_file(f, result);
  }

  {
   QMap<QString, QString> result;
   QMap<QString, QString> files {{
     { "xpdf", CUSTOM_LIBS_PRI_FOLDER "/_xpdf.pri" },
     { "kph", CUSTOM_LIBS_PRI_FOLDER "/_kph.pri" },
     { "ss3d", CUSTOM_LIBS_PRI_FOLDER "/_ss3d.pri" }
    }};
   acm.insert_to_custom_libs(files, result);

   QMapIterator<QString, QString> it(result);

   while(it.hasNext())
   {
    it.next();
    save_file(it.key(), it.value());
   }
  }

  dlg->register_proceed_completed(qs);
 });

 dlg->show();
}
#endif //def HIDE


int main(int argc, char **argv)
{
 QApplication qapp(argc, argv);
 qapp.setWindowIcon(QIcon(DEFAULT_ICON_FOLDER "/app-icon.png"));

 Dataset ds;
 ds.load_from_file(DEFAULT_NTXH_FOLDER  "/ctg.ngml.ntxh");

 ds.set_pdf_path(DEFAULT_NTXH_FOLDER  "/main.pdf");


#ifdef USING_XPDF
 XPDF_Bridge xpdf_bridge(argc, argv);
 ScignStage_Ling_Dialog dlg (&xpdf_bridge, &ds);
#else
 ScignStage_Ling_Dialog dlg (nullptr, &ds);
#endif

 dlg.set_replace_dataset_function([](QString path) -> Dataset*
 {
  Dataset* result = new Dataset;
  result->load_from_file(path);
  if(result->groups().isEmpty())
    return nullptr;
  return result;
 });

#ifdef USING_KPH
 dlg.set_phr_init_function([&dlg](PHR_Runner& phr, PHR_Symbol_Scope*& pss)
 {
  PHR_Code_Model& pcm = phr.get_pcm();
  pcm.set_origin(phr.origin());
  pcm.set_direct_eval_fn(&phr_direct_eval);
  PHR_Runtime_Scope* prs = new PHR_Runtime_Scope(nullptr);
  pss = new PHR_Symbol_Scope(prs);
  init_test_functions(*phr.get_pcm().phaon_ir(), pcm, phr.get_table(), *pss);
  pcm.scopes()->phr_scope_queue().push_front(prs);
 });
#endif

 Application_Model apm(&dlg);
 dlg.set_application_model(&apm);

#ifdef USING_LEXPAIR
 dlg.set_launch_lexpair_dialog_function([](QString s)
 {
  Lexpair_Dialog* dlg = new Lexpair_Dialog(Lexpair_Dialog::split(s), nullptr);
  dlg->show();
 });
#endif // USING_LEXPAIR

 dlg.set_screenshot_function([&dlg, &qapp]()
 {
  QScreen* screen = QGuiApplication::primaryScreen();
  if (!screen)
    return;
  QApplication::beep();
  int target_window_id  = dlg.winId();

  QTimer::singleShot(10000, [=]
  {
   QPixmap pixmap = screen->grabWindow(target_window_id );
   QString path = SCREENSHOTS_FOLDER "/ScignStage_Ling_Dialog.png";
   qDebug() << "Saving to path: " << path;

   QFile file(path);
   if(file.open(QIODevice::WriteOnly))
   {
    pixmap.save(&file, "PNG");
   }
  });
 });

#ifdef USING_CONFIG_DIALOG
 Config_Dialog* cdlg = nullptr;
 dlg.set_launch_config_function([&cdlg, &dlg]()
 {
  launch_config_dialog(cdlg, &dlg);
 });
#endif

 dlg.show();

 qapp.exec();

}
