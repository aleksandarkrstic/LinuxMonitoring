#include "util.h"

std::string sudo_password;

bool starts_with(std::string src, std::string pattern)
{
    if(strcmp(src.substr(0, pattern.length()).c_str(), pattern.c_str()) == 0)
        return true;
    else
        return false;
}

uint32_t contains(std::string src, std::string pattern)
{
    uint32_t pattern_len = pattern.length();

    for(uint32_t i = 0; i < src.length() - pattern_len; i++)
    {
        if(strcmp(src.substr(i, pattern_len).c_str(), pattern.c_str()) == 0)
        {
            return i;
        }
    }

    return 0;
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

void sendit()
{
    fflush(stdin);

    std::string cmd = "";

    getline(std::cin, cmd);

    fflush(stdin);

    std::cout << send_command(cmd);
}

void do_command(uint32_t cmd)
{
    switch(cmd)
    {
        case 1:
            print_memory_stats();
            break;
        case 2:
            break;
        case 0:
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
    std::cout << "  1. Print memory info                      " << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}
