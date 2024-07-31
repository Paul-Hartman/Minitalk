/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:59:40 by phartman          #+#    #+#             */
/*   Updated: 2024/07/31 01:50:12 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "ft_printf/ft_printf.h"
# include "ft_printf/libft/libft.h"
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

#define BEGIN 0
#define END 3
#define BUFFER_SIZE	4096


void	error(char *message);

#endif