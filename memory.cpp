#include "memory.h"

void print_ram_memory_stats(void)
{
    std::string response = send_command("cat /proc/meminfo");
    std::vector<std::string> splitted = split(response, '\n');

    std::string temp_str_total = get_numbers_from_str(splitted.at(0));
    std::string temp_str_free = get_numbers_from_str(splitted.at(1));

    double mem_total = atof(temp_str_total.c_str());
    double mem_free = atof(temp_str_free.c_str());
    double mem_used = mem_total - mem_free;

    std::cout << "Total memory:    " << (uint32_t)mem_total/1024 << " MB   [100%]" << std::endl;
    std::cout << "Used memory:     " << (uint32_t)mem_used/1024 << " MB    ["  << llround((mem_used / mem_total) * 100) << "%]" << std::endl;
    std::cout << "Free memory:     " << (uint32_t)mem_free/1024 << " MB    [" << llround((mem_free / mem_total) * 100) << "%]" << std::endl;
}

void print_hard_disk_memory_stats(void)
{
    std::string response = send_command("df");

    std::vector<std::string> splitted = split(response, '\n');

    std::cout << "Filesystem     1K-blocks    Used Available Use% Mounted on" << std::endl;

    for(uint32_t i = 0; i < splitted.size(); i++)
    {
        uint32_t sda = 0;
        uint32_t sdb = 0;

        if(contains(splitted.at(i), "sdb", &sdb))
        {
            std::cout << splitted.at(i) << std::endl;
        }

        if(contains(splitted.at(i), "sda", &sda))
        {
            std::cout << splitted.at(i) << std::endl;
        }
    }
}

void print_active_processes(void)
{
    std::cout << send_command("ps -eo pid,ppid,cmd,%mem,%cpu --sort=-%mem | head");
}
