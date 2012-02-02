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

#include "configuration.h"
#include "property_manager.h"
#include "log.h"

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>

/* Set the default configuration file */
static configuration cfg("default.conf");


using namespace std;
using namespace boost;
using namespace boost::system;

configuration::configuration(string filename)
{
    /* Load a configuration file */

    // try to get the home directory. As x-platform as possible
    string home = getenv("HOME");

    if(home.compare("") == 0)
    {
        home = string(getenv("HOMEDRIVE")) + string(getenv("HOMEPATH"));
        if(home.compare("") == 0)
        {
            log::error("No home folder found...");
        }
    }

    //the main working directory is a period (.) folder in the home dir.
    boost::filesystem::path yaydrdir(home + "/.yaydr/");
    if(!boost::filesystem::is_directory(yaydrdir))
    {
        //and if it doesn't exist, create it
        boost::filesystem::create_directory(yaydrdir);
    }
    //safe the state.
    this->yaydrdir = yaydrdir;
    this->cfgfile = filename;
}

void configuration::init_new_config()
{
    /* A new installation of yaydr when called! Thanks for trying out.
       This function creates a new configuration directory and file
       Along with a new computer ID, which is just a random bunch of characters.
       This ID will be visible in the hole network to (poorly) identify your computer
       This should be made stronger with RSA and signing/encrypting lator on */
    string computerID;

    string allowed_characters = "abcdefghijklmnopqrstuvwxyz0123456789-_.";

    //init our random number generator
    boost::random::random_device rng;
    boost::random::uniform_int_distribution<> index_dist(0, allowed_characters.size() - 1);

    //get 64 chars
    for(int i = 0; i < 64; ++i) {
        computerID = computerID + allowed_characters[index_dist(rng)];
    }

    //save the stuff
    property_manager::Instance().set("public.systemid", computerID);
    //and tell the user
    log::debug("Your computer gets ID '" + computerID + "'");
}

void configuration::save()
{
    /* This function saves the .conf file */

    // open a write file stream
    ofstream pf;
    pf.open( (this->yaydrdir.string() + this->cfgfile.string()).c_str() , ios::trunc);

    //write each property in the main property manager
    for(uint i = 0; i < property_manager::Instance().properties.size(); i++)
    {
        pf << property_manager::Instance().properties[i].name << "=" << property_manager::Instance().properties[i].value << endl;
    }
    pf.close();
}

void configuration::load()
{
    /* Open the configuration file and load the property manager with it's contents */

    if(boost::filesystem::is_regular(this->yaydrdir.string() + this->cfgfile.string()))
    {
        //standard crap to read it out...
        ifstream pf;
        pf.open((this->yaydrdir.string() + this->cfgfile.string()).c_str() );
        string line;
        while ( pf.good() )
        {
            getline(pf,line);

            //split it by the '=' sign. Left is key, right is value.
            vector<string> splitvector;
            split(splitvector, line, is_any_of("="));

            if(splitvector.size() == 2)
            {
                //[0] = key, [1] = value
                property_manager::Instance().set(splitvector[0],splitvector[1]);
            }
        }
        pf.close();
    }
    else
    {
        ofstream pf;
        pf.open( (this->yaydrdir.string() + this->cfgfile.string()).c_str() );
        pf.close(); //touch it and stop the program.
        log::warning("No configuration file at " + this->yaydrdir.string() + this->cfgfile.string()); // warn the user about it
    }
    if(property_manager::Instance().get("public.systemid").compare("") == 0)
    {
        this->init_new_config();
        this->save();
    }
}

configuration& configuration::Instance()
{
    return cfg;
}
configuration::~configuration()
{
    //dtor
}
