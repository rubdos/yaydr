include_directories("include")
set(GUI_SRC
    main.cpp
    projectmanagerwindow.cpp
)
set(GUI_HEADERS
    include/projectmanagerwindow.hpp
)
set(GUI_RCCS resources.qrc)
QT4_ADD_RESOURCES(GUI_RCC_SRCS ${GUI_RCCS})

QT4_WRAP_CPP(GUI_HEADERS_MOC ${GUI_HEADERS})
add_executable(qyaydr
    ${GUI_SRC}
    ${GUI_HEADERS_MOC}
    ${GUI_RCC_SRCS})

target_link_libraries(qyaydr
    ap2p
    ${QT_LIBRARIES}
    ${SQLITE_LIBRARY}
)
