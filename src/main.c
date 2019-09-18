/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajulanov <ajulanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 19:42:12 by ajulanov          #+#    #+#             */
/*   Updated: 2019/09/16 02:17:25 by ajulanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fract_ol.h"

int	set_choice(char **av, t_fractol *set)
{
	if (ft_strcmp(av[1], "M") == 0)
		{
			set->win = mlx_new_window(set->mlx, WIDTH, WIDTH, "Jaan's Fractol: Mandelbrot set");
			mandelbrot_fractal(set);
			mlx_mouse_hook(set->win, mouse_M_J, set);
		}
	else if (ft_strcmp(av[1], "J") == 0)
		{
			set->win = mlx_new_window(set->mlx, WIDTH, WIDTH, "Jaan's Fractol: Julia set");
			julia_fractal(set);
			mlx_mouse_hook(set->win, mouse_M_J, set);
			mlx_hook(set->win, 6, 0, mouse_motion, set);
		}
	else if (ft_strcmp(av[1], "S") == 0)
		{
			set->win = mlx_new_window(set->mlx, WIDTH, WIDTH, "Jaan's Fractol: Burning ship");
			burning_fractal(set);
			mlx_mouse_hook(set->win, mouse_M_J, set);
		}
	else if (ft_strcmp(av[1], "H") == 0)
		{
			set->win = mlx_new_window(set->mlx, WIDTH, WIDTH, "Jaan's Fractol: Heart");
			heart_fractal(set);
			mlx_mouse_hook(set->win, mouse_M_J, set);
		}
	else
		kill_bill(ERR_USAGE);
	return (1);
}

void init_env(t_fractol *set)
{
	set->mlx = 0;
	set->win = 0;
	set->img = 0;
	set->bpp = 4;
	set->sl = 0;
	set->endian = 0;
	set->max_n = 100;
	set->zoom = 1;
	set->r = 0xE0ffff;
	set->g = 0xffE9ff;
	set->b = 0xffff07;
	set->move_x = WIDTH / 2;
	set->move_y = WIDTH / 2;
	set->drawn = 0;
	set->x0 = 0;
	set->y0 = 0;
}

void	init_win(t_fractol *set)
{
	set->mlx = mlx_init();
	set->img = mlx_new_image(set->mlx, WIDTH, WIDTH);
	set->img_ptr = (int*)mlx_get_data_addr(set->img, &set->bpp, &set->sl, &set->endian);
}

void	kill_bill(char *s)
{
	if (errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	exit(1);
}

int		main(int ac, char **av)
{
	t_fractol	*set;

	if (!(set = ft_memalloc(sizeof(t_fractol))))
		kill_bill(ERR_CREATE);
	if (ac == 2)
	{
		init_env(set);
		init_win(set);
		if ((set_choice(av, set)) == 0)
			kill_bill(ERR_CREATE);
		ft_putstr("fractol was created\n");
		set_hooks(set);
		mlx_loop(set->mlx);
		free(set);
	}
	else
		kill_bill(ERR_USAGE);
	return (0);
}
