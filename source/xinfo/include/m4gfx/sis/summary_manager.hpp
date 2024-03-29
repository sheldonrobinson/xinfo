// Copyright 2019 Sheldon Robinson. All Rights Reserved.

#ifndef SUMMARY_MANAGER_HPP
#define SUMMARY_MANAGER_HPP

#include "xinfo/xinfo_api.h"
#include "m4gfx/sis/x_info.hpp"
#include "m4gfx/sis/info_provider.hpp"

namespace m4gfx
{

class XINFO_API summary_manager
{
    static summary_manager* ms_instance;

private:
    bool RunOnce = true;
    summary_manager(const summary_manager& rhs);
    summary_manager& operator=(const summary_manager& rhs);
    m4gfx::typed_info_provider<m4gfx::XINFOCLASS::XIC_SUMMARY> summary_provider;
    void setup();

public:
    static summary_manager* Instance();

    static void Release();

    XINFO_API const x_info& GetSystemInformationSummary(){
        if(RunOnce){
            setup();
            RunOnce = false;
        }
        return summary_provider.retrieve();
    }
    


private:
    summary_manager();
    ~summary_manager();

};

}

#endif // SUMMARY_MANAGER_HPP
