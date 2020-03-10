
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef MPF_TEST_DIALOG__H
#define MPF_TEST_DIALOG__H

#include <QDialog>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QCheckBox>
#include <QGroupBox>
#include <QGridLayout>


#include "kans.h"


USING_KANS(MPF)

//KANS_(MPF)

class MPF_Test_Dialog  : public QDialog
{
 Q_OBJECT

 QHBoxLayout* minimize_layout_;

 QDialogButtonBox* button_box_;
 QPushButton* button_prev_;
 QPushButton* button_next_;
 QPushButton* button_suspend_;

 QVBoxLayout* main_layout_;

 QLabel* question_label_;
 QGridLayout* answer_layout_;

 QCheckBox* answer1_ckb_;
 QCheckBox* answer2_ckb_;
 QCheckBox* answer3_ckb_;
 QCheckBox* answer4_ckb_;
 QCheckBox* answer5_ckb_;

public:


 MPF_Test_Dialog();

 ~MPF_Test_Dialog();

Q_SIGNALS:


public Q_SLOTS:


};

//_KANS(MPF)

#endif // MPF_PLUGIN_INFO_DIALOG__H



