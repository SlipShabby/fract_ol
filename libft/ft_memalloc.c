/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajulanov <ajulanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 03:50:49 by ajulanov          #+#    #+#             */
/*   Updated: 2019/08/30 19:31:31 by ajulanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*new;

	if (!size)
		return (NULL);
	new = (void *)malloc(sizeof(void*) * size);
	if (!new)
		return (NULL);
	ft_bzero(new, size);
	return (new);
}
