/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:48:17 by phartman          #+#    #+#             */
/*   Updated: 2024/07/31 02:38:17 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"



void	error(char *message)
{
	ft_printf("%s\n", message);
	exit(1);
}

// void	process_buffer(unsigned char *buffer, int *buffer_index,
// 	char **str, unsigned char character)
// {
// 	char	*temp;

// 	buffer[*buffer_index] = '\0';
// 	if (*str != NULL)
// 	{
// 		temp = *str;
// 		*str = ft_strjoin(*str, (const char *)buffer);
// 		free(temp);
// 		temp = NULL;
// 	}
// 	else
// 		*str = ft_strdup((const char *)buffer);
// 	if (!*str)
// 		error("Error allocating memory");
// 	*buffer_index = 0;
// 	memset(buffer, 0, BUFFER_SIZE);
// 	if (character == END)
// 	{
// 		ft_printf("%s\n", *str);
// 		free(*str);
// 		str = NULL;
// 		return ;
// 	}
// }


void process_buffer(unsigned char *buffer, int *buffer_index, char **str, unsigned char character) {
    char *temp;

    buffer[*buffer_index] = '\0';
    if (*str != NULL) {
        temp = *str;
        *str = ft_strjoin(*str, (const char *)buffer);
        if (!*str)
            error("Error reallocating memory");
        free(temp);
    } else {
        *str = ft_strdup((const char *)buffer);
        if (!*str)
            error("Error allocating memory");
    }
    *buffer_index = 0;
    memset(buffer, 0, BUFFER_SIZE);
    if (character == END) {
        ft_printf("%s\n", *str);
        free(*str);
        *str = NULL;
    }
}

void	add_to_string(unsigned char character)
{
	static unsigned char	buffer[BUFFER_SIZE];
	static int				buffer_index;
	static char				*str;
	//char					*temp;

	if (character == BEGIN)
	{
		buffer_index = 0;
		memset(buffer, 0, BUFFER_SIZE);
		if (str)
		{
			free(str);
			str = NULL;
		}
		return ;
	}
	if (character == END || buffer_index == BUFFER_SIZE - 1)
	{
		process_buffer(buffer, &buffer_index, &str, character);
   		if (character == END)
		{
			
			return ;
		}
		// buffer[buffer_index] = '\0';
		// temp = str;
		// if(str != NULL)
		// {
		// 	temp = str;
		// 	str = ft_strjoin(str, (const char*)buffer);
		// 	if (!str)
		// 		error("Error reallocating memory");
		// 	free(temp);
		// }
		// else
		// {
		// 	str = ft_strdup((const char*)buffer);
		// 	if (!str)
		// 		error("Error allocating memory");
		// }
		// buffer_index = 0;
        // memset(buffer, 0, BUFFER_SIZE);
		// if (character == END)
		// {
		// 	ft_printf("%s\n", str);
		// 	free(str);
		// 	str = NULL;
		// 	return ;
		// }
	}
	else
	{
		buffer[buffer_index++] = character;
		return ;
	}
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static unsigned char	character;
	static int				bits_received;
	static int				zero_counter;

	(void)context;
	character <<= 1;
	if (signum == SIGUSR1)
	{
		character |= 1;
		zero_counter = 0;
	}
	else
		zero_counter++;
	kill(info->si_pid, SIGUSR1);
	if (++bits_received == 8)
	{
		add_to_string(character);
		character = 0;
		bits_received = 0;
	}
	if (zero_counter == 24 && bits_received != 0)
	{
		bits_received = 0;
		character = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("%d\n", getpid());
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
