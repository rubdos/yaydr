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


#ifndef DEBUG_H
#define DEBUG_H

#include <string>

using namespace std;

class log
{
    public:
        static void debug(string);
        static void warning(string);
        static void error(string);
        static void message(string);
    protected:
    private:
};

#endif // DEBUG_H
