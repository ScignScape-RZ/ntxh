
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
  dataset/dsmain/_run__dsmain-console \

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
  rz/PhaonIR/phaon-ir \
  rz/PhaonLib/phaon-lib \
  rz/phr-runtime/phr-env \
  rz/phr-runtime/phr-fn-doc \
  rz/PhaonLib/phr-command-runtime \
  rz/PhaonLib/phr-direct-eval \


SUBDIRS += \
  rz/rz-phr-runtime/rz-phr-runtime-console \


#  rz/rz-dynamo/rz-dynamo-console \
#  rz/rz-dynamo/rz-graph-dynamo-console \
#  kauvir/kcm-runtime-eval/fn-doc \
#  kauvir/kcm-runtime-eval/basic-functions \
#  rz/rz-dynamo/rz-dynamo-runtime-console \
#  rz/rz-dynamo/rgd-runtime-console \
#  rz/rz-dynamo/rz-multi-console \
#  rz/rz-dynamo/rgd-kph-console \



CONFIG += ordered
