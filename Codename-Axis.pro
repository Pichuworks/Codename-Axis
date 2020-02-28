#-------------------------------------------------
#
# Project created by QtCreator 2020-01-05T19:52:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Codename-Axis
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    FileTraverseThread.cpp \
    utils/StringUtils.cpp

HEADERS  += mainwindow.h \
    FileTraverseThread.h \
    version.h \
    include/exiv2/asfvideo.hpp \
    include/exiv2/basicio.hpp \
    include/exiv2/bigtiffimage.hpp \
    include/exiv2/bmpimage.hpp \
    include/exiv2/config.h \
    include/exiv2/convert.hpp \
    include/exiv2/cr2image.hpp \
    include/exiv2/crwimage.hpp \
    include/exiv2/datasets.hpp \
    include/exiv2/easyaccess.hpp \
    include/exiv2/epsimage.hpp \
    include/exiv2/error.hpp \
    include/exiv2/exif.hpp \
    include/exiv2/exiv2.hpp \
    include/exiv2/futils.hpp \
    include/exiv2/gifimage.hpp \
    include/exiv2/http.hpp \
    include/exiv2/image.hpp \
    include/exiv2/ini.hpp \
    include/exiv2/iptc.hpp \
    include/exiv2/jp2image.hpp \
    include/exiv2/jpgimage.hpp \
    include/exiv2/matroskavideo.hpp \
    include/exiv2/metadatum.hpp \
    include/exiv2/mrwimage.hpp \
    include/exiv2/orfimage.hpp \
    include/exiv2/pgfimage.hpp \
    include/exiv2/pngimage.hpp \
    include/exiv2/preview.hpp \
    include/exiv2/properties.hpp \
    include/exiv2/psdimage.hpp \
    include/exiv2/quicktimevideo.hpp \
    include/exiv2/rafimage.hpp \
    include/exiv2/riffvideo.hpp \
    include/exiv2/rw2image.hpp \
    include/exiv2/rwlock.hpp \
    include/exiv2/slice.hpp \
    include/exiv2/ssh.hpp \
    include/exiv2/tags.hpp \
    include/exiv2/tgaimage.hpp \
    include/exiv2/tiffimage.hpp \
    include/exiv2/types.hpp \
    include/exiv2/utilsvideo.hpp \
    include/exiv2/value.hpp \
    include/exiv2/version.hpp \
    include/exiv2/webpimage.hpp \
    include/exiv2/xmp_exiv2.hpp \
    include/exiv2/xmpsidecar.hpp \
    include/exiv2.hpp \
    include/exiv2/exv_conf.h \
    include/exiv2/exiv2lib_export.h \
    utils/StringUtils.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc

DISTFILES += \
    .gitignore \
    LICENSE \
    README.md \
    Debug/debug/Codename-Axis.ilk \
    Debug/debug/Codename-Axis.pdb \
    Debug/debug/Codename-Axis.vc.pdb \
    lib/linux-x64/libexiv2-xmp.a \
    lib/linux-x64/libexiv2.a \
    lib/windows-x86/exiv2-xmp.lib \
    lib/windows-x86/exiv2.lib \
    lib/windows-x86/expat.lib \
    lib/windows-x86/gmock.lib \
    lib/windows-x86/gmock_main.lib \
    lib/windows-x86/gtest.lib \
    lib/windows-x86/gtest_main.lib \
    lib/windows-x86/iconv_x86.lib \
    lib/windows-x86/Psapi.Lib \
    lib/windows-x86/zlib.lib

INCLUDEPATH += ./include

LIBS += -lD:/Code/Qt/Codename-Axis/lib/windows-x86/exiv2 \
        -lD:/Code/Qt/Codename-Axis/lib/windows-x86/exiv2-xmp \
-lD:/Code/Qt/Codename-Axis/lib/windows-x86/expat \
-lD:/Code/Qt/Codename-Axis/lib/windows-x86/gmock \
-lD:/Code/Qt/Codename-Axis/lib/windows-x86/gmock_main \
-lD:/Code/Qt/Codename-Axis/lib/windows-x86/gtest \
-lD:/Code/Qt/Codename-Axis/lib/windows-x86/gtest_main \
-lD:/Code/Qt/Codename-Axis/lib/windows-x86/iconv_x86 \
-lD:/Code/Qt/Codename-Axis/lib/windows-x86/zlib \
-lD:/Code/Qt/Codename-Axis/lib/windows-x86/psapi
