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


#include "../include/property_manager.h"

#include "../include/log.h"

#include <string>


#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::system;

property_manager::property_manager()
{
    //ctor
}

property_manager& property_manager::Instance()
{
    static property_manager pm;
    return pm;
}

string property_manager::get(string query)
{
    for(uint i = 0; i != this->properties.size(); i++)
    {
        if(this->properties[i].name.compare(query) == 0)
        {
            return this->properties[i].value;
        }
    }
    return "";
}

void property_manager::set(string query, string value)
{
    for(uint i = 0; i != this->properties.size(); i++)
    {
        if(this->properties[i].name.compare(query) == 0)
        {
            this->properties[i].value = value;
            return;
        }
    }
    property prop;
    prop.name = query;
    prop.value = value;
    this->properties.push_back(prop);
}

property_manager::~property_manager()
{
    //dtor
}
