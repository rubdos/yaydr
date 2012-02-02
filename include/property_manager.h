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


#ifndef PROPERTY_MANAGER_H
#define PROPERTY_MANAGER_H

#include "log.h"

#include <string>


#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::system;

struct property
{
    string name;
    string value;
};

class property_manager
{
    public:
        property_manager();
        static property_manager& Instance();
        virtual ~property_manager();

        string get(string);
        void set(string, string);

        vector<property> properties;
    protected:
    private:
};

#endif // PROPERTY_MANAGER_H
