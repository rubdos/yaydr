/*
	Copyright 2011-2012 Ruben De Smet

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef RENDER_PROGRESS_MANAGER_H
#define RENDER_PROGRESS_MANAGER_H

#include <yafraycore/monitor.h>

using namespace yafaray;


class render_progress_manager : public progressBar_t
{
    public:
        render_progress_manager();

        void init(int);
        void update(int);
        void done();
        void setTag(const char*);

        virtual ~render_progress_manager();
    protected:
    private:
        int steps;
};

#endif // RENDER_PROGRESS_MANAGER_H
