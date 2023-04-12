QT -= gui
QT += network

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        models/sources/appmodel.cpp \
        models/sources/datamodel.cpp \
        models/sources/debtmodel.cpp \
        models/sources/depositmodel.cpp \
        models/sources/modelhandler.cpp \
        models/sources/categorymodel.cpp \
        models/sources/operationmodel.cpp \
        models/sources/debtmodelhandler.cpp \
        models/sources/depositmodelhandler.cpp \
        models/sources/categorymodelhandler.cpp \
        models/sources/operationmodelhandler.cpp \
        views/sources/menuview.cpp \
        views/sources/closeview.cpp \
        views/sources/debtlistview.cpp \
        views/sources/depositlistview.cpp \
        views/sources/categorylistview.cpp \
    views/sources/operationhandler.cpp \
        views/sources/operationslistview.cpp \
        views/sources/modelviewwithinputfield.cpp \
        main.cpp \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../stf/release/ -lstf
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../stf/debug/ -lstf
else:unix:!macx: LIBS += -L$$PWD/../stf/ -lstf

INCLUDEPATH += $$PWD/../stf \
                models/headers \
                views/headers \
DEPENDPATH += $$PWD/../stf \
                models/headers \
                views/headers \

HEADERS += \
    models/headers/appmodel.hpp \
    models/headers/crudmodel.hpp \
    models/headers/debtmodel.hpp \
    models/headers/datamodel.hpp \
    models/headers/depositmodel.hpp \
    models/headers/modelhandler.hpp \
    models/headers/categorymodel.hpp \
    models/headers/operationmodel.hpp \
    models/headers/debtmodelhandler.hpp \
    models/headers/depositmodelhandler.hpp \
    models/headers/categorymodelhandler.hpp \
    models/headers/operationmodelhandler.hpp \
    views/headers/menuview.hpp \
    views/headers/closeview.hpp \
    views/headers/debtlistview.hpp \
    views/headers/depositlistview.hpp \
    views/headers/categorylistview.hpp \
    views/headers/operationslistview.hpp \
    views/headers/modelviewwithinputfield.hpp \
    views/sources/operationhandler.hpp

DISTFILES += \
    sprs/losses.spr \
    sprs/main_stats.spr \
    sprs/pnl_stats.spr
