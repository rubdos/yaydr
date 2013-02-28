set(PM_INC_DIR "${PROJECT_SOURCE_DIR}/include/utils/yaydr-gui/project_manager/")

set( PROJECTMANAGER_SRC
    project_manager_window.cpp
#    project_list_item_widget.cpp
    ${PM_INC_DIR}/project_manager_window.hpp
)
add_library(projectmanager ${PROJECTMANAGER_SRC})
