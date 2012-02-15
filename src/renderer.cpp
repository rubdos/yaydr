/*
	copyright 2011-2012 Ruben De Smet

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

    Code partly based on yafaray xml_loader
*/

#include "renderer.h"
#include "render_task.h"
#include "log.h"
#include "render_progress_manager.h"

#include <yafray_config.h>
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
    this->render_environment = new renderEnvironment_t();

    string ppath; //try to get the plugin path

    Y_INFO << "Trying to get pluginspath from environment..." << yendl;

    yafout.setMasterVerbosity(3);
    yafout.setMasterVerbosity(VL_WARNING);


    this->render_environment->getPluginPath(ppath);

    if (ppath.empty())
    {
        Y_ERROR << "Couldn't read pluginpath from environment!" << yendl;
        exit(-1);
    }
    this->render_environment->loadPlugins(ppath);

    std::vector<std::string> formats = render_environment->listImageHandlers();
    for(int i = 0; i < formats.size() ; i++)
    {
        Y_INFO << "Format: " << formats[i] << yendl;
    }
}

renderer& renderer::Instance()
{
    static renderer ren;
    return ren;
}

void renderer::set_job(render_task* rt)
{
    /* Set new renderjob */
    if(!this->is_accepting) return;
    log::message("New renderjob.");
    this->current_job = rt;
    this->is_accepting = false; //No overwrite here...
}

void renderer::start()
{
    /* Prepare the scene */
    log::message("Preparing a new scene to render locally...");

    scene_t* scene = new scene_t();

    Y_INFO << "Adding to the environment" << yendl;
    this->render_environment->setScene(scene);

    paraMap_t render;

    Y_INFO << "XML file loading." << this->current_job->xml_file_name << yendl;

    bool success = parse_xml_file(this->current_job->xml_file_name.c_str(), scene, this->render_environment, render);

    if(!success)
    {
        Y_ERROR << "Invalid xmlfile in job " << this->current_job->hash << yendl;
        return;
    }
    else
    {
        Y_INFO << "XML file loaded." << yendl;
    }

    int width=320, height=240;
    int bx = 0, by = 0;
    render.getParam("width", width); // width of rendered image
    render.getParam("height", height); // height of rendered image
    render.getParam("xstart", bx); // border render x start
    render.getParam("ystart", by); // border render y start


    //TODO: Make user changeable!
    render["threads"] = -1;
    render["z_channel"] = false;

    Y_INFO << "width: " << width << "height: " << height << yendl;

    // Are we using z_buf?
    bool use_zbuf = false;
    render.getParam("z_channel", use_zbuf);

    //Start rendering! Finally :-D
    colorOutput_t *out = NULL;

    //No, joking. We need to set more params...
    paraMap_t ihParams;
    ihParams["type"] = string("tga"); //TODO: Make user changeable
    ihParams["width"] = width;
    ihParams["height"] = height;
    ihParams["alpha_channel"] = false; //Yeh. Must be user configured. Sorry :-(
    ihParams["z_channel"] = use_zbuf;

    string outputPath = this->current_job->unique_dir + "render.tga";

    imageHandler_t *ih = this->render_environment->createImageHandler("outFile", ihParams);
    if(ih)
    {
            out = new imageOutput_t(ih, outputPath, bx, by);
            if(!out)
            {
                Y_ERROR << "Couldn't create imageOutput_t." << yendl;
                return;
            }
    }
    else
    {
        Y_ERROR << "Couldn't create imageHandler_t" << yendl;
        return;
    }

    render_progress_manager* rpm = new render_progress_manager();

    if(! this->render_environment->setupScene(*scene, render, *out, rpm) )
    {
        Y_ERROR << "Couldn't setupScene" << yendl;
    }

    scene->render();
    this->render_environment->clearAll(); //Clear our environment

    imageFilm_t *film = scene->getImageFilm();

    delete film; //Some cleaning...
    delete out;

    this->current_job->done = true;
}

renderer::~renderer()
{
    //dtor
}
