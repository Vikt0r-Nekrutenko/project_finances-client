QT += network

TEMPLATE = lib
DEFINES += CORE_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

OBJECTS_DIR = objects

INCLUDEPATH += \
    headers \
    sources \

DEPENDPATH += \
    headers \
    sources \

SOURCES += \
    sources/basemodel.cpp \
    sources/localmodel.cpp \
    sources/datamodel.cpp \
    sources/debtmodel.cpp \
    sources/debtmodelhandler.cpp \
    sources/depositmodel.cpp \
    sources/depositmodelhandler.cpp \
    sources/categorymodel.cpp \
    sources/categorymodelhandler.cpp \
    sources/modelhandler.cpp \
    sources/operationmodel.cpp \
    sources/operationmodelhandler.cpp

HEADERS += \
    headers/basemodel.hpp \
    headers/core_global.hpp \
    headers/datamodel.hpp \
    headers/debtmodel.hpp \
    headers/debtmodelhandler.hpp \
    headers/depositmodel.hpp \
    headers/depositmodelhandler.hpp \
    headers/categorymodel.hpp \
    headers/categorymodelhandler.hpp \
    headers/localmodel.hpp \
    headers/modelhandler.hpp \
    headers/crudmodel.hpp \
    headers/operationmodel.hpp \
    headers/operationmodelhandler.hpp

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
