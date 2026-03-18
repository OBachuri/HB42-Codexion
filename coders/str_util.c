/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obachuri <obachuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 20:48:43 by obachuri          #+#    #+#             */
/*   Updated: 2026/03/17 20:06:33 by obachuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"codexion.h"

size_t	ft_strlcpy(char *dest_, const char *src_, size_t cnt_)
{
	size_t	i_;

	i_ = 0;
	while (src_[i_])
		i_++;
	if (cnt_)
	{	
		while (*src_ && --cnt_)
		{
			*(dest_++) = *(src_++);
		}	
		*dest_ = 0;
	}
	return (i_);
}

char	*ft_strdup(const char *string)
{
	char	*str_;
	size_t	len_;

	len_ = (size_t)strlen(string);
	str_ = malloc(len_ + 1);
	if (!str_)
		return (NULL);
	ft_strlcpy(str_, string, len_ + 1);
	return (str_);
}

char	*ft_strchr(const char *str, int c)
{
	if (!str)
		return (NULL);
	while (((unsigned char)*str != (unsigned char)c) && (*str))
		str++;
	if ((unsigned char)*str == (unsigned char)c)
		return ((char *)str);
	return (NULL);
}

// fm_str_trim ( string , charstes set ) 
// return string wo charsters from charstes set in begin and end of string

char	*fm_str_trim(char *str_, char *c_set_)
{
	size_t	l_;

	if (!str_ || !c_set_)
		return (str_);
	while (*str_ && ft_strchr(c_set_, *str_))
		str_++;
	if (!(*str_))
		return (str_);
	l_ = strlen(str_);
	while (l_ && ft_strchr(c_set_, str_[l_]))
		l_--;
	str_[l_ + 1] = 0;
	return (str_);
}

char	fm_isspace(const char c_)
{
	return ((c_ == ' ') || (c_ == '\t') || (c_ == '\n')
		|| (c_ == '\r') || (c_ == '\v') || (c_ == '\f'));
}
