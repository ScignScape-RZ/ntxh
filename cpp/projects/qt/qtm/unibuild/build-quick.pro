
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


CONFIG += ordered
