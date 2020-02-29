
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef MPF_PLUGIN_INFO_DIALOG__H
#define MPF_PLUGIN_INFO_DIALOG__H

#include <QDialog>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QFrame>
#include <QScrollArea>


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

 QFormLayout* main_form_layout_;
 QFrame* main_form_frame_;
 QScrollArea* main_scroll_area_;

 MPF_Plugin_Info* info_;


public:


 MPF_Plugin_Info_Dialog(MPF_Plugin_Info* info);

 ~MPF_Plugin_Info_Dialog();

Q_SIGNALS:


public Q_SLOTS:


};

//_KANS(MPF)

#endif // MPF_PLUGIN_INFO_DIALOG__H



