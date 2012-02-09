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



#include "server.h"

#include "log.h"
#include "property_manager.h"
#include "node_manager.h"
#include "node.h"
#include "render_manager.h"

#include <string>

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::system;
using namespace boost::algorithm;

server::server()
{
    this->stop = false;
    this->running = false;
}

server::~server()
{
    //dtor
}

void server::loop()
{
    /* The main server loop port 10015 */
    boost::asio::io_service io_service;

    tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), 10015));
    for (;;)
    {
        this->running = true;
        socket_ptr sock(new tcp::socket(io_service));
        a.accept(*sock);
        boost::thread t(boost::bind(&server::session, this, sock));
        if(this->stop)
        {
            break;
        }
    }
}

bool server::parse_command(string data, string ip_address)
{
    /* Parse a command that the node has sent */

    node* n = node_manager::Instance().get_node_by_ip(ip_address);
    string command = data.substr(0,3);
    if(command.compare("GET") == 0)
    {
        /* GET command: send back ONLY from public. namespace */
        string return_data = property_manager::Instance().get( "public." + data.substr( 4 , data.length( ) - 4 ) );
        if(return_data.compare("") == 0)
        {
            log::warning("Client " + ip_address + " requested unknown property " + data);
            return false;
        }
        else
        {
            /* Not found! */

            if(n->connect())
            {
                n->answer(data.substr( 4 , data.length( ) - 4 ), return_data);
            }
            else
            {
                log::warning("Couldn't answer node " + ip_address);
                return false;
            }
            return true;
        }
    }
    else if(command.compare("ANS") == 0)
    {
        //TODO: send ans to node-specific propertymanager
        return true;
    }
    else if(command.compare("REN") == 0) //Do we've got this?
    {
        /* Check if we are permitted to use some CPU for a task. */
        if(render_manager::Instance().task_by_hash(data.substr( 4 , data.length( ) - 4 ) ) == NULL)
        {

            if(n->connect())
            {
                /* Let's already download it */
                n->ask_for_task_xml(data.substr( 4 , data.length( ) - 4 ));
            }
            else
            {
                log::warning("Couldn't answer node " + ip_address);
                return false;
            }
            return true;
        }
        return true;
    }
    else if(command.compare("REQ") == 0) //request for xml
    {
        /* External node asks for an xml file, if available. Else negate. */


        // First check if the rendertask xml/gz is available here... If not, negate request
        render_task* rt;
        if((rt = render_manager::Instance().task_by_hash(data.substr(4, data.length() - 4) ) )!= NULL )
        {
            n->send_render_task(rt); //So, let's do it :-)
        }
        return true;
    }
    else if(command.compare("XML") == 0)
    {
        /* We're receiving an XML file guys. Let's pray! */
        render_task::from_xml_base64_string(
                                            data.substr(4, 44), //first 40 characters after pipe are sha1sum of password
                                            data.substr(45, data.length() - 4)); //following stuff is base64 encoded. Carefull here :p
        return true;
    }
    return false;
}

void server::session(socket_ptr sock)
{
    /* If somebody connects to this node, this function is called */
    try
    {
        /* Infinitly loop till disconnection */
        for (;;)
        {
            char data[1024];
            memset( data, 0, sizeof(data) );

            boost::system::error_code error;
            /*size_t length = */
            sock->read_some(boost::asio::buffer(data), error);

            string ip = (*sock).remote_endpoint().address().to_string();

            if (error == boost::asio::error::eof)
            {
                log::debug( ip + " disconnected");
                node_manager::Instance().get_node_by_ip(ip)->connected = false;
                break; // Connection closed cleanly by peer.
            }
            else if (error)
                throw boost::system::system_error(error); // Some other error.

            string strData = string(data);
            string lastchar = strData.substr(strData.length(),1);
            trim_if(strData, is_any_of("\r\n"));

            if(lastchar.compare("\r") || lastchar.compare("\n")) //if command has ended
            {
                if(this->parse_command(strData, ip ) )
                {
                    boost::asio::write(*sock, boost::asio::buffer("OK\n\r", 4)); //send OK
                }
                else
                {
                    log::debug("error: " + strData);
                    boost::asio::write(*sock, boost::asio::buffer("ER\n\r", 4)); //send ERROR
                }

            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception in server::session thread: " << e.what() << "\n";
    }
}
