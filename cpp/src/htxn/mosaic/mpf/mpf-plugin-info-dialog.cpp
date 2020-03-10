
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

//#ifdef HIDE

#include "mpf-plugin-info-dialog.h"

#include "styles.h"

#include "add-minimize-frame.h"

#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QDateTime>

//USING_KANS(MPF)

MPF_Plugin_Info_Dialog::MPF_Plugin_Info_Dialog(MPF_Plugin_Info* info)
{
 setWindowTitle("IQmol");

 button_box_ = new QDialogButtonBox(this);

 button_ok_ = new QPushButton("OK");

 button_cancel_ = new QPushButton("Cancel");

 button_ok_->setDefault(false);
 button_ok_->setAutoDefault(false);

 button_ok_->setDefault(true);

 button_ok_->setStyleSheet(basic_button_style_sheet_());
 button_cancel_->setStyleSheet(basic_button_style_sheet_());

 button_box_->addButton(button_ok_, QDialogButtonBox::AcceptRole);

 button_box_->addButton(button_cancel_, QDialogButtonBox::RejectRole);

 connect(button_box_, SIGNAL(accepted()), this, SLOT(accept()));
 connect(button_box_, SIGNAL(rejected()), this, SLOT(close()));

 main_layout_ = new QVBoxLayout;

 main_tab_widget_ = new QTabWidget(this);

 QString styles = tab_style_sheet_();

 QString line_clr = "rgb(197, 212, 217)";
 QString normal_bkg = "rgb(237, 232, 237)";
 QString back_bkg = "rgb(207, 217, 219)"; // "rgb(197, 212, 217)";
 QString mid_bkg = "rgb(207, 217, 219)";


 styles.append(group_box_style_sheet_().arg(normal_bkg).arg(mid_bkg).arg(line_clr));

 styles.append(QString(
   "QFrame {background-color: %1;}\n"   
   "QLabel {background-color: %2;}\n").arg(back_bkg).arg(normal_bkg)
);

 main_tab_widget_->setStyleSheet(styles); 

 basic_info_frame_ = new QFrame(this);

 basic_info_group_box_ = new QGroupBox("Plugin Origin", basic_info_frame_); 

 basic_info_layout_ = new QVBoxLayout;

 basic_form_layout_ = new QFormLayout;
 basic_form_layout_->addRow("Plugin Name: ", new QLabel("ETS", basic_info_frame_));
 basic_form_layout_->addRow("Plugin Version: ", new QLabel("1.0.0", basic_info_frame_));
 basic_form_layout_->addRow("Plugin Provider: ", new QLabel("Educational Testing Service", basic_info_frame_));

 plugin_active_layout_ = new QHBoxLayout;
 plugin_active_ckb_ = new QCheckBox("Active", basic_info_frame_);
 plugin_active_ckb_->setChecked(true);
 plugin_active_layout_->addWidget(plugin_active_ckb_);
 plugin_active_button_ = new QPushButton("Deactivate", basic_info_frame_);
 plugin_active_button_->setStyleSheet(colorful_small_button_style_sheet_());
 plugin_active_layout_->addWidget(plugin_active_button_);
 plugin_active_layout_->addStretch();

 basic_form_layout_->addRow("Plugin State: ", plugin_active_layout_);

 basic_info_group_box_->setLayout(basic_form_layout_);
 basic_info_layout_->addWidget(basic_info_group_box_);

 can_group_box_ = new QGroupBox("Plugin Can", basic_info_frame_);
 can_layout_ = new QHBoxLayout;
 can_send_ckb_ = new QCheckBox("Send Requests", basic_info_frame_);
 can_receive_ckb_ = new QCheckBox("Receive Requests", basic_info_frame_);
 can_launch_ckb_ = new QCheckBox("Launch Applications", basic_info_frame_);
 can_send_ckb_->setChecked(true);
 can_receive_ckb_->setChecked(true);
 can_launch_ckb_->setChecked(true);

 can_layout_->addWidget(can_send_ckb_);
 can_layout_->addWidget(can_receive_ckb_);
 can_layout_->addWidget(can_launch_ckb_);

 can_group_box_->setLayout(can_layout_);
 basic_info_layout_->addWidget(can_group_box_);

 basic_list_group_box_ = new QGroupBox("View ETS Plugin Applications", basic_info_frame_);
 basic_list_layout_ = new QGridLayout;
 basic_list_layout_->setColumnStretch(0, 1);
 basic_list_layout_->setColumnStretch(2, 1);

 view_local_application_list_ = new QPushButton("Local Applications", basic_info_frame_);
 view_application_list_ = new QPushButton("Browse All (launches web browser)", basic_info_frame_);

 view_local_application_list_->setStyleSheet(colorful_small_button_style_sheet_());
 view_application_list_->setStyleSheet(colorful_small_button_style_sheet_());

 basic_list_layout_->addWidget(view_local_application_list_, 0, 1);
 basic_list_layout_->addWidget(view_application_list_, 1, 1);

 basic_list_group_box_->setLayout(basic_list_layout_);

 basic_info_layout_->addWidget(basic_list_group_box_); 


 basic_view_group_box_ = new QGroupBox("Documentation", basic_info_frame_);
 basic_view_layout_ = new QGridLayout;
 basic_view_layout_->setColumnStretch(0, 1);
 basic_view_layout_->setColumnStretch(2, 1);

 view_mosaic_documentation_ = new QPushButton("View Mosaic Documentation", basic_info_frame_);
 view_plugin_documentation_ = new QPushButton("View ETS Plugin Documentation", basic_info_frame_);

 view_mosaic_documentation_->setStyleSheet(colorful_small_button_style_sheet_());
 view_plugin_documentation_->setStyleSheet(colorful_small_button_style_sheet_());

 basic_view_layout_->addWidget(view_mosaic_documentation_, 0, 1);
 basic_view_layout_->addWidget(view_plugin_documentation_, 1, 1);

 basic_view_group_box_->setLayout(basic_view_layout_);
 basic_info_layout_->addWidget(basic_view_group_box_); 

 basic_info_layout_->addStretch();

 basic_info_frame_->setLayout(basic_info_layout_);

 main_tab_widget_->addTab(basic_info_frame_, "Basic Plugin Info");

 request_info_frame_ = new QFrame(this);
 request_info_layout_ = new QVBoxLayout;

 QGroupBox* request_app_box_ = new QGroupBox("Application Info", request_info_frame_);

 request_app_layout_ = new QFormLayout;

 request_app_layout_->addRow("Source Application Name: ", new QLabel("XpdfReader", request_info_frame_));
 request_app_layout_->addRow("Source Application Path: ", new QLabel("/home/.../xpdf-console", request_info_frame_));
 request_app_layout_->addRow("Target Application Name: ", new QLabel("IQmol", request_info_frame_));
 request_app_layout_->addRow("Target Application Path: ", new QLabel("/home/.../IQmol", request_info_frame_));
 
 request_app_box_->setLayout(request_app_layout_);
 request_info_layout_->addWidget(request_app_box_);


 QGroupBox* request_form_box_ = new QGroupBox("Request Info", request_info_frame_);
 request_form_layout_ = new QFormLayout;

 request_form_layout_->addRow("Request Resource Description: ", new QLabel("Lactose (3D View)", request_info_frame_));

 request_form_layout_->addRow("Request Resource Type: ", new QLabel("Molecular Data File", request_info_frame_));

 request_form_layout_->addRow("Request Resource File: ", new QLabel("14641-93-1.mol", request_info_frame_));

 request_detail_layout_ = new QHBoxLayout;
 request_detail_layout_->addWidget(new QLabel("NTXH", request_info_frame_));
 request_detail_button_ = new QPushButton("View Request Details", request_info_frame_);
 request_detail_button_->setStyleSheet(colorful_small_button_style_sheet_());
 request_detail_layout_->addWidget(request_detail_button_);
 request_detail_layout_->addStretch();

 request_form_layout_->addRow("Request Format: ", request_detail_layout_);
 request_form_box_->setLayout(request_form_layout_);

 request_info_layout_->addWidget(request_form_box_);

 launch_form_box_ = new QGroupBox("Launch Info", request_info_frame_);
 launch_form_layout_ = new QFormLayout;
 
 launch_form_layout_->addRow("TimeStamp: ", new QLabel(QDateTime::currentDateTime().toString(), request_info_frame_));

 launch_form_layout_->addRow("Launch/Request Info: ", new QLabel("Not Applicable", request_info_frame_));

 launch_form_box_->setLayout(launch_form_layout_);

 request_info_layout_->addWidget(launch_form_box_);

 request_info_frame_->setLayout(request_info_layout_);

 main_tab_widget_->addTab(request_info_frame_, "Request/Launch Info");

 main_tab_widget_->addTab(new QFrame(), "Cloud Service Info");
 main_tab_widget_->addTab(new QFrame(), "User Account Info");

 main_layout_->addWidget(main_tab_widget_);


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
}

MPF_Plugin_Info_Dialog::~MPF_Plugin_Info_Dialog()
{

}

//#endif //def HIDE
