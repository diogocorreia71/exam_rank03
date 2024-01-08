#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

char	*ft_cut_line(char *temp)
{
	int i = 0;
	int j = 0;
	char *remain;

	while (temp[i] && temp[i] != '\n')
		i++;
	if (!temp[i] || temp[0] == '\0')
	{
		free(temp);
		return (NULL);
	}
	remain = malloc(sizeof(char) * (ft_strlen(temp) - i + 1));
	if (!remain)
		return (NULL);
	i++;
	while (temp[i])
	{
		remain[j] = temp[i];
		j++;
		i++;
	}
	remain[j] = '\0';
	if (remain[0] == '\0')
	{
		free(remain);
		free(temp);
		return (NULL);
	}
	free(temp);
	return (remain);
}

char	*ft_get_line(char *temp)
{
	char *line;
	int i = 0;

	while (temp[i] && temp[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (temp[i] && temp[i] != '\n')
	{
		line[i] = temp[i];
		i++;
	}
	if (temp[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_strjoin(char *temp, char *buffer)
{
	char *array;
	int i = 0;
	int j = 0;
	int size = 0;

	if (!buffer && !temp)
		return (NULL);
	size = ft_strlen(buffer) + ft_strlen(temp);
	array = malloc(sizeof(char) * (size + 1));
	if (!array)
	{
		free(buffer);
		free(temp);
		return (NULL);
	}
	if (temp)
	{
		while (temp[i])
		{
			array[i] = temp[i];
			i++;
		}
	}
	while (buffer[j])
	{
		array[i] = buffer[j];
		i++;
		j++;
	}
	array[i] = '\0';
	free(temp);
	return (array);
}

int	ft_strchr(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static char *temp;
	char *buffer;
	char *line;
	int count = 1;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	while (!ft_strchr(buffer) && count != 0)
	{
		if ((count = read(fd, buffer, BUFFER_SIZE)) == (-1))
		{
			free(buffer);
			return NULL;
		}
		buffer[count] = '\0';
		temp = ft_strjoin(temp, buffer);
	}
	line = ft_get_line(temp);
	temp = ft_cut_line(temp);
	if (line[0] == '\0')
	{
		free(line);
		free(buffer);
		return NULL;
	}
	free(buffer);
	return (line);
}

// #include <fcntl.h>

// int main()
// {
// 	int fd = 0;
// 	int i = 0;
// 	char *rd;
// 	fd = open("test", O_RDONLY);
// 	while(i < 5)
// 	{
// 		rd = get_next_line(fd);
// 		printf("%s", rd);
// 		free(rd);
// 		i++;
// 	}
// 	return(0);
// }