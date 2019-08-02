
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
  dataset/application-model/application-model \
  QScign/ScignStage/ScignStage-ling \
  dataset/dsmain/_run__dsmain-console \


CONFIG += ordered
