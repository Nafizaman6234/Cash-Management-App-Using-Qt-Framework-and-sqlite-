QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_new_rec.cpp \
    delete_rec.cpp \
    home_page.cpp \
    main.cpp \
    mainwindow.cpp \
    search_rec.cpp \
    update_rec.cpp

HEADERS += \
    add_new_rec.h \
    database_manage.h \
    delete_rec.h \
    home_page.h \
    mainwindow.h \
    search_rec.h \
    update_rec.h

FORMS += \
    add_new_rec.ui \
    delete_rec.ui \
    home_page.ui \
    mainwindow.ui \
    search_rec.ui \
    update_rec.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
