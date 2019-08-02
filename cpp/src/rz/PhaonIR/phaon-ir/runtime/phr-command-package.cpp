
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

USING_KANS(Phaon)

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

template<typename T>
QPair<T&, void*>& operator>>(QPair<T&, void*>& thet, PHR_Channel_Semantic_Protocol*& rhs)
{
 QString n;
 thet.first >> n;
 PHR_Command_Package* pcp = static_cast<PHR_Command_Package*>(thet.second);
 rhs = pcp->channel_system()->value(n);
 return thet;
}

template<typename T>
QPair<T&, void*>& operator>>(QPair<T&, void*>& thet, PHR_Channel*& rhs)
{
 rhs = new PHR_Channel;
 readArrayBasedContainer(thet, *rhs);
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

    PHR_Type* pty = type_system_->get_type_by_name("fbase");
    phc->set_phr_type(pty);
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

    phc->set_symbol_name(symref);
    phc->set_raw_value_string(value);

    QString tn = type_names[typec].first;

    PHR_Type* pty = type_system_->get_type_by_name(tn);
    phc->set_phr_type(pty);
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


QVector<PHR_Command_Package*> PHR_Command_Package::parse_multi_from_file(PHR_Channel_System* cs,
  PHR_Type_System* ts, QString path)
{
 QString qs = load_file(path);
 return parse_multi_from_string(cs, ts, path, qs);
}

QVector<PHR_Command_Package*> PHR_Command_Package::parse_multi_from_string(PHR_Channel_System* cs,
  PHR_Type_System* ts, QString path,
  const QString& qs)
{
 int index = qs.indexOf("\n.\n##\n.\n");
 if(index == -1)
 {
  PHR_Command_Package* pcp = new PHR_Command_Package(cs, ts);
  pcp->parse_from_string(path, qs);
  return {pcp};
 }
 QVector<PHR_Command_Package*> result;
 parse_multi_from_string(cs, ts, path, qs, 0, index + 6, result);
 return result;
}

void PHR_Command_Package::parse_multi_from_string(PHR_Channel_System* cs,
  PHR_Type_System* ts, QString path,
  const QString& qs, int i1, int i2, QVector<PHR_Command_Package*>& result)
{
 QString mid = qs.mid(i1, i2 - i1);
 PHR_Command_Package* pcp = new PHR_Command_Package(cs, ts);
 pcp->parse_from_string(path, mid);
 result.push_back(pcp);
 i2 += 2;
 int i3 = qs.indexOf("\n.\n##\n.\n", i2);
 if(i3 == -1)
 {
  QString mid = qs.mid(i2);
  PHR_Command_Package* pcp = new PHR_Command_Package(cs, ts);
  pcp->parse_from_string(path, mid);
  result.push_back(pcp);
  return;
 }
 parse_multi_from_string(cs, ts, path, qs, i2, i3 + 6, result);
}

void PHR_Command_Package::multi_to_map(const QVector<PHR_Command_Package*>& pcps,
  QMap<QString, QVector<PHR_Command_Package*>>& qmap)
{
 for(PHR_Command_Package* pcp: pcps)
 {
  QString sigma = pcp->sigma_type_name();
  if(sigma.isEmpty())
    continue;
  qmap[sigma].push_back(pcp);
 }
}

QString PHR_Command_Package::sigma_type_name()
{
 std::map<PHR_Channel_Semantic_Protocol*, PHR_Channel*> sm = this->toStdMap();
 auto it = std::find_if(sm.begin(), sm.end(),
   [](const std::pair<const PHR_Channel_Semantic_Protocol*, PHR_Channel*>& pr) -> bool
 {
  return pr.first->name() == "sigma";
 });
 if(it != sm.end())
 {
  PHR_Channel* pch = it->second;
  if(pch && !pch->isEmpty())
  {
   PHR_Type* pty = pch->first()->phr_type();
   if(pty)
     return pty->name();
  }
 }
 return QString();
}

QString PHR_Command_Package::moc_signature()
{
 QString fn_name;
 QString result;

 QMapIterator<PHR_Channel_Semantic_Protocol*, PHR_Channel*> it(*this);

 while(it.hasNext())
 {
  it.next();
  QString n = it.key()->name();
  if(n == "fground")
  {
   fn_name = it.value()->get_first_symbol_name();
  }
  else if(n == "lambda")
  {
   for(PHR_Carrier* phc : *it.value())
   {
    PHR_Type* pty = phc->phr_type();
    if(pty)
      result += pty->name() + ", ";
   }
  }
 }
 if(result.endsWith(", "))
   result.chop(2);
 result = QString("%1(%2)").arg(fn_name).arg(result);
 return result;
}
