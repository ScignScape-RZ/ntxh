
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "test-functions.h"

#include "phaon-ir/types/phr-type-system.h"
#include "phaon-ir/phr-code-model.h"
#include "phaon-ir/channel/phr-channel-group.h"
#include "phaon-ir/table/phr-channel-group-table.h"

#include "phaon-ir/channel/phr-channel-system.h"
#include "phaon-ir/channel/phr-carrier.h"
#include "phaon-ir/phaon-ir.h"

#include "phaon-ir/scopes/phr-scope-system.h"

#include <QTextStream>

#include <QDebug>

#include <QEventLoop>

USING_KANS(Phaon)


void test_prss(QString str1, QString str2)
{
 qDebug() << str1;
 qDebug() << str2;
}

void prn(qint32 arg)
{
 qDebug() << arg;
}


void test_0_ss(QString s1, QString s2)
{
 qDebug() << "s1 = " << s1 << "s2 = " << s2;
}

void test_0_s(QString s1)
{
 qDebug() << "s1 = " << s1;
}

QString test_s_ss(QString s1, QString s2)
{
 qDebug() << "s1 = " << s1 << "s2 = " << s2;
 qDebug() << "returning: s_ss";
 return "s_ss";
}

QString test_s_s(QString s1)
{
 qDebug() << "s1 = " << s1;
 qDebug() << "returning: s_s";
 return "s_s";
}

int test_i_ss(QString s1, QString s2)
{
 qDebug() << "s1 = " << s1 << "s2 = " << s2;
 qDebug() << "returning: 66";
 return 66;
}

int test_i_s(QString s1)
{
 qDebug() << "s1 = " << s1;
 qDebug() << "returning: 66";
 return 66;
}


void init_test_functions(PhaonIR& phr, PHR_Code_Model& pcm,
  PHR_Channel_Group_Table& table, PHR_Symbol_Scope& pss)
{
 PHR_Type_System* type_system = pcm.type_system();
 PHR_Channel_System& pcs = *phr.channel_system();

 PHR_Channel_Semantic_Protocol* lambda = pcs["lambda"];
 PHR_Channel_Semantic_Protocol* result = pcs["result"];
 PHR_Channel_Semantic_Protocol* sigma = pcs["sigma"];

 PHR_Channel_Group g1;//(pcm.channel_names());
 {
  PHR_Type* ty = type_system->get_type_by_name("u4");
  PHR_Carrier* phc = new PHR_Carrier;
  phc->set_phr_type(ty);
  //PHR_Channel_Semantic_Protocol* pcsp = pcs["lambda"];
  g1.init_channel(lambda, 1);
  (*g1[lambda])[0] = phc;

//  g1.add_lambda_carrier(
//    {pcm.get_pcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
//     QString()
//    );

  table.init_phaon_function(g1, pss, "prn", 700, &prn);

  //?
  g1.clear_all();
 }

 {
  PHR_Type* ty = type_system->get_type_by_name("str");
  PHR_Carrier* phc1 = new PHR_Carrier;
  phc1->set_phr_type(ty);
  PHR_Carrier* phc2 = new PHR_Carrier;
  phc2->set_phr_type(ty);
  g1.init_channel(lambda, 2);
  (*g1[lambda])[0] = phc1;
  (*g1[lambda])[1] = phc2;

  table.init_phaon_function(g1, pss, "test-prss", 700, &test_prss);

  g1.clear_all();
 }



#ifdef HIDE
 Kauvir_Type_System* type_system = kcm.type_system();

 KCM_Channel_Group g1(kcm.channel_names());
 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, pss, "test_0_ss", 700, &test_0_ss);

  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, pss, "test_0_s", 700, &test_0_s);

  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  g1.add_result_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, pss, "test_s_ss", 600, &test_s_ss);

  g1.clear_all();
 }

#endif //def HIDE

}

//?_KANS(Phaon)


