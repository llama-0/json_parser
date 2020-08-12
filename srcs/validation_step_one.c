#include "libparse.h"

static char	*file_error(char *error_message, char *file_name)
{
	ft_putstr_fd(error_message, 2);
	ft_putendl_fd(file_name, 2);
	exit(1);
}

static char	*file_warning(char *warning_message, char *file_name,
								char *suggestion)
{
	ft_putstr_fd(warning_message, 1);
	ft_putendl_fd(file_name, 1);
	ft_putchar_fd('\n', 1);
	ft_putendl_fd(suggestion, 1);
	exit(1);
}

char		*read_file_strip_ws(char *file_name)
{
	char	*src;
	char	tmp;
	char	buf[BUFF_SIZE + 1];
	int		fd;
	int		ret;

	if (!(fd = open(file_name, O_RDONLY)))
		return (file_error("Error: couldn't open the file: ", file_name));
	ret = 0;
	while (read(fd, &tmp, 1) > 0)
	{
		if (ft_isspace(tmp))
			continue ;
		else
			buf[ret++] = tmp;
		if (ret == BUFF_SIZE)
			return (file_warning("File is too big: ", file_name,
														JSON_FILE_ERROR));
	}
	if (ret == 0)
		return (file_error("error reading file of file is empty: ", file_name));
	buf[ret] = '\0';
	src = ft_strdup(buf);
	close(fd);
	return (src);
}
