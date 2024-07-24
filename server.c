/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:48:17 by phartman          #+#    #+#             */
/*   Updated: 2024/07/24 19:25:24 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

void	decode_char(int signum, siginfo_t *info, unsigned char *character,
		int *bits_received, int *len, char **str)
{
	int	valid;

	valid = 0;
	if (signum == SIGUSR1 || signum == SIGUSR2)
	{
		*character <<= 1;
		if (signum == SIGUSR1)
			*character |= 1;
		valid = kill(info->si_pid, SIGUSR1);
		ft_printf("Received signal %d\n", valid);
		if (valid == -1)
		{
			*len = 0;
			free(*str);
			*str = NULL;
			*bits_received = 0;
			*character = 0;
			error("Error sending signal");
		}
		(*bits_received)++;
	}
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int				bits_received;
	static unsigned char	character;
	static char				*str = NULL;
	static int				len;

	(void)context;
	decode_char(signum, info, &character, &bits_received, &len, &str);
	if (bits_received == 8)
	{
		if (character == '\0')
		{
			ft_printf("%s\n", str);
			free(str);
			str = NULL;
			len = 0;
		}
		else
		{
			str = reallocate(str, len + 2);
			str[len++] = character;
			str[len] = '\0';
		}
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
