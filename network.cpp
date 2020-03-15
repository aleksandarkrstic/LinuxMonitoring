#include "network.h"

void print_network_info(void)
{
    std::string response = send_command("ifconfig");
    std::vector<std::string> splitted = split(response, '\n');

    for(uint32_t i = 0; i < splitted.size(); i++)
    {
        uint32_t ip_pos = 0;
        uint32_t bcast_pos = 0;
        uint32_t sub_mask_pos = 0;

        bool contain_ip = contains(splitted.at(i), "inet addr:", &ip_pos);
        bool contain_bcast = contains(splitted.at(i), "Bcast:", &bcast_pos);
        bool contain_sub_mask = contains(splitted.at(i), "Mask:", &sub_mask_pos);

        if(contain_ip && contain_bcast && contain_sub_mask)
        {
            std::cout << splitted.at(i).substr(ip_pos) << std::endl;
        }
    }
}
