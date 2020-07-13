
// // license___here_h

#ifndef Transformation__H
#define Transformation__H

// package facsanadu.transformations;

// // Transformation

class Transformation
{
public:

 int channel_; //=-1;
 virtual void transform(QList<double> v) = 0;
 virtual void invert(QList<double> v) = 0;
 virtual double transform(double x, int index);
 virtual double invert(double x, int index);
};

#endif //  Transformation__H


