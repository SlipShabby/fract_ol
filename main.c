/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajulanov <ajulanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 19:42:12 by ajulanov          #+#    #+#             */
/*   Updated: 2019/08/31 03:18:13 by ajulanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include "libft.h"

int	set_choice(char **av, t_fractol *set)
{
	if (ft_strcmp(av[1], "M") == 0)
		set->choice = 1;
	else if (ft_strcmp(av[1], "J") == 0)
		set->choice = 2;
	else if (ft_strcmp(av[1], "C") == 0)
		set->choice = 3;
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
	set->width = 1000;
	set->height = 1000;
}

void	win_init(t_fractol *set)
{
	set->mlx = mlx_init();
	set->win = mlx_new_window(set->mlx, set->width, set->height, "Jaan's Fractol");
	set->img = mlx_new_image(set->mlx, set->width, set->height);
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
		return (-1);
	if (ac == 2)
	{
		init_env(set);
		win_init(set);
		if ((set_choice(av, set)) == 0)
			kill_bill(ERR_CREATE);
		ft_putstr("fractol was created\n");
		// init_hooks(set);
		mlx_loop(set->mlx);
	}
	else
		kill_bill(ERR_USAGE);
	return (0);
}
