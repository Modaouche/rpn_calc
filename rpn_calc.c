/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 08:05:19 by modaouch          #+#    #+#             */
/*   Updated: 2019/01/10 18:18:29 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int		ft_opt(int save, int prev, char *str)
{
	char opt;

	opt = *str;
	*str = ' ';
	//ft_no_divmod_byzero
	if (opt == '+')
		return (save + prev);
	if (opt == '-')
		return (save - prev);
	if (opt == '*')
		return (save * prev);
	if (opt == '/' && prev)
		return (save / prev);
	if (opt == '%' && prev)
		return (save % prev);
	return (0);
}

int		ft_isoperator(char c)
{
	return ((c == '+' || c == '-' || c == '*' || c == '/' || c == '%') ? 1 : 0);
}

int		ft_isdigit(char c)
{
	return ((c >= '0' && c <= '9') ? 1 : 0);
}

int		ft_next(char *str)
{
	int i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		++i;
	if (str[i])
		i++;
	return (i);
}

int		rpn_calc(char *str, int prev, int *i, int dept)
{
	int	mini_stack;
	int	cp_i;
	int check;

	cp_i = *i;
	while (str[cp_i] && !ft_isdigit(str[cp_i]) && !ft_isoperator(str[cp_i]))
		cp_i++;
	if (!str[cp_i])
	{
		*i = cp_i;
		return (prev);
	}
	mini_stack = atoi(&str[cp_i]);
	if (ft_isdigit(str[cp_i]))
	{
		cp_i += ft_next(&str[cp_i]);
		check = cp_i;
		while (str[check] && !ft_isdigit(str[check]) && !ft_isoperator(str[check]))
			check++;
		if (ft_isdigit(str[check]))
		{
			mini_stack = rpn_calc(str, mini_stack, &cp_i, dept + 1);
		}
		else if (str[check])
		{
			*i = cp_i;
			mini_stack = ft_opt(prev, mini_stack, &str[check]);
			return (mini_stack);
		}
	}
	while (str[cp_i] && !ft_isdigit(str[cp_i]) && !ft_isoperator(str[cp_i]))
		cp_i++;
	if (ft_isoperator(str[cp_i]))
		mini_stack = ft_opt(prev, mini_stack, &str[cp_i]);
	else
		while (str[cp_i])
			mini_stack = rpn_calc(str, mini_stack, &cp_i, dept + 1);
	*i = cp_i;
	return (mini_stack);
}

int main(int ac, char **av)
{
	int		tab[2];
	int ret;
	int i;

	ret = 0;
	i = 0;
	tab[0] = 0;
	tab[1] = 0;//osef
	if (ac != 2)
	{
		write(1, "Error\n", 7);
		return (0);
	}
	ret = rpn_calc(av[1], tab[0], &i, 1);
	printf("%d\n",ret ); 
	return (0);
}
