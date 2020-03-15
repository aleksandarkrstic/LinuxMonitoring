#include "util.h"

std::string sudo_password;

std::string get_numbers_from_str(std::string str)
{
    std::string temp = "";

    for(uint32_t i = 0; i < str.length(); i++)
    {
        if(isdigit(str[i]))
        {
            temp += str[i];
        }
    }

    return temp;
}


bool starts_with(std::string src, std::string pattern)
{
    if(src.empty() || pattern.empty())
        return false;

    if(src.length() < pattern.length())
        return false;

    if(strcmp(src.substr(0, pattern.length()).c_str(), pattern.c_str()) == 0)
        return true;
    else
        return false;
}

bool contains(std::string src, std::string pattern, uint32_t *pos)
{
    *pos = 0;

    if(src.empty() || pattern.empty())
        return false;

    uint32_t src_len = src.length();
    uint32_t pattern_len = pattern.length();

    if(src_len < pattern_len)
        return false;

    for(uint32_t i = 0; i < src_len - pattern_len; i++)
    {
        if(strcmp(src.substr(i, pattern_len).c_str(), pattern.c_str()) == 0)
        {
            *pos = i;
            return true;
        }
    }

    return false;
}

std::vector<std::string> split(const std::string &s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);

	while (getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}

	return tokens;
}

int _kbhit(void)
{
    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);
    return byteswaiting > 0;
}

void sudo_login()
{
    std::cout << "Enter your sudo password:" << std::endl;

    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    fflush(stdin);
    std::cin >> sudo_password;

    std::stringstream ss;
    ss << "'" << sudo_password << "'";
    sudo_password = ss.str();

    fflush(stdin);

    termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

std::string send_command(std::string command)
{
    if(command.substr(0, 4) == "sudo")
    {
        return "sudo commands not implemented yet!\n";
    }

	FILE* pipe = popen(command.c_str(), "r");

	if (!pipe)
		return "";

	char buffer[256];
	std::string result = "";

	while(!feof(pipe))
	{
		if(fgets(buffer, 256, pipe) != NULL)
			result.append(buffer);
	}

	pclose(pipe);

	return result;
}

void send_terminal_command()
{
    fflush(stdin);

    std::string cmd = "";

    getline(std::cin, cmd);

    fflush(stdin);

    std::cout << send_command(cmd);
}

void do_command(char cmd)
{
    switch(cmd)
    {
        case '1':
            std::cout << "--------------------------------------------" << std::endl;
            print_ram_memory_stats();
            std::cout << "--------------------------------------------\n" << std::endl;
            break;
        case '2':
            std::cout << "--------------------------------------------" << std::endl;
            print_hard_disk_memory_stats();
            std::cout << "--------------------------------------------\n" << std::endl;
            break;
        case '3':
            std::cout << "--------------------------------------------" << std::endl;
            print_cpu_info();
            std::cout << "--------------------------------------------\n" << std::endl;
            break;
        case '4':
            std::cout << "--------------------------------------------" << std::endl;
            print_network_info();
            std::cout << "--------------------------------------------\n" << std::endl;
            break;
        case '5':
            std::cout << "--------------------------------------------" << std::endl;
            print_active_processes();
            std::cout << "--------------------------------------------\n" << std::endl;
            break;
        case '0':
            break;
        default:
            print_menu();
            break;
    }
}

void print_menu(void)
{
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "                                            " << std::endl;
    std::cout << "      Linux Monitoring version 1.0          " << std::endl;
    std::cout << "                                            " << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "                        For exit, press 0.  " << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "  1. Print RAM memory info                  " << std::endl;
    std::cout << "  2. Print hard disk memory info            " << std::endl;
    std::cout << "  3. Print CPU info                         " << std::endl;
    std::cout << "  4. Print Network info                     " << std::endl;
    std::cout << "  5. Print active proccesses                " << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}
