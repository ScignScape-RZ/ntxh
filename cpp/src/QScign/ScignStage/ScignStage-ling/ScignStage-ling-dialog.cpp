
//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "ScignStage-ling-dialog.h"

#include "defines.h"


#include "styles.h"

#ifdef USING_LEXPAIR
#include "lexpair/lexpair-dialog.h"
#endif // USING_LEXPAIR

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

#include <QTreeWidget>
#include <QWidgetAction>
#include <QComboBox>

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

#include "dsmain/language-sample.h"
#include "dsmain/language-sample-group.h"

#include "xpdf-bridge.h"


#include "phaon-lib/phr-runner.h"
#include "phaon-ir/phr-code-model.h"
#include "phaon-ir/channel/phr-channel-group.h"
#include "phaon-ir/runtime/phr-command-package.h"

#ifdef USING_KPH
#include "phaon-ir/channel/phr-channel-system.h"
#include "phaon-ir/phaon-ir.h"
extern void default_phr_startup(PhaonIR& phr);
#endif


#include "dsmain/dataset.h"

#include "textio.h"

USING_KANS(TextIO)


Q_DECLARE_METATYPE(Language_Sample*)
Q_DECLARE_METATYPE(Language_Sample_Group*)


#include "add-minimize-frame.h"


ScignStage_Ling_Dialog::ScignStage_Ling_Dialog(XPDF_Bridge* xpdf_bridge,
  Dataset* ds,
  QWidget* parent)
  : QDialog(parent), xpdf_bridge_(xpdf_bridge),
    current_sample_(nullptr),
    last_highlight_(nullptr), xpdf_process_(nullptr),
    screenshot_function_(nullptr),
    #ifdef USING_CONFIG_DIALOG
    launch_config_function_(nullptr),
    #endif // USING_CONFIG_DIALOG
    application_model_(nullptr),
    #ifdef USING_LEXPAIR
    launch_lexpair_dialog_function_(nullptr),
    #endif // USING_LEXPAIR
    //xpdf_port_(0),
    current_index_(-1), max_index_(0),
    current_volume_(50), current_group_index_(-1),
    current_open_group_(nullptr),
    no_auto_expand_(nullptr),
    current_peer_index_(0),
    current_section_number_(0)
     // KPH only ...
    #ifdef USING_KPH
    ,current_tcp_msecs_(0)
    ,phr_(nullptr)
    ,tcp_server_(nullptr)
    ,phr_channel_system_(nullptr)
    ,phaonir_(nullptr)
    ,phr_symbol_scope_(nullptr)
    ,phr_init_function_(nullptr)
    #endif
{
 filter_forms_grid_layout_ = new QGridLayout;
 filter_issues_grid_layout_ = new QGridLayout;

 issues_ = ds->issues();

 int fcolmax = 2;
 int icolmax = 5;

 filter_forms_button_group_ = new QButtonGroup(this);
 filter_forms_button_group_->setExclusive(false);
 {
  int c = 0;
  for(QString f: forms_)
  {
   current_filters_.insert(f);
   QCheckBox* cb = new QCheckBox(f, this);
   cb->setChecked(true);
   filter_forms_grid_layout_->addWidget(cb,
     c / fcolmax, c % fcolmax);
   filter_forms_button_group_->addButton(cb);
   ++c;
  }
 }
 for(int i = 0; i < fcolmax; ++i)
   filter_forms_grid_layout_->setColumnStretch(i, 0);

 filter_issues_button_group_ = new QButtonGroup(this);
 filter_issues_button_group_->setExclusive(false);
 {
  int c = 0;
  for(QString i: issues_)
  {
   current_filters_.insert(i);
   QCheckBox* cb = new QCheckBox(i, this);
   cb->setChecked(true);

//   // // temporary while issues are notated in the data set
//   cb->setEnabled(false);

   filter_issues_grid_layout_->addWidget(cb, c / icolmax,
     c % icolmax);
   filter_issues_button_group_->addButton(cb);
   ++c;
  }
 }

 for(int i = 0; i < icolmax; ++i)
   filter_issues_grid_layout_->setColumnStretch(i, 0);

 connect(filter_issues_button_group_,
   SIGNAL(buttonToggled(QAbstractButton*,bool)), this,
   SLOT(checked_label_change(QAbstractButton*,bool)));

 connect(filter_forms_button_group_,
   SIGNAL(buttonToggled(QAbstractButton*,bool)), this,
   SLOT(checked_label_change(QAbstractButton*,bool)));


 button_box_ = new QDialogButtonBox(this);

 button_ok_ = new QPushButton("OK");
 button_proceed_ = new QPushButton("Proceed");
 button_cancel_ = new QPushButton("Cancel");

 button_ok_->setDefault(false);
 button_ok_->setAutoDefault(false);

 button_proceed_->setDefault(false);
 button_proceed_->setAutoDefault(false);

 button_cancel_->setDefault(true);

 button_ok_->setEnabled(false);

 // // unless this is being embedded ...
 button_proceed_->setEnabled(false);
 button_cancel_->setText("Close");

 button_box_->addButton(button_ok_, QDialogButtonBox::AcceptRole);
 button_box_->addButton(button_proceed_, QDialogButtonBox::ApplyRole);
 button_box_->addButton(button_cancel_, QDialogButtonBox::RejectRole);

 button_ok_->setStyleSheet(basic_button_style_sheet_());
 button_proceed_->setStyleSheet(basic_button_style_sheet_());
 button_cancel_->setStyleSheet(basic_button_style_sheet_());


 connect(button_proceed_, SIGNAL(clicked()), this, SLOT(proceed()));
 connect(button_box_, SIGNAL(accepted()), this, SLOT(accept()));
 connect(button_box_, SIGNAL(rejected()), this, SLOT(cancel()));

 main_layout_ = new QVBoxLayout;

 launch_config_button_ = new QPushButton("Customize Build", this);
 take_screenshot_button_ = new QPushButton("Screenshot", this);
 activate_tcp_button_ = new QPushButton("Activate TCP", this);

 launch_config_button_->setStyleSheet(colorful_button_style_sheet_());
 take_screenshot_button_->setStyleSheet(colorful_button_style_sheet_());
 activate_tcp_button_->setStyleSheet(colorful_button_style_sheet_());

 connect(take_screenshot_button_, SIGNAL(clicked()),
   this, SLOT(handle_take_screenshot_requested()));

 connect(activate_tcp_button_, SIGNAL(clicked()),
   this, SLOT(activate_tcp_requested()));

 connect(launch_config_button_, SIGNAL(clicked()),
   this, SLOT(handle_launch_config_requested()));

 paths_layout_ = new QHBoxLayout;
 ds_path_label_ = new QLabel("Path:", this);
 ds_path_line_edit_ = new QLineEdit(this);

 ds_path_open_button_ = new QPushButton("Open", this);
 pdf_path_label_ = new QLabel("PDF Path:", this);
 pdf_path_line_edit_ = new QLineEdit(this);

 connect(ds_path_open_button_, SIGNAL(clicked()),
   this, SLOT(get_replacement_dataset_path()));

 paths_layout_->addWidget(ds_path_label_);
 paths_layout_->addWidget(ds_path_line_edit_);

 paths_layout_->addWidget(ds_path_open_button_);

 paths_layout_->addStretch();

 paths_layout_->addWidget(pdf_path_label_);
 paths_layout_->addWidget(pdf_path_line_edit_);

 set_paths_from_dataset(*ds);

 main_layout_->addLayout(paths_layout_);

 filters_layout_ = new QHBoxLayout;

 filter_forms_group_box_ = new QGroupBox(
   "Filter Forms", this);

 filter_issues_group_box_ = new QGroupBox(
    "Filter Issues", this);

 filter_forms_group_box_->setLayout(filter_forms_grid_layout_);
 filter_issues_group_box_->setLayout(filter_issues_grid_layout_);


 filters_layout_->addWidget(filter_forms_group_box_);
 filters_layout_->addWidget(filter_issues_group_box_);
 filters_layout_->addStretch();

 quasi_toolbar_layout_ = new QGridLayout;
 quasi_toolbar_layout_->setRowStretch(0, 1);
 quasi_toolbar_layout_->addWidget(activate_tcp_button_, 1, 0);
 quasi_toolbar_layout_->addWidget(take_screenshot_button_, 1, 1);
 config_layout_ = new QHBoxLayout;
 config_layout_->addStretch();
 config_layout_->addWidget(launch_config_button_);
 config_layout_->addStretch();
 quasi_toolbar_layout_->addLayout(config_layout_, 2, 0, 1, 2);
 quasi_toolbar_layout_->setRowStretch(3, 1);

 filters_layout_->addLayout(quasi_toolbar_layout_);

 main_layout_->addLayout(filters_layout_);

 full_sentence_layout_ = new QHBoxLayout;

 full_sentence_splitter_ = new QSplitter(this);
 full_sentence_pre_label_ = new QLabel("pre", this);
 full_sentence_post_label_ = new QLabel("post", this);
 full_sentence_plain_text_edit_ = new QPlainTextEdit("main", this);
 full_sentence_splitter_->addWidget(full_sentence_pre_label_);
 full_sentence_splitter_->addWidget(full_sentence_plain_text_edit_);
 full_sentence_splitter_->addWidget(full_sentence_post_label_);

 show_archival_version_button_ = new QPushButton("OFF", this);
 show_archival_version_button_->setStyleSheet(
   colorful_toggle_button_style_sheet_() + "QPushButton{max-width: 35px;}");

 show_archival_version_button_->setToolTip("Set to ON");

 show_archival_version_group_box_ = new QGroupBox("Show Archival", this);
 show_archival_version_layout_ = new QVBoxLayout;
 show_archival_version_layout_->addWidget(show_archival_version_button_);
 show_archival_version_group_box_->setLayout(show_archival_version_layout_);

 show_archival_version_button_->setCheckable(true);
 connect(show_archival_version_button_, &QPushButton::toggled,
   [this](bool checked)
 {
  if(checked)
  {
   show_archival_version_button_->setText("ON");
   show_archival_version_button_->setToolTip("Set to OFF");
   if(current_sample_)
     full_sentence_plain_text_edit_->setPlainText(current_sample_->archival_or_text());
   else if(current_open_group_)
    full_sentence_plain_text_edit_->setPlainText(current_open_group_->get_main_archival_or_text());
  }
  else
  {
   show_archival_version_button_->setText("OFF");
   show_archival_version_button_->setToolTip("Set to ON");

   if(current_sample_)
     full_sentence_plain_text_edit_->setPlainText(current_sample_->text());

   else if(current_open_group_)
    full_sentence_plain_text_edit_->setPlainText(current_open_group_->get_main_text());

  }

 });

 show_archival_version_group_box_->setMaximumWidth(90);

 full_sentence_layout_->addWidget(full_sentence_splitter_);
 full_sentence_layout_->addWidget(show_archival_version_group_box_);

 full_sentence_pre_label_->setStyleSheet("QLabel{background:yellow}");

 full_sentence_plain_text_edit_->setStyleSheet("QLabel{background:white}");
 full_sentence_plain_text_edit_->setMaximumHeight(50);
 full_sentence_post_label_->setStyleSheet("QLabel{background:pink}");

 full_sentence_splitter_->setSizes({1, 10, 1});

 main_layout_->addLayout(full_sentence_layout_);

 middle_layout_ = new QHBoxLayout;

 // //   Foreground

 main_tree_widget_ = new QTreeWidget(this);

 QStringList headers {
  "Text",
  "Form",
  "#",
  "Issue",
  "Page",
  "Section"
 };


 main_tree_widget_->setColumnCount(6);
 main_tree_widget_->setHeaderLabels(headers);

 main_tree_widget_->setColumnWidth(0, 400);
 main_tree_widget_->setColumnWidth(1, 45);
 main_tree_widget_->setColumnWidth(2, 20);
 main_tree_widget_->setColumnWidth(3, 45);
 main_tree_widget_->setColumnWidth(4, 35);
 main_tree_widget_->setColumnWidth(5, 50);

 main_tree_widget_->header()->setStretchLastSection(false);
 main_tree_widget_->header()->setSectionResizeMode(0, QHeaderView::Stretch);

 main_tree_widget_->header()->setContextMenuPolicy(Qt::CustomContextMenu);

 select_section_layout_ = new QHBoxLayout;
 select_section_frame_ = new QFrame(this);
 select_section_label_ = new QLabel("Jump to Section", this);

 select_section_combo_box_ = new QComboBox(this);
 select_section_combo_box_->addItem("<select>");
 select_section_combo_box_->addItem("Cancel");

 for(int i = 1; i <= 32; ++i)
 {
  if(i == 20)
    continue;
  if(i == 31)
    continue;
  select_section_combo_box_->addItem(QString::number(i));
 }

 select_section_combo_box_->setItemData(0, QBrush(Qt::gray), Qt::TextColorRole);
 select_section_combo_box_->setItemData(1, QBrush(Qt::white), Qt::TextColorRole);
 select_section_combo_box_->setItemData(1, QBrush(Qt::gray), Qt::BackgroundColorRole);

 connect(select_section_combo_box_, QOverload<int>::of(&QComboBox::currentIndexChanged),
   [this](int index)
 {
  QSignalBlocker qsb(select_section_combo_box_);
  for(QMenu* qm : popped_up_menus_)
    qm->close();
  if(index > 1)
  {
   current_section_number_ = index - 1;
   handle_section_start();
   select_section_combo_box_->setCurrentIndex(0);
  }
 });

 select_section_frame_->hide();

 select_section_layout_->addWidget(select_section_label_);

 select_section_layout_->addWidget(select_section_combo_box_);

 select_section_frame_->setLayout(select_section_layout_);

 connect(main_tree_widget_->header(), &QHeaderView::customContextMenuRequested, [this](const QPoint& qp)
 {
  int col = main_tree_widget_->header()->logicalIndexAt(qp);
  if(col == 5)
  {
   QMenu* qm = new QMenu(this);
   QWidgetAction* qwa = new QWidgetAction(this);
   select_section_frame_->show();
   qwa->setDefaultWidget(select_section_frame_);
   qm->addAction(qwa);
   popped_up_menus_.push(qm);
   qm->popup(main_tree_widget_->header()->mapToGlobal(qp));
  }
 });

 main_tree_widget_->clear();

 absorb_dataset(*ds);

 connect(main_tree_widget_, &QTreeWidget::itemSelectionChanged,
   [this]()
 {
  QList<QTreeWidgetItem*> ltwi = main_tree_widget_->selectedItems();
  if(ltwi.size() == 1)
  {
   QTreeWidgetItem* twi = ltwi.first();
   handle_user_expand(twi);
  }
 });

 middle_layout_->addWidget(main_tree_widget_);

 main_tree_widget_->setContextMenuPolicy(Qt::CustomContextMenu);

 connect(main_tree_widget_, &QTreeWidget::customContextMenuRequested, [this](const QPoint& qp)
 {
  QTreeWidgetItem* twi = main_tree_widget_->itemAt(qp);
  if(twi)
  {
   int page;
   QString text;
   QStringList qsl;
   if(twi->parent())
   {
    // //  for the double-nested cases (e.g. Dialogs)
    if(twi->parent()->parent())
      twi = twi->parent();
    Language_Sample* ls
      = twi->data(0, Qt::UserRole).value<Language_Sample*>();
    page = 1;//ls->page();
    text = ls->text().simplified();
   }
   else
   {
    Language_Sample_Group* lsg
      = twi->data(0, Qt::UserRole).value<Language_Sample_Group*>();
    page = lsg->page();
    text = lsg->get_main_text().simplified();
//?    qsl = lsg->all_sample_text();
   }
   if(qsl.isEmpty())
   {
    run_sample_context_menu(qp, page, text, [this](int page, int flag)
    {
     open_pdf_file(pdf_file_, page, flag);
    },
    [](QString s)
    {
     QClipboard* clipboard = QApplication::clipboard();
     clipboard->setText(s);
    },
    [this](QString s)
    {
#ifdef USING_LEXPAIR
     if(launch_lexpair_dialog_function_)
       launch_lexpair_dialog_function_(s);
#else
     QMessageBox::warning(this, "Not Built",
       "LexPair / Tri Link Dialog Support is not Part of this Build.");
#endif // USING_LEXPAIR
    });
   }
   else
   {
    run_group_context_menu(qp, page, text, qsl, [this](int page, int flag)
    {
     open_pdf_file(pdf_file_, page, flag);
    },
    [](QString s)
    {
     QClipboard* clipboard = QApplication::clipboard();
     clipboard->setText(s);
    },
    [this](QString s)
    {
#ifdef USING_LEXPAIR
     launch_lexpair_dialog(s);
#else
     // //?
#endif // USING_LEXPAIR
    },
    [](QStringList qsl)
    {
     QClipboard* clipboard = QApplication::clipboard();
     clipboard->setText(qsl.join('\n'));
    },
    [this, twi]()
    {
     highlight(twi, &current_group_index_);
    }
    );
   }
  }
 });

 main_layout_->addLayout(middle_layout_);

 nav_panel_ = new NAV_Ling1D_Panel(0, 100, 50, this);

 connect(nav_panel_, SIGNAL(filtered_up_requested()),
   this, SLOT(handle_filtered_up()));

 connect(nav_panel_, SIGNAL(filtered_down_requested()),
   this, SLOT(handle_filtered_down()));

 connect(nav_panel_, SIGNAL(sample_up_requested()),
   this, SLOT(handle_sample_up()));

 connect(nav_panel_, SIGNAL(sample_down_requested()),
   this, SLOT(handle_sample_down()));

 connect(nav_panel_, SIGNAL(peer_up_requested()),
   this, SLOT(handle_peer_up()));

 connect(nav_panel_, SIGNAL(peer_down_requested()),
   this, SLOT(handle_peer_down()));

 connect(nav_panel_, SIGNAL(section_up_requested()),
   this, SLOT(handle_section_up()));

 connect(nav_panel_, SIGNAL(section_down_requested()),
   this, SLOT(handle_section_down()));


 connect(nav_panel_, SIGNAL(section_start_requested()),
   this, SLOT(handle_section_start()));

 connect(nav_panel_, SIGNAL(section_end_requested()),
   this, SLOT(handle_section_end()));

 connect(nav_panel_, SIGNAL(sample_first_requested()),
   this, SLOT(handle_sample_first()));

 connect(nav_panel_, &NAV_Ling1D_Panel::auto_expand_changed, [this](bool b)
 {
  no_auto_expand_ = b?nullptr:nav_panel_;
  if(current_open_group_)
    check_expand(twi_by_group_[current_open_group_]);
 });

 main_layout_->addWidget(nav_panel_);

 minimize_layout_ = add_minimize_frame(button_box_, [this]
 {
#ifdef USE_UBUNTU_MINIMIZE
   this->setWindowFlags(Qt::Window);
   showMinimized();
#else
   setWindowState(Qt::WindowMinimized);
#endif
 });

 main_layout_->addLayout(minimize_layout_);

 setLayout(main_layout_);

#ifdef USING_XPDF
 // // xpdf connections ...
 if(xpdf_bridge_)
 {
  connect(xpdf_bridge_, SIGNAL(xpdf_is_ready()),
    this, SLOT(handle_xpdf_is_ready()));
 }
#endif // USING_XPDF
}

void ScignStage_Ling_Dialog::get_replacement_dataset_path()
{
 if(replace_dataset_function_)
 {
  QString path = QFileDialog::getOpenFileName(this,
    "Choose Dataset File", DATA_ROOT_DIR);
  if(path.isEmpty())
    return;
  Dataset* ds = replace_dataset_function_(path);
  if(ds)
  {
   main_tree_widget_->clear();
   set_paths_from_dataset(*ds);
   absorb_dataset(*ds);
  }
 }
}


void ScignStage_Ling_Dialog::set_paths_from_dataset(Dataset& ds)
{
 ds_path_line_edit_->setText(ds.file());
 ds_path_line_edit_->setCursorPosition(0);
 pdf_path_line_edit_->setText(ds.pdf_path());
 pdf_path_line_edit_->setCursorPosition(0);
}


void ScignStage_Ling_Dialog::absorb_dataset(Dataset& ds)
{
 QVector<QPair<QPair<QString, int>, QPair<int, int>>>& sd = ds.subdocuments();
 section_pages_first_last_.clear();
 for(auto& it : sd)
   section_pages_first_last_[it.first.second] = it.second;

 pdf_file_ = ds.pdf_path();

 subdocument_kind_ = ds.subdocument_kind();

 samples_ = &ds.samples();
 groups_ = &ds.groups();

 int c = 0;
 for(Language_Sample_Group* group : *groups_)
 {
  ++c;
  QString mt = group->get_main_text().simplified();
  if(mt.isEmpty())
    continue;

  QStringList qsl;

  qsl.push_back(mt);

  qsl.push_back(group->first()->get_form());
  int id = group->id();
  qsl.push_back(QString::number(id));
  qsl.push_back(group->get_issue());
  qsl.push_back(QString::number(group->page()));
  int sn = group->section_num();
  qsl.push_back(QString::number(sn));

  auto it = section_groups_first_last_.find(sn);
  if(it == section_groups_first_last_.end())
  {
   it = section_groups_first_last_.insert(sn, {0, 0});
  }
  QPair<int, int>& pr = *it;
  if(!pr.first)
    pr.first = c;
  pr.second = c;

  QTreeWidgetItem* twi = new QTreeWidgetItem((QTreeWidget*) nullptr,
    qsl);

  twi_by_group_[group] = twi;
  twi->setData(0, Qt::UserRole, QVariant::fromValue(group));

  QString gf = group->get_form();

  for(Language_Sample* samp: *group)
  {
   QStringList qsl;

   QString sp;

   if(sp == "I1")
      sp = "1";
   else if(sp == "I2")
      sp = "2";

   if(sp.isEmpty())
     qsl.push_back(samp->text().simplified());
   else
     qsl.push_back(QString("Speaker %1:").arg(sp));

   QString sf = samp->get_form();

   if(sf != gf)
     qsl.push_back(sf);
   else
     qsl.push_back(QString());

   QString si;
   QString sbi; //? = samp->sub_index();

   if(sbi.endsWith('\''))
   {
    si = "(none)";
   }
   else
   {
    sbi.replace('/', '\'');
    sbi.replace('_', "");
   }

   qsl.push_back(si);

   qsl.push_back(QString());
   qsl.push_back("");
   qsl.push_back("");

   QTreeWidgetItem* stwi = new QTreeWidgetItem((QTreeWidget*) nullptr,
     qsl);
   twi->addChild(stwi);
   stwi->setData(0, Qt::UserRole, QVariant::fromValue(samp));
   if(!sp.isEmpty())
   {
    QStringList qsl; //? = group->all_sample_text();
    qsl.push_back(samp->text().simplified());
    QTreeWidgetItem* sstwi = new QTreeWidgetItem((QTreeWidget*) nullptr,
      qsl);
    stwi->addChild(sstwi);
   }
  }

  main_tree_widget_->addTopLevelItem(twi);
 }


}

#ifdef USING_LEXPAIR
void ScignStage_Ling_Dialog::launch_lexpair_dialog(QString s)
{
 if(launch_lexpair_dialog_function_)
   launch_lexpair_dialog_function_(s);
}
#endif // USING_LEXPAIR

void ScignStage_Ling_Dialog::highlight(QTreeWidgetItem* twi)
{
 if(current_open_group_)
 {
  QTreeWidgetItem* twi = twi_by_group_[current_open_group_];
  twi->setExpanded(false);
  clear_group_foreground(twi);
  if(current_peer_index_)
  {
   clear_child_group_foreground(twi);
   current_peer_index_ = 0;
  }
 }
 current_open_group_ = twi->data(0, Qt::UserRole).value<Language_Sample_Group*>();
 show_full_sentence(current_open_group_);
 current_section_number_ = current_open_group_->section_num();
 set_group_foreground(twi);
}

void ScignStage_Ling_Dialog::highlight(QTreeWidgetItem* twi,
  Language_Sample_Group* g, int* index)
{
 if(current_open_group_)
 {
  QTreeWidgetItem* twi = twi_by_group_[current_open_group_];
  twi->setExpanded(false);
  clear_group_foreground(twi);
  if(current_peer_index_)
  {
   clear_child_group_foreground(twi);
   current_peer_index_ = 0;
  }
 }
 if(!g)
 {
  g = twi->data(0, Qt::UserRole).value<Language_Sample_Group*>();
  if(index)
    *index = g->id() - 1;
 }
 current_open_group_ = g;
 show_full_sentence(g);

 current_section_number_ = g->section_num();

 // // ensure last subitem is visible
 QTreeWidgetItem* stwi = twi->child(twi->childCount() - 1);
 main_tree_widget_->scrollToItem(stwi);
 main_tree_widget_->scrollToItem(twi);
 check_expand(twi);

 set_group_foreground(twi_by_group_[current_open_group_]);
}

void ScignStage_Ling_Dialog::checked_label_change(QAbstractButton* qab, bool checked)
{
 if(checked)
 {
  current_filters_.insert(qab->text());
 }
 else
 {
  current_filters_.remove(qab->text());
 }
}

void ScignStage_Ling_Dialog::handle_filtered_down()
{
 if(current_open_group_)
   find_sample_down(current_open_group_, &current_filters_);
 else
   find_sample_down(groups_->constLast(), &current_filters_);
}

void ScignStage_Ling_Dialog::handle_filtered_up()
{
 if(current_open_group_)
   find_sample_up(current_open_group_, &current_filters_);
 else
   find_sample_up(groups_->first(), &current_filters_);
}

void ScignStage_Ling_Dialog::set_group_foreground(QTreeWidgetItem* twi)
{
 for(int i = 0; i < 6; ++i)
   twi->setForeground(i, QBrush("darkRed"));
}

void ScignStage_Ling_Dialog::clear_group_foreground(QTreeWidgetItem* twi)
{
 for(int i = 0; i < 6; ++i)
   twi->setForeground(i, QBrush("black"));
}

void ScignStage_Ling_Dialog::set_full_sentence_from_child(QTreeWidgetItem* twi)
{
 QTreeWidgetItem* stwi = twi->child(current_peer_index_ - 1);
 Language_Sample* samp = stwi->data(0, Qt::UserRole).value<Language_Sample*>();
 show_full_sentence(samp);
 current_sample_ = samp;
}

void ScignStage_Ling_Dialog::set_child_group_foreground(QTreeWidgetItem* twi)
{
 set_group_foreground(twi->child(current_peer_index_ - 1));
}

void ScignStage_Ling_Dialog::clear_child_group_foreground(QTreeWidgetItem* twi)
{
 clear_group_foreground(twi->child(current_peer_index_ - 1));
}

void ScignStage_Ling_Dialog::handle_section_start()
{
 if(current_open_group_)
 {
  QTreeWidgetItem* twi = twi_by_group_[current_open_group_];
  twi->setExpanded(false);
  clear_group_foreground(twi);
  if(current_peer_index_)
  {
   clear_child_group_foreground(twi);
   current_peer_index_ = 0;
  }
 }
 if(!current_section_number_)
   current_section_number_ = 1;
 current_group_index_ = section_groups_first_last_[current_section_number_].first - 2;
 handle_sample_down();
}

void ScignStage_Ling_Dialog::handle_sample_down()
{
 find_sample_down(nullptr, nullptr);
}

void ScignStage_Ling_Dialog::show_full_sentence(Language_Sample_Group* g)
{
 full_sentence_pre_label_->setText(g->get_main_pre());
 if(show_archival_version_button_->isChecked())
   full_sentence_plain_text_edit_->setPlainText(g->get_main_archival_or_text());
 else
   full_sentence_plain_text_edit_->setPlainText(g->get_main_text());
 full_sentence_post_label_->setText(g->get_main_post());
}

void ScignStage_Ling_Dialog::show_full_sentence(Language_Sample* samp)
{
 full_sentence_pre_label_->setText(samp->pre());

 if(show_archival_version_button_->isChecked())
   full_sentence_plain_text_edit_->setPlainText(samp->archival_or_text());
 else
   full_sentence_plain_text_edit_->setPlainText(samp->text());

 full_sentence_post_label_->setText(samp->post());
}

void ScignStage_Ling_Dialog::expand_sample(int index)
{
 Language_Sample_Group* g  = groups_->at(index);

 if(QTreeWidgetItem* twi = twi_by_group_.value(g))
 {
  current_group_index_ = index;
  expand(twi);
  highlight(twi);
 }
}


void ScignStage_Ling_Dialog::find_sample_down(Language_Sample_Group* start,
  QSet<QString>* temp_filters)
{
 while(true)
 {
  if(current_group_index_ == -1)
    current_group_index_ = 0;
  else if(current_group_index_ == groups_->size() - 1)
    current_group_index_ = 0;
  else
    ++current_group_index_;

  Language_Sample_Group* g  = groups_->at(current_group_index_);


  if(QTreeWidgetItem* twi = twi_by_group_.value(g))
  {
   if(temp_filters)
   {
    if(g == start)
    {
     // // i.e. all way round
     QMessageBox::information(this, "No More",
       "There are no more samples given the current filters.");
     return;
    }
   }
   highlight(twi, g);
   break;
  }
 }
}

void ScignStage_Ling_Dialog::handle_user_expand(QTreeWidgetItem* twi)
{
 twi->setExpanded(true);

 if(Language_Sample_Group* g = twi->data(0, Qt::UserRole).value<Language_Sample_Group*>())
   show_full_sentence(g);
}

void ScignStage_Ling_Dialog::expand(QTreeWidgetItem* twi)
{
 twi->setExpanded(true);
 int cc = twi->childCount();
 while(cc)
 {
  --cc;
  QTreeWidgetItem* stwi = twi->child(cc);
  stwi->setExpanded(true);
 }
}

void ScignStage_Ling_Dialog::check_expand(QTreeWidgetItem* twi)
{
 if(no_auto_expand_)
 {
  twi->setExpanded(false);
  return;
 }
 expand(twi);
}

void ScignStage_Ling_Dialog::handle_section_end()
{
 if(current_open_group_)
 {
  QTreeWidgetItem* twi = twi_by_group_[current_open_group_];
  twi->setExpanded(false);
  clear_group_foreground(twi);
  if(current_peer_index_)
  {
   clear_child_group_foreground(twi);
   current_peer_index_ = 0;
  }
 }
 if(!current_section_number_)
   current_section_number_ = 1;
 current_group_index_ = section_groups_first_last_[current_section_number_].second - 2;
 handle_sample_down();
}

void ScignStage_Ling_Dialog::handle_sample_up()
{
 find_sample_up(nullptr, nullptr);
}

void ScignStage_Ling_Dialog::find_sample_up(Language_Sample_Group* start,
  QSet<QString>* temp_filters)
{
 while(true)
 {
  if(current_group_index_ == -1)
    current_group_index_ = groups_->size() - 1;
  else if(current_group_index_ == 0)
    current_group_index_ = groups_->size() - 1;
  else
    --current_group_index_;

  Language_Sample_Group* g  = groups_->at(current_group_index_);

  if(QTreeWidgetItem* twi = twi_by_group_.value(g))
  {
   if(temp_filters)
   {
    if(g == start)
    {
     // // i.e. all way round
     QMessageBox::information(this, "No More",
                              "NM");
     return;
    }
   }

   highlight(twi, g);
   break;
  }
 }
}

void ScignStage_Ling_Dialog::handle_peer_down()
{
 if(!current_open_group_)
   handle_sample_down();
 QTreeWidgetItem* twi = twi_by_group_.value(current_open_group_);
 if(current_peer_index_ == 0)
 {
  clear_group_foreground(twi);
  current_peer_index_ = 1;
 }
 else if(current_peer_index_ == twi->childCount())
 {
  clear_child_group_foreground(twi);
  current_peer_index_ = 1;
 }
 else
 {
  clear_child_group_foreground(twi);
  ++current_peer_index_;
 }
 set_full_sentence_from_child(twi);
 set_child_group_foreground(twi);
}

void ScignStage_Ling_Dialog::handle_peer_up()
{
 if(!current_open_group_)
   handle_sample_down();
 QTreeWidgetItem* twi = twi_by_group_.value(current_open_group_);
 if(current_peer_index_ == 0)
 {
  clear_group_foreground(twi);
  current_peer_index_ = twi->childCount();
 }
 else if(current_peer_index_ == 1)
 {
  clear_child_group_foreground(twi);
  current_peer_index_ = twi->childCount();
 }
 else
 {
  clear_child_group_foreground(twi);
  --current_peer_index_;
 }
 set_full_sentence_from_child(twi);
 set_child_group_foreground(twi);
}

void ScignStage_Ling_Dialog::handle_section_down()
{
 while(true)
 {
  if(current_section_number_ == 0)
    current_section_number_ = 1;
  else
  {
   Language_Sample_Group* g  = groups_->constLast();
   if(current_section_number_ == g->section_num())
     current_section_number_ = 1;
   else
     ++current_section_number_;
  }
  if(section_groups_first_last_.contains(current_section_number_))
  {
   handle_section_start();
   break;
  }
 }

}

void ScignStage_Ling_Dialog::handle_section_up()
{
 while(true)
 {
  if(current_section_number_ == 0 || current_section_number_ == 1)
  {
   Language_Sample_Group* g  = groups_->constLast();
   current_section_number_ = g->section_num();
  }
  else
    --current_section_number_;
  if(section_groups_first_last_.contains(current_section_number_))
  {
   handle_section_start();
   break;
  }
 }
}


void ScignStage_Ling_Dialog::handle_sample_first()
{
 current_group_index_ = groups_->size() - 1;
 handle_sample_down();
}


void ScignStage_Ling_Dialog::handle_launch_config_requested()
{
 Q_EMIT(launch_config_requested());

#ifdef USING_CONFIG_DIALOG
 if(launch_config_function_)
   launch_config_function_();
#else
 QMessageBox::warning(this, "Not Built",
   "Config Dialog Support is not Part of this Build.");
#endif


}


void ScignStage_Ling_Dialog::handle_take_screenshot_requested()
{
 Q_EMIT(take_screenshot_requested());
 if(screenshot_function_)
   screenshot_function_();
}

void ScignStage_Ling_Dialog::check_phr()
{
#ifdef USING_KPH
 if(!phr_channel_system_)
 {
  phr_channel_system_ = new PHR_Channel_System;
 }
 if(!phaonir_)
 {
  phaonir_ = new PhaonIR(phr_channel_system_);
  default_phr_startup(*phaonir_);
 }
 if(!phr_)
 {
  phr_ = new PHR_Runner(phaonir_->code_model());
  phr_->set_origin(this);
 }
 if(phr_init_function_)
    phr_init_function_(*phr_, phr_symbol_scope_);
#endif // USING_KPH

}

// // KAI
void ScignStage_Ling_Dialog::test_msgbox(QString msg)
{
 QString m = QString("Received Message: %1").arg(msg);
 QMessageBox::information(this, "Test OK", m);
}



void ScignStage_Ling_Dialog::save_to_user_select_file(QString text)
{
 QString f = QFileDialog::getSaveFileName();
 if(!f.isEmpty())
 {
  save_file(f, text);
 }
}

void ScignStage_Ling_Dialog::run_group_context_menu(const QPoint& p, int page, QString text,
  QStringList texts,
  std::function<void(int, int)> pdf_fn,
  std::function<void(QString)> copy_fn,
  std::function<void(QString)> launch_fn,
  std::function<void(QStringList)> copies_fn,
  std::function<void()> highlight_fn)
{
 QMenu* qm = new QMenu(this);
 qm->addAction("Show in Document (requires XPDF)",
   [page, pdf_fn](){pdf_fn(page, 0);});
 qm->addAction(
   QString("Show in Document -- %1 Start").arg(subdocument_kind_),
   [page, pdf_fn](){pdf_fn(page, 1);});
 qm->addAction(
   QString("Show in Document -- %1 End").arg(subdocument_kind_),
   [page, pdf_fn](){pdf_fn(page, 2);});
 qm->addAction("Copy Text to Clipboard",
   [text, copy_fn](){copy_fn(text);});
 qm->addAction("Launch Triple-Link Dialog with Text",
   [text, launch_fn](){launch_fn(text);});
 qm->addAction("Copy Samples to Clipboard",
   [texts, copies_fn](){copies_fn(texts);});
 qm->addAction("Highlight (scroll from here)",
   [highlight_fn](){highlight_fn();});
 QPoint g = main_tree_widget_->mapToGlobal(p);
 qm->popup(g);
}

void ScignStage_Ling_Dialog::run_sample_context_menu(const QPoint& p, int page, QString text,
  std::function<void(int, int)> pdf_fn,
  std::function<void(QString)> copy_fn, std::function<void(QString)> launch_fn)
{
 QMenu* qm = new QMenu(this);
 qm->addAction("Show in Document (requires XPDF)",
   [page, pdf_fn](){pdf_fn(page, 0);});
 qm->addAction(
   QString("Show in Document -- %1 Start").arg(subdocument_kind_),
   [page, pdf_fn](){pdf_fn(page, 1);});
 qm->addAction(
   QString("Show in Document -- %1 End").arg(subdocument_kind_),
   [page, pdf_fn](){pdf_fn(page, 2);});
 qm->addAction("Copy Text to Clipboard",
   [text, copy_fn](){copy_fn(text);});
 qm->addAction("Launch Triple-Link Dialog with Text",
   [text, launch_fn](){launch_fn(text);});
 QPoint g = main_tree_widget_->mapToGlobal(p);
 qm->popup(g);
}


void ScignStage_Ling_Dialog::run_message_by_grid_position(const QPoint& p, int r, int c)
{
//?
// static QMap<QPair<int, int>, void(ScignStage_Ling_Dialog::*)(const QPoint&, int col)>
//   static_map {{
//   {{0, 1}, &run_section_message},
//  }};

// auto it = static_map.find({r, c});
// if(it != static_map.end())
// {
//  (this->**it)(p, c);
//  return;
// }

// if(c == 0)
// {
//  run_sample_context_menu(p, [this, r]
//  {
//   current_index_ = r - 2;
//   play_file_at_current_index();
//  },[this, r]
//  {
//   QString f = files_[r - 2];
//   QString path = SAMPLES_FOLDER "/" + f;

//   QClipboard* clipboard = QApplication::clipboard();
//   clipboard->setText(path);
//  });
// }
}

void ScignStage_Ling_Dialog::send_xpdf_msg(QString msg)
{
 if(xpdf_bridge_)
   xpdf_bridge_->take_message(msg);
}

int ScignStage_Ling_Dialog::resolve_pdf_page(int page, int flag)
{
 bool end;
 switch (flag)
 {
 default:
 case 0: return page;
 case 1: end = false;
  break;
 case 2: end = true;
  break;
 }
 QMapIterator<int, QPair<int, int>> it(section_pages_first_last_);
 int s = 0;
 while(it.hasNext())
 {
  it.next();
  if((page >= it.value().first) && (page <= it.value().second))
  {
   s = it.key();
   break;
  }
 }
 if(s == 0)
   return page;
 if(end)
   return section_pages_first_last_[s].second;
 return section_pages_first_last_[s].first;
}


void ScignStage_Ling_Dialog::open_pdf_file(QString name, int page, int flag)
{
#ifdef USING_XPDF
 page = resolve_pdf_page(page, flag);
 check_launch_xpdf([this, name, page]()
 {
  send_xpdf_msg(QString("open:%1;%2").arg(name).arg(page));
 },[this, name, page]()
 {
  held_xpdf_msg_ = QString("open:%1;%2").arg(name).arg(page);
 });
#else
 QMessageBox::information(this, "XPDF Needed",
   "You need to build the customized XPDF library "
   "to view PDF files from this application.  See "
   "build_quick.pro or build_most.pro "
   "for more information."
 );
#endif
}

void ScignStage_Ling_Dialog::run_kph(const QByteArray& qba)
{
#ifdef USING_KPH
 check_phr();

 PHR_Channel_Group pcg;

 PHR_Command_Package pcp(pcg, phaonir_->channel_system(), phaonir_->type_system());
 pcp.absorb_data(qba);
 phr_->run(pcp, phr_symbol_scope_);

#endif
}

void ScignStage_Ling_Dialog::run_msg(QString msg, QByteArray qba)
{
 qDebug() << QString("received: %1").arg(msg);

 if(msg == "kph")
 {
  run_kph(qba);
 }
}

bool ScignStage_Ling_Dialog::xpdf_is_ready()
{
 if(xpdf_bridge_)
   return xpdf_bridge_->is_ready();
 return false;
}

void ScignStage_Ling_Dialog::handle_xpdf_is_ready()
{
 if(!held_xpdf_msg_.isEmpty())
 {
  send_xpdf_msg(held_xpdf_msg_);
  held_xpdf_msg_.clear();
 }
}

void ScignStage_Ling_Dialog::check_launch_xpdf(std::function<void()> fn,
  std::function<void()> waitfn)
{
 if(xpdf_is_ready())
 {
  fn();
  return;
 }

 if(xpdf_bridge_)
 {
  xpdf_bridge_->init();
  waitfn();
  return;
 }
}


void ScignStage_Ling_Dialog::activate_tcp_requested()
{
#ifdef USING_KPH
 QString waiting_message;

 if(tcp_server_)
 {
  waiting_message = QString("TCP is already started, using IP: %1\nport: %2\n\n")
    .arg(tcp_server_->serverAddress().toString()).arg(tcp_server_->serverPort());
  QMessageBox::information(this, "Already Activated", waiting_message);
  return;
 }
 tcp_server_ = new QTcpServer();
 QMap<qintptr, QByteArray>* temps = new QMap<qintptr, QByteArray>();

 int port = 18261; // // r z 1

 if (!tcp_server_->listen(QHostAddress::LocalHost, port))
 {
  QMessageBox::critical(this, "TCP Initialization Failed",
                         QString("Could not use port: %1.")
                         .arg(tcp_server_->errorString()));
 }
 else
 {
  waiting_message = QString("Using IP: %1\nport: %2\n\n")
     .arg(tcp_server_->serverAddress().toString()).arg(tcp_server_->serverPort());

  QMessageBox::information(this, "TCP is Started",
                            QString(waiting_message));
 }

 QObject::connect(tcp_server_, &QTcpServer::newConnection, [this, temps]
 {
  QTcpSocket* clientConnection = tcp_server_->nextPendingConnection();
  QObject::connect(clientConnection, &QAbstractSocket::disconnected,
    clientConnection, &QObject::deleteLater);
  clientConnection->write("OK");
  QObject::connect(clientConnection, &QTcpSocket::readyRead, [clientConnection, this, temps]
  {
   qintptr sd = clientConnection->socketDescriptor();
   QByteArray received;
   while(clientConnection->bytesAvailable())
   {
    received.append(clientConnection->readAll());
   }
   if(received.endsWith("<//>"))
   {
    received.chop(4);
    QByteArray qba = (*temps)[sd];
    qba.append(received);
    temps->remove(sd);

    int index = qba.indexOf("<<>>");

    if(index != -1)
    {
     int i1 = qba.indexOf('@', index);
     int i2 = qba.indexOf(':', i1);
     QString msg = QString::fromLatin1(qba.mid(index + 4, i1 - index - 4));
     QByteArray ms = qba.mid(i1 + 1, i2 - i1 - 2);
     quint64 msecs = ms.toLongLong();
     if(msecs != current_tcp_msecs_)
     {
      current_tcp_msecs_ = msecs;
      run_msg( msg, qba.mid(i2 + 1) );
     }
    }
    clientConnection->write("END");
   }
   else
   {
    (*temps)[sd] += received;
   }
  });
 });
#else
 QMessageBox::information(this, "Kauvir/Phaon Needed",
   QString(
     "To use TCP for testing/demoing \"Kernel Application Interface\" "
     "functions you need to build several additional libraries "
     "(see the build-order.txt file for Qt project files and %1, line %2).")
     .arg(__FILE__).arg(__LINE__)
 );
#endif
}


ScignStage_Ling_Dialog::~ScignStage_Ling_Dialog()
{
 //  //  Child widgets should delete automatically ...
}


void ScignStage_Ling_Dialog::cancel()
{
 Q_EMIT(rejected());
 Q_EMIT(canceled(this));
 Q_EMIT(rejected());
 close();
}

void ScignStage_Ling_Dialog::accept()
{
 Q_EMIT(accepted(this));
}

