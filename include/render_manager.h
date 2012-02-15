/*
        copyright 2011-2012 Ruben De Smet
        This file is part of yaydr


    yaydr is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    yaydr is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with yaydr.  If not, see <http://www.gnu.org/licenses/>.
 */



#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "render_task.h"

#include <string>
#include <vector>

class render_manager
{
    public:
        render_manager();
        virtual ~render_manager();
        static render_manager& Instance();
        void load_tasks();

        vector<render_task*> load_file_or_directory(string);
        void announce(vector<render_task*>);

        render_task* task_by_hash(string);

        render_task* new_task(string);
        render_task* input_task(string);

        void loop();
    protected:
    private:
        vector<render_task*> load_directory(string);

        vector<render_task*> _tasks;
};

#endif // RENDER_MANAGER_H
