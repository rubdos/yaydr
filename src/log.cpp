/*
        copyright 2011 Ruben De Smet
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


#include "log.h"

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void log::debug(string message)
{
    /* Debug message */
    //TODO: Insert #if DEBUG.
    cout << "DEBUG:  " << message << endl;
}
void log::warning(string message)
{
    /* Warn the user about something what's almost serious */
    cerr << "WARNING:" << message << endl;
}
void log::error(string message)
{
    /* Print error and quit */
    cerr << "ERROR:  " << message << endl;
    exit(-1);
}
void log::message(string message)
{
    /* Inform the user. Better than cout!!!*/
    cout << message << endl;
}
