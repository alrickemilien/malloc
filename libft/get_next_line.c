/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 13:43:30 by aemilien          #+#    #+#             */
/*   Updated: 2016/12/12 09:29:19 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_create_file(int fd)
{
	t_file	new_file;

	new_file.fd = fd;
	new_file.buf = NULL;
	return (ft_lstnew(&new_file, sizeof(t_file)));
}

t_list	*ft_lstsearch(t_list *list, int fd)
{
	if (!list)
		return (NULL);
	if (((t_file*)(list->content))->fd == fd)
		return (list);
	while (list)
	{
		if (((t_file*)(list->content))->fd == fd)
			return (list);
		list = list->next;
	}
	return (NULL);
}

int		ft_buf(t_list *tmp, char **line)
{
	char			*buf_tmp;

	if (ft_strchr(((t_file*)(tmp->content))->buf, '\n'))
	{
		*line = ft_strsub(((t_file*)(tmp->content))->buf, 0,
				ft_strchr(((t_file*)(tmp->content))->buf, '\n')
				- ((t_file*)(tmp->content))->buf);
		buf_tmp = ((t_file*)(tmp->content))->buf;
		((t_file*)(tmp->content))->buf = ft_strsub(ft_strchr(
			((t_file*)(tmp->content))->buf, '\n') + 1,
		0, ft_strlen(((t_file*)(tmp->content))->buf) - ft_strlen(*line));
		ft_strdel(&buf_tmp);
		return (1);
	}
	if (!ft_strcmp(((t_file*)(tmp->content))->buf, ""))
	{
		ft_strdel(&((t_file*)(tmp->content))->buf);
		return (0);
	}
	*line = ft_strdup(((t_file*)(tmp->content))->buf);
	ft_strdel(&((t_file*)(tmp->content))->buf);
	return (1);
}

void	ft_addtobuf(t_list *tmp, char *read_buf)
{
	char			*buf_tmp;

	if (!((t_file*)(tmp->content))->buf)
		((t_file*)(tmp->content))->buf = ft_strdup(read_buf);
	else
	{
		buf_tmp = ((t_file*)(tmp->content))->buf;
		((t_file*)(tmp->content))->buf = ft_strjoin(
		((t_file*)(tmp->content))->buf, read_buf);
		ft_strdel(&buf_tmp);
	}
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*list = NULL;
	t_list			*tmp;
	char			read_buf[BUFF_SIZE + 1];
	int				ret;

	if (!(tmp = ft_lstsearch(list, fd)) && fd != -1)
	{
		ft_lstadd(&list, ft_create_file(fd));
		tmp = list;
	}
	ft_bzero(read_buf, BUFF_SIZE);
	while (!ft_strchr(read_buf, '\n')
			&& (ret = read(fd, read_buf, BUFF_SIZE)) > 0)
	{
		read_buf[ret] = '\0';
		ft_addtobuf(tmp, read_buf);
	}
	if (ret == -1)
		return (-1);
	if (((t_file*)(tmp->content))->buf && ft_buf(tmp, line))
		return (1);
	return (0);
}
