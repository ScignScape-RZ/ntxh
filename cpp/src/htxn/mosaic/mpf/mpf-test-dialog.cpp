
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

//#ifdef HIDE

#include "mpf-test-dialog.h"

#include "styles.h"

#include "add-minimize-frame.h"

#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QDebug>

#include <QTextDocument>
#include <QPainter>
#include <QPixmap>

#include <QFileInfo>
#include <QDir>

//QTextDocument

//USING_KANS(MPF)

MPF_Test_Dialog::MPF_Test_Dialog()
{
//? setWindowTitle("Xpdf");

 button_box_ = new QDialogButtonBox(this);

 // // temporary, use this file to get an icon folder ...
 QString folder = DEFAULT_PDF_FILE;
 QFileInfo qfi(folder);
 QDir qd = qfi.absoluteDir();
 qd.cd("icons");
 folder = qd.absolutePath(); 
 qDebug() << folder;

 int w = 13;
 int fs = 13;
 int pb = 10;

 QTextDocument doc_prev;
 doc_prev.setHtml(QString("<img src='%1/larrowx.png' width='%2'><span style='font-size:%3px'>Previous Question</span>").arg(folder).arg(w).arg(fs));
 doc_prev.setTextWidth(doc_prev.size().width());

 QPixmap pixmap_prev(doc_prev.size().width(), doc_prev.size().height());
 pixmap_prev.fill( Qt::transparent );
 QPainter painter_prev(&pixmap_prev);
 doc_prev.drawContents(&painter_prev);

 QTextDocument doc_next;
 doc_next.setHtml(QString("<img src='%1/arrowx.png' width='%2'><span style='font-size:%3px'>Next Question</span>").arg(folder).arg(w).arg(fs).arg(pb));
 doc_next.setTextWidth(doc_next.size().width());

 QPixmap pixmap_next(doc_next.size().width(), doc_next.size().height());
 pixmap_next.fill( Qt::transparent );
 QPainter painter_next(&pixmap_next);
 doc_next.drawContents(&painter_next);

 QTextDocument doc_susp;
 doc_susp.setHtml(QString("<img src='%1/susp.png' width=16><span style='font-size:%2px'>Suspend ...</span>").arg(folder).arg(fs));
 doc_susp.setTextWidth(doc_susp.size().width());

 QPixmap pixmap_susp(doc_susp.size().width(), doc_susp.size().height());
 pixmap_susp.fill( Qt::transparent );
 QPainter painter_susp(&pixmap_susp);
 doc_susp.drawContents(&painter_susp);


// QPushButton button;
// button.setIconSize(pixmap.size());
// button.setIcon(pixmap);
// button.show();

 button_prev_ = new QPushButton(this);
 button_prev_->setIconSize(pixmap_prev.size());
 button_prev_->setIcon(pixmap_prev);

 button_next_ = new QPushButton(this);
 button_next_->setIconSize(pixmap_next.size());
 button_next_->setIcon(pixmap_next);

 button_suspend_ = new QPushButton(this);
 button_suspend_->setIconSize(pixmap_susp.size());
 button_suspend_->setIcon(pixmap_susp);

// button_ok_->setDefault(false);
// button_ok_->setAutoDefault(false);
// button_ok_->setDefault(true);
// button_ok_->setStyleSheet(basic_button_style_sheet_());
// button_cancel_->setStyleSheet(basic_button_style_sheet_());

 button_box_->addButton(button_prev_, QDialogButtonBox::RejectRole);
 button_box_->addButton(button_next_, QDialogButtonBox::AcceptRole);
 button_box_->addButton(button_suspend_, QDialogButtonBox::RejectRole);

 button_box_->setStyleSheet(colorful_small_button_style_sheet_alt_());

 connect(button_box_, SIGNAL(accepted()), this, SLOT(accept()));
 connect(button_box_, SIGNAL(rejected()), this, SLOT(close()));

 main_layout_ = new QVBoxLayout;

 main_layout_->addStretch();
 question_label_ = new QLabel(R"(<b>4</b>. The molecular geometry of
thionyl chloride, SOCl<sub>2</sub>, is best described as:)", this);

 main_layout_->addWidget(question_label_);

 answer_layout_ = new QGridLayout;

 answer1_ckb_ = new QCheckBox("(A) trigonal planar", this);
 answer2_ckb_ = new QCheckBox("(B) T-shaped", this);
 answer3_ckb_ = new QCheckBox("(C) tetrahedral", this);
 answer4_ckb_ = new QCheckBox("(D) trigonal pyramidal", this);
 answer5_ckb_ = new QCheckBox("(E) linear", this);

 answer_layout_->setRowStretch(0, 1);
 answer_layout_->setRowStretch(3, 1);

 answer_layout_->addWidget(answer1_ckb_, 0, 1);
 answer_layout_->addWidget(answer2_ckb_, 0, 2);
 answer_layout_->addWidget(answer3_ckb_, 1, 1);
 answer_layout_->addWidget(answer4_ckb_, 1, 2);
 answer_layout_->addWidget(answer5_ckb_, 2, 1);

 main_layout_->addLayout(answer_layout_);
 main_layout_->addStretch();

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

MPF_Test_Dialog::~MPF_Test_Dialog()
{

}

//#endif //def HIDE
