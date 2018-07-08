/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 12:12:34 by knovytsk          #+#    #+#             */
/*   Updated: 2018/01/07 13:21:53 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_make(char **line, t_file *temp, char *buf, int i)
{
	char	*res;

	if (temp->content)
	{
		res = ft_memalloc(ft_strlen(temp->content) + i + 1);
		ft_memcpy(res, temp->content, ft_strlen(temp->content));
		ft_memcpy(res + ft_strlen(temp->content), buf, i);
	}
	else
	{
		res = ft_memalloc(i + 1);
		ft_memcpy(res, buf, i);
	}
	*line = res;
	if (temp->content)
		ft_strdel(&temp->content);
	if (buf[i + 1])
	{
		temp->content = ft_memalloc(ft_strlen(buf) - i);
		ft_memcpy(temp->content, buf + (i + 1), ft_strlen(buf) - i - 1);
	}
	return (1);
}

static void		ft_read_read(t_file **temp, char *buf, int *j)
{
	int		i;
	char	*res;

	i = *j;
	if (!buf[i] && !((*temp)->content))
	{
		(*temp)->content = ft_memalloc(i + 1);
		ft_memcpy((*temp)->content, buf, i);
	}
	else if (!buf[i] && (*temp)->content)
	{
		res = (*temp)->content;
		(*temp)->content = ft_memalloc(ft_strlen(res) + i + 1);
		ft_memcpy((*temp)->content, res, ft_strlen(res));
		ft_memcpy((*temp)->content + ft_strlen(res), buf, i);
		ft_strdel(&res);
	}
}

static int		ft_read(const int fd, char **line, t_file *temp)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;
	int				i;

	ft_memset(buf, 0, BUFF_SIZE + 1);
	if (!(ret = read(fd, buf, BUFF_SIZE)) && !temp->content)
		return (0);
	i = -1;
	while (ret && ++i != (BUFF_SIZE + 1))
	{
		if (buf[i] == '\n')
			return (ft_make(line, temp, buf, i));
		if (!buf[i])
		{
			ft_read_read(&temp, buf, &i);
			ft_memset(buf, 0, BUFF_SIZE + 1);
			ret = read(fd, buf, BUFF_SIZE);
			i = -1;
		}
	}
	*line = temp->content;
	temp->content = NULL;
	return (1);
}

static int		ft_check(const int fd, char **line, t_file *temp)
{
	char		*res;
	size_t		len;

	len = 0;
	while (temp->content && temp->content[len] &&
			temp->content[len] != '\n')
		len++;
	if (!temp->content || !temp->content[len])
		return (ft_read(fd, line, temp));
	res = ft_memalloc(len + 1);
	ft_memcpy(res, temp->content, len);
	*line = res;
	res = ft_memalloc(ft_strlen(temp->content) - len);
	ft_memcpy(res, temp->content + (len + 1),
		ft_strlen(temp->content) - len - 1);
	ft_strdel(&temp->content);
	if (*res)
		temp->content = res;
	else
		free(res);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_file	*ls_files = NULL;
	t_file			*temp;

	if (fd <= -1 || (read(fd, NULL, 0) == -1) || !line)
		return (-1);
	*line = NULL;
	temp = ls_files;
	while (temp != NULL && temp->fd != fd)
		temp = temp->next;
	if (temp == NULL)
	{
		temp = (t_file*)malloc(sizeof(t_file));
		temp->fd = fd;
		temp->next = NULL;
		temp->content = ft_strnew(1);
		if (ls_files != NULL)
			temp->next = ls_files;
		ls_files = temp;
	}
	return (ft_check(fd, line, temp));
}
