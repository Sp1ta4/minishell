/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:22:33 by mikayel           #+#    #+#             */
/*   Updated: 2025/05/21 11:22:34 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ht_unset(t_ht *ht, const char *key)
{
	unsigned long	index;
	t_ht_item		*node;
	t_ht_item		*prev;

    if (!ht || !key)
        return;
    index = ht_hash(key) % ht->size;
    node = ht->buckets[index];
    prev = NULL;
    while (node)
    {
        if (ft_strcmp(node->key, key) == 0)
        {
            if (prev)
                prev->next = node->next;
            else
                ht->buckets[index] = node->next;
            ht_free_node(node);
            ht->count--;
            return;
        }
        prev = node;
        node = node->next;
    }
}

char *ht_get(t_ht *ht, const char *key)
{
    t_ht_item		*node;
	unsigned long	index;

    if (!ht || !key)
        return NULL;
    index = ht_hash(key) % ht->size;
    node = ht->buckets[index];
    while (node)
    {
        if (ft_strcmp(node->key, key) == 0)
            return node->value;
        node = node->next;
    }
    return NULL;
}

void	ht_print(t_ht *ht)
{
    size_t		i = 0;
    t_ht_item	*node;

    if (!ht)
        return;
    while (i < ht->size)
    {
        node = ht->buckets[i];
        while (node)
        {
            printf("%s=%s\n", node->key, node->value);
            node = node->next;
        }
        i++;
    }
}
