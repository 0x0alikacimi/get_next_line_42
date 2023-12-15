/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 19:32:00 by abkacimi          #+#    #+#             */
/*   Updated: 2023/12/15 19:32:01 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef "GET_NEXT_LINE_H"
# define "GET_NEXT_LINE_H"

char    *get_reminder(char **str, int nl)
{
    char    *reminder;
    int        rlen;

    rlen = ft_strlen(*str + nl);
    reminder = ft_substr(*str, nl, rlen);
    free(*str);
    *str = NULL;
    return (reminder);
}

char    *func(char **line, char **tmp, int nl)
{
    *line = ft_substr(*tmp, 0, nl + 1);
    *tmp = get_reminder(tmp, nl + 1);
    return (*line);
}

int    check_newline(char *buff)
{
    int    i;

    i = 0;
    while (buff[i])
    {
        if (buff[i] == '\n')
            return (i);
        i++;
    }
    return (-1);
}

char    *get_next_line(int fd)
{
    static char    *tmp;
    char        buff[BUFFER_SIZE + 1];
    char        *line;
    int            ret;
    int            nl;

    if (!tmp)
        tmp = ft_strdup("");
    ret = read(fd, buff, BUFFER_SIZE);
    while (ret >= 0)
    {
        buff[ret] = 0;
        tmp = ft_strjoin(tmp, buff);
        nl = check_newline(tmp);
        if (nl != -1)
            return (func(&line, &tmp, nl));
        if (!ret && !tmp[0])
            break ;
        if (!ret)
            return (get_reminder(&tmp, 0));
        ret = read(fd, buff, BUFFER_SIZE);
    }
    free(tmp);
    tmp = NULL;
    return (NULL);
}