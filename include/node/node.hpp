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

namespace yaydr
{
    class Node
    {
        public:
            Node();
            Node(libap2p::Node*);
        private:
            /** A pointer to the ap2p connection.
             *  If not connected, _connection == NULL
             */
            libap2p::Node* _connection;
    };
}

#endif
