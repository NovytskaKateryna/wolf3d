/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:18:31 by knovytsk          #+#    #+#             */
/*   Updated: 2018/02/26 14:18:33 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	errors(int error_msg)
{
	if (error_msg == INCORRECT_NUM_OF_ARGS)
		ft_putendl("Usage: ./wolf3d [map]");
	else if (error_msg == INCORRECT_MAP)
		ft_putendl("Incorrect map.");
	else if (error_msg == INCORRECT_MAP_SIZE)
		ft_putendl("Too small map. Min size: 4x4");
	else if (error_msg == NON_VALID_FILE)
		ft_putendl("File is not valid.");
	else if (error_msg == FAIL_TO_READ)
		ft_putendl("Usage: ./wolf3d [map]");
	else if (error_msg == INCORRECT_PLAYER_POSITION)
		ft_putendl("Incorrect player position.");
	else if (error_msg == TEXTURE_ERROR)
		ft_putendl("Failed to download texture.");
	exit(0);
}
