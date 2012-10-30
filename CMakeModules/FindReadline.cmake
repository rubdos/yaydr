# FOUND AT: http://code.google.com/p/libpbc/source/browse/trunk/FindReadline.cmake
# A GPLv3 licensed project at time of writing: 17 oktober 2012 17:25
# Here shown in modified version
    
FIND_PATH(READLINE_INCLUDE_DIR readline/readline.h)
FIND_LIBRARY(READLINE_LIBRARY NAMES readline)

IF (READLINE_INCLUDE_DIR AND READLINE_LIBRARY)
    SET(READLINE_FOUND TRUE)
ENDIF (READLINE_INCLUDE_DIR AND READLINE_LIBRARY)

IF (READLINE_FOUND)
    IF (NOT Readline_FIND_QUIETLY)
        MESSAGE(STATUS "Found GNU readline: ${READLINE_LIBRARY}")
    ENDIF (NOT Readline_FIND_QUIETLY)
ELSE (READLINE_FOUND)
    IF (Readline_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find GNU readline")
    ELSE (Readline_FIND_REQUIRED)
        MESSAGE(STATUS "Did not find readline; not compiling console")
    ENDIF (Readline_FIND_REQUIRED)
ENDIF (READLINE_FOUND)
