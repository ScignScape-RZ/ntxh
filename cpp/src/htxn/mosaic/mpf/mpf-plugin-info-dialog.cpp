
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


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

 main_form_layout_ = new QFormLayout;

 main_form_layout_->addRow("Plugin Name", new QLabel("ETS"));

 main_scroll_area_ = new QScrollArea(this);
 main_form_frame_ = new QFrame(this);
 main_form_frame_->setLayout(main_form_layout_);

 main_scroll_area_->setWidget(main_form_frame_);

 main_layout_->addWidget(main_scroll_area_);

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
