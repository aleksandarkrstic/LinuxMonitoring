#include "util.h"
#include <iostream>

static struct termios old, new_one;

// Initialize new terminal i/o settings:
void init_termios(int echo)
{
	tcgetattr(0, &old); // grab old terminal i/o settings
	new_one = old; // make new settings same as old settings
	new_one.c_lflag &= ~ICANON; // disable buffered i/o
	new_one.c_lflag &= echo ? ECHO : ~ECHO; // set echo mode
	tcsetattr(0, TCSANOW, &new_one); // use these new terminal i/o settings now
}

int main()
{
    print_menu();

    char key = 0;

    init_termios(0);

    do
	{
		while(!_kbhit());

		key = getchar();

        do_command(key);
	}
	while(key != '0');

	tcflush(0, TCIFLUSH); // Clear stdin to prevent characters appearing on prompt

    return 0;
}
