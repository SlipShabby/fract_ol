/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajulanov <ajulanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 02:43:08 by ajulanov          #+#    #+#             */
/*   Updated: 2019/09/16 02:46:49 by ajulanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fract_ol.h"

int		mouse_motion(int x, int y, t_fractol *set)
{
	if ((x == set->aj && y == set->bj) || !set->lock)
		return (0);
	set->aj = ((((double)x - WIDTH) / (WIDTH / 2)) + 1);
	set->bj = ((((double)y - WIDTH) / (WIDTH / 2)) + 1);
	multithread(set);
	return (0);
}

int		mouse_M_J(int key, int x, int y, t_fractol *set)
{
	if (key == 4 || key == 5)
	{
		set->x0 += (x - set->move_x) / ((WIDTH / 4) * set->zoom);
		set->y0 += (y - set->move_y) / ((WIDTH / 4) * set->zoom);
		set->zoom *= ((key == 4) ? Z_MULT : 1 / Z_MULT);
		set->move_x = x;
		set->move_y = y;
		multithread(set);
	}
	return (0);
}