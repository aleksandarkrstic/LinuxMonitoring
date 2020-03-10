#include "util.h"
#include <iostream>

int main()
{
    print_menu();

    uint32_t key = 0;

    do
	{
        key = 0;

        scanf("%d%*c", &key);

		do_command(key);

		fflush(stdin);
	}
	while (key != 0);

    return 0;
}
