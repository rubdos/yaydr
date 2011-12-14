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

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "../include/configuration.h"
#include "../include/property_manager.h"
#include "../include/log.h"

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>


static configuration cfg("default.conf");


using namespace std;
using namespace boost;
using namespace boost::system;

configuration::configuration(string filename)
{
    //ctor
    //property_manager::Instance().set("public.system.yd.version","a.0.0.0");

    string home = getenv("HOME");

    if(home.compare("") == 0)
    {
        home = string(getenv("HOMEDRIVE")) + string(getenv("HOMEPATH"));
        if(home.compare("") == 0)
        {
            log::error("No home folder found...");
        }
    }
    boost::filesystem::path yaydrdir(home + "/.yaydr/");
    if(!boost::filesystem::is_directory(yaydrdir))
    {
        boost::filesystem::create_directory(yaydrdir);
    }
    this->yaydrdir = yaydrdir;
    this->cfgfile = filename;
}

void configuration::init_new_config()
{
    string computerID;

    string allowed_characters = "abcdefghijklmnopqrstuvwxyz0123456789-_.";
    boost::random::random_device rng;
    boost::random::uniform_int_distribution<> index_dist(0, allowed_characters.size() - 1);
    for(int i = 0; i < 64; ++i) {
        computerID = computerID + allowed_characters[index_dist(rng)];
    }
    property_manager::Instance().set("public.systemid", computerID);
    log::debug("Your computer gets ID '" + computerID + "'");
}

void configuration::save()
{
    ofstream pf;
    pf.open( (this->yaydrdir.string() + this->cfgfile.string()).c_str() , ios::trunc);
    for(uint i = 0; i < property_manager::Instance().properties.size(); i++)
    {
        pf << property_manager::Instance().properties[i].name << "=" << property_manager::Instance().properties[i].value << endl;
    }
    pf.close();
}

void configuration::load()
{
    if(boost::filesystem::is_regular(this->yaydrdir.string() + this->cfgfile.string()))
    {
        ifstream pf;
        pf.open((this->yaydrdir.string() + this->cfgfile.string()).c_str() );
        string line;
        while ( pf.good() )
        {
            getline(pf,line);
            vector<string> splitvector;
            split(splitvector, line, is_any_of("="));
            if(splitvector.size() == 2)
            {
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
        log::error("No configuration file at " + this->yaydrdir.string() + this->cfgfile.string());
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
