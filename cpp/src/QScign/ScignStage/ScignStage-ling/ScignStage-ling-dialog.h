
//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SCIGNSTAGE_LING_DIALOG__H
#define SCIGNSTAGE_LING_DIALOG__H

#include <QObject>

#include <QMetaType>

#include <QList>
#include <QStack>


#include <QPoint>

#include <QDialog>
#include <QTableWidget>

#include <functional>

#include "accessors.h"
#include "qsns.h"

#include "nav-protocols/nav-ling-1d-panel.h"

#include <functional>

#include "kans.h"

KANS_CLASS_DECLARE(DSM ,Language_Sample)
KANS_CLASS_DECLARE(DSM ,Language_Sample_Group)
KANS_CLASS_DECLARE(DSM, Dataset)

USING_KANS(DSM)

class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QTabWidget;
class QTextEdit;
class QFrame;
class QHBoxLayout;
class QVBoxLayout;
class QSlider;
class QPlainTextEdit;
class QBoxLayout;
class QButtonGroup;
class QGroupBox;
class QScrollArea;
class QGridLayout;
class QMediaPlayer;
class QProcess;
class QTcpServer;
class QTreeWidget;
class QTreeWidgetItem;
class QAbstractButton;
class QSplitter;
class QComboBox;

class ScignStage_Clickable_Label;

class XPDF_Bridge;

#ifdef USING_KPH

KANS_(Phaon)

class PHR_Runner;
class PHR_Channel_System;
class PhaonIR;
class PHR_Symbol_Scope;

_KANS(Phaon)
USING_KANS(Phaon)

#endif


class ScignStage_Ling_Dialog : public QDialog
{
 Q_OBJECT

 QHBoxLayout* minimize_layout_;

 QDialogButtonBox* button_box_;
 QPushButton* button_ok_;
 QPushButton* button_cancel_;
 QPushButton* button_proceed_;


 QHBoxLayout* middle_layout_;
 QVBoxLayout* main_layout_;

 QPushButton* launch_config_button_;
 QPushButton* activate_tcp_button_;
 QPushButton* take_screenshot_button_;

 QHBoxLayout* paths_layout_;
 QLabel* ds_path_label_;
 QLineEdit* ds_path_line_edit_;
 QPushButton* ds_path_open_button_;
 QLabel* pdf_path_label_;
 QLineEdit* pdf_path_line_edit_;


 QHBoxLayout* filters_layout_;
 QGridLayout* filter_forms_grid_layout_;
 QGridLayout* filter_issues_grid_layout_;

 QGridLayout* quasi_toolbar_layout_;
 QHBoxLayout* config_layout_;

 QButtonGroup* filter_forms_button_group_;
 QButtonGroup* filter_issues_button_group_;

 QGroupBox* filter_forms_group_box_;
 QGroupBox* filter_issues_group_box_;

 QStringList issues_;
 QStringList forms_;

 QTreeWidget* main_tree_widget_;

 NAV_Ling1D_Panel* nav_panel_;

 XPDF_Bridge* xpdf_bridge_;

 QVector<Language_Sample*>* samples_;
 QVector<Language_Sample_Group*>* groups_;

 QSet<QString> current_filters_;

 QHBoxLayout* full_sentence_layout_;
 QSplitter* full_sentence_splitter_;
 QLabel* full_sentence_pre_label_;
 QLabel* full_sentence_post_label_;
 QPlainTextEdit* full_sentence_plain_text_edit_;

 QVBoxLayout* show_archival_version_layout_;
 QPushButton* show_archival_version_button_;
 QGroupBox* show_archival_version_group_box_;


 QFrame* select_section_frame_;
 QLabel* select_section_label_;
 QComboBox* select_section_combo_box_;
 QHBoxLayout* select_section_layout_;

 QStack<QMenu*> popped_up_menus_;

#ifdef USING_KPH
 PHR_Channel_System* phr_channel_system_;
 PhaonIR* phaonir_;
#endif

 void show_full_sentence(Language_Sample_Group* g);
 void show_full_sentence(Language_Sample* samp);

 void section_to_string(QString& result, bool wl);
 void group_to_string(QString& result, bool wl);

 void save_to_user_select_file(QString text);

 QMap<Language_Sample*, QPair<QLabel*, int> > sample_to_label_map_;

 Language_Sample* current_sample_;

 int current_index_;

 int max_index_;

 QWidget* last_highlight_;

 int current_volume_;

 QProcess* xpdf_process_;

 void* application_model_;

 QString held_xpdf_msg_;

#ifdef USING_KPH
 quint64 current_tcp_msecs_;
 QTcpServer* tcp_server_;
 PHR_Runner* phr_;
 PHR_Symbol_Scope* phr_symbol_scope_;
 std::function<void(PHR_Runner&, PHR_Symbol_Scope*& pss)> phr_init_function_;
#endif

 std::function<void()> screenshot_function_;

#ifdef USING_CONFIG_DIALOG
 std::function<void()> launch_config_function_;
#endif // USING_LEXPAIR

#ifdef USING_LEXPAIR
 std::function<void(QString)> launch_lexpair_dialog_function_;
#endif // USING_LEXPAIR

 int current_group_index_;
 Language_Sample_Group* current_open_group_;

 QMap<Language_Sample_Group*, QTreeWidgetItem*> twi_by_group_;

 void* no_auto_expand_;
 int current_peer_index_;

 int current_section_number_;
 QMap<int, QPair<int, int>> section_groups_first_last_;
 QMap<int, QPair<int, int>> section_pages_first_last_;


 std::function<Dataset*(QString)> replace_dataset_function_;

 QString subdocument_kind_;

 QString pdf_file_;

 bool xpdf_is_ready();
 void check_phr();

 void run_msg(QString msg, QByteArray qba);
 void run_kph(const QByteArray& qba);


 void open_pdf_file(QString name, int page, int flag);
 int resolve_pdf_page(int page, int flag);

 void check_launch_xpdf(std::function<void()> fn,
   std::function<void()> waitfn);
 void send_xpdf_msg(QString msg);

 QString load_about_file(QString name);

 bool ask_pdf_proceed(QString name);

 void set_group_foreground(QTreeWidgetItem* twi);
 void clear_group_foreground(QTreeWidgetItem* twi);

 void set_full_sentence_from_child(QTreeWidgetItem* twi);
 void set_child_group_foreground(QTreeWidgetItem* twi);
 void clear_child_group_foreground(QTreeWidgetItem* twi);

 void run_section_message(const QPoint& p, int col);
 void run_group_message(const QPoint& p, int col);

 void check_expand(QTreeWidgetItem* twi);
 void expand(QTreeWidgetItem* twi);

 void handle_user_expand(QTreeWidgetItem* twi);

 void highlight(QTreeWidgetItem* twi);

 void highlight(QTreeWidgetItem* twi,
   Language_Sample_Group* g, int* index = nullptr);

 void highlight(QTreeWidgetItem* twi,
   int* index)
 {
  highlight(twi, nullptr, index);
 }

 void run_group_context_menu(const QPoint& p, int page, QString text,
   QStringList texts,
   std::function<void(int, int)> pdf_fn,
   std::function<void(QString)> copy_fn,
   std::function<void(QString)> launch_fn,
   std::function<void(QStringList)> copies_fn,
   std::function<void()> highlight_fn);

 void run_sample_context_menu(const QPoint& p, int page, QString text,
   std::function<void(int, int)> pdf_fn,
   std::function<void(QString)> copy_fn,
   std::function<void(QString)> launch_fn);

 void run_message_by_grid_position(const QPoint& p, int r, int c);

 void absorb_dataset(Dataset& ds);

 void set_paths_from_dataset(Dataset& ds);


public:

 ScignStage_Ling_Dialog(XPDF_Bridge* xpdf_bridge,
   Dataset* ds, QWidget* parent = nullptr);

 ~ScignStage_Ling_Dialog();

#ifdef USING_KPH
 ACCESSORS__SET(std::function<void(PHR_Runner&, PHR_Symbol_Scope*&)>, phr_init_function)
#endif // USING_KPH

 ACCESSORS__SET(std::function<void()> ,screenshot_function)

 ACCESSORS__SET(std::function<Dataset*(QString)> ,replace_dataset_function)

#ifdef USING_LEXPAIR
 ACCESSORS__SET(std::function<void(QString)> ,launch_lexpair_dialog_function)
#endif // USING_LEXPAIR

#ifdef USING_CONFIG_DIALOG
 ACCESSORS__SET(std::function<void()> ,launch_config_function)
#endif // USING_CONFIG


 ACCESSORS(void* ,application_model)

 // //  Kernel Application Interface
 void test_msgbox(QString msg);
 void expand_sample(int index);

#ifdef USING_LEXPAIR
 void launch_lexpair_dialog(QString s);
#endif // USING_LEXPAIR

 void find_sample_down(Language_Sample_Group* start,
   QSet<QString>* temp_filters);

 void find_sample_up(Language_Sample_Group* start,
   QSet<QString>* temp_filters);


Q_SIGNALS:
 void canceled(QDialog*);
 void accepted(QDialog*);
 void take_screenshot_requested();
 void launch_config_requested();

public Q_SLOTS:

 void checked_label_change(QAbstractButton* qab, bool checked);

 void get_replacement_dataset_path();

 void handle_xpdf_is_ready();
 void handle_take_screenshot_requested();
 void handle_launch_config_requested();

 void accept();
 void cancel();

 void activate_tcp_requested();

 void handle_sample_down();
 void handle_sample_up();

 void handle_sample_first();

 void handle_filtered_down();
 void handle_filtered_up();

 void handle_peer_down();
 void handle_peer_up();

 void handle_section_down();
 void handle_section_up();

 void handle_section_start();
 void handle_section_end();

};

#endif  // SCIGNSTAGE_LING_DIALOG__H


