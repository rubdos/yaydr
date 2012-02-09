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


#include "node.h"
#include "log.h"

#include <string>


#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lambda/lambda.hpp>

using namespace std;

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::system;
using boost::lambda::var;
//using boost::lambda::_1;


node::node(string _ip_address)
{
    /* Initialize a new node by ip adress */
    this->ip_address = _ip_address;

    this->connected = false;
    //'init' socket (=set to NULL...)
    this->_socket = NULL;
    this->_deadline = new deadline_timer(io_service);
}

bool node::is_online()
{
    return true; //todo: ping, save ping, return;
}

void node::handle_connect(const boost::system::error_code& error)
{
    log::debug("start handle_connect for " + this->ip_address);
    if(!error && this->_socket->is_open())
    {
        this->connected = true;
    }
    log::debug("end   handle_connect for " + this->ip_address);
}
bool node::connect()
{
    /* Connect to another node */
    //Perhaps we even dont HAVE to connect. Let's check
    if(this->_socket != NULL && this->_socket->is_open() && this->connected)
    {
        return true;
    }
    // open boost error
    boost::system::error_code error; //= boost::asio::error::host_not_found;
    boost::system::error_code resolver_error;


    //resolve IP address
    tcp::resolver resolver( io_service );
    tcp::resolver::query query( this->ip_address.c_str() , "10015" );
    tcp::resolver::iterator endpoint_iterator = resolver.resolve( query , resolver_error);
    tcp::resolver::iterator end;

    tcp::endpoint endpoint = *endpoint_iterator;


    if(resolver_error || endpoint_iterator == end)
    {
        log::debug("Resolver error");
        return false;
    }


    _socket = new tcp::socket( io_service );

    _socket->async_connect(endpoint, boost::bind(&node::handle_connect, this, boost::asio::placeholders::error));


    _deadline->expires_from_now(boost::posix_time::millisec(100)); //not to long; TODO: make variable via property
    this->check_deadline();


    do io_service.run_one(); while (_deadline->expires_at() <= deadline_timer::traits_type::now());

    if(error)
    {
        log::debug(error.message());
        return false;
    }
    if(this->connected)
    {
        log::debug( this->ip_address + " connected!" );
        return true;
    }
    log::debug(this->ip_address + " is offline" );
    return false;
}

void node::check_deadline()
  {
    // Check whether the deadline has passed. We compare the deadline against
    // the current time since a new asynchronous operation may have moved the
    // deadline before this actor had a chance to run.
    if (_deadline->expires_at() <= deadline_timer::traits_type::now())
    {
      // The deadline has passed. The socket is closed so that any outstanding
      // asynchronous operations are cancelled. This allows the blocked
      // connect(), read_line() or write_line() functions to return.
      _socket->close();

      // There is no longer an active deadline. The expiry is set to positive
      // infinity so that the actor takes no action until a new deadline is set.
      _deadline->expires_at(boost::posix_time::pos_infin);
    }

    // Put the actor back to sleep.
    _deadline->async_wait(bind(&node::check_deadline, this));
  }

void node::load_data(string data)
{
    /* Try to get a public property from the node */
    log::debug("Loading data " + data);
    if(this->connect())
    {
        this->_send("GET|" + data);
    }
}

void node::answer(string query, string data)
{
    /* Send back a property to the node who requested it.*/
    if(this->connect())
    {
        this->_send("ANS|" + query + "|" + data);
    }
}

void node::check_render_task(string sum)
{
    /* This checks if the opposing node is interested in rendering a file (=ONE frame).
       The opposing node can:
        - Refuse (=just negate)
         - because hard drive limit
         - because to much work
         - because the opposing node's user turned local rendering off
        - Accept */

    if(this->connect())
    {
        this->_send("REN|" + sum);
    }
}

void node::ask_for_task_xml(string hash)
{
    /* Called function when interested in rendering a file. Expect a MB data back */
    if(this->connect())
    {
        this->_send("REQ|" + hash);
    }
}

void node::_send(string data)
{
    /* Raw write to node */
    _socket->send( boost::asio::buffer( data + "\r\n" , data.length() + 2 ) );

    char received_data[ 4 ];
    _socket->read_some( boost::asio::buffer( received_data , 4 ) );
    if(string(received_data).substr(0,2).compare("OK") == 0)
    {

    }
    else if(string(received_data).substr(0,2).compare("ER") == 0)
    {
        log::warning("Foreign client doesn't support " + data);
    }
    else
    {

        log::warning("TCP error: No OK/ER returned on request.");
    }
}

node::~node()
{
    //dtor
}
