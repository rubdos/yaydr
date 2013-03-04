#include <iostream>
#include <sstream>

#include "project/project.hpp"

namespace yaydr
{
    Project::Project(sqlite3* dbHandle, uint64_t projectId)
    {
        this->_projectId = projectId;
        this->_databaseHandle = dbHandle;
    }
    Project::Project(sqlite3* dbHandle, std::string name, std::string description)
    {
        // path will be autogenerated

        this->_databaseHandle = dbHandle;

        std::string insert_sql = "INSERT INTO projects(name, description, path) VALUES(?,?,?)";
        sqlite3_stmt* insert_stmt;

        int result = sqlite3_prepare_v2(this->_databaseHandle, 
                insert_sql.c_str(), 
                insert_sql.length(), 
                &insert_stmt, 
                NULL);

        if (result)
        {
            // TODO Throw
        }

        result = sqlite3_bind_text(insert_stmt, 1, name.c_str(), name.length(), NULL); 
        // ? values are 1 indexed when being bound
        result = sqlite3_bind_text(insert_stmt, 2, description.c_str(), description.length(), NULL);
        result = sqlite3_bind_text(insert_stmt, 3, name.c_str(), name.length(), NULL); 
        // FIXME autogenerate a valid path!!!

        result = sqlite3_step(insert_stmt);

        if(result != SQLITE_DONE)
        {
            std::cerr << "Error when executing insert statement" << std::endl;
        }

        this->_projectId = sqlite3_last_insert_rowid(this->_databaseHandle);

        sqlite3_finalize(insert_stmt);
    }
    void Project::Remove()
    {
        std::stringstream sql;
        sql << "DELETE FROM projects WHERE id=";
        sql << this->_projectId;
        
        sqlite3_stmt* statement;
        int result = sqlite3_prepare_v2(this->_databaseHandle, 
                sql.str().c_str(),
                sql.str().length(),
                &statement,
                NULL );
        if( result || !statement )
        {
            std::cerr << "Sqlite error: " << result << std::endl;
        }
        if(sqlite3_step(statement) == SQLITE_DONE)
        {
            std::cout << "Removed " << this->_projectId << std::endl;
        }
        
        sqlite3_finalize(statement);
    }
    std::string Project::getName()
    {
        std::string name;
        std::stringstream sql;
        sql << "SELECT name FROM projects WHERE id=";
        sql << this->_projectId;
        
        sqlite3_stmt* statement;
        int result = sqlite3_prepare_v2(this->_databaseHandle, 
                sql.str().c_str(),
                sql.str().length(),
                &statement,
                NULL );
        if( result || !statement )
        {
            std::cerr << "Sqlite error: " << result << std::endl;
        }
        if(sqlite3_step(statement) == SQLITE_ROW)
        {
            name = std::string((const char*)sqlite3_column_text(statement, 0)); // collumn zero is for the name
        }
        
        sqlite3_finalize(statement);
        return name;
    }
    std::string Project::getDescription()
    {
        std::string desc;
        std::stringstream sql;
        sql << "SELECT description FROM projects WHERE id=";
        sql << this->_projectId;
        
        sqlite3_stmt* statement;
        int result = sqlite3_prepare_v2(this->_databaseHandle, 
                sql.str().c_str(),
                sql.str().length(),
                &statement,
                NULL );
        if( result || !statement )
        {
            std::cerr << "Sqlite error: " << result << std::endl;
        }
        if(sqlite3_step(statement) == SQLITE_ROW)
        {
            desc = std::string((const char*)sqlite3_column_text(statement, 0)); // collumn zero is for the desc
        }
        
        sqlite3_finalize(statement);

        return desc;
    }
}
