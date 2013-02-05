FIND_PATH(YAFARAY_INCLUDEDIR NAMES yafaray/interface/xmlinterface.h
    /usr/local/include
    /usr/include
)
FIND_LIBRARY(YAFARAY_LIBS NAMES libyafaraycore.so
        libyafarayplugin.so
        plugins  
        _yafrayinterface.so
    HINTS
        /usr/local/lib
        /usr/local/bin
        /usr/lib
        /usr/bin
)
IF(YAFARAY_INCLUDEDIR AND YAFARAY_LIBS)
    SET(YAFARAY_INCLUDE_DIRS ${YAFARAY_INCLUDEDIR})
    MESSAGE(STATUS "Yafaray found")
    SET(YAFARAY_FOUND TRUE)
ELSE()
    MESSAGE(FATAL_ERROR "Yafaray NOT found")
    SET(YAFARAY_FOUND FALSE)
ENDIF()
