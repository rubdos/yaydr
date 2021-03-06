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

#ifndef YAYDR_PROJECT
#define YAYDR_PROJECT

#include <string>
#include <sqlite3.h>
#include <stdint.h>

#include "project/image.hpp"

namespace yaydr
{
    class Project
    {
        public:
            Project(sqlite3* databaseHandle, uint64_t projectId);
            Project(sqlite3* databaseHandle, std::string name, std::string description);

            std::string getName();
            std::string getDescription();

            /** Removes the project from the database. 
             */
            void Remove();
            
            ImageList* getImageList();
            VideoSequenceList* getVideoSequenceList();
        private:
            uint64_t _projectId;
            sqlite3* _databaseHandle;
            ImageList _images;
            VideoSequenceList _videos;
    };
}

#endif
