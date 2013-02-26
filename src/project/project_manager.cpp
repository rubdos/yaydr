
#include <iostream>
#include "project/project_manager.hpp"

namespace yaydr
{
    ProjectManager::ProjectManager(sqlite3* db_handle)
    {
        this->_databaseHandle = db_handle;
        this->_initDatabase();
    }
    void ProjectManager::_initDatabase()
    {
        char* error;
        int result = sqlite3_exec(this->_databaseHandle, 
                "CREATE TABLE IF NOT EXISTS projects\
                (id INTEGER PRIMARY KEY,\
                 name STRING,\
                 description STRING,\
                 path STRING);",
                NULL, NULL, &error); // No callback needed
        if(result != 0)
        {
            std::cerr << "Sqlite error: " << result << std::endl;
        }
    }
    ProjectManager::~ProjectManager()
    {
    }
}
