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

#ifndef YAYDR_IMAGE
#define YAYDR_IMAGE

#include <string>
#include <vector>

namespace yaydr
{
    class Image
    {
    public:
        Image(std::string xml_file);
    };
    typedef std::vector<Image*> ImageList;
    typedef ImageList VideoSequence;
    typedef std::vector<VideoSequence> VideoSequenceList;
}
#endif