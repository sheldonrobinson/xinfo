#include <cstdlib> // NULL

#include "m4gfx/sis/predef.hpp"
#include "m4gfx/sis/info_provider.hpp"
#include "m4gfx/sis/summary_manager.hpp"

m4gfx::summary_manager* m4gfx::summary_manager::ms_instance = NULL;

m4gfx::summary_manager::summary_manager()
{
}

m4gfx::summary_manager::~summary_manager()
{
}

 m4gfx::summary_manager* m4gfx::summary_manager::Instance()
{
    if (ms_instance == NULL) {
        ms_instance = new m4gfx::summary_manager();
    }
    return ms_instance;
}



void m4gfx::summary_manager::Release()
{
    if (ms_instance) {
        delete ms_instance;
    }
    ms_instance = NULL;
}

void m4gfx::summary_manager::setup(){
    m4gfx::typed_info_provider<m4gfx::XINFOCLASS::XIC_CPU> cpuinfo_pro;
    m4gfx::typed_info_provider<m4gfx::XINFOCLASS::XIC_GPU> gpuinfo_pro;
    
    summary_provider.add(cpuinfo_pro.retrieve());
    summary_provider.add(gpuinfo_pro.retrieve());
}

