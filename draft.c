/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajulanov <ajulanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 18:51:03 by ajulanov          #+#    #+#             */
/*   Updated: 2019/09/02 01:15:57 by ajulanov         ###   ########.fr       */
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

# define WIDTH			1200
# define HEIGHT			1200
# define THREADS 		10
# define Z_MULT			1.05
# define SHIFT	5

# define ERR_USAGE		"usage: ./fractol [Letter:\"M - mandelbrot\", \"J - julia\", \"S - Suprise me\"]"
# define ERR_CREATE		"error: could not initialize fractol"
# define ERR_NAME	    "error: invalid name for fractol [M J S]"

# define BLACK			0x000000

/*
** hooks
*/
# define PRESS_ESC			53
# define NMAX_DCR			69
# define NMAX_IN			78
# define ZOOM_IN_MOUSE		5
# define ZOOM_OUT_MOUSE		4
# define NMAX_IN_KEYBRD		24
# define NMAX_DCR_KEYBD		27
# define NUM_0				82
# define NUM_1				83
# define NUM_2				84
# define NUM_3				85
# define NUM_4				86
# define NUM_5				87
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
# define CLEAR				71
# define TAB				48



// ____________________________________________

typedef struct	s_fractol
{
	void                *mlx;
	void                *win;
	void                *img;
	int             	*img_ptr;

	int					bpp;
	int					sl;
	int					endian;
	int					max_n;

	double				x0;
	double				y0;
	int					x_trans;
	int					y_trans;
	
	int					color;
	int					r;
	int					g;
	int					b;

	int					drawn;
	int					lock;
	double				zoom;
	pthread_t			threads[THREADS];
	int					(*name)(struct s_fractol *set, int x, int y);
//  ???

	double				c_r;
	double				c_im;
	double				tmp1;
	double				tmp2;

	double				z_r;
	double				z_im;
	double				z_r_2;
	double				z_im_2;
}				t_fractol;
// __________________________________________________

void	kill_bill(char *s);
void	multithread(t_fractol *set);


int		mouse_M_J(int key, int x, int y, t_fractol *set)
{
	if (key == 4 || key == 5)
	{
		set->x0 += (x - set->x_trans) / ((WIDTH / 4) * set->zoom);
		set->y0 += (y - set->y_trans) / ((WIDTH / 4) * set->zoom);
		set->zoom *= ((key == 4) ? Z_MULT : 1 / Z_MULT);
		set->x_trans = x;
		set->y_trans = y;
		multithread(set);
	}
	return (0);
}

int		mandelbrot(t_fractol *set, int x, int y)
{
	int		i;
	double	tab[6];

	tab[2] = ((double)x - set->x_trans) / ((WIDTH / 4) * set->zoom) + set->x0;
	tab[3] = ((double)y - set->y_trans) / ((WIDTH / 4) * set->zoom) + set->y0;
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

void mandelbrot_fractal(t_fractol *set)
{
	set->name = &mandelbrot;
	set->x0 = 0;
	set->y0 = 0;
	set->color = 0xd7afd7;
	multithread(set);
}

void	reset(t_fractol *set)
{
	set->max_n = 100;
	set->zoom = 1;
	set->x_trans = WIDTH / 2;
	set->y_trans = WIDTH / 2;
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
		set->r = 0x030000;
		set->g = 0x000300;
		set->b = 0x000003;
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
	if (key >= NUM_0 && key <= NUM_9)
			key_color(key, set);
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
			set->win = mlx_new_window(set->mlx, WIDTH, WIDTH, "Jaan's Fractol: Mandelbrot set");
			mandelbrot_fractal(set);
			mlx_mouse_hook(set->win, mouse_M_J, set);
		}
	else if (ft_strcmp(av[1], "J") == 0)
		{
			set->win = mlx_new_window(set->mlx, WIDTH, WIDTH, "Jaan's Fractol: Julia set");
			// julia_fractal(set);
		}
	else if (ft_strcmp(av[1], "S") == 0)
		{
			set->win = mlx_new_window(set->mlx, WIDTH, WIDTH, "Jaan's Fractol: Random set");
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
	set->max_n = 100;
	set->zoom = 1;
	set->r = 0xE0ffff;
	set->g = 0xffE9ff;
	set->b = 0xffff07;
	set->x_trans = WIDTH / 2;
	set->y_trans = WIDTH / 2;
	set->drawn = 0;
	set->lock = 0;
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

