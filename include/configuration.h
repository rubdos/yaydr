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


#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

using namespace std;
using namespace boost;
using namespace boost::system;

//#define fs boost::filesystem


class configuration
{
    public:
        configuration(string);
        static configuration& Instance();
        virtual ~configuration();

        void load();
        void init_new_config();
        void save();

        boost::filesystem::path yaydrdir;
        boost::filesystem::path cfgfile;
    protected:
    private:
};

#endif // CONFIGURATION_H
