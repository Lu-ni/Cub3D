# include "cub3d.h"

int parse_score(int score, t_all *a)
{
	int unit;
	int ten;
	int hundred;

	a->score.unit = score % 10;
	a->score.ten = (score / 10) % 10;
	a->score.hundred = (score / 100) % 10;
}
