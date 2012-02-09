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


#ifndef RENDER_TASK_H
#define RENDER_TASK_H

#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;


class render_task
{
    public:
        render_task();
        virtual ~render_task();

        static render_task* from_xml_file(string);
        static render_task* from_gzip_file(string);
        static render_task* from_hash(string);
        static render_task* from_xml_base64_string(string /*hash*/, string /*encoder*/);

        void announce();
        void generate_password();
        void save_configuration();

        string xml_file_name;
        string gzip_file_name;

        string unique_dir;

        string password;
        string hash;
        string owner;
    protected:
    private:
};

#endif // RENDER_TASK_H
