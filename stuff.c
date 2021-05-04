#include "hdrs/cub3d.h"

//#define ABS(a) ((a) < 0 ? -(a) : (a))

int ABS(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}