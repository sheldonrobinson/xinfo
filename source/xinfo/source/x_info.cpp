#include <cstdlib> // NULL

#include "m4gfx/sis/defines.h"
#include "m4gfx/sis/x_info.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/pointer.h>

m4gfx::x_info::x_info() : _tag(boost::uuids::to_string(boost::uuids::random_generator()())),
_type(m4gfx::XIC_NONE){
    }

m4gfx::x_info::x_info(m4gfx::XINFOCLASS x_type) : _tag(boost::uuids::to_string(boost::uuids::random_generator()())),
_type(x_type){
    }


m4gfx::x_info::x_info(m4gfx::XINFOCLASS type, rapidjson::Document& info, 
std::set<std::string> attrs ) : _tag(boost::uuids::to_string(boost::uuids::random_generator()())),
_type(type), _attrs(attrs){
    xis_info.CopyFrom(info, xis_info.GetAllocator());
    }


m4gfx::x_info::x_info(const x_info& rhs){
        _tag = rhs._tag;
        _type = rhs._type;
        xis_info.CopyFrom(rhs.xis_info, xis_info.GetAllocator());        
        _attrs = rhs._attrs;
    }
   

const void m4gfx::x_info::insert_json(const rapidjson::Document& d){
    xis_info.CopyFrom(d, xis_info.GetAllocator());
}

const void m4gfx::x_info::insert_info(std::string info_path, const x_info&  data){
    rapidjson::Pointer(info_path).Set(xis_info, data.xis_info);
     _attrs.insert(info_path);
    for(auto s : data._attrs){
        std::string attr_path = info_path + s;
        _attrs.insert(attr_path);
    }
}

const std::string m4gfx::x_info::get_data_as_string() const {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    xis_info.Accept(writer);
    return std::string(buffer.GetString());
}
