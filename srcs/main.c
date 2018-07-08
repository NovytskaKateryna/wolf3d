/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 13:45:01 by knovytsk          #+#    #+#             */
/*   Updated: 2018/03/18 15:31:15 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	scene_files(t_render *r)
{
	int n;
	int fd[3];

	n = -1;
	fd[0] = open("maps/map1", O_RDONLY);
	fd[1] = open("maps/map2", O_RDONLY);
	fd[2] = open("maps/map3", O_RDONLY);
	while (++n < 3)
	{
		if (fd[n] == -1)
			errors(NON_VALID_FILE);
		else if (read(fd[n], NULL, 0) == -1)
			errors(FAIL_TO_READ);
		if (n == 0)
			get_map_data(&r->scene[n], fd[n], "maps/map1");
		if (n == 1)
			get_map_data(&r->scene[n], fd[n], "maps/map2");
		if (n == 2)
			get_map_data(&r->scene[n], fd[n], "maps/map3");
	}
	init_player(r, 0);
}

int		main(int ac, char **av)
{
	int			fd;
	t_render	r;

	if (ac > 2)
		errors(INCORRECT_NUM_OF_ARGS);
	if (ac == 2)
	{
		if ((fd = open(av[1], O_RDONLY)) == -1)
			errors(NON_VALID_FILE);
		else if (read(fd, NULL, 0) == -1)
			errors(FAIL_TO_READ);
		get_map_data(&r.map, fd, av[1]);
		init_player(&r, 1);
	}
	if (ac == 1)
		scene_files(&r);
	return (0);
}
