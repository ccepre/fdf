/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:00:53 by ccepre            #+#    #+#             */
/*   Updated: 2019/05/31 18:09:51 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_keys(t_key *keys)
{
	printf("---- print_keys ----\n");
	while (keys)
	{
		printf("key : %d\n", keys->keycode);
		keys = keys->next;
	}
	printf("--------------------\n");
}

t_key *create_key(int keycode)
{
	t_key	*new;

	if (!(new = (t_key*)malloc(sizeof(t_key))))
		return (NULL);
	new->keycode = keycode;
	new->next = NULL;
	return (new);
}

void	append_key(t_key **keys, t_key *new)
{
	t_key *current;

	print_keys(*keys);
	if (!*keys)
	{
		*keys = new;
		return ;
	}
	current = *keys;
	while (current->next)
	{
		if (current->keycode == new->keycode)
		{
			free(new);
			return ;
		}
		current = current->next;
	}
	if (current->keycode == new->keycode)
		free(new);
	else
		current->next = new;
}

void	remove_elem(t_key **keys, int keycode)
{
	t_key *current;
	t_key *prev;

	current = *keys;
	prev = NULL;
	while (current)
	{
		if (current->keycode == keycode)
		{
			if (!prev)
				*keys = current->next;
			else
				prev->next = current->next;
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

int		search_key(t_key *keys, int keycode)
{
	while (keys)
	{
		if (keys->keycode == keycode)
			return (1);
		keys = keys->next;
	}
	return (0);
}
