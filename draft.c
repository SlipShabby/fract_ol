/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajulanov <ajulanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 18:51:03 by ajulanov          #+#    #+#             */
/*   Updated: 2019/09/01 05:01:21 by ajulanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// gcc -g draft.c libft/libft.a -L ./minilibx_macos/ -lmlx -framework OpenGL -framework AppKit -o fractol

# include "./libft/libft.h"
# include "./minilibx_macos/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <pthread.h>
# include <errno.h>

# define WIDTH			1600
# define WIDTH_W		1400
# define HEIGHT      	1200
# define HEIGHT_W      	1000
# define TRD_WIDTH      5
# define TRD_NUM        100
# define THREADS 		8

# define ERR_USAGE		"usage: ./fractol [Letter:\"M - mandelbrot\", \"J - julia\", \"S - Suprise me\"]"
# define ERR_CREATE		"error: could not initialize fractol"
# define ERR_NAME	    "error: invalid name for fractol [M J S]"

# define BLACK			0x000000

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
	int                *img_ptr;
	int					bpp;
	int					sl;
	int					endian;
	int					bound;
	int					width;
	int					height;
	int					choice;
	int					r;
	int					g;
	int					b;
	int					x;
	int					y;
	int					n;
	int					max_n;
	double				min_real;
	double				min_imaginary;
	double				max_real;
	double				max_imaginary;
	double				delta_r;
	double				delta_im;
	double				c_r;
	double				c_im;
	double				real_factor;
	double				imaginary_factor;
	double				tmp;
	double				z_r;
	double				z_im;
	double				z_r_2;
	double				z_im_2;
	double		x0;
	double		y0;
	int					color;
	int					color_shift;
	int					color_change;
	int					x_trans;
	int					y_trans;
	int					drawn;
	int					lock;
	double				zoom;
	pthread_t			threads[THREADS];
	int					(*name)(struct s_fractol *set, int x, int y);
}				t_fractol;
// __________________________________________________

void	kill_bill(char *s);

// __________________________________________________

// int calculate_n(t_fractol *set)
// {
// 	int i;

// 	i = 0;
// 	while (i < set->max_n && set->z_r_2 + set->z_im_2 < 4.0)
// 	{
// 		set->tmp = set->z_r_2 - set->z_im_2 + set->c_r;
// 		set->z_im = 2.0 * set->z_r * set->z_im + set->c_im;
// 		set->z_r = set->tmp;
// 		i++;
// 	}
// 	return (i);
// }

int		mandelbrot(t_fractol *set, int x, int y)
{
	int		i;
	double	tab[6];

	tab[2] = ((double)x - set->x_trans) / ((WIDTH_W / 4) * set->zoom) + set->x0;
	tab[3] = ((double)y - set->y_trans) / ((HEIGHT_W / 4) * set->zoom) + set->y0;
	tab[0] = tab[2];
	tab[1] = tab[3];
	i = 0;
	while (i < set->bound && tab[2] + tab[3] <= 16)
	{
		tab[4] = (tab[2] * tab[2]) - (tab[3] * tab[3]);
		tab[5] = 2 * tab[2] * tab[3];
		tab[2] = tab[4] + tab[0];
		tab[3] = tab[5] + tab[1];
		i++;
	}
	return (i);
}

// int mandelbrot(t_fractol *set, int x, int y)
// {
// 	int i;

// 	i = 0;
// 	while (i < set->bound && set->z_r_2 + set->z_im_2 < 4.0)
// 	{
// 		set->tmp = set->z_r_2 - set->z_im_2 + set->c_r;
// 		set->z_im = 2.0 * set->z_r * set->z_im + set->c_im;
// 		set->z_r = set->tmp;
// 		i++;
// 	}	
// 	return (i);
// }

void draw(t_fractol *set, int y, int y_fin)
{
	int x;
	int i;
	int color;

	while (y < y_fin)
		{
			x = 0;
			while (x < set->width)
			{
				i = set->name(set, x, y);
				color = (i * set->r) + (i * set-> g) + (i * set->b);
				set->img_ptr[x + (y * set->width)] = ((i < set->bound) ? color : 0);
				x++;
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
			draw(f, i * (HEIGHT_W/ THREADS), i * (HEIGHT_W/THREADS) + (HEIGHT_W/THREADS));
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
	while (++i < 10)
	{
		pthread_join(set->threads[i], NULL);
	}
	mlx_put_image_to_window(set->mlx, set->win, set->img, 0, 0);
	set->drawn = 1;
}

void mandelbrot_env(t_fractol *set)
{
	set->width = 1400;
	set->height = 1000;
	// set->min_real = -2.05;
	// set->min_imaginary = -1.4;
	// set->max_real = 1.2;
	// set->max_imaginary = 1.2;
	// set->zoom = 100;
	// set->max_n = 100;
	set->z_r_2 = set->z_r * set->z_r;
	set->z_im_2 = set->z_im * set->z_im;
	set->delta_r = set->max_real - set->min_real;
	set->delta_im = set->max_imaginary - set->min_imaginary;
	set->x = WIDTH - set->width;
	set->y = HEIGHT - set->height;
	set->name = &mandelbrot;
	set->x0 = 0;
	set->y0 = 0;
}

void	mandelbrot_fractal(t_fractol *set)
{
	mandelbrot_env(set);
	mlx_string_put(set->mlx, set->win, WIDTH/2 - 45, 100, 0xFFFFFF, "Mandelbrot");
	multithread(set);
}

// void	mandelbrot_fractal(t_fractol *set)
// {
// 	mandelbrot_env(set);
// 	set->x = 200;
// 	mlx_string_put(set->mlx, set->win, WIDTH/2 - 45, 100, 0xFFFFFF, "Mandelbrot");
// 	while (set->x < set->width)
// 	{
// 		set->y = 200;
// 		while (set->y < set->height)
// 		{
// 			// Convert pixel coordinate to complex number
// 			set->c_r = set->y * (set->real_factor + set->min_real);
// 			set->c_im = set->y * (set->imaginary_factor + set->min_imaginary);
// 			set->n = calculate_n(set);
// 			if (set->n == set->max_n)
// 				mlx_pixel_put(set->mlx, set->win, set->x, set->y, BLACK);
// 			else
// 			mlx_pixel_put(set->mlx, set->win, set->x, set->y, (set->color * set->n / set->max_n));
// 			set->y++;
// 		}
// 		set->x++;
// 	}
// }

// void	init_hooks(t_fractol *set);

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
			set->win = mlx_new_window(set->mlx, WIDTH, HEIGHT, "Jaan's Fractol: Mandelbrot set");
			mandelbrot_fractal(set);
		}
	else if (ft_strcmp(av[1], "J") == 0)
		{
			set->choice = 2;
			set->win = mlx_new_window(set->mlx, WIDTH, HEIGHT, "Jaan's Fractol: Julia set");
			// julia_fractal(set);
		}
	else if (ft_strcmp(av[1], "S") == 0)
		{
			set->choice = 3;
			set->win = mlx_new_window(set->mlx, WIDTH, HEIGHT, "Jaan's Fractol: Random set");
			// surprise_me(set);
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
	set->bound = 100;
	set->width = 1000;
	set->height = 1000;
	set->min_real = -2.0;
	set->min_imaginary = -2.0;
	set->max_real = 2.0;
	set->max_imaginary = 2.0;
	set->max_n = 100;
	set->n = 0;
	set->zoom = 1;
	set->color = 0xE0E907;
	set->r = 0x030000;
	set->g = 0x000300;
	set->b = 0x000003;
	set->x_trans = WIDTH / 2;
	set->y_trans = HEIGHT / 2;
	set->drawn = 0;
	set->lock = 0;
}

void	init_win(t_fractol *set)
{
	set->mlx = mlx_init();
	set->img = mlx_new_image(set->mlx, WIDTH, HEIGHT);
	set->img_ptr = (int*)mlx_get_data_addr(set->img, &set->bpp, &set->sl, &set->endian);
}

// void	reset(t_fractol *set)
// {
// 	set->bound = 100;
// 	set->zoom = 1;
// 	set->x_trans = WIDTH / 2;
// 	set->y_trans = HEIGHT / 2;
// 	multithread(set);
// }

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
		// free(set);
	}
	else
		kill_bill(ERR_USAGE);
	return (0);
}

