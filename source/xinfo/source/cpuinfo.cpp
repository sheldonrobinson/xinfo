#include <boost/predef/architecture.h>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/algorithm/string/join.hpp>
#include "m4gfx/sis/predef.hpp"
#include "m4gfx/sis/defines.h"
#include "m4gfx/sis/info_provider.hpp"

#include <stdlib.h>
#include <string.h>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <cpu_features_macros.h>

#if defined(CPU_FEATURES_ARCH_X86)
#include <cpuinfo_x86.h>
#elif defined(CPU_FEATURES_ARCH_ARM)
#include <cpuinfo_arm.h>
#elif defined(CPU_FEATURES_ARCH_AARCH64)
#include <cpuinfo_aarch64.h>
#elif defined(CPU_FEATURES_ARCH_MIPS)
#include <cpuinfo_mips.h>
#elif defined(CPU_FEATURES_ARCH_PPC)
#include <cpuinfo_ppc.h>
#endif


#if defined(CPU_FEATURES_ARCH_X86)
template<>
void m4gfx::typed_info_provider<m4gfx::XIC_CPU>::build() {
    cpu_features::X86Info infoVals = cpu_features::GetX86Info();
    rapidjson::Document d;
    d.SetObject();
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
    d.AddMember("isa","X86",allocator);
    info.add_attribute("/isa");
#if defined(BOOST_ARCH_X86_64)
    d.AddMember("architecture","x86-64",allocator);
    d.AddMember("bits","64",allocator);
#else
    d.AddMember("architecture","x86-32",allocator);
    d.AddMember("bits","32",allocator);
#endif
    info.add_attribute("/architecture");
    info.add_attribute("/bits");
    char brand_string[49];
    cpu_features::FillX86BrandString(brand_string);
    d.AddMember("name", std::string(brand_string), allocator);
     info.add_attribute("/name");
    d.AddMember("uarch",  std::string(cpu_features::GetX86MicroarchitectureName(cpu_features::GetX86Microarchitecture(&infoVals))), allocator);
     info.add_attribute("/uarch");
    d.AddMember("family", infoVals.family, allocator);
     info.add_attribute("/family");
    d.AddMember("model", infoVals.model, allocator);
     info.add_attribute("/model");
    d.AddMember("stepping", infoVals.stepping, allocator);
     info.add_attribute("/stepping");
    
    rapidjson::Value cpu_instructions(rapidjson::kObjectType);    
    for(unsigned int i = 0; i< cpu_features::X86_LAST_;++i){
        std::string attr_name(cpu_features::GetX86FeaturesEnumName((cpu_features::X86FeaturesEnum)i));
        rapidjson::Value feature_name(attr_name, allocator);
        rapidjson::Value feature_value((cpu_features::GetX86FeaturesEnumValue(&(infoVals.features), (cpu_features::X86FeaturesEnum)i))?true:false);
        cpu_instructions.AddMember(feature_name, feature_value, allocator);
        info.add_attribute("/features/"+attr_name);
    }
    d.AddMember("features",cpu_instructions, allocator);
    info.add_attribute("/features");       
    info.insert_json(d);
    info.set_type(m4gfx::XIC_CPU);
}
#endif


#if defined(CPU_FEATURES_ARCH_ARM)
template<>
void m4gfx::typed_info_provider<m4gfx::XIC_CPU>::build()  {
    cpu_features::ArmInfo infoVals = cpu_features::GetArmInfo();
    rapidjson::Document d;
    d.SetObject();
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
    d.AddMember("isa","ARM",allocator);
    info.add_attribute("/isa");
    d.AddMember("architecture",info.architecture,allocator);
    info.add_attribute("/architecture");
    d.AddMember("bits","32",allocator);
    info.add_attribute("/bits");
    d.AddMember("implementer", infoVals.implementer, allocator);
     info.add_attribute("/implementer");
    d.AddMember("uarch", "arm", allocator);
     info.add_attribute("/uarch");
    d.AddMember("variant", infoVals.variant, allocator);
     info.add_attribute("/variant");
    d.AddMember("part", infoVals.part, allocator);
     info.add_attribute("/part");
    d.AddMember("revision", infoVals.revision, allocator);
     info.add_attribute("/revision");
    
    rapidjson::Value cpu_instructions(rapidjson::kObjectType);    
    for(unsigned int i = 0; i< cpu_features::ARM_LAST_;++i){
        std::string attr_name(cpu_features::GetArmFeaturesEnumName((cpu_features::ArmFeaturesEnum)i));
        rapidjson::Value feature_name(attr_name, allocator);
        rapidjson::Value feature_value((cpu_features::GetArmFeaturesEnumValue(&(infoVals.features), (cpu_features::ArmFeaturesEnum)i))?true:false);
        cpu_instructions.AddMember(feature_name, feature_value, allocator);
        info.add_attribute("/features/"+attr_name);
    }
    d.AddMember("features",cpu_instructions, allocator);
    info.add_attribute("/features");       
    info.insert_json(d);
    info.set_type(m4gfx::XIC_CPU);
}
#endif

#if defined(CPU_FEATURES_ARCH_AARCH64)
template<>
void m4gfx::typed_info_provider<m4gfx::XIC_CPU>::build()  {
    cpu_features::Aarch64Info infoVals = cpu_features::GetAarch64Info();
    rapidjson::Document d;
    d.SetObject();
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
    d.AddMember("isa","ARM",allocator);
    info.add_attribute("/isa");
    d.AddMember("bits","64",allocator);
    info.add_attribute("/bits");
    d.AddMember("implementer", infoVals.implementer, allocator);
     info.add_attribute("/implementer");
    d.AddMember("uarch", "aarch64", allocator);
     info.add_attribute("/uarch");
    d.AddMember("variant", infoVals.variant, allocator);
     info.add_attribute("/variant");
    d.AddMember("part", infoVals.part, allocator);
     info.add_attribute("/part");
    d.AddMember("revision", infoVals.revision, allocator);
     info.add_attribute("/revision");
    
    rapidjson::Value cpu_instructions(rapidjson::kObjectType);    
    for(unsigned int i = 0; i< cpu_features::AARCH64_LAST_;++i){
        std::string attr_name(cpu_features::GetAarch64FeaturesEnumName((cpu_features::Aarch64FeaturesEnum)i));
        rapidjson::Value feature_name(attr_name, allocator);
        rapidjson::Value feature_value((cpu_features::GetAarch64FeaturesEnumValue(&(infoVals.features), (cpu_features::Aarch64FeaturesEnum)i))?true:false);
        cpu_instructions.AddMember(feature_name, feature_value, allocator);
        info.add_attribute("/features/"+attr_name);
    }
    d.AddMember("features",cpu_instructions, allocator);
    info.add_attribute("/features");       
    info.insert_json(d);
    info.set_type(m4gfx::XIC_CPU);
}
#endif

void CpuInfoProviderFunction ()
{
    m4gfx::typed_info_provider<m4gfx::XIC_CPU> CpuObj;
}
