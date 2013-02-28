/* Copyright (C) 
 * 2013 - Ruben De Smet
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://gnu.org/licenses/>
 * 
 */

#include <string>
#include <sqlite3.h>
#include <vector>
#include <project/project.hpp>

namespace yaydr
{
    class ProjectManager
    {
        public:
            ProjectManager(sqlite3* db_handle);
            ~ProjectManager();
        private:
            void _initDatabase();
            void _loadProjects();
            sqlite3* _databaseHandle;

            std::vector<Project*> _projects;
    };
}
