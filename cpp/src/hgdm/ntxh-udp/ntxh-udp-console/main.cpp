
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "udpipe/udpipe.h"

#include <QDebug>
#include <QFile>


#include "ntxh-udp/ntxh-udp-corpus.h"
#include "ntxh-udp/ntxh-udp-sentence.h"

#include <QDir>

#include "textio.h"

USING_KANS(TextIO)


int main(int argc, char* argv[])
{
 QString root = "&" CONLLU_DIR ;
 NTXH_UDP_Corpus ntc(root);

 QString infile = "@/joint/j.ntxh";

 ntc.add_file(infile);

 ntc.init_sentences();
 ntc.check_write_latex();

 return 0;
}

