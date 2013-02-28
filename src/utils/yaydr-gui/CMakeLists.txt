include_directories("${PROJECT_SOURCE_DIR}/include/utils/yaydr-gui")

set(CMAKE_AUTOMOC TRUE)

add_subdirectory(project_manager)

set(GUI_SRC
    main.cpp
)

set(GUI_LIBS
    projectmanager
)

set(GUI_RCCS resources.qrc)
QT4_ADD_RESOURCES(GUI_RCC_SRCS ${GUI_RCCS})

add_executable(qyaydr
    ${GUI_SRC}
    ${GUI_RCC_SRCS})

target_link_libraries(qyaydr
    ${GUI_LIBS}
    ${YAYDR_LIBS}
    ap2p
    ${SQLITE_LIBRARY}
    ${QT_LIBRARIES}
)
