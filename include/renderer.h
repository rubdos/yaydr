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

#ifndef RENDERER_H
#define RENDERER_H

#include "render_task.h"

#include <core_api/scene.h>
#include <core_api/environment.h>
#include <core_api/integrator.h>
#include <core_api/imagefilm.h>
#include <yafraycore/xmlparser.h>
#include <yaf_revision.h>
#include <yafraycore/imageOutput.h>

using namespace yafaray;

class renderer
{
    public:
        renderer();
        static renderer& Instance(); /* Get the current renderering subsystem */

        void set_job(render_task*); /* Set the current render_job*/
        void start();

        bool is_accepting;

        virtual ~renderer();
    protected:
    private:
        render_task* current_job;

        renderEnvironment_t* render_environment;
};

#endif // RENDERER_H
