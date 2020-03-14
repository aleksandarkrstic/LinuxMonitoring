#include "cpu.h"

void print_cpu_info(void)
{
    std::string response = send_command("cat /proc/cpuinfo");
    std::vector<std::string> splitted = split(response, '\n');

    for(uint32_t i = 0; i < splitted.size(); i++)
    {
        uint32_t pos = 0;
        std::string mn_pattern = "model name	: ";
        std::string cpu_mhz_pattern = "cpu MHz		: ";
        std::string cache_size_pattern = "cache size	: ";
        std::string core_id_pattern = "core id		: ";

        if(contains(splitted.at(i), mn_pattern, &pos))
        {
            std::cout << "Model name: " << splitted.at(i).substr(pos + mn_pattern.length()) << std::endl;
        }

        if(contains(splitted.at(i), cpu_mhz_pattern, &pos))
        {
            std::cout << "CPU MHz: " << splitted.at(i).substr(pos + cpu_mhz_pattern.length()) << std::endl;
        }

        if(contains(splitted.at(i), cache_size_pattern, &pos))
        {
            std::cout << "Cache size: " << splitted.at(i).substr(pos + cache_size_pattern.length()) << std::endl;
        }

        if(contains(splitted.at(i), core_id_pattern, &pos))
        {
            std::cout << "Core ID: " << splitted.at(i).substr(pos + core_id_pattern.length()) << std::endl << std::endl;
        }
    }
}
