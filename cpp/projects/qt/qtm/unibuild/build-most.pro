
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


TEMPLATE = subdirs

SUBDIRS = \
  hgdm/ntxh/ntxh \
  hgdm/ntxh/ntxh-parser \
  hgdm/ntxh/ntxh-builder \
  dataset/dsmain/dsmain \

SUBDIRS += \
  external/xpdf/xpdf \


SUBDIRS += \
  rz/PhaonIR/phaon-ir \
  rz/PhaonLib/phaon-lib \


SUBDIRS += \
  QScign/ScignStage/ScignStage-ling \

SUBDIRS += \
  dataset/application-model/application-model \
  dataset/config/config-dialog \

SUBDIRS += \
  external/udpipe/udpipe \
  QScign/QRing/qring \
  hgdm/ntxh-udp/ntxh-udp \
  hgdm/ntxh-udp/ntxh-udp-console \


SUBDIRS += \
  rz/phr-runtime/phr-env \
  rz/phr-runtime/phr-fn-doc \
  rz/PhaonLib/phr-command-runtime \
  rz/PhaonLib/phr-direct-eval \
  rz/tests-phr/kph-generator \


SUBDIRS += \
  rz/tests-phr/kauvir-phaon-console \
  rz/tests-phr/kph-generator-console \
  rz/tests-phr/kph-tcp-console \


SUBDIRS += \
  dataset/application-model/application-model-test-dialog  \
  dataset/application-model/amtd-console  \


SUBDIRS += \
  dataset/pdf-pull/pdf-pull  \
  dataset/pdf-pull/pdf-pull-console  \


SUBDIRS += \
  QScign/LexPair/lexpair  \
  QScign/LexPair/lexpair-console  \


SUBDIRS += \
  dataset/dsmain/_run__dsmain-console \


CONFIG += ordered
