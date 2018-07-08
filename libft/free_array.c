/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 16:32:16 by knovytsk          #+#    #+#             */
/*   Updated: 2017/12/30 16:34:51 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_array(void **array)
{
	int	n;

	n = 0;
	while (array[n] != NULL)
	{
		ft_memdel((void*)&array[n]);
		n++;
	}
	free(array);
	array = NULL;
}
