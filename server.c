/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:48:17 by phartman          #+#    #+#             */
/*   Updated: 2024/07/26 17:20:12 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char *g_str = NULL;
int timeout;

void	error(char *message)
{
	ft_printf("%s\n", message);
	exit(1);
}

char	*reallocate(char *old_str, int len)
{
	char	*new_str;

	new_str = malloc(len);
	if (!new_str)
		error("Error allocating memory");
	if (old_str)
	{
		ft_memcpy(new_str, old_str, ft_strlen(old_str));
		free(old_str);
	}
	else
		new_str[0] = '\0';
	return (new_str);
}

int	add_to_string(unsigned char character, int client_pid)
{
	static unsigned char buffer[1024];
	static int buffer_index = 0;
	char *temp;

	if(character == '\0' || buffer_index == sizeof(buffer)-1)
	{
		buffer[buffer_index] = '\0';
		temp = g_str;
		if(g_str != NULL)
		{
			temp = g_str;
			g_str = ft_strjoin(g_str, (const char*)buffer);
			if (!g_str)
				error("Error reallocating memory");
			free(temp);
		}
		else
		{
		
			g_str = ft_strdup((const char*)buffer);
			if (!g_str)
				error("Error allocating memory");
		}
		buffer_index = 0;
        memset(buffer, 0, sizeof(buffer));
		if (character == '\0')
		{
			ft_printf("%s\n", g_str);
			free(g_str);
			g_str = NULL;
			return ;
		}
	}
	else
		buffer[buffer_index++] = character;
		return 0;
	if(kill(client_pid, 0) == -1)
	{
		free(g_str);
		buffer_index = 0;
        memset(buffer, 0, sizeof(buffer));
		g_str = NULL;
		return 1;
	}
}


void	signal_handler(int signum, siginfo_t *info, void *context)
{
	int	valid;
	static unsigned char	character;
	static int				bits_received;

	(void)context;
	valid = 0;
	
	if (signum == SIGUSR1 || signum == SIGUSR2)
	{
		character <<= 1;
		if (signum == SIGUSR1)
			character |= 1;
		valid = kill(info->si_pid, SIGUSR1);
		if (valid == -1)
		{
			free(g_str);
			g_str = NULL;
			bits_received = 0;
			character = 0;
			error("Error sending signal");
		}
		bits_received++;
		timeout = 0;
		if (bits_received == 8)
		{
			add_to_string(character, info->si_pid);
			character = 0;
			bits_received = 0;
			
		}
		if (kill(info->si_pid, 0) == -1)
		{
			free(g_str);
			g_str = NULL;
			bits_received = 0;
			character = 0;
			error("Error sending signal");
		}
		
	}
}



// void	decode_char(int signum, siginfo_t *info, unsigned char *character,
// 		int *bits_received)
// {
// 	int	valid;

// 	valid = 0;
// 	if (signum == SIGUSR1 || signum == SIGUSR2)
// 	{
// 		*character <<= 1;
// 		if (signum == SIGUSR1)
// 			*character |= 1;
// 		valid = kill(info->si_pid, SIGUSR1);
// 		if (valid == -1)
// 		{
// 			free(g_str);
// 			g_str = NULL;
// 			*bits_received = 0;
// 			*character = 0;
// 			error("Error sending signal");
// 		}
// 		(*bits_received)++;
// 	}
// }

// void	signal_handler(int signum, siginfo_t *info, void *context)
// {
// 	static int				bits_received;
// 	static unsigned char	character;
// 	static char				*str = NULL;
// 	static int				len;

// 	(void)context;
// 	decode_char(signum, info, &character, &bits_received);
// 	if (bits_received == 8)
// 	{
// 		if (character == '\0')
// 		{
// 			ft_printf("%s\n", str);
// 			free(str);
// 			str = NULL;
// 			len = 0;
// 		}
// 		else
// 		{
// 			str = reallocate(str, len + 2);
// 			str[len++] = character;
// 			str[len] = '\0';
// 		}
// 		bits_received = 0;
// 		character = 0;
// 	}
// }

int	main(void)
{
	struct sigaction	sa;
	int timeout;

	timeout = 0;
	ft_printf("%d\n", getpid());
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
		// usleep(100);
		// timeout += 100;
		// if (timeout > 1000000)
		// {
		// 	//printf("%s", g_str);
		// 	if(g_str)
		// 	{
		// 		free(g_str);
		// 		g_str = NULL;
		// 	}
			
		// 	timeout = 0;
		// }
		
	}
	return (0);
}
