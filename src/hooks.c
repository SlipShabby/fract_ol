/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajulanov <ajulanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 02:17:48 by ajulanov          #+#    #+#             */
/*   Updated: 2019/09/16 02:39:44 by ajulanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fract_ol.h"

void	reset(t_fractol *set)
{
	set->max_n = 100;
	set->zoom = 1;
	set->move_x = WIDTH / 2;
	set->move_y = WIDTH / 2;
	multithread(set);
}

void	key_color(int key, t_fractol *set)
{
	if (key == NUM_1)
		set->r -= 0x010000;
	if (key == NUM_2)
		set->r += 0x010000;
	if (key == NUM_3)
		set->r = 0;
	if (key == NUM_4)
		set->g -= 0x000100;
	if (key == NUM_5)
		set->g += 0x000100;
	if (key == NUM_6)
		set->g = 0;
	if (key == NUM_7)
		set->b -= 0x000001;
	if (key == NUM_8)
		set->b += 0x000001;
	if (key == NUM_9)
		set->b = 0;
	if (key == NUM_0)
	{
		set->r = 0xd70000;
		set->g = 0x00af00;
		set->b = 0x0000d7;
	}
	multithread(set);
}

int key_press_hook(int key, t_fractol *set)
{
	if (key == PRESS_ESC)
		exit(0);
	if (key == CLEAR)
		reset(set);
	if (key == NMAX_DCR || key == NMAX_IN || key == NMAX_DCR_KEYBD || key == NMAX_IN_KEYBRD)
	{
		if ((key == NMAX_DCR || key == NMAX_DCR_KEYBD) && set->max_n > 0)
			set->max_n -= 5;
		if (key == NMAX_IN || key == NMAX_IN_KEYBRD)
			set->max_n += 5;
		multithread(set);	
	}
	if (key == MOVE_DOWN || key == MOVE_LEFT || key == MOVE_RIGHT || key ==MOVE_UP)
	{
		(key == MOVE_DOWN) ? set->move_y += SHIFT : 0;
		(key == MOVE_UP) ? set->move_y -= SHIFT : 0;
		(key == MOVE_RIGHT) ? set->move_x += SHIFT : 0;
		(key == MOVE_LEFT) ? set->move_x -= SHIFT : 0;
		multithread(set);
	}
	if (key >= NUM_0 && key <= NUM_9)
			key_color(key, set);
	if (key == SPACE)
		set->lock = (set->lock == 0) ? 1 : 0;
	return (0);
}

void set_hooks(t_fractol *set)
{
	mlx_hook(set->win, 2, 0, key_press_hook, set);
	mlx_hook(set->win, 6, 0, mouse_motion, set);
}
