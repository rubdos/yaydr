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


#include "../include/node_manager.h"

#include "../include/log.h"

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
    this->nodes.push_back(new_node);
}

node_manager& node_manager::Instance()
{
    return nm;
}

void node_manager::load_node_file(string file)
{
    ifstream node_file(file.c_str());
    string line;
    while ( node_file.good() )
    {
        getline (node_file,line);
        std::vector<string> splitted;
        split(splitted, line, boost::is_any_of("\t "));
        if(splitted[0].length() > 7)
        {
            node* new_node = new node(splitted[0]);
            if(splitted.size() > 1) //the part after \t or space is the part that holds the success rate per node.
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
