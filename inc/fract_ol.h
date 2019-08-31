/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajulanov <ajulanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 18:17:32 by ajulanov          #+#    #+#             */
/*   Updated: 2019/08/31 03:07:52 by ajulanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <pthread.h>

# define TRD_WIDTH      5
# define TRD_NUM        100

# define ERR_USAGE			"usage: ./fractol [Letter:\"M - mandelbrot\", \"J - julia\", \"3 - Custom\"]"
# define ERR_READ	    	"error: could not read the fractol"
# define ERR_CREATE			"error: could not initialize memory for fractol"

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
}				t_fractol;

#endif
