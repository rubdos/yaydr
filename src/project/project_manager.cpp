
#include <iostream>
#include "project/project_manager.hpp"

namespace yaydr
{
    ProjectManager::ProjectManager()
    {
        this->_databaseHandle = 
            sqlite_open("projects.sqlite3", 0, NULL); 
        // @feb 2013, second argument not implemented, NULL for no error message

        if(! this->_databaseHandle)
        {
            std::cerr << "No database file opened" << std::endl;
        }
    }
    ProjectManager::~ProjectManager()
    {
        sqlite_close(this->_databaseHandle);
    }
}
