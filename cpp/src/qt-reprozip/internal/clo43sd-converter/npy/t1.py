import numpy
a = numpy.load("/home/nlevisrael/hypergr/bird/CLO-43SD/mfcc/AMRE2330536360101.mfcc.npy", allow_pickle=True, encoding='latin1')
numpy.savetxt("foo.csv", a, delimiter=",")

numpy.save("/home/nlevisrael/hypergr/bird/CLO-43SD/mfcc/AMRE2330536360101.mfcc.2.npy", a, fix_imports=True)

