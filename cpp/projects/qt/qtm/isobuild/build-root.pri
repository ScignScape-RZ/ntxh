

CHOICE_CODE = isobuild-choices

WHICH_BUILD_DIR_CODE = isobuild

include(../_choices/$${WHICH_BUILD_DIR_CODE}_choices.pri)

defined(QMAKE_CONSOLE_TARGET_DIR, var){
 BUILD_DIR_CODE = qmake-console
} else {
 BUILD_DIR_CODE = $$OUT_PWD
 BUILD_DIR_CODE ~= s!.*/(build|release)-($$PROJECT_NAME)-(.*)-(Debug|Release)!\3
}

include(../build-root-both.pri)


