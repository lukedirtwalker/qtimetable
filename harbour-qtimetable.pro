# The name of your app.
# NOTICE: name defined in TARGET has a corresponding QML filename.
#         If name defined in TARGET is changed, following needs to be
#         done to match new name:
#         - corresponding QML filename must be changed
#         - desktop icon filename must be changed
#         - desktop filename must be changed
#         - icon definition filename in desktop file must be changed
TARGET = harbour-qtimetable

QT += sql core quick qml xml

CONFIG += sailfishapp quick2 qml link_pkgconfig
PKGCONFIG += sailfishapp

database.files = stations.db
database.path = /usr/share/harbour-qtimetable/data
INSTALLS += desktop icon database


QMAKE_CXXFLAGS += -std=c++0x

SOURCES += src/qtimetable.cpp \
    src/listitems/locationitem.cpp \
    src/listmodels/resultlistmodel.cpp \
    src/db/databasehandler.cpp \
    src/uihandlers/timehandler.cpp \
    src/uihandlers/timetablehandler.cpp \
    src/db/threadeddbhandler.cpp \
    src/core/sbbhandler.cpp \
    src/net/sbbservercommunication.cpp \
    src/net/sbbrequest.cpp \
    src/query/sbbquery.cpp \
    src/query/sbbquerycontainer.cpp \
    src/util/serializable.cpp \
    src/core/sbbconnectionhandler.cpp \
    src/query/sbbconnectionquery.cpp \
    src/query/sbbrelativeconnectionquery.cpp \
    src/domout/domaddress.cpp \
    src/domout/domstation.cpp \
    src/domout/domflags.cpp \
    src/domout/domdate.cpp

OTHER_FILES += qml/qtimetable.qml \
    qml/cover/CoverPage.qml \
    qml/pages/Help.qml \
    qml/pages/About.qml \
    qml/pages/TimeTable.qml \
    qml/components/TimeTableInput.qml \
    qml/pages/Favorites.qml \
    qml/pages/DepArr.qml \
    qml/pages/Settings.qml \
    qml/components/SearchDialog.qml \
    qml/components/DepArrSwitch.qml \
    harbour-qtimetable.desktop \
    rpm/harbour-qtimetable.spec \
    qml/components/SearchListItem.qml \
    qml/components/DeletableTextField.qml
HEADERS += \
    src/listitems/locationitem.h \
    src/listmodels/resultlistmodel.h \
    src/listitems/listitem.h \
    src/db/databasehandler.h \
    src/uihandlers/timehandler.h \
    src/uihandlers/timetablehandler.h \
    src/db/threadeddbhandler.h \
    src/db/db.h \
    src/core/sbbhandler.h \
    src/net/sbbservercommunication.h \
    src/net/sbbrequest.h \
    src/query/sbbquery.h \
    src/query/sbbquerycontainer.h \
    src/util/serializable.h \
    src/util/globalshared.h \
    src/core/sbbconnectionhandler.h \
    src/query/sbbconnectionquery.h \
    src/query/sbbrelativeconnectionquery.h \
    src/domout/domaddress.h \
    src/domout/domstation.h \
    src/domout/domflags.h \
    src/domout/domdate.h \
    src/listmodels/stationlistmodel.h

