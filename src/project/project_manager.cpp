
#include <iostream>
#include "project/project_manager.hpp"

namespace yaydr
{
    ProjectManager::ProjectManager(sqlite3* db_handle)
    {
        this->_databaseHandle = db_handle;
        this->_initDatabase();
        this->_loadProjects();
    }
    ProjectList* ProjectManager::GetProjectList()
    {
        return &this->_projects;
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
        sqlite3_free(error);
    }
    void ProjectManager::_loadProjects()
    {
        std::string query = "SELECT id FROM projects";
        sqlite3_stmt* statement;
        int result = sqlite3_prepare_v2(this->_databaseHandle, 
                query.c_str(),
                query.length(),
                &statement,
                NULL );
        if( result || !statement )
        {
            std::cerr << "Sqlite error: " << result << std::endl;
        }
        while(sqlite3_step(statement) == SQLITE_ROW)
        {
            int64_t id = sqlite3_column_int64(statement, 0); // collumn zero is for the ID
            Project* p = new Project(this->_databaseHandle, id);
            this->_projects.push_back(p);
        }
        sqlite3_finalize(statement);

        std::clog << "Loaded " << this->_projects.size() << " projects from disk." << std::endl;
    }
    ProjectManager::~ProjectManager()
    {
    }
}
