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


#ifndef FILE_COMPRESSOR_H
#define FILE_COMPRESSOR_H

#include <assert.h>
#include <iostream>
#include <stdio.h>
#include "zlib.h"

//Shity ugly and Microsoft fanboy hack, so MS systems can do zlib to...
#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif
/* A memory chunk will be 128K
    if your system is low on this kind of resource (why are you using Yafaray?) You could reduce it.
*/
#define CHUNK 512*1024


class file_compressor
{
    public:
        static int compress(FILE*, FILE*);
        static int decompress(FILE*, FILE*);
    protected:
    private:
};

#endif // FILE_COMPRESSOR_H
