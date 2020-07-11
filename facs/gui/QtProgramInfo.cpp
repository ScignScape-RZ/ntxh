
// // license___here

#include "QtProgramInfo.h"

#include <QString>

QString QtProgramInfo::programName = "FACSanadu";

QString QtProgramInfo::programVersion = "0.1.0";

QString QtProgramInfo::licenseText =
   "If you use this software, please cite: ...\n"
   "\n"
   "Available under the 3-clause BSD license";
 
 
QString QtProgramInfo::getVersionString()
{
 return programVersion;
}


