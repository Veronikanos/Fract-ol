/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_color_scheme.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 20:35:29 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/06/24 20:35:29 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int		chose_color(size_t i, int maxIter, t_color col, int color)
{
	if (color == 0)
		return (color_red(i, maxIter, col));
	else if (color == 1)
		return (color_burning_ship(i, maxIter, col));
	else if (color == 2)
		return (color_flame(i, maxIter, col));
	else if (color == 3)
		return (color_psy(i, maxIter));
	else if (color == 4)
		return (color_breeze(i, maxIter, col));
	return (0);
}