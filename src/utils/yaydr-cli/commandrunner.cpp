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

#include "commandrunner.hpp"
#include <iostream>

namespace yaydrcli
{
    CommandRunner::CommandRunner()
    {
    }
    int CommandRunner::Run(int argc, char** argv)
    {
        this->_argc = argc;
        this->_argv = argv;

        bool stop = false;

        while(!stop)
        {
            // Print head
            std::cout << "yaydr $ ";
            std::string command;
            std::getline(std::cin, command);
        }
        return 0; // Default return value
    }
}
