
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-command-package.h"

#include "phaon-ir/channel/phr-carrier.h"
#include "phaon-ir/channel/phr-channel-system.h"
#include "phaon-ir/types/phr-type-system.h"
#include "phaon-ir/types/phr-type.h"


#include "textio.h"

USING_KANS(TextIO)

#include <QDataStream>


PHR_Command_Package::PHR_Command_Package(const PHR_Channel_Group& pcg,
  PHR_Channel_System* pcs, PHR_Type_System* pts)
  :  PHR_Channel_Group(pcg), bind_pto_(nullptr),
     eval_result_(0), result_type_object_(nullptr),
     channel_system_(pcs), type_system_(pts)
{

}

PHR_Command_Package::PHR_Command_Package(PHR_Channel_System* pcs, PHR_Type_System* pts)
 :  PHR_Channel_Group(), bind_pto_(nullptr),
    eval_result_(0), result_type_object_(nullptr),
    channel_system_(pcs), type_system_(pts)
{

}

// adopted from qdatastream.h
template <typename Container>
QPair<QDataStream&, void*>& readAssociativeContainer(QPair<QDataStream&, void*>& s, Container& c)
{
    QtPrivate::StreamStateSaver stateSaver(&s.first);

    c.clear();
    quint32 n;
    s.first >> n;
    for (quint32 i = 0; i < n; ++i) {
        typename Container::key_type k;
        typename Container::mapped_type t;
        s >> k >> t;
        if (s.first.status() != QDataStream::Ok) {
            c.clear();
            break;
        }
        c.insertMulti(k, t);
    }

    return s;
}
template <typename Container>
QPair<QDataStream&, void*>& readArrayBasedContainer(QPair<QDataStream&, void*>& s, Container &c)
{
    QtPrivate::StreamStateSaver stateSaver(&s.first);

    c.clear();
    quint32 n;
    s.first >> n;
    c.reserve(n);
    for (quint32 i = 0; i < n; ++i) {
        typename Container::value_type t;
        s >> t;
        if (s.first.status() != QDataStream::Ok) {
            c.clear();
            break;
        }
        c.append(t);
    }

    return s;
}

//template<typename T, typename Container>
//QPair<T&, void*>& operator<<(QPair<T&, void*>& )
//template <typename Container>
//QPair<QDataStream&, void*>& readAssociativeContainer(QPair<QDataStream&, void*>& s, Container& c)
//{


template<typename T>
QPair<T&, void*>& operator>>(QPair<T&, void*>& thet, PHR_Channel_Semantic_Protocol*& rhs)
{
 //rhs = new PHR_Channel_Semantic_Protocol;
 QString n;
 thet.first >> n;
 PHR_Command_Package* pcp = static_cast<PHR_Command_Package*>(thet.second);
 rhs = pcp->channel_system()->value(n);
 //rhs->set_name(n);
 return thet;
}

template<typename T>
QPair<T&, void*>& operator>>(QPair<T&, void*>& thet, PHR_Channel*& rhs)
{
 rhs = new PHR_Channel;
 readArrayBasedContainer(thet, *rhs);
 //thet >> *rhs;
 return thet;
}

template<typename T>
QPair<T&, void*>& operator>>(QPair<T&, void*>& thet, PHR_Carrier& rhs)
{
 QString tn;
 QString sn;
 QString rvs;

 thet.first >> tn;
 thet.first >> sn;
 thet.first >> rvs;

 PHR_Command_Package* pcp = static_cast<PHR_Command_Package*>(thet.second);

 PHR_Type* pty = pcp->type_system()->get_type_by_name(tn);
 rhs.set_phr_type(pty);
 rhs.set_symbol_name(sn);
 rhs.set_raw_value_string(rvs);

 return thet;
}

template<typename T>
QPair<T&, void*>& operator>>(QPair<T&, void*>& thet, PHR_Carrier*& rhs)
{
 rhs = new PHR_Carrier;
 thet >> *rhs;
 return thet;
}

template<typename T>
T& operator<<(T& thet, const PHR_Channel_Semantic_Protocol* rhs)
{
 thet << rhs->name();
 return thet;
}

template<typename T>
T& operator<<(T& thet, const PHR_Channel* rhs)
{
 thet << *rhs;
 return thet;
}

template<typename T>
T& operator<<(T& thet, const PHR_Carrier& rhs)
{
 if(rhs.phr_type())
   thet << rhs.phr_type()->name();
 else
   thet << QString();

 thet << rhs.symbol_name();
 thet << rhs.raw_value_string();
 return thet;
}

template<typename T>
T& operator<<(T& thet, const PHR_Carrier* rhs)
{
 thet << *rhs;
 return thet;
}

void PHR_Command_Package::supply_data(QByteArray& qba) const
{
 QDataStream qds(&qba, QIODevice::WriteOnly);

 qds << output_symbol_name_;
 qds << *this;
}


void PHR_Command_Package::absorb_data(const QByteArray& qba)
{
 QDataStream qds(qba);
 QPair<QDataStream&, void*> pr {qds, this};

 qds >> output_symbol_name_;
 readAssociativeContainer(pr, *this);
}


void PHR_Command_Package::parse_from_string_list(QString path, const QStringList& qsl)
{
 QMap<int, QString> channel_names;
 int current_expression_code = 0;
 parse_from_string_list(path, qsl, channel_names, current_expression_code);
}


void PHR_Command_Package::parse_from_string_list(QString path, const QStringList& qsl,
  QMap<int, QString>& channel_names, int& current_expression_code)
{
 if(!channel_system_)
   return;

 static auto add_carrier_to_channel = [](PHR_Command_Package* pcp, QString ch) -> PHR_Carrier*
 {
  PHR_Channel_Semantic_Protocol* sp = pcp->channel_system_->value(ch);
  PHR_Channel* pch = pcp->value(sp);

  if(!pch)
  {
   pch = new PHR_Channel;
   (*pcp)[sp] = pch;
  }

  PHR_Carrier* phc = new PHR_Carrier;
  pch->push_back(phc);
  return phc;
 };

 QMap<int, QPair<QString, QString>> type_names;
 QStringList pins;
 QMap<QString, QString> docus;
 QString fn_code;
 QString fn_name;

 for(QString qs : qsl)
 {
  switch(qs[0].toLatin1())
  {
  case '-' : break; // // comment

  case '~' :
   {
    QStringList files = qs.mid(1).simplified().split(' ');
    parse_from_file_list(path, files, channel_names, current_expression_code);
   }
   break;
  case ';' : // // channel name
   {
    int index = qs.indexOf(':');
    QString channel_name = qs.mid(1, index - 1);
    int code = qs.mid(index + 1).toInt();
    channel_names[code] = channel_name;
   }
   break;
  case '#' : // // expression
   {
    if(qs[1] != '#')
      current_expression_code = qs.mid(1).toInt();
   }
   break;
  case '@' : // // type name
   {
    int index = qs.indexOf(':');
    QString type_name = qs.mid(1, index - 1);
    int index1 = qs.indexOf(':', index + 1);
    QString mode = qs.mid(index, index1 - index - 1);
    int code = qs.mid(index1 + 1).toInt();
    type_names[code] = {type_name, mode};
   }
   break;
  case '&' : // // fn name
   {
    int index = qs.indexOf(':');
    fn_code = qs.mid(1, index - 1).toInt();
    fn_name = qs.mid(index + 1);

    PHR_Carrier* phc = add_carrier_to_channel(this, "fground");
    phc->set_symbol_name(fn_name);

//    PHR_Channel_Semantic_Protocol* sp = channel_system_->value("fground");
//    PHR_Channel* pch = this->value(sp);
//    if(!pch)
//    {
//     pch = new PHR_Channel;
//     (*this)[sp] = pch;
//    }
//    PHR_Carrier* phc = new PHR_Carrier;
//    phc->set_symbol_name(fn_name);
    PHR_Type* pty = type_system_->get_type_by_name("fbase");
    phc->set_phr_type(pty);
//    PHR_Type_Object* pto = phc->type_object();
   // phc->
//    pch->push_back(phc);
   }
   break;
  case '+' : // // pins
   {
    pins.push_back(qs.mid(1));
   }
   break;
  case '%' : // // documentation
   {
    int index = qs.indexOf(':');
    if(index != -1)
    {
     docus[qs.mid(1, index - 1)] = qs.mid(index + 1);
    }
   }
   break;
  default : // // carrier
   {
    // // field order:
     //    channel (numeric index code)
     //    keyword (for function parameter)
     //    position (carrier's position in channel)
     //    mode (modifier on carrier; spec on carrier state
     //    type code (numeric code)
     //    expression ref (numeric code if carrier holds expression result)
     //    symbolic ref (if carrier holds symbol in lieu of value)
     //    value (if carrier holds actual value)

    int index = qs.indexOf(':');
    int channel = qs.left(index).toInt();
    int index1 = qs.indexOf(':', index + 1);
    QString kw = qs.mid(index + 1, index1 - index - 1);
    int index2 = qs.indexOf(':', index1 + 1);
    int pos = qs.mid(index1 + 1, index2 - index1 - 1).toInt();
    int index3 = qs.indexOf(':', index2 + 1);
    QString mode = qs.mid(index2 + 1, index3 - index2 - 1);
    int index4 = qs.indexOf(':', index3 + 1);
    int typec = qs.mid(index3 + 1, index4 - index3 - 1).toInt();
    int index5 = qs.indexOf(':', index4 + 1);
    int expref = qs.mid(index4 + 1, index5 - index4 - 1).toInt();
    int index6 = qs.indexOf(':', index5 + 1);
    QString symref = qs.mid(index5 + 1, index6 - index5 - 1);
    QString value = qs.mid(index6 + 1);

    PHR_Carrier* phc = add_carrier_to_channel(this, channel_names[channel]);

//    PHR_Channel_Semantic_Protocol* sp = channel_system_->value(channel_names[channel]);
//    PHR_Channel* pch = this->value(sp);
//    if(!pch)
//    {
//     pch = new PHR_Channel;
//     (*this)[sp] = pch;
//    }
//    PHR_Carrier* phc = new PHR_Carrier;
    phc->set_symbol_name(symref);
    phc->set_raw_value_string(value);

    QString tn = type_names[typec].first;

    PHR_Type* pty = type_system_->get_type_by_name(tn);
    phc->set_phr_type(pty);
//    PHR_Type_Object* pto = phc->type_object();

//    pch->push_back(phc);

//    phc->set_channel_name(channel_names[channel]);
//    phc->set_carrier_mode(mode);
//    phc->set_type_name(type_names_[typec].first);
//    phc->set_type_mode(type_names_[typec].second);
//    phc->set_pos(pos);
//    phc->set_key(kw);
//    phc->set_expref(expref);
//    phc->set_symref(symref);
//    phc->set_value(value);
//    check_channel_count_maximum(kpc->channel_name(), pos);
//    carriers_.push_back(kpc);
   }
   break;
  }
 }
}

void PHR_Command_Package::channel_names_to_codes(QMap<QString,
  QPair<int, const PHR_Channel*>>& qmap)
{
 int channel_code_count = 1;
 QMapIterator<PHR_Channel_Semantic_Protocol*, PHR_Channel*> it(*this);
 while(it.hasNext())
 {
  it.next();

//  // // assumes kind will not always be initialized ...
//  if( (it.value().kind() == KCM_Channel::Kinds::Fuxe)
//      || (*it.key() == "fuxe") )
//  {
//   qmap[*it.key()] = {0, &it.value()};
//   continue;
//  }

  QString chn = it.key()->name();

  if(chn == "fground")
  {
   qmap[chn] = {0, it.value()};
   continue;
  }

  qmap[chn] = {channel_code_count, it.value()};
  ++channel_code_count;
 }
}

void PHR_Command_Package::parse_from_string(QString path, const QString& qs)
{
 QStringList qsl = qs.split("\n.\n");
 parse_from_string_list(path, qsl);
}

void PHR_Command_Package::parse_from_file(QString path)
{
 QString qs = load_file(path);
 parse_from_string(path, qs);
}

void PHR_Command_Package::parse_from_string(QString path, const QString& qs,
  QMap<int, QString>& channel_names, int& current_expression_code)
{
 QStringList qsl = qs.split("\n.\n");
 parse_from_string_list(path, qsl, channel_names, current_expression_code);
}

void PHR_Command_Package::parse_from_file_list(QString path,
  const QStringList& paths,
  QMap<int, QString>& channel_names, int& current_expression_code)
{
 for(QString p : paths)
 {
  if(p.contains('/'))
  {
   if(p.contains('.'))
     parse_from_file(p, channel_names, current_expression_code);
   else
     parse_from_file(p + ".kph", channel_names, current_expression_code);
   continue;
  }
  int index = path.lastIndexOf('/');
  if(p.contains('.'))
    parse_from_file(path.left(index + 1) + p, channel_names, current_expression_code);
  else
    parse_from_file(path.left(index + 1) + p + ".kph",
    channel_names, current_expression_code);
 }
}


void PHR_Command_Package::parse_from_file(QString path,
  QMap<int, QString>& channel_names, int& current_expression_code)
{
 QString qs = load_file(path);
 parse_from_string(path, qs, channel_names, current_expression_code);
}

