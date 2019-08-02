
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "kph-generator.h"

#include "kph-generator-substitutions.h"


#include "phaon-ir/channel/phr-channel-group.h"
#include "phaon-ir/types/phr-type.h"
#include "phaon-ir/runtime/phr-command-package.h"

#include "phaon-ir/channel/phr-carrier.h"

#include "textio.h"

#include <QDebug>
#include <QDataStream>

USING_KANS(TextIO)

USING_KANS(Phaon)

KPH_Generator::KPH_Generator(QString file_path,
  KPH_Generator_Substitutions* subs)
  :  file_path_(file_path), subs_(subs)
{

}

KPH_Generator::KPH_Generator(KPH_Generator_Substitutions* subs)
  :  subs_(subs)
{

}

void KPH_Generator::close_line(QTextStream& qts)
{
 qts << "\n.\n";
}

void KPH_Generator::encode(PHR_Channel_Group& pcg, QMap<QString, QString> docus,
  QString fn)
{
 PHR_Command_Package pcp(pcg, nullptr, nullptr);
 encode(pcp, docus, fn);
}


void KPH_Generator::encode(PHR_Command_Package& pcp, QMap<QString, QString> docus,
  QString fn)
{
 QString fuxe_name = fn;
 QMap<QString, QPair<int, const PHR_Channel*>> channel_codes;
 pcp.channel_names_to_codes(channel_codes);

 QTextStream qts(&text_);
 qts << "-\nAuto Generated";
 close_line(qts);

 QMapIterator<QString, QString> dit(docus);
 while(dit.hasNext())
 {
  dit.next();
  qts << "%" << dit.key() << ": " << dit.value();
  close_line(qts);
 }

 QString args;
 QTextStream aqts(&args);

 QString types;
 QTextStream tqts(&types);

 QMap<const PHR_Type*, int> tycodes;
 int tyc = 1;

 QMapIterator<QString, QPair<int, const PHR_Channel*>> it(channel_codes);
 while(it.hasNext())
 {
  it.next();
  const PHR_Channel& pch = *it.value().second;
  if(it.key() == "fground")
    fuxe_name = pch.first()->symbol_name(); //pch.get_carrier_at_position(0)->symbol();
  else
  {
   QString chc = QString::number(it.value().first);
   qts << ';' << it.key() << ':' << chc;
   close_line(qts);
   int c = 1;
   //const QVector<PHR_Carrier>& phcs = pch;.carriers();
   for(const PHR_Carrier* phc : pch)
   {
    const PHR_Type* pty = phc->phr_type();
    int ty = tycodes.value(pty);
    if(ty == 0)
    {
     ty = tyc;
     tycodes[pty] = tyc;
     if(pty)
       tqts << '@' << pty->name() << "::" <<
       QString::number(tyc);
     else
       tqts << "@??::" <<
       QString::number(tyc);
     close_line(tqts);
     ++tyc;
    }

    // // field order:
     //    channel (numeric index code)
     //    keyword (for function parameter)
     //    position (carrier's position in channel)
     //    mode (modifier on carrier; spec on carrier state
     //    type code (numeric code)
     //    expression ref (numeric code if carrier holds expression result)
     //    symbolic ref (if carrier holds symbol in lieu of value)
     //    value (if carrier holds actual value)

    //QString src_val;
    QString src_val = subs_? subs_->get_src_value(it.key(), *phc, c - 1)
      : phc->get_src_value();

    aqts << chc << "::" << QString::number(c) << "::"
      << QString::number(ty) << ":::"
      << src_val;
    ++c;
    close_line(aqts);
   }
  }
 }
 qts << types;
 qts << "#1";
 close_line(qts);
 qts << "&:" << fuxe_name;
 close_line(qts);
 qts << args;
 qts << '-';
}

void KPH_Generator::save_kph_file()
{
 save_file(file_path_, text_);
}
