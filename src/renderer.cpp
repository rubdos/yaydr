/*
	Copyright 2011 Ruben De Smet

    yaydr is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    yaydr is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with yaydr.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "renderer.h"
#include "render_task.h"
#include "log.h"

#include <core_api/scene.h>
#include <core_api/environment.h>
#include <core_api/integrator.h>
#include <core_api/imagefilm.h>
#include <yafraycore/xmlparser.h>
#include <yaf_revision.h>
#include <yafraycore/imageOutput.h>

using namespace yafaray;

renderer::renderer()
{
    this->is_accepting = true;
    //TODO: Insert logic to determine if the enduser is actually WILLING to render

    //set up render environment
    render_environment = new renderEnvironment_t();

    string ppath; //try to get the plugin path
    render_environment->getPluginPath(ppath);

    if (ppath.empty())
    {
        log::error("Couldn't read pluginpath from environment!");
    }
    render_environment->loadPlugins(ppath);
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

void start()
{

}

renderer::~renderer()
{
    //dtor
}
