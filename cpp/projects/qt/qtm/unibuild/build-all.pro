
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
  dataset/pdf-pull/pdf-pull  \
  dataset/pdf-pull/pdf-pull-console  \


SUBDIRS += \
  external/xpdf/xpdf \


SUBDIRS += \
  rz/PhaonIR/phaon-ir \
  rz/PhaonLib/phaon-lib \
  rz/PhaonLib/phaon-lib-console \


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
  rz/tests-phr/kph-generator \
  rz/PhaonLib/phr-direct-eval \


SUBDIRS += \
  rz/tests-phr/kauvir-phaon-console \
  rz/tests-phr/kph-generator-console \
  rz/tests-phr/kph-multigen-console \
  rz/tests-phr/kph-tcp-console \


SUBDIRS += \
  dataset/application-model/application-model-test-dialog  \
  dataset/application-model/amtd-console  \


SUBDIRS += \
  QScign/LexPair/lexpair  \
  QScign/LexPair/lexpair-console  \


SUBDIRS += \
  dataset/ro-info/ro-info  \
  dataset/ro-info/ro-info-console  \


SUBDIRS += \
  dataset/ds-kdmi/ds-kdmi  \
  dataset/ds-kdmi/ds-kdmi-console  \
  dataset/ds-kdmi/kdmi-bridge  \
  dataset/ds-kdmi/kdmi-bridge-console  \


SUBDIRS += \
  hgdm/charm/charm-lib  \
  hgdm/charm/charm-lib-console  \


SUBDIRS += \
  rz/rz-kauvir/rz-graph-core \
  rz/rz-kauvir/rz-graph-token \
  rz/rz-kauvir/rz-graph-build \
  rz/rz-kauvir/rz-graph-embed \
  rz/rz-kauvir/rz-function-def \
  rz/rz-kauvir/rz-code-elements \
  rz/rz-kauvir/rz-graph-valuer \
  rz/rz-kauvir/rz-graph-embed-run \
  rz/rz-kauvir/rz-graph-run \
  rz/rz-kauvir/rz-graph-visit \
  rz/rz-kauvir/rz-code-generators \
  rz/rz-kauvir/rz-graph-sre \
  rz/rz-kauvir/rz-graph-code \


SUBDIRS += \
  hgdm/phr-graph/phr-graph-core \
  rz/rz-kauvir/rz-graph-phaon-console \


SUBDIRS += \
  rz/rz-phr-runtime/rz-phr-runtime-console \
  rz/rz-phr-runtime/rz-phr-multi-console \
  rz/rz-kph-runtime/rz-kph-runtime-console \


SUBDIRS += \
  dataset/dsmain/_run__dsmain-console \


#  rz/rz-dynamo/rz-dynamo-console \
#  rz/rz-dynamo/rz-graph-dynamo-console \
#  kauvir/kcm-runtime-eval/fn-doc \
#  kauvir/kcm-runtime-eval/basic-functions \
#  rz/rz-dynamo/rz-dynamo-runtime-console \
#  rz/rz-dynamo/rgd-runtime-console \
#  rz/rz-dynamo/rz-multi-console \
#  rz/rz-dynamo/rgd-kph-console \



CONFIG += ordered
