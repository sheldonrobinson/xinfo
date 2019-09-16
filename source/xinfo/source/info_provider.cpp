#include <boost/predef/architecture.h>

#include "m4gfx/sis/predef.hpp"
#include "m4gfx/sis/defines.h"
#include "m4gfx/sis/info_provider.hpp"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/algorithm/string/join.hpp>




m4gfx::info_provider::info_provider() : _tag(boost::uuids::to_string(boost::uuids::random_generator()())), dirty(true), info(m4gfx::XIC_NONE){}

m4gfx::info_provider::info_provider(m4gfx::XINFOCLASS x_type) : _tag(boost::uuids::to_string(boost::uuids::random_generator()())), dirty(true), info(x_type){}

m4gfx::info_provider::info_provider(x_info& _info) : _tag(boost::uuids::to_string(boost::uuids::random_generator()())),info(_info),dirty(true){}

template<>
void m4gfx::typed_info_provider<m4gfx::XIC_NONE>::build() {
        info.set_type(m4gfx::XIC_NONE);
}

template<>
void m4gfx::typed_info_provider<m4gfx::XIC_SUMMARY>::build() {
        info.set_type(m4gfx::XIC_SUMMARY);
}



void InfoProviderFunction ()
{
    m4gfx::typed_info_provider<m4gfx::XIC_SUMMARY> SummaryObj;
    m4gfx::typed_info_provider<m4gfx::XIC_NONE> NoneObj;
}


/*
template<>
const m4gfx::x_info& m4gfx::typed_info_provider<m4gfx::SESSION>::construct() const {
    return m4gfx::x_info();
}

template<>
const m4gfx::x_info& m4gfx::typed_info_provider<m4gfx::ENVIRONMENT>::construct() const {
    return m4gfx::x_info();
}

template<>
const m4gfx::x_info& m4gfx::typed_info_provider<m4gfx::OS>::construct() const {
    return m4gfx::x_info();
}

template<>
const m4gfx::x_info& m4gfx::typed_info_provider<m4gfx::OS_INSTANCES>::construct() const {
    return m4gfx::x_info();
}

template<>
const m4gfx::x_info& m4gfx::typed_info_provider<m4gfx::OPENCL>::construct() const {
    return m4gfx::x_info();
}


template<>
const m4gfx::x_info& m4gfx::typed_info_provider<m4gfx::GL_RENDERERS>::construct() const {
    return m4gfx::x_info();
}

template<>
const m4gfx::x_info& m4gfx::typed_info_provider<m4gfx::GRAPHICS_DEVICES>::construct() const {
    return m4gfx::x_info();
}

template<>
const m4gfx::x_info& m4gfx::typed_info_provider<m4gfx::CL_ACCELERATORS>::construct() const {
    return m4gfx::x_info();
}

template<>
const m4gfx::x_info& m4gfx::typed_info_provider<m4gfx::CPU>::construct() const {
    return m4gfx::x_info();
}

template<>
const m4gfx::x_info& m4gfx::typed_info_provider<m4gfx::PROCESSORS>::construct() const {
    
}

template<>
const m4gfx::x_info& m4gfx::typed_info_provider<m4gfx::VULKAN>::construct() const {
    return m4gfx::x_info();
}

template<>
const m4gfx::x_info& m4gfx::typed_info_provider<m4gfx::VK_RUNTIMES>::construct() const {
    return m4gfx::x_info();
}
*/
