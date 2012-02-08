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


#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <string>
#include <iostream>

using namespace std;

class command_parser
{
    public:
        command_parser();
        virtual ~command_parser();

        void start();
        bool parse(string);
    protected:
    private:
};

#endif // COMMAND_PARSER_H
