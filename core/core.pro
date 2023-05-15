QT += network

TEMPLATE = lib
DEFINES += CORE_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    headers \
    sources \

DEPENDPATH += \
    headers \
    sources \

SOURCES += \
    sources/datamodel.cpp \
    sources/depositmodel.cpp \

HEADERS += \
    headers/core_global.h \
    headers/datamodel.hpp \
    headers/depositmodel.hpp \
    headers/crudmodel.hpp \

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
