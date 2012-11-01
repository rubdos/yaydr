FIND_PATH(LIBAP2P_INCLUDEDIR NAMES libap2p/network/network.hpp
    HINTS
        /usr/local/include
        /usr/include
)
FIND_LIBRARY(LIBAP2P_LIBS NAMES ap2p
    HINTS
        /usr/local/lib
        /usr/lib
)
IF(LIBAP2P_INCLUDEDIR AND LIBAP2P_LIBS)
    SET(LIBAP2P_INCLUDE_DIRS ${LIBAP2P_INCLUDEDIR})
    SET(LIBAP2P_FOUND TRUE)
    MESSAGE(STATUS "Found libap2p")
ELSE()
    IF (libap2p_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Fatal: Could not find libap2p.")
    ELSE ()
        MESSAGE(STATUS "Not compiling with libap2p")
    ENDIF()
    SET(LIBAP2P_FOUND FALSE)
ENDIF()
