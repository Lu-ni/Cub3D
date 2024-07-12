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




void draw_score(t_all *a)
{
	parse_score(a->score.score, a);

	draw_digit(a, 2, a->score.hundred);
	draw_digit(a, 1, a->score.ten);
	draw_digit(a, 0, a->score.unit);
}
