include_directories("include")
set(GUI_SRC
    main.cpp
)
set(GUI_HEADERS
        )
QT4_WRAP_CPP(GUI_HEADERS_MOC ${GUI_HEADERS})
add_executable(qyaydr
    ${GUI_SRC}
    ${GUI_HEADERS_MOC})

target_link_libraries(qyaydr
    ap2p
    ${QT_LIBRARIES}
)
