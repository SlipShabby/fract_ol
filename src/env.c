/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajulanov <ajulanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 02:40:56 by ajulanov          #+#    #+#             */
/*   Updated: 2019/09/22 16:56:10 by ajulanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fract_ol.h"

void		heart_fractal(t_fractol *set)
{
	set->name = &heart;
	set->max_n = 200;
	set->r = 255;
	set->g = 192;
	set->b = 203;
	multithread(set);
	mlx_mouse_hook(set->win, mouse_m_j, set);
}

void		burning_fractal(t_fractol *set)
{
	set->name = &burning_ship;
	set->max_n = 140;
	set->color = 0xd7afd7;
	multithread(set);
	mlx_mouse_hook(set->win, mouse_m_j, set);
}

void		julia_fractal(t_fractol *set)
{
	set->name = &julia;
	set->aj = 0.388333;
	set->bj = -0.3001667;
	set->lock = 1;
	multithread(set);
	mlx_mouse_hook(set->win, mouse_m_j, set);
	mlx_hook(set->win, 6, 0, mouse_motion, set);
}

void		mandelbrot_fractal(t_fractol *set)
{
	set->name = &mandelbrot;
	set->color = 0xd7afd7;
	multithread(set);
	mlx_mouse_hook(set->win, mouse_m_j, set);
}
