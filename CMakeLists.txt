cmake_minimum_required (VERSION 2.8.2)
project (yaydr)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules")
set(CMAKE_COLOR_MAKEFILE ON)
set(YAYDR_LIBS project node network)
set(INCLUDE_FILES
)


# ---------- Setup output Directories -------------------------
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/bin
   CACHE PATH
   "Single Directory for all Libraries"
   )

# --------- Setup the Executable output Directory -------------
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/bin
   CACHE PATH
   "Single Directory for all Executables."
   )

# --------- Setup the Executable output Directory -------------
SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/bin
   CACHE PATH
   "Single Directory for all static libraries."
   )

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON) 
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS iostreams filesystem system thread signals)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif(Boost_FOUND)

find_package (Threads REQUIRED)
find_package (CryptoPP REQUIRED)
find_package (Readline) #not required
find_package (libap2p REQUIRED)
find_package (yafaray REQUIRED)
find_package (sqlite REQUIRED)

include_directories ("${PROJECT_SOURCE_DIR}/include")
include_directories ("${CRYPTOPP_INCLUDE_DIRS}")
include_directories ("${SQLITE_INCLUDE_DIR}")

add_subdirectory(src)
add_subdirectory(tests)

# INSTALL

foreach(file ${INCLUDE_FILES})
    install(FILES ${file} DESTINATION ${file})
endforeach()

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  SET_TARGET_PROPERTIES(${AP2P_LIBS} PROPERTIES COMPILE_FLAGS "-fPIC")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
