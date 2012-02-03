/*
	Copyright 2011 Ruben De Smet

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

#include "renderer.h"
#include "render_task.h"

renderer::renderer()
{
    this->is_accepting = true;
    //TODO: Insert logic to determine if the user is actually WILLING to render
}

renderer& renderer::Instance()
{
    static renderer ren;
    return ren;
}

void renderer::set_job(render_task* rt)
{
    this->current_job = rt;
}

renderer::~renderer()
{
    //dtor
}
