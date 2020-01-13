
#ifndef RZ_NGML_PARALEX_TILE__H
#define RZ_NGML_PARALEX_TILE__H

#include <QString>
#include <QMap>

#include "accessors.h"
#include "flags.h"

#include "global-types.h"

#include "whitespace/rz-ngml-whitespace-holder.h"

#include "rzns.h"

RZNS_(NGML)

class NGML_Paralex_Tile : public NGML_Whitespace_Holder
{
public:
 enum Kind {
  N_A, Alt_Interpretation, Pipe_Escape, 
   Numeric_Character_Reference
  };

private:

 Kind kind_;
 QString argument_;
 QString command_;
 
 u1 width_or_alt_;  

public:

 NGML_Paralex_Tile(QString raw_text, Kind k, u1 w);

 QString to_string();

 QString thumbnail(int max_characters = 6);
  // QString get_accent_as_html();

 template<typename T>
 void write_latex(T& t)
 {
 }

 template<typename T>
 void write_html(T& t)
 {
 }

};

_RZNS(NGML)

#endif
