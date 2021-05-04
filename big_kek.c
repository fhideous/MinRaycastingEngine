#include "hdrs/cub3d.h"

t_kek	kek_full(t_point start, float *ratio_ij, int *ij_s, int high)
{
	t_kek	kek;

	kek.start = start;
	kek.ij_s = ij_s;
	kek.ratio_ij =ratio_ij;
	kek.high = high;
	return (kek);
}
