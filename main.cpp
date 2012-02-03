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

#include "node_manager.h"
#include "property_manager.h"
#include "log.h"
#include "server.h"
#include "configuration.h"
#include "command_parser.h"
#include "render_manager.h"
#include "renderer.h"

#include <iostream>
#include <stdlib.h>
#include <signal.h>

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

static int OS_windows = 1;
static int OS_linux = 0;
//static int OS_mac = 2;

#ifdef _WIN32
static int OS = OS_windows;
#else
static int OS = OS_linux;
#endif

using namespace std;

using namespace boost;
using namespace boost::asio;
using namespace boost::system;


static server _server;


void sighandler(int sig)
{
    cout << "Signal " << sig << " caught..." << endl;

	_server.stop = true;
}

int main()
{
    log::message("Loading config");

    configuration::Instance().load();

    /* try catching ctrl-c */
    signal(SIGABRT, &sighandler);
	signal(SIGTERM, &sighandler);
	signal(SIGINT,  &sighandler);

    /*fs::path up = fs::current_path();
    string unique_dir = up.string();
    cout << unique_dir;*/

    /* initialize nodes by nodefile */
    log::message( "Loading nodelist..." );
    node_manager::Instance( ).load_node_file( "nodes.txt" ); //todo: add static server in file, Ruben/Rubdos can perhaps arrange one, just for initial IP's;

    /* Init properties */
    log::message( "Initing properties" );
    FILE* pp;

    static int OS;

    if(OS == OS_windows)
    {
        pp = popen("ver","r");
    }
    else
    {
        pp = popen("uname -r -v -s","r"); // DONT use -a, privacy!!!
    }

    if(!pp)
    {

    }

    char line[130];
    string operating_system_string;

    while ( fgets( line, sizeof line, pp))
    {
        operating_system_string = string((char*)line);
    }

    pclose(pp);

    property_manager::Instance().set("public.system.operating_system",operating_system_string);

    /* Start server thread */
    log::message("Starting server main thread...");
    thread serverthread( bind( &server::loop , _server ) );
    uint i = 0;
    while(!_server.running){
        i++;
        if(i > 10000000) break;
    }
    node_manager::Instance().global_connect();

    render_manager::Instance().load_tasks();

    log::message( "Initialze Yafaray system" );

    renderer::Instance();

    log::message( "Done loading system... Ready when you are!" );

    command_parser _cp;
    _cp.start();
    //thread cpthread( bind( &command_parser::start , _cp ) );
    /*while(!_server.stop)
    {
        //lets wait the server to stop... Main thread blocking, but this isn't a problem ^^
    }*/
    return 0;
}
