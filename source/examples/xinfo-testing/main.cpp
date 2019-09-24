#include <iostream>
#include <sstream>
#include <cstdlib>
#include <m4gfx/sis/x_info.hpp>
#include <m4gfx/sis/summary_manager.hpp>



int main(int argc, char **argv)
{
    /* m4gfx::typed_info_provider<m4gfx::XINFOCLASS::XIC_NONE> blank_pro;
    m4gfx::typed_info_provider<m4gfx::XINFOCLASS::XIC_CPU> cpuinfo_pro;
    m4gfx::typed_info_provider<m4gfx::XINFOCLASS::XIC_GPU> gpuinfo_pro;
    blank_pro.add(cpuinfo_pro.retrieve());
    blank_pro.add(gpuinfo_pro.retrieve());
    */
    //std::stringstream ss;
    //summary_manager::Instance()::GetSystemInformationSummary();
    //boost::property_tree::json_parser::write_json(ss, m4gfx::summary_manager::Instance()->GetSystemInformationSummary().get_data());

    //std::string json;
    std::cout <<m4gfx::summary_manager::Instance()->GetSystemInformationSummary().get_data_as_string() << std::endl;

	//d::set<std::string> fields();
	for (auto field : m4gfx::summary_manager::Instance()->GetSystemInformationSummary().get_fields()) {
		std::cout << field << std::endl;
	}
	return 0;
}
