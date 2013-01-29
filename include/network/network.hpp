/* Copyright (C) 
 * 2013 - Ruben De Smet
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://gnu.org/licenses/>
 * 
 */

#ifndef CLASS_YAYDR_NODE
#define CLASS_YAYDR_NODE

#include <libap2p/node/node.hpp>
#include <libap2p/network/network.hpp>

namespace yaydr
{
    class Network
    {
        public:
            Network();
            /** Constructs a network object.
             *  @param port The TCP port on which yaydr will bind.
             */
            Network(unsigned int port);
            ~Network();
        private:
            void _Init();
            void _Start();
            
            libap2p::Network* _connection;
            libap2p::Configuration* _configuration;
    };
}

#endif
