
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_RUNNER__H
#define PHR_RUNNER__H


#include "kans.h"

#include "phr-function.h"

#include <QString>
#include <QQueue>

//KANS_CLASS_DECLARE(KCM ,KCM_Channel_Group)
//KANS_CLASS_DECLARE(KCM ,Kauvir_Code_Model)
//USING_KANS(KCM)

//KANS_CLASS_DECLARE(CMD ,KCM_Scope_System)
//USING_KANS(CMD)


//KANS_(PhaonLib)

KANS_(Phaon)

class PHR_Runtime_Scope;
class PHR_Function_Vector;
class PHR_Channel_Group_Table;

class PHR_Channel_Group;
class PHR_Channel_System;
class PHR_Command_Package;

class PHR_Scope_System;
class PHR_Code_Model;

class PHR_Symbol_Scope;

class PHR_Runner
{
// Kauvir_Code_Model* kcm_;
 PHR_Code_Model* pcm_;
 PHR_Scope_System* scopes_;
 PHR_Channel_Group_Table* table_;

 void* origin_;

public:

 PHR_Runner(PHR_Code_Model* pcm);

 ACCESSORS(void* ,origin)

 void init(PHR_Code_Model* pcm);

 PHR_Code_Model& get_pcm()
 {
  return *pcm_;
 }

 PHR_Channel_Group_Table& get_table()
 {
  return *table_;
 }

//? void init_scope_system();

// QQueue<PHR_Symbol_Scope*>& get_phaon_scope_queue();
 QQueue<PHR_Runtime_Scope*>& get_runtime_scope_queue();

 void run(PHR_Channel_Group& pcg, PHR_Channel_System* pcs, PHR_Symbol_Scope* pss);
 void run(PHR_Command_Package& pcp, PHR_Symbol_Scope* pss);


};


//_KANS(PhaonLib)

_KANS(Phaon)

#endif //PHR_RUNNER__H
