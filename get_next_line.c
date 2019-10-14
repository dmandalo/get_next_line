/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmandalo <dmandalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 22:08:53 by dmandalo          #+#    #+#             */
/*   Updated: 2019/10/14 16:44:38 by dmandalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_arr		*newlist(const int fd) //функция которая создает новый элемент листа
{
	t_arr	*new;

	if (!(new = (t_arr *)malloc(sizeof(t_arr)))) // выделить память
		return (NULL);
	new->fd = fd; //записать в него fd
	new->rest = ft_strnew(BUFF_SIZE);
	new->next = NULL; //последний элемент должен быть за нулем 
	return (new);
}

char		*checkrest(char **p_n, char *rest)
{
	char *str;

	if ((*p_n = ft_strchr(rest, '\n')) != NULL)
	{
		str = ft_strsub(rest, 0, *p_n - rest);
		ft_strcpy(rest, ++(*p_n)); //в отстаток из самого же остатка начиная там где у нас стояла \n , новую линию копировать уже ненужно поэтому  его пропускаем ++
	}
	else 
	{
		str = ft_strnew(ft_strlen(rest) + 1);
		ft_strcat(str, rest);
		ft_strclr(rest);
	}
	return (str);
}

int			get_line(const int fd, char **line, char *rest)
{
	char			buf[BUFF_SIZE + 1];
	char			*p_n;
	char			*tmp;
	int				rd;

	p_n = NULL;
	rd = 1;
	*line = checkrest(&p_n, rest);
	while (p_n == 0 && ((rd = read(fd, buf, BUFF_SIZE)) != 0))//принимаются fd и буфер | считаются добавяться новые сложаться со старыми и по циклу
	{
		buf[rd] = '\0';
		if ((p_n = ft_strchr(buf, '\n')) != NULL) //возвращает указатель на \n внутри строки 
		{
			ft_strcpy(rest, ++p_n);
			ft_strclr(--p_n);
		}
		tmp = *line;
		if (!(*line = ft_strjoin(tmp, buf)) || rd < 0) // если аллоцирование памяти не удалось возвращаем -1
			return (-1);
		ft_strdel(&tmp);
	}
	return ((ft_strlen(*line) || ft_strlen(rest) || rd) ? 1 : 0); //если хотя бы одно не равно 1, иначе 0
}

int			get_next_line(const int fd, char **line)
{
	static t_arr	*list; //дефолт null 
	t_arr			*tmp;
	int				ret;

	if (fd < 0 || line == 0) //если fd изначально <0 | проверка 
		return (-1);
	if (!list)
		list = newlist(fd);
	tmp = list;
	while (tmp->fd != fd) // когда нашли нужный можно выодить и его отправлять
	{
		if (tmp->next == NULL) //все условия выполнены но мы не дошли знчт создать новый лист  
			tmp->next = newlist(fd);
		tmp = tmp->next; // скипать на следующий пока не будет наш fd 
	}
	ret = get_line(fd, line, tmp->rest);
	return (ret);
}

int		main(void)
{
	char	*line;
	int		fd1;
	int		fd2;
	int		couner;

	fd1 = open("text.txt", O_RDONLY);
	fd2 = open("vim.txt", O_RDONLY);
	couner = 0;
	while (get_next_line(fd1, &line) && couner < 3)
	{
		printf("%s\n", line);
		couner++;
	}
	while (get_next_line(fd2, &line) && couner < 10)
	{
		printf("%s\n", line);
		couner++;
	}
}
