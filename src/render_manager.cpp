/*
        copyright 2011 Ruben De Smet
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


#include "render_manager.h"
#include "render_task.h"
#include "log.h"
#include "configuration.h"
#include "property_manager.h"

#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/progress.hpp>

using namespace std;
using namespace boost;
using namespace boost::system;
using namespace boost::filesystem;

render_manager::render_manager()
{
    //ctor
}

void render_manager::load_tasks()
{
    /* Loads all previously started rendertasks and starts/annouces them */
    log::debug("Loading open rendertasks");
    vector<render_task*> result;
    const path dir_path(configuration::Instance().yaydrdir.string() + "rendertasks");

    directory_iterator end_itr; // default construction yields past-the-end

    for ( directory_iterator itr( dir_path ); itr != end_itr; ++itr )
    {
        vector<string> SplitVec;
        split( SplitVec, itr->path().string(), is_any_of("/\\"), token_compress_on );
        if( is_directory(itr->path()) )
        {
            render_task* task = render_task::from_hash( SplitVec[SplitVec.size() - 1]);
            if(task != NULL)
            {
                this->_tasks.push_back( task );
                log::debug("Recent task: " + SplitVec[SplitVec.size() - 1] );
                task->announce();
            }
        }
    }
}

render_manager& render_manager::Instance()
{
    static render_manager rm;
    return rm;
}

void render_manager::announce(vector<render_task*> tasks)
{
    /* Announce and add a render task */
    log::debug("Announcing... Have a second.");
    for(unsigned int i = 0; i < tasks.size(); i++)
    {
        tasks[i]->announce();
        this->_tasks.push_back(tasks[i]);
    }
}

vector<render_task*> render_manager::load_file_or_directory(string file_or_directory)
{
    /* Takes a raw input string from the user and checks whether it's nothing, a file, or a dir */
    if(is_regular(file_or_directory))
    {
        vector<render_task*> task;
        task.push_back(this->new_task(file_or_directory));
        return task;
    }
    else
    {
        return this->load_directory(file_or_directory);
    }
}

vector<render_task*> render_manager::load_directory(string directory)
{
    /* Loads a directory with XML files */
    log::debug("Recursing directory " + directory);

    //prepare results
    vector<render_task*> result;
    const path dir_path(directory);

    if(! is_directory(dir_path) )
    {
        return result; // If the directory doesn't exist, return no tasks.
    }

    directory_iterator end_itr; // default construction yields past-the-end
    int i = 0;
    for ( directory_iterator itr( dir_path ); itr != end_itr; ++itr )
    {
        vector<string> SplitVec;
        split( SplitVec, itr->path().string(), is_any_of("."), token_compress_on );
        if( SplitVec[SplitVec.size()-1].compare("xml") == 0 )
        {
            render_task* rt = this->new_task( itr->path().string() );
            rt->owner = property_manager::Instance().get("public.systemid");
            rt->save_configuration();
            result.push_back( rt );
            i++;
        }
    }
    return result;
}

render_task* render_manager::task_by_hash(string hash)
{
    /* Get a render_task* object pointer by the sha1 hash identification string */
    for(unsigned int i = 0;i < this->_tasks.size(); i++)
    {
        if(this->_tasks[i]->hash == hash)
        {
            return this->_tasks[i];
        }
    }
    return NULL;
}

render_task* render_manager::new_task(string filename)
{
    /* Load a newly created render_task by the filename*/
    render_task* result = render_task::from_xml_file(filename);
    result->owner = property_manager::Instance().get("public.systemid");
    result->save_configuration();
    return result;
}

render_task* render_manager::input_task(string gzipdata)
{
    /* Loads a task from a gzipped xml file */
    /*render_task* result = render_task::from_gzip_data(gzipdata);
    this->_tasks.push_back(result);
    return result;*/
    return NULL;
}

render_manager::~render_manager()
{
    //dtor
}
