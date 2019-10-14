/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmandalo <dmandalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 22:08:48 by dmandalo          #+#    #+#             */
/*   Updated: 2019/10/14 12:53:55 by dmandalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		main(int argc, char **argv)
{
	char	*line;
	int		fd;
	int		ret;

	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	line = NULL;
	ret = 1;
	while (ret)
	{
		ret = get_next_line(fd, &line);
		printf("%s\treturn value - %d\n", line, ret);
		ft_strdel(&line);
	}
	close(fd);
}
