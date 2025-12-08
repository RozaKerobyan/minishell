/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:31:00 by rkerobya          #+#    #+#             */
/*   Updated: 2025/02/10 17:37:04 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*object;
	void	*element;

	list = NULL;
	if (!f || !lst || !del)
		return (NULL);
	while (lst)
	{
		element = f(lst->content);
		if (!element)
		{
			return (ft_lstclear(&list, del), NULL);
		}
		object = ft_lstnew(element);
		if (!object)
		{
			del(element);
			return (ft_lstclear(&list, del), NULL);
		}
		ft_lstadd_back(&list, object);
		lst = lst->next;
	}
	return (list);
}
