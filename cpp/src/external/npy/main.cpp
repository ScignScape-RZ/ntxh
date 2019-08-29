
#include"cnpy.h"


#include<complex>
#include<cstdlib>
#include<iostream>
#include<map>
#include<string>

#include<QString>
#include<QDebug>

#include <QProcess>
#include <QDir>
#include <QFileInfo>


const int Nx = 128;
const int Ny = 64;
const int Nz = 32;

//#include "npy.hpp"
//cnpy::NpyArray arr = cnpy::npy_load("C:/clg/CLO-43SD/mfcc/AMRE_233054328_0101.mfcc.npy");
//double* mv1 = arr.data<double>();
//qDebug() << "Key: " << *mv1;
//std::vector<unsigned long> shape;
//std::vector<double> data;
//npy::LoadArrayFromNumpy(filename, shape, data);

//std::vector<unsigned long> shape;
//std::vector<double> data;
//npy::LoadArrayFromNumpy(filename, shape, data);

#include "textio.h"

USING_KANS(TextIO)

QString convert(QString dir, QString ndir, QString file, QString py_file)
{
 QString py = QString(R"(
import numpy
a = numpy.load("%1/%2.npy", allow_pickle=True, encoding='latin1')
numpy.save("%3/%2.2.npy", a, fix_imports=True))").arg(dir).arg(file).arg(ndir);

 save_file(py_file, py);

 QProcess proc;
 QString cmd = QString("python3 %1").arg(py_file);
 proc.execute(cmd);

 return QString("%1/%2.2.npy").arg(ndir).arg(file);
}



int main()
{
 QString dir = "/home/nlevisrael/hypergr/bird/CLO-43SD/mfcc";
 QString ndir = "/home/nlevisrael/hypergr/bird/CLO-43SD/mfcc2";
 QString script = "/home/nlevisrael/hypergr/bird/CLO-43SD/conv-mfcc.py";

 QDir qdir(dir);

 QStringList npys = qdir.entryList(QStringList() << "*.npy", QDir::Files);

 QMap<QString, int> species;


 for(QString npy: npys)
 {
  QFileInfo qfi(npy);

  QString sp = qfi.baseName();

  sp = sp.left(4);

  ++species[sp];

  QString bn = qfi.completeBaseName();
  qDebug() << bn;

  QString c = convert(dir, ndir, bn, script);

 }




#ifdef HIDE
 {
  std::string filename = c.toStdString();

  cnpy::NpyArray arr = cnpy::npy_load(filename);

  std::vector<double> ds = arr.as_vec<double>();

  int nfs = arr.shape[0];
  int dim = arr.shape[1];

  int c = 0;

  qDebug() << ds.size();
  qDebug() << nfs;
  qDebug() << dim;
  qDebug() << dim * nfs;

  for(int i = 0; i < nfs; ++i)
  {
   for(int j = 0; j < dim; ++j)
   {
    double d = ds[c];
 //   qDebug() << "d: " << d;
    ++c;

//    qDebug() << arr.as_vec[i][j];
   }
  }

//  for(auto it = arr.shape.begin(); it != arr.shape.end(); ++it)
//  {
//   qDebug() << "Key: " << *it;
//  }
 }

// {
//  std::string filename = "C:/clg/CLO-43SD/logmelspec.npy";

//  cnpy::NpyArray arr = cnpy::npy_load(filename);
//  for(auto it = arr.shape.begin(); it != arr.shape.end(); ++it)
//  {
//   qDebug() << "Key: " << *it;
//  }
// }

 //?double* mv1 = arr.data<double>();
// qDebug() << "Key: " << *mv1;

//? qDebug() << "Key: " << data[0];

// for(auto it = my_npz.begin(); it != my_npz.end(); ++it)
// {
//  QString key = QString::fromStdString(it->first);
//  cnpy::NpyArray arr_mv1 = it->second;
//  double* mv1 = arr_mv1.data<double>();

//  qDebug() << "Key: " << *mv1;

// }

// check that the loaded myVar1 matches myVar1
// cnpy::NpyArray arr_mv1 = my_npz["myVar1"];
// double* mv1 = arr_mv1.data<double>();
#endif // HIDE
}

int main3()
{
    //set random seed so that result is reproducible (for testing)
    srand(0);
    //create random data
    std::vector<std::complex<double>> data(Nx*Ny*Nz);
    for(int i = 0;i < Nx*Ny*Nz;i++) data[i] = std::complex<double>(rand(),rand());

    //save it to file
    cnpy::npy_save("arr1.npy",&data[0],{Nz,Ny,Nx},"w");

    //load it into a new array
    cnpy::NpyArray arr = cnpy::npy_load("arr1.npy");
    std::complex<double>* loaded_data = arr.data<std::complex<double>>();

    //make sure the loaded data matches the saved data
    assert(arr.word_size == sizeof(std::complex<double>));
    assert(arr.shape.size() == 3 && arr.shape[0] == Nz && arr.shape[1] == Ny && arr.shape[2] == Nx);
    for(int i = 0; i < Nx*Ny*Nz;i++) assert(data[i] == loaded_data[i]);

    //append the same data to file
    //npy array on file now has shape (Nz+Nz,Ny,Nx)
    cnpy::npy_save("arr1.npy",&data[0],{Nz,Ny,Nx},"a");

    //now write to an npz file
    //non-array variables are treated as 1D arrays with 1 element
    double myVar1 = 1.2;
    char myVar2 = 'a';
    cnpy::npz_save("out.npz","myVar1",&myVar1,{1},"w"); //"w" overwrites any existing file
    cnpy::npz_save("out.npz","myVar2",&myVar2,{1},"a"); //"a" appends to the file we created above
    cnpy::npz_save("out.npz","arr1",&data[0],{Nz,Ny,Nx},"a"); //"a" appends to the file we created above

    //load a single var from the npz file
    cnpy::NpyArray arr2 = cnpy::npz_load("out.npz","arr1");

    //load the entire npz file
    cnpy::npz_t my_npz = cnpy::npz_load("out.npz");

    //check that the loaded myVar1 matches myVar1
    cnpy::NpyArray arr_mv1 = my_npz["myVar1"];
    double* mv1 = arr_mv1.data<double>();
    assert(arr_mv1.shape.size() == 1 && arr_mv1.shape[0] == 1);
    assert(mv1[0] == myVar1);    
}
