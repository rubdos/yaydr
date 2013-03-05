set(PM_INC_DIR "${PROJECT_SOURCE_DIR}/include/utils/yaydr-gui/project_manager/")

set( PROJECTMANAGER_SRC
    project_manager_window.cpp
    ${PM_INC_DIR}/project_manager_window.hpp
    
    project_list_item_widget.cpp
    ${PM_INC_DIR}/project_list_item_widget.hpp

    new_project_dialog.cpp
    ${PM_INC_DIR}/new_project_dialog.hpp
)
add_library(projectmanager ${PROJECTMANAGER_SRC})
