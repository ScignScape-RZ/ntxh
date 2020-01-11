
#ifndef RZ_NGML_OUTPUT_BUNDLE__H
#define RZ_NGML_OUTPUT_BUNDLE__H

#include "relae-graph/relae-caon-ptr.h"
#include "rz-ngml-connection-descriptor.h"

#include "rzns.h"

class QTextStream;


RZNS_(NGML)

class NGML_Node;
class NGML_Connection_Descriptor;
class NGML_Command_Callback;

struct NGML_Output_Bundle
{
 typedef NGML_Node tNode;

 QTextStream& qts;
 caon_ptr<tNode> node;
 NGML_Connection_Descriptor connection_descriptor;
 caon_ptr<NGML_Command_Callback> cb;

 NGML_Output_Bundle with(QTextStream& new_qts) const;
 NGML_Output_Bundle with(caon_ptr<tNode> n, NGML_Connection_Descriptor descriptor) const;
 NGML_Output_Bundle with(NGML_Connection_Descriptor descriptor) const;
 NGML_Output_Bundle with_node(caon_ptr<tNode> n) const;
 NGML_Output_Bundle with_callback(caon_ptr<NGML_Command_Callback> c) const;
};

struct NGML_Output_Partial_Bundle
{
 typedef NGML_Node tNode;

 QTextStream& qts;
 caon_ptr<tNode> node;

 operator NGML_Output_Bundle()
 {
  return {qts, node, NGML_Connection_Descriptor(), caon_ptr<NGML_Command_Callback> ( nullptr )};
 }
};



_RZNS(NGML)


#endif
