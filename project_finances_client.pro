QT -= gui
QT += network

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        appmodel.cpp \
    categorymodel.cpp \
        closeview.cpp \
        datamodel.cpp \
        depositlistview.cpp \
        depositmodel.cpp \
        depositmodelhandler.cpp \
        main.cpp \
        menuview.cpp \
        modelhandler.cpp \
        modelviewwithinputfield.cpp \
        operationmodel.cpp \
    operationmodelhandler.cpp \
    operationslistview.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../stf/release/ -lstf
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../stf/debug/ -lstf
else:unix:!macx: LIBS += -L$$PWD/../stf/ -lstf

INCLUDEPATH += $$PWD/../stf
DEPENDPATH += $$PWD/../stf

HEADERS += \
    appmodel.hpp \
    categorymodel.hpp \
    closeview.hpp \
    crudmodel.hpp \
    datamodel.hpp \
    depositlistview.hpp \
    depositmodel.hpp \
    depositmodelhandler.hpp \
    menuview.hpp \
    modelhandler.hpp \
    modelviewwithinputfield.hpp \
    operationmodel.hpp \
    operationmodelhandler.hpp \
    operationslistview.hpp
