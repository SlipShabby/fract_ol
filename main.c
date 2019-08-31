/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajulanov <ajulanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 19:42:12 by ajulanov          #+#    #+#             */
/*   Updated: 2019/08/30 19:45:23 by ajulanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include "libft.h"

int	main(int ac, char **av)
{
	t_fractol	*set;

	if (!(set = ft_memmaloc(size_of(t_fractol))))
		return (-1);
	if (ac == 2)
	{
		win_init(set);
	}
	else
		ft_putendl("Usage /fractol \"mandelbrot\", \"julia\", \"custom\"");
	return (0);
}
