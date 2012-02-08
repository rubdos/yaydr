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




#include "render_task.h"
#include "file_compressor.h"
#include "node_manager.h"
#include "log.h"
#include "configuration.h"
#include "renderer.h"

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <iostream>
#include <fstream>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>

using namespace std;
using namespace boost;

render_task::render_task()
{
    /* Construct a new render_task */

    //make sure we can store our task
    boost::filesystem::path rtsksdir(configuration::Instance().yaydrdir.string() + "rendertasks/");
    if(!boost::filesystem::is_directory(rtsksdir))
    {
        boost::filesystem::create_directory(rtsksdir);
    }
}

render_task* render_task::from_xml_file(string filename)
{
    /* Load the task from an xml file */
    render_task* rt = new render_task();

    if(rt->hash.compare("") == 0)
    {
        rt->generate_password();
    }

    boost::filesystem::path rtdir(configuration::Instance().yaydrdir.string() + "rendertasks/" + rt->hash + "/");
    if(!boost::filesystem::is_directory(rtdir))
    {
        boost::filesystem::create_directory(rtdir);
    }

    rt->unique_dir = rtdir.string();

    vector<string> strsplit;
    split(strsplit, filename, is_any_of("/\\") );
    string destination_filename = rtdir.string() + strsplit[strsplit.size()-1] + ".gz"; //remove stupid directory!

    filesystem::copy_file(filename, rtdir.string() + strsplit[strsplit.size()-1]); //copy in the good directory

    filename = rtdir.string() + strsplit[strsplit.size()-1];

    FILE* source = fopen(filename.c_str(),"r");
    FILE* dest = fopen( destination_filename.c_str() , "w+");

    file_compressor::compress(source,dest);

    fclose(source);
    fclose(dest);
    /*
    We have to compress the stuff. When testing, I had an array of 6000 xml's (=one xml per frame). Well. It was 6 gigabytes.
    1 file @ 1.6 MB. 1 gzip file @ 280 kb. Much better ;)
    */

    rt->xml_file_name = filename;
    rt->gzip_file_name = destination_filename;

    rt->save_configuration();


    return rt;
}

render_task* render_task::from_gzip_file(string filename)
{
    /* Load a gzipped xml file by filename. */
    render_task* rt = new render_task();

    if(rt->hash.compare("") == 0)
    {
        rt->generate_password();
    }

    boost::filesystem::path rtdir(configuration::Instance().yaydrdir.string() + "rendertasks/" + rt->hash + "/");
    if(!boost::filesystem::is_directory(rtdir))
    {
        boost::filesystem::create_directory(rtdir);
    }

    rt->unique_dir = rtdir.string();


    vector<string> strsplit;
    split(strsplit, filename, is_any_of("/\\") );
    string destination_filename =  rtdir.string() + strsplit[strsplit.size()-1] + ".xml"; //remove stupid directory!

    filesystem::copy_file(filename, rtdir.string() + strsplit[strsplit.size()-1]); //copy in the good directory

    filename = rtdir.string() + strsplit[strsplit.size()-1];

    FILE* source = fopen(filename.c_str(),"r");
    FILE* dest = fopen( destination_filename.c_str() , "w+");

    file_compressor::decompress(source,dest);

    fclose(source);
    fclose(dest);
    /*
    We have to compress the stuff. When testing, I had an array of 6000 xml's. Well. It was 6 gigabytes.
    1 file @ 1.6 MB. 1 gzip file @ 280 kb. Much better ;)
    */

    rt->xml_file_name = filename;
    rt->gzip_file_name = destination_filename;

    rt->save_configuration();


    return rt;
}


render_task* render_task::from_hash(string hash)
{
    /* Load the task by a sha1 identification hash */
    ifstream file;
    file.open( (configuration::Instance().yaydrdir.string() + "rendertasks/" + hash + "/" + "configuration.conf").c_str());
    if (file.is_open())
    {
        render_task* rt = new render_task;
        string line;
        while ( file.good() )
        {
            getline (file,line);
            vector<string> SplitVec;
            split( SplitVec, line, is_any_of("="), token_compress_on );
            if(SplitVec.size() > 1)
            {
                if(SplitVec[0].compare("xml") == 0)
                {
                    rt->xml_file_name = SplitVec[1];
                }
                if(SplitVec[0].compare("gz") == 0)
                {
                    rt->gzip_file_name = SplitVec[1];
                }
                if(SplitVec[0].compare("pwd") == 0)
                {
                    rt->password = SplitVec[1];
                }
                if(SplitVec[0].compare("owner") == 0)
                {
                    rt->owner = SplitVec[1];
                }
            }
        }
        rt->unique_dir = configuration::Instance().yaydrdir.string() + "rendertasks/" + hash + "/";
        file.close();
        return rt;
    }
    else
    {
        log::debug("Corrupt rendertask(1): " + hash);
        return NULL;
    }
    return NULL;
}

void render_task::generate_password()
{
    /* Generate a __sha1sum identification and a new password, to release the task from
       the cloud when it's been received well.*/
    string __password;
    string __sha1sum;

    /*        Generate random password    */

    string allowed_characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_.&é'";
    boost::random::random_device rng;
    boost::random::uniform_int_distribution<> index_dist(0, allowed_characters.size() - 1);
    for(int i = 0; i < 30; ++i) {
        __password = __password + allowed_characters[index_dist(rng)];
    }

    byte digest[ CryptoPP::SHA1::DIGESTSIZE ];

    CryptoPP::SHA1 hash;
    hash.CalculateDigest(digest, (unsigned char*)__password.c_str(), __password.length());

    CryptoPP::HexEncoder encoder;
    encoder.Attach( new CryptoPP::StringSink( __sha1sum ) );
    encoder.Put( digest, sizeof(digest) );
    encoder.MessageEnd();
    this->password = __password;
    this->hash = __sha1sum;
}

void render_task::save_configuration()
{
    /* Save the configuration.conf file in the rendertasks directory */
    ofstream pf;
    pf.open( (this->unique_dir + "configuration.conf").c_str() , ios::trunc);
    pf << "xml=" << this->xml_file_name << endl;
    pf << "gz=" << this->gzip_file_name << endl;
    pf << "pwd=" << this->password << endl;
    pf << "owner=" << this->owner << endl;
    pf.close();
}




void render_task::announce()
{
    /* Check if someone is interested in rendering this task */

    if(renderer::Instance().is_accepting)
    {
        renderer::Instance().set_job(this);
        renderer::Instance().start();
    }

    node_manager nm = node_manager::Instance();
    for(unsigned int i = 0;i < nm.nodes.size();i++)
    {
        if(nm.nodes[i]->connected)
        {
            nm.nodes[i]->check_render_task(this->hash);
        }
    }
}

render_task::~render_task()
{
    //dtor
}
