/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:11:41 by lnicolli          #+#    #+#             */
/*   Updated: 2024/08/05 14:15:23 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	parse_score(int score, t_all *a)
{
	a->score.unit = score % 10;
	a->score.ten = (score / 10) % 10;
	a->score.hundred = (score / 100) % 10;
}

void	draw_score(t_all *a)
{
	parse_score(a->score.score, a);
	draw_digit(a, 2, a->score.hundred);
	draw_digit(a, 1, a->score.ten);
	draw_digit(a, 0, a->score.unit);
}
