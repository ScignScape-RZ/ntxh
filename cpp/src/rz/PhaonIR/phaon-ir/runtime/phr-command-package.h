
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_COMMAND_PACKAGE__H
#define PHR_COMMAND_PACKAGE__H

#include <QString>

#include "accessors.h"

#include "phaon-ir/channel/phr-channel-group.h"

#include "kans.h"

KANS_(Phaon)


class PHR_Type;
class PHR_Type_Object;
class PHR_Channel_System;
class PHR_Type_System;

class PHR_Command_Package : public PHR_Channel_Group
{
 QString bind_val_;

 PHR_Type_Object* bind_pto_;

 quint64 eval_result_;
 const PHR_Type_Object* result_type_object_;
 QString output_symbol_name_;
 QString string_result_;

 PHR_Channel_System* channel_system_;
 PHR_Type_System* type_system_;

 void parse_from_string_list(QString path, const QStringList& qsl,
   QMap<int, QString>& channel_names, int& current_expression_code);

 void parse_from_string(QString path, const QString& qs,
   QMap<int, QString>& channel_names, int& current_expression_code);

 void parse_from_file(QString path,
   QMap<int, QString>& channel_names, int& current_expression_code);

 void parse_from_file_list(QString path, const QStringList& paths,
   QMap<int, QString>& channel_names, int& current_expression_code);

public:

 PHR_Command_Package(const PHR_Channel_Group& pcg, PHR_Channel_System* pcs, PHR_Type_System* pts);
 PHR_Command_Package(PHR_Channel_System* pcs, PHR_Type_System* pts);

 ACCESSORS(PHR_Type_Object* ,bind_pto)
 ACCESSORS(const PHR_Type_Object* ,result_type_object)
 ACCESSORS(quint64 ,eval_result)
 ACCESSORS(QString ,output_symbol_name)
 ACCESSORS(QString ,string_result)

 ACCESSORS(PHR_Channel_System* ,channel_system)
 ACCESSORS(PHR_Type_System* ,type_system)

 QString* string_result_as_pointer()
 {
  return &string_result_;
 }

 // //  this does not use any PHR functionality
  //    so implementing it in the header makes
  //    it unnecessary to link against the
  //    library just for this one function
 static void read_docus(const QString& text, QMap<QString, QString>& docus)
 {
  QStringList qsl = text.split("\n.\n");
  for(QString qs : qsl)
  {
   switch(qs[0].toLatin1())
   {
   case '%' : // documentation
    {
     int index = qs.indexOf(':');
     if(index != -1)
     {
      docus[qs.mid(1, index - 1)] = qs.mid(index + 1).simplified();
     }
    }
    break;
   default: break;
   }
  }
 }

 void absorb_data(const QByteArray& qba);
 void supply_data(QByteArray& qba) const;

 void parse_from_file(QString path);


 void parse_from_string_list(QString path, const QStringList& qsl);

 void parse_from_string(QString path, const QString& qs);

 void channel_names_to_codes(QMap<QString,
   QPair<int, const PHR_Channel*>>& qmap);


 static QVector<PHR_Command_Package*> parse_multi_from_file(PHR_Channel_System* cs,
   PHR_Type_System* ts, QString path);
 static QVector<PHR_Command_Package*> parse_multi_from_string(PHR_Channel_System* cs,
   PHR_Type_System* ts, QString path,
   const QString& qs);
 static void parse_multi_from_string(PHR_Channel_System* cs,
   PHR_Type_System* ts, QString path,
   const QString& qs, int i1, int i2, QVector<PHR_Command_Package*>& result);

 static void multi_to_map(const QVector<PHR_Command_Package*>& kcps,
   QMap<QString, QVector<PHR_Command_Package*>>& qmap);

 QString sigma_type_name();
 QString moc_signature();


};

_KANS(Phaon)


#endif //  PHR_COMMAND_PACKAGE__H
