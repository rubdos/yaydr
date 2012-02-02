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


#include "command_parser.h"
#include "render_manager.h"
#include "node_manager.h"
#include "log.h"


#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>

command_parser::command_parser()
{
    //ctor
}

bool command_parser::parse(string line)
{
    /* Parse the document */
    vector<string> linesplit;
    /* Split the line by spaces and tabs */
    split( linesplit, line, is_any_of(" \t"), token_compress_on );

    if(linesplit[0].compare("quit") == 0 || line.compare("exit") == 0)
    {
        /* Quit the application */
        return false;
    }
    if(linesplit[0].compare("refresh") == 0)
    {
        /* Refresh the nodelist */
        node_manager::Instance().global_connect();
        return true;
    }
    if(linesplit[0].compare("render") == 0)
    {
        /* Lets render some file(s) */
        string filename = line.substr(7, line.length() - 7 );
        trim_if(filename, is_any_of(" \t\n\r\""));

        // Our render_manager will take care of the filename. It'll scan for all xml's
        vector<render_task*> tasks = render_manager::Instance().load_file_or_directory( filename );

        stringstream ss; //create a stringstream for converting our number
        ss << tasks.size();
        log::message("Starting render job of " + ss.str());
        render_manager::Instance().announce(tasks);

        return true;
    }
    if(linesplit[0].compare("add_ip") == 0)
    {
        /* Manually add an IP to the nodelist */
        node_manager::Instance().get_node_by_ip(linesplit[1]);
        return true;
    }

    if(linesplit[0].compare("help") == 0)
    {
        /* Print help and return */

        cout << "quit\t\t\tQuit the yafaray distributor" << endl;
        cout << "exit\t\t\tIdem" << endl;
        cout << "help\t\t\tShow this help message" << endl;
        cout << "refresh\t\t\tRefresh the nodes manually" << endl;
        cout << "add_ip [ip]\t\tAdd an ipv4 address to the node list" << endl;
        cout << "render [directory/file]\tRender a file or recurse a directory" << endl;

        return true;
    }
    return true;
}

void command_parser::start()
{
    while(true)
    {
        /* This stuff isn't as reliable as it should be; If the console prints something
           while the user is typing, he can start over. Somebody should explain me how
           to do this right ;-) */
        cout << ">";
        char line[512];
        cin.getline(line, 511); //we won't go over half a KB...

        if(!this->parse(string(line)))
        {
            break; //when parse returns FALSE, it means the software has to quit.
        }
    }
}

command_parser::~command_parser()
{
    //dtor
}
