/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajulanov <ajulanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 18:17:32 by ajulanov          #+#    #+#             */
/*   Updated: 2019/09/22 15:05:28 by ajulanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <pthread.h>
# include <errno.h>
# include <inttypes.h>

# define WIDTH				1200
# define THREADS			10
# define Z_MULT				1.1
# define SHIFT				10

# define ERR_USAGE			"usage: ./fractol [Type 1st letter: M, J, S, H]"
# define ERR_CREATE			"error: could not initialize fractol"
# define ERR_NAME			"error: invalid name for fractol [M J S H]"

# define PRESS_ESC			53
# define N_DCR				69
# define N_IN				78
# define ZOOM_IN_MOUSE		5
# define ZOOM_OUT_MOUSE		4
# define N_IN_KBRD			24
# define N_DCR_KBRD			27
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
# define UP					126
# define DOWN				125
# define LEFT				123
# define RIGHT				124
# define CLEAR				71
# define SPACE				49

typedef struct				s_fractol
{
	void					*mlx;
	void					*win;
	void					*img;
	int						*img_ptr;
	int						bpp;
	int						sl;
	int						endian;
	int						max_n;
	double					x0;
	double					y0;
	double					aj;
	double					bj;
	int						r;
	int						g;
	int						b;
	int						color;
	int						move_x;
	int						move_y;
	int						drawn;
	int						lock;
	double					zoom;
	pthread_t				threads[THREADS];
	int						(*name)(struct s_fractol *set, int x, int y);
}							t_fractol;

void						kill_bill(char *s);
void						init_win(t_fractol *set);
void						init_env(t_fractol *set);
int							set_choice(char **av, t_fractol *set);
void						set_hooks(t_fractol *set);
int							key_press_hook(int key, t_fractol *set);
void						key_color(int key, t_fractol *set);
void						reset(t_fractol *set);
int							mouse_motion(int x, int y, t_fractol *set);
int							mouse_m_j(int key, int x, int y, t_fractol *set);
void						multithread(t_fractol *set);
void						*find_thread(void *set);
void						draw(t_fractol *set, int y, int y_final);
int							heart(t_fractol *set, int x, int y);
void						heart_fractal(t_fractol *set);
void						burning_fractal(t_fractol *set);
int							burning_ship(t_fractol *set, int x, int y);
void						julia_fractal(t_fractol *set);
int							julia(t_fractol *set, int x, int y);
void						mandelbrot_fractal(t_fractol *set);
int							mandelbrot(t_fractol *set, int x, int y);

#endif
