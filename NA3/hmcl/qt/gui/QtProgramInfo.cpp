
#include <QString>

QtProgramInfo::programName = "FACSanadu";

QtProgramInfo::programVersion = "0.1.0";

QtProgramInfo::licenseText =
   "If you use this software, please cite: ...\n"
   "\n"
   "Available under the 3-clause BSD license";
 
 
QString QtProgramInfo::getVersionString()
{
 return programVersion;
}


