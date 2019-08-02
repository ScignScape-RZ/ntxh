
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


TEMPLATE = subdirs


#__CHOICE_SUBDIRS__#

SUBDIRS = \
  hgdm/ntxh/ntxh \
  hgdm/ntxh/ntxh-parser \
  hgdm/ntxh/ntxh-builder \
  QScign/QRing/qring \
  dataset/ro-info/ro-info \
  dataset/config/config-dialog \
  dataset/dsmain/dsmain \
  dataset/pdf-pull/pdf-pull \
  dataset/ds-kdmi/ds-kdmi \
  dataset/ds-kdmi/ds-kdmi-console \
  dataset/ds-kdmi/kdmi-bridge \
  dataset/ds-kdmi/kdmi-bridge-console \
  dataset/pdf-pull/pdf-pull-console \
  dataset/ro-info/ro-info-console \
  external/udpipe/udpipe \
  hgdm/ntxh-udp/ntxh-udp \
  hgdm/ntxh-udp/ntxh-udp-console \
  rz/PhaonIR/phaon-ir \
  rz/PhaonLib/phaon-lib \
  QScign/ScignStage/ScignStage-ling \
  QScign/LexPair/lexpair \
  QScign/LexPair/lexpair-console \
  dataset/config/config-dialog-console \
  rz/rz-kauvir/rz-graph-core \
  rz/rz-kauvir/rz-graph-token \
  dataset/application-model/application-model \
  dataset/application-model/application-model-test-dialog \
  dataset/application-model/amtd-console \
  rz/phr-runtime/phr-env \
  rz/phr-runtime/phr-fn-doc \
  rz/PhaonLib/phr-command-runtime \
  rz/PhaonLib/phr-direct-eval \
  rz/tests-phr/kph-generator \
  rz/tests-phr/kph-generator-console \
  rz/tests-phr/kph-multigen-console \
  dataset/dsmain/_run__dsmain-console \


#__END_INSERT__#

CONFIG += ordered


