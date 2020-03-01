
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef MPF_PLUGIN_INFO_DIALOG__H
#define MPF_PLUGIN_INFO_DIALOG__H

#include <QDialog>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QFrame>
#include <QTabWidget>
#include <QCheckBox>
#include <QGroupBox>
#include <QGridLayout>


#include "kans.h"

KANS_CLASS_DECLARE(MPF ,MPF_Plugin_Info)

USING_KANS(MPF)

//KANS_(MPF)

class MPF_Plugin_Info_Dialog  : public QDialog
{
 Q_OBJECT

 QHBoxLayout* minimize_layout_;

 QDialogButtonBox* button_box_;
 QPushButton* button_ok_;
 QPushButton* button_cancel_;
 QVBoxLayout* main_layout_;

 QFrame* basic_info_frame_;

 QFormLayout* basic_form_layout_;
 QVBoxLayout* basic_info_layout_;

 QGroupBox* basic_info_group_box_;

 QGroupBox* basic_view_group_box_;
 QGridLayout* basic_view_layout_;
 QPushButton* view_mosaic_documentation_;
 QPushButton* view_plugin_documentation_;

 QGroupBox* basic_list_group_box_;
 QGridLayout* basic_list_layout_;
 QPushButton* view_local_application_list_;
 QPushButton* view_application_list_;

 QHBoxLayout* plugin_active_layout_;
 QCheckBox* plugin_active_ckb_;
 QPushButton* plugin_active_button_;

 QGroupBox* can_group_box_;
 QHBoxLayout* can_layout_;
 QCheckBox* can_send_ckb_;
 QCheckBox* can_receive_ckb_;
 QCheckBox* can_launch_ckb_;

 QFrame* request_info_frame_;
 QVBoxLayout* request_info_layout_;

 QGroupBox* request_app_box_;
 QFormLayout* request_app_layout_;

 QGroupBox* request_form_box_;
 QFormLayout* request_form_layout_;

 QHBoxLayout* request_detail_layout_;
 QPushButton* request_detail_button_;

 QGroupBox* launch_form_box_;
 QFormLayout* launch_form_layout_;


 QTabWidget* main_tab_widget_;

 MPF_Plugin_Info* info_;


public:


 MPF_Plugin_Info_Dialog(MPF_Plugin_Info* info);

 ~MPF_Plugin_Info_Dialog();

Q_SIGNALS:


public Q_SLOTS:


};

//_KANS(MPF)

#endif // MPF_PLUGIN_INFO_DIALOG__H



