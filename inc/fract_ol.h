/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajulanov <ajulanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 18:17:32 by ajulanov          #+#    #+#             */
/*   Updated: 2019/08/30 18:54:48 by ajulanov         ###   ########.fr       */
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

# define WIDTH          600
# define TRD_WIDTH      5
# define TRD_NUM        100

typedef struct	s_fractol
{
	void                *mlx;
	void                *win;
	void                *img;
	void                *img_ptr;
}				t_fractol;

#endif
