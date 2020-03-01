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
    include/Exiv2/asfvideo.hpp \
    include/Exiv2/basicio.hpp \
    include/Exiv2/bigtiffimage.hpp \
    include/Exiv2/bmpimage.hpp \
    include/Exiv2/config.h \
    include/Exiv2/convert.hpp \
    include/Exiv2/cr2image.hpp \
    include/Exiv2/crwimage.hpp \
    include/Exiv2/datasets.hpp \
    include/Exiv2/easyaccess.hpp \
    include/Exiv2/epsimage.hpp \
    include/Exiv2/error.hpp \
    include/Exiv2/exif.hpp \
    include/Exiv2/Exiv2.hpp \
    include/Exiv2/futils.hpp \
    include/Exiv2/gifimage.hpp \
    include/Exiv2/http.hpp \
    include/Exiv2/image.hpp \
    include/Exiv2/ini.hpp \
    include/Exiv2/iptc.hpp \
    include/Exiv2/jp2image.hpp \
    include/Exiv2/jpgimage.hpp \
    include/Exiv2/matroskavideo.hpp \
    include/Exiv2/metadatum.hpp \
    include/Exiv2/mrwimage.hpp \
    include/Exiv2/orfimage.hpp \
    include/Exiv2/pgfimage.hpp \
    include/Exiv2/pngimage.hpp \
    include/Exiv2/preview.hpp \
    include/Exiv2/properties.hpp \
    include/Exiv2/psdimage.hpp \
    include/Exiv2/quicktimevideo.hpp \
    include/Exiv2/rafimage.hpp \
    include/Exiv2/riffvideo.hpp \
    include/Exiv2/rw2image.hpp \
    include/Exiv2/rwlock.hpp \
    include/Exiv2/slice.hpp \
    include/Exiv2/ssh.hpp \
    include/Exiv2/tags.hpp \
    include/Exiv2/tgaimage.hpp \
    include/Exiv2/tiffimage.hpp \
    include/Exiv2/types.hpp \
    include/Exiv2/utilsvideo.hpp \
    include/Exiv2/value.hpp \
    include/Exiv2/version.hpp \
    include/Exiv2/webpimage.hpp \
    include/Exiv2/xmp_Exiv2.hpp \
    include/Exiv2/xmpsidecar.hpp \
    include/Exiv2.hpp \
    include/Exiv2/exv_conf.h \
    include/Exiv2/Exiv2lib_export.h \
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
