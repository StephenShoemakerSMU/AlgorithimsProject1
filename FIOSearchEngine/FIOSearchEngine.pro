TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DISTFILES += \
    Shoemaker, Clark UML Design Diagram.pdf \
    cityhash-master/m4/libtool.m4 \
    cityhash-master/m4/ltoptions.m4 \
    cityhash-master/m4/ltsugar.m4 \
    cityhash-master/m4/ltversion.m4 \
    cityhash-master/m4/lt~obsolete.m4 \
    cityhash-master/aclocal.m4 \
    cityhash-master/config.guess \
    cityhash-master/config.sub \
    cityhash-master/configure \
    cityhash-master/depcomp \
    cityhash-master/install-sh \
    cityhash-master/ltmain.sh \
    cityhash-master/missing \
    cityhash-master/configure.ac \
    cityhash-master/NEWS \
    SrcFiles/stop.txt \
    cityhash-master/COPYING \
    cityhash-master/README

SUBDIRS += \
    FIOSearchEngine.pro

HEADERS += \
    cityhash-master/src/city.h \
    cityhash-master/src/citycrc.h \
    cityhash-master/config.h.in \
    util/hash.h \
    util/string_view.h \
    catch.hpp \
    documentparse.h \
    fioavltree.h \
    hashtablechaining.h \
    index.h \
    indexavltree.h \
    indexentry.h \
    mmaping.h \
    porter2_stemmer.h \
    sanitizer.h \
    documentparse.h \
    searchengine.h \
    FIODocument.h \
    searchengine.h \
    rapidjson/error/en.h \
    rapidjson/error/error.h \
    rapidjson/internal/biginteger.h \
    rapidjson/internal/diyfp.h \
    rapidjson/internal/dtoa.h \
    rapidjson/internal/ieee754.h \
    rapidjson/internal/itoa.h \
    rapidjson/internal/meta.h \
    rapidjson/internal/pow10.h \
    rapidjson/internal/regex.h \
    rapidjson/internal/stack.h \
    rapidjson/internal/strfunc.h \
    rapidjson/internal/strtod.h \
    rapidjson/internal/swap.h \
    rapidjson/msinttypes/inttypes.h \
    rapidjson/msinttypes/stdint.h \
    rapidjson/allocators.h \
    rapidjson/document.h \
    rapidjson/encodedstream.h \
    rapidjson/encodings.h \
    rapidjson/filereadstream.h \
    rapidjson/filewritestream.h \
    rapidjson/fwd.h \
    rapidjson/istreamwrapper.h \
    rapidjson/memorybuffer.h \
    rapidjson/memorystream.h \
    rapidjson/ostreamwrapper.h \
    rapidjson/pointer.h \
    rapidjson/prettywriter.h \
    rapidjson/rapidjson.h \
    rapidjson/reader.h \
    rapidjson/schema.h \
    rapidjson/stream.h \
    rapidjson/stringbuffer.h \
    rapidjson/writer.h \
    hashindex.h \
    hashmap.h \
    hashnode.h

SOURCES += \
    cityhash-master/src/city-test.cc \
    cityhash-master/src/city.cc \
    documentparse.cpp \
    index.cpp \
    indexavltree.cpp \
    indexentry.cpp \
    main.cpp \
    mmaping.cpp \
    porter2_stemmer.cpp \
    sanitizer.cpp \
    searchengine.cpp \
    tests.cpp \
    fiodocument.cpp \
    hashindex.cpp
