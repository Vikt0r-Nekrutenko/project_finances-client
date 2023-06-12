QT = core
QT += network

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    $$PWD/../core \
    $$PWD/../../stf \
    headers \
    sources \

DEPENDPATH += \
    $$PWD/../core \
    $$PWD/../../stf \
    headers \
    sources \

SOURCES += \
    sources/depositsview.cpp \
    sources/imenu.cpp \
    sources/inputfield.cpp \
    sources/ioption.cpp \
    sources/iview.cpp \
    sources/mainview.cpp \
    sources/viewholder.cpp \
    sources\main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../core/release/ -lcore \
    -L$$PWD/../../stf/release/ -lstf
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../core/debug/ -lcore \
    -L$$PWD/../../stf/debug/ -lstf

HEADERS += \
    headers/appmodel.hpp \
    headers/depositsview.hpp \
    headers/imenu.hpp \
    headers/inputfield.hpp \
    headers/ioption.hpp \
    headers/iview.hpp \
    headers/logitem.hpp \
    headers/mainview.hpp \
    headers/viewholder.hpp
