
// // license___here_h


#ifndef GateMeasureMean__H
#define GateMeasureMean__H

// package facsanadu.gates.measure;

#include <QString>
#include <QObject>

class Gate;
class FacsanaduProject;
class GatingResult;

// package facsanadu.gates.measure;


// // Calculation: Mean
class GateMeasureMean : public GateMeasureUnivariate
{
public:

 double calc(Dataset* ds, Gate* g, GatingResult* res);

 QString getDesc(FacsanaduProject* proj) Q_DECL_OVERRIDE;
 
 
};


#endif // def GateMeasureMean__H

