#include "hdrs/cub3d.h"

void	message2(int err)
{
	if (err == 10)
		printf("To much paths fields");
	else if (err == 11)
		printf("Path field has wrong number of arguments");
	else if (err == 12)
		printf("System WHUT");
	else if (err == 21)
		printf("Wrong bit map");
	else if (err == 13)
		printf("Fuck you and your color");
	else if (err == 19)
		printf("To many players");
	else if (err == 15)
		printf("Empty line in map");
	else if (err == 16)
		printf("Screenshot");
	else if (err == 17)
		printf("Need more data");
	else if (err == 18)
		printf("Open map");
	else if (err == 22)
		printf("Bad arguments");
}

void	message(int err)
{
	if (err == 0)
		return ;
	printf("Error\n");
	if (err > 9)
		message2(err);
	else if (err == 1)
		printf(" ");
	else if (err == 2)
		printf("To much R fields");
	else if (err == 3)
		printf("R field has wrong number of arguments");
	else if (err == 4)
		printf("R field has non digit sumbols");
	else if (err == 5)
		printf("Wow, memory error");
	else if (err == 6)
		printf("To much color fields");
	else if (err == 7)
		printf("Color field has wrong number of arguments");
	else if (err == 8)
		printf("Color field has non digit symbols");
	else if (err == 9)
		printf("Color must include only [0:255] numbers");
	exit(err);
}
