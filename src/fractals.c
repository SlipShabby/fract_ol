/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajulanov <ajulanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 02:43:44 by ajulanov          #+#    #+#             */
/*   Updated: 2019/12/17 20:10:18 by ajulanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fract_ol.h"

int			heart(t_fractol *set, int x, int y)
{
	int		i;
	double	tab[6];

	tab[2] = ((double)x - set->move_x) / ((WIDTH / 4) * set->zoom) + set->x0;
	tab[3] = ((double)y - set->move_y) / ((WIDTH / 4) * set->zoom) + set->y0;
	tab[0] = tab[2];
	tab[1] = tab[3];
	i = 0;
	while (i < set->max_n && tab[2] + tab[3] <= 4)
	{
		tab[4] = (tab[2] * tab[2]) - (tab[3] * tab[3]);
		tab[5] = 2 * tab[2] * tab[3];
		tab[2] = fabs(tab[4] + tab[0]);
		tab[3] = tab[5] + tab[1];
		i++;
	}
	return (i);
}

int			burning_ship(t_fractol *set, int x, int y)
{
	int		i;
	double	tab[6];

	tab[2] = ((double)x - set->move_x) / ((WIDTH / 4) * set->zoom) + set->x0;
	tab[3] = ((double)y - set->move_y) / ((WIDTH / 4) * set->zoom) + set->y0;
	tab[0] = tab[2];
	tab[1] = tab[3];
	i = 0;
	while (i < set->max_n && (tab[2] + tab[3]) <= 16)
	{
		tab[4] = (tab[2] * tab[2]) - (tab[3] * tab[3]);
		tab[5] = 2 * tab[2] * tab[3];
		tab[2] = fabs(tab[4] + tab[0]);
		tab[3] = fabs(tab[5]) + tab[1];
		i++;
	}
	return (i);
}

int			julia(t_fractol *set, int x, int y)
{
	int		i;
	double	a;
	double	b;
	double	aa;
	double	bb;

	i = -1;
	a = ((double)x - set->move_x) / ((WIDTH / 4) * set->zoom) + set->x0;
	b = ((double)y - set->move_y) / ((WIDTH / 4) * set->zoom) + set->y0;
	while (++i < set->max_n && a + b <= 16)
	{
		aa = (a * a) - (b * b);
		bb = 2 * a * b;
		a = aa + set->aj;
		b = bb + set->bj;
	}
	return (i);
}

int			mandelbrot(t_fractol *set, int x, int y)
{
	int		i;
	double	tab[6];

	tab[2] = ((double)x - set->move_x) / ((WIDTH / 4) * set->zoom) + set->x0;
	tab[3] = ((double)y - set->move_y) / ((WIDTH / 4) * set->zoom) + set->y0;
	tab[0] = tab[2];
	tab[1] = tab[3];
	i = 0;
	while (i < set->max_n && tab[2] + tab[3] <= 4)
	{
		tab[4] = (tab[2] * tab[2]) - (tab[3] * tab[3]);
		tab[5] = 2 * tab[2] * tab[3];
		tab[2] = tab[4] + tab[0];
		tab[3] = tab[5] + tab[1];
		i++;
	}
	return (i);
}
