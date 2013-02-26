# Yaydr
## Copyright notice
    copyright 2011 - 2013 Ruben De Smet
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
## About

yaydr (yet another yafaray distributed raytracer) is (or: will be) a fully
distributed and decentralised frontend for network rendering yafaray xml files,
focussed on video rendering and later on single image rendering for Linux, BSD 
and, if found a maintainer, Windows and Mac OSX.


-Have fun rendering your stuff! Will be upping to Archlinux AUR and Ubuntu PPA

## Dependencies

 libap2p (available on github, easy to install)
 Qt for the GUI
 libreadline (linux only) for the debugging console
 sqlite:
     sqlite-devel (on Fedora or other RHEL based distro's) 
     libsqlite-dev (on Ubuntu/Debian and derived systems)
     or Windows / Mac equivalent (try ports/cygwin/mingw package manager)
 
 cmake (build dependency)
 gnu toolchain
 g++ (or mingw equivalent)

## Compiling:
 mkdir build
 cd build
 cmake ..
 make
 sudo make install

# Bugs or Feature requests

Report bugs and featurerequests on github -> Issues.
