/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajulanov <ajulanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 02:41:41 by ajulanov          #+#    #+#             */
/*   Updated: 2019/09/16 02:42:10 by ajulanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fract_ol.h"

void draw(t_fractol *set, int y, int y_final)
{
	int x;
	int i;
	int color;

	while (y < y_final)
		{
			x = -1;
			while (++x < WIDTH)
			{
				i = set->name(set, x, y);
				color = (i * set->r/set->max_n) + (i * set->g/set->max_n) + (i * set->b/set->max_n);
				set->img_ptr[x + (y * WIDTH)] = ((i < set->max_n) ? color : 0);
			}
			y++;
		}
}

void *find_thread(void *set)
{
	t_fractol	*f;
	int i;

	f = (t_fractol*)set;
	i = -1;
	while (++i < THREADS)
	{
		if (pthread_equal(pthread_self(), f->threads[i]))
			draw(f, i * (WIDTH / THREADS), i * (WIDTH / THREADS) + (WIDTH / THREADS));
	}
	return (0);
}

void multithread(t_fractol *set)
{
	int i;

	if (set->drawn)
	{
		mlx_clear_window(set->mlx, set->win);
		set->drawn = 0;
	}
	i = -1;
	while (++i < THREADS)
	{
		pthread_create(&set->threads[i], NULL, find_thread, set);
	}
	i = -1;
	while (++i < THREADS)
	{
		pthread_join(set->threads[i], NULL);
	}
	mlx_put_image_to_window(set->mlx, set->win, set->img, 0, 0);
	set->drawn = 1;
}
