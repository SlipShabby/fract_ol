/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajulanov <ajulanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 18:51:03 by ajulanov          #+#    #+#             */
/*   Updated: 2019/08/31 04:09:40 by ajulanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//  gcc -g draft.c libft/libft.a -L ./minilibx_macos/ -lmlx -framework OpenGL -framework AppKit 

# include "./libft/libft.h"
# include "./minilibx_macos/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <pthread.h>
# include <errno.h>

# define TRD_WIDTH      5
# define TRD_NUM        100

# define ERR_USAGE		"usage: ./fractol [Letter:\"M - mandelbrot\", \"J - julia\", \"3 - Suprise me\"]"
# define ERR_CREATE		"error: could not initialize memory for fractol"
# define ERR_READ	    "error: could not read the fractol"

/*
** hooks
*/
# define PRESS_ESC			53
# define ZOOM_IN			69
# define ZOOM_OUT			78
# define ZOOM_IN_MOUSE		5
# define ZOOM_OUT_MOUSE		4
# define ZOOM_IN_KEYBRD		24
# define ZOOM_OUT_KEYBRD	27
# define NUM_1				83
# define NUM_2				84
# define NUM_3				85
# define NUM_4				86
# define NUM_6				88
# define NUM_7				89
# define NUM_8				91
# define NUM_9				92
# define MOVE_UP			126
# define MOVE_DOWN			125
# define MOVE_LEFT			123
# define MOVE_RIGHT			124
# define MAIN_I				34
# define MAIN_P				35
# define MAIN_R				15
# define MAIN_T				17
# define NUM_3				85
# define NUM_9				92

// ____________________________________________

typedef struct	s_fractol
{
	void                *mlx;
	void                *win;
	void                *img;
	void                *img_ptr;
	int					bpp;
	int					sl;
	int					endian;
	int					bound;
	int					width;
	int					height;
	int					choice;
	int					red;
	int					blue;
	int					green;
	int					max_iter;
	double				min_real;
	double				min_imaginary;
	double				max_real;
	double				max_imaginary;
	double				real_factor;
	double				imaginary_factor;
	int					color;
	double				zoom;
}				t_fractol;
// __________________________________________________

// void	init_hooks(t_fractol *set);
void	kill_bill(char *s);

int key_press_hook(int key, t_fractol *set)
{
	if (key == PRESS_ESC)
		exit(0);
	return (0);
}

void set_hooks(t_fractol *set)
{
	mlx_hook(set->win, 2, 0, key_press_hook, set);
	// mlx_hook(set->win, 4, 0, mouse_press_hook, set);
	// mlx_hook(set->win, 6, 0, mouse_motion_hook, set);
}

int	set_choice(char **av, t_fractol *set)
{
	if (ft_strcmp(av[1], "M") == 0)
		{
			set->choice = 1;
			mandelbrot_fractal(set);
		}
	else if (ft_strcmp(av[1], "J") == 0)
		{
			set->choice = 2;
			julia_fractal(set);
		}
	else if (ft_strcmp(av[1], "S") == 0)
		{
			set->choice = 3;
			surprise_me(set);
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
	set->width = 1000;
	set->height = 1000;
	set->min_real = -2.0;
	set->min_imaginary = -2.0;
	set->max_real = 2.0;
	set->max_imaginary = 2.0;
	set->max_iter = 50;
	set->zoom = 1;
	set->color = 0xE0E907;
	set->real_factor = (set->max_real - set->min_real) / set->width;
	set->imaginary_factor= (set->max_imaginary - set->min_imaginary) / set->width;
	set->min_real += (((set->width / 2) - (set->width / 2)) * set->real_factor);
	set->min_imaginary -= (((set->width / 2) - (set->width / 2)) * set->imaginary_factor);
	set->max_real += (((set->width / 2) - (set->width / 2)) * set->real_factor);
	set->max_imaginary -= (((set->width / 2) - (set->width / 2)) * set->imaginary_factor);
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
		kill_bill(ERR_CREATE);
	if (ac == 2)
	{
		init_env(set);
		win_init(set);
		if ((set_choice(av, set)) == 0)
			kill_bill(ERR_READ);
		ft_putstr("fractol was created\n");
		set_hooks(set);
		mlx_loop(set->mlx);
		free(set);
	}
	else
		kill_bill(ERR_USAGE);
	return (0);
}

