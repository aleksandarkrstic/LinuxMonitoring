#include "memory.h"

void print_memory_stats()
{
    std::string response = send_command("cat /proc/meminfo");

    std::vector<std::string> splitted = split(response, '\n');

    std::string temp_str_total = "";
    std::string temp_str_free = "";

    for(uint8_t i = 0; i < splitted.at(0).length(); i++)
    {
        if(isdigit(splitted.at(0)[i]))
        {
            temp_str_total += splitted.at(0)[i];
        }
    }

    for(uint8_t i = 0; i < splitted.at(1).length(); i++)
    {
        if(isdigit(splitted.at(1)[i]))
        {
            temp_str_free += splitted.at(1)[i];
        }
    }

    double mem_total = atof(temp_str_total.c_str());
    double mem_free = atof(temp_str_free.c_str());
    double mem_used = mem_total - mem_free;

    std::cout << "Total memory:    " << (uint32_t)mem_total/1024 << " MB   [100%]" << std::endl;
    std::cout << "Used memory:     " << (uint32_t)mem_used/1024 << " MB    ["  << llround((mem_used / mem_total) * 100) << "%]" << std::endl;
    std::cout << "Free memory:     " << (uint32_t)mem_free/1024 << " MB    [" << llround((mem_free / mem_total) * 100) << "%]" << std::endl;
}
