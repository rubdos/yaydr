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


#include "node_manager.h"
#include "log.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

using namespace boost;
using namespace boost::asio;
using namespace boost::system;

static node_manager nm;

node_manager::node_manager()
{

}

void node_manager::add_node(node* new_node)
{
    /* Add a node to the local node manager */
    this->nodes.push_back(new_node);
}

node_manager& node_manager::Instance()
{
    return nm;
}

void node_manager::load_node_file(string file)
{
    /* Nodes are stored into a file. Loads it up here */

    //standard reading of file with an ifstream
    ifstream node_file(file.c_str());
    string line;
    while ( node_file.good() )
    {
        getline (node_file,line);
        std::vector<string> splitted;
        split(splitted, line, boost::is_any_of("\t "));
        if(splitted[0].length() > 7)
        {
            /* Succesrate isn't used yet. It will be used to prioritize a node above another if connection succeeds more than
               with another one */
            node* new_node = new node(splitted[0]);
            if(splitted.size() > 1) //the part after \t or space is the part that holds the success rate per node (not yet used).
            {
                try
                {
                    new_node->success_rate = lexical_cast<int>(splitted[1]);
                }
                catch(bad_lexical_cast &)
                {
                    log::warning("In nodes file: " + splitted[0] + " has bad success_rate. IP added, rate = 0 (no integer)");
                }
            }
            this->add_node(new_node);
        }
    }
}

void node_manager::global_connect()
{
    /* Try to connect to all known nodes */
    log::debug("Global connect");
    for(uint i = 0; i < this->nodes.size(); i++)
    {
        if(this->nodes[i]->connect())
        {
            this->nodes[i]->load_data("systemid");
            this->nodes[i]->load_data("system.yd.version");
        }
    }
}

node* node_manager::get_node_by_ip(string ip)
{
    /* Convert an ip address into a node* object pointer */
    for(uint i = 0; i != this->nodes.size(); i++)
    {
        if(this->nodes[i]->ip_address.compare(ip) == 0)
        {
            return this->nodes[i];
        }
    }
    node* nnode = new node(ip);
    this->nodes.push_back(nnode);
    return nnode;
}

node_manager::~node_manager()
{
    //dtor
}
