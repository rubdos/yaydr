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


#ifndef NODE_H
#define NODE_H

#include "render_task.h"

#include <string>


#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::system;

class node
{
    public:
        node(string /* ipadress */);
        virtual ~node();

        bool is_online();
        bool connect();
        void check_deadline();

        void load_data(string);
        void answer(string, string);
        void check_render_task(string);
        void ask_for_task_xml(string);
        void send_render_task(render_task*);
        /* vars */
        bool connected;
        int success_rate;
        string ip_address;
    protected:
        /* vars */
        int _ping;
        tcp::socket* _socket;
        void handle_connect(const boost::system::error_code&);
        deadline_timer* _deadline;
    private:
        void _send(string);

        boost::asio::io_service io_service;
};

#endif // NODE_H
