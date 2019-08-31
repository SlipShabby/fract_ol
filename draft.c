/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajulanov <ajulanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 18:51:03 by ajulanov          #+#    #+#             */
/*   Updated: 2019/08/30 19:44:20 by ajulanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// gcc -g draft.c ../libft/libft.a -L ../minilibx/ -lmlx -framework OpenGL -framework AppKit

# include "./libft/libft.h"
# include "./minilibx_macos/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <pthread.h>

# define WIDTH          600
# define TRD_WIDTH      5
# define TRD_NUM        100

// ____________________________________________

typedef struct	s_fractol
{
	void        *mlx;
	void        *win;
	void        *img;
	void        *img_ptr;
	int			x;
}				t_fractol;

// __________________________________________________

void		win_init(t_fractol *set)
{
	set->mlx = mlx_init();
	set->win = mlx_new_window(set->mlx, WIDTH, WIDTH, "Fractol Jaan");
	// set->img = mlx
}

int		main(int ac, char **av)
{
	t_fractol	*set;

	if (!(set = ft_memalloc(size_of(t_fractol))))
		return (-1);
	if (ac == 2)
	{
		win_init(set);
	}
	else
		ft_putendl("Usage /fractol \"mandelbrot\", \"julia\", \"custom\"");
	return (0);
}
