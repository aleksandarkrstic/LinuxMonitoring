#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <inttypes.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>
#include <string.h>

#include "memory.h"

extern std::string sudo_password;

//------------------------------------------------------------------------------------
bool starts_with(std::string src, std::string pattern);
//------------------------------------------------------------------------------------
uint32_t contains(std::string src, std::string pattern);
//------------------------------------------------------------------------------------
std::vector<std::string> split(const std::string &s, char delimiter);
//------------------------------------------------------------------------------------
int _kbhit(void);
//------------------------------------------------------------------------------------
void sudo_login(); //TODO: Not implemented yet
//------------------------------------------------------------------------------------
std::string send_command(std::string command);
//------------------------------------------------------------------------------------
void do_command(uint32_t cmd);
//------------------------------------------------------------------------------------
void print_menu(void);
//------------------------------------------------------------------------------------
void sendit();
//------------------------------------------------------------------------------------

#endif // UTIL_H_INCLUDED
