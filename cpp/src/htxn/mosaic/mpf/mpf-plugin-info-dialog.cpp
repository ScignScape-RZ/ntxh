
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

//USING_KANS(MPF)

MPF_Plugin_Info_Dialog::MPF_Plugin_Info_Dialog(MPF_Plugin_Info* info)
{
 button_box_ = new QDialogButtonBox(this);

 button_ok_ = new QPushButton("OK");

 button_cancel_ = new QPushButton("Cancel");

 button_ok_->setDefault(false);
 button_ok_->setAutoDefault(false);

 button_cancel_->setDefault(true);

 button_ok_->setStyleSheet(basic_button_style_sheet_());
 button_cancel_->setStyleSheet(basic_button_style_sheet_());

 button_box_->addButton(button_ok_, QDialogButtonBox::AcceptRole);

 button_box_->addButton(button_cancel_, QDialogButtonBox::RejectRole);

 connect(button_box_, SIGNAL(accepted()), this, SLOT(accept()));
 connect(button_box_, SIGNAL(rejected()), this, SLOT(close()));

 main_layout_ = new QVBoxLayout;

 main_tab_widget_ = new QTabWidget(this);

 main_tab_widget_->setStyleSheet(tab_style_sheet_()); 

 basic_info_frame_ = new QFrame(this);
 basic_info_layout_ = new QVBoxLayout;

 basic_form_layout_ = new QFormLayout;
 basic_form_layout_->addRow("Plugin Name: ", new QLabel("ETS", basic_info_frame_));
 basic_form_layout_->addRow("Plugin Version: ", new QLabel("1.0.0", basic_info_frame_));
 basic_form_layout_->addRow("Plugin Provider: ", new QLabel("Educational Testing Service", basic_info_frame_));

 plugin_active_layout_ = new QHBoxLayout;
 plugin_active_ckb_ = new QCheckBox("Active", basic_info_frame_);
 plugin_active_layout_->addWidget(plugin_active_ckb_);
 plugin_active_button_ = new QPushButton("Deactivate", basic_info_frame_);
 plugin_active_layout_->addWidget(plugin_active_button_);

 basic_form_layout_->addRow("Plugin State: ", plugin_active_layout_);
 basic_info_layout_->addLayout(basic_form_layout_);

 can_group_box_ = new QGroupBox("Plugin Can", basic_info_frame_);
 can_layout_ = new QHBoxLayout;
 can_send_ckb_ = new QCheckBox("Send Requests", basic_info_frame_);
 can_receive_ckb_ = new QCheckBox("Receive Requests", basic_info_frame_);
 can_launch_ckb_ = new QCheckBox("Launch Applications", basic_info_frame_);

 can_layout_->addWidget(can_send_ckb_);
 can_layout_->addWidget(can_receive_ckb_);
 can_layout_->addWidget(can_launch_ckb_);

 can_group_box_->setLayout(can_layout_);
 basic_info_layout_->addWidget(can_group_box_);

 basic_info_frame_->setLayout(basic_info_layout_);

 main_tab_widget_->addTab(basic_info_frame_, "Basic Plugin Info");

 request_info_frame_ = new QFrame(this);
 request_form_layout_ = new QFormLayout;
 request_form_layout_->addRow("Source Application", new QLabel("XPDF", request_info_frame_));
 request_info_frame_->setLayout(request_form_layout_);

 main_tab_widget_->addTab(request_info_frame_, "Request/Launch Info");

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
