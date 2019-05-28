/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 13:13:42 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/05/28 21:08:21 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int	color_burning_ship(int i, int maxIter, t_color col)
{
	double j;
	double t;

	t = (double)i / maxIter;
	j = 1 - t;
	if (i == maxIter)
		return (0);
	col = (t_color) { 6.7 * j * t * 255,
				12.5 * j * t * 255,
				9.3 * j * j * j * t * 255};
	return ((col.R << 16) + (col.G << 8) + col.B);
}

unsigned int	color_flame(int i, int maxIter, t_color col)
{
	if (i == maxIter)
		return (0);
	col = (t_color) { sin(0.3 * (double)i + 2.5) * 128 + 128,
				sin(0.3 * (double)i + 3.5) * 128 + 128,
				sin(0.3 * (double)i + 4.5) * 128 + 190 };
	return ((col.R << 16) + (col.G << 8) + col.B);
}

unsigned int	color(int i, int maxIter, t_color col)
{
	if (i == maxIter)
		return (0);
	else if (i < 64)
		col = (t_color) { i * 2, 0, 0 };
	else if (i < 128)
		col = (t_color) { ((i - 64) * 128 / 126) + 128, 0, 0 };
	else if (i < 256)
		col = (t_color) { ((i - 128) * 62 / 127) + 193, 0, 0 };
	else if (i < 512)
		col = (t_color) { 255, ((i - 256) * 62 / 255) + 1, 0 };
	else if (i < 1024)
		col = (t_color) { 255, ((i - 512) * 63 / 511) + 64, 0 };
	else if (i < 2048)
		col = (t_color) { 255, ((i - 1024) * 63 / 1023) + 128, 0 };
	else if (i < 4096)
		col = (t_color) { 255, ((i - 2048) * 63 / 2047) + 192, 0 };
	return ((col.R << 16) + (col.G << 8) + col.B);
}

unsigned int	get_color_psy(int i, int maxIter)
{
	if (i == maxIter)
		return (0);
	return ((0xFFFFFF / maxIter) * (i + 1000));
}

unsigned int	color_breeze(int i, int maxIter, t_color col)
{
	if (i == maxIter)
		return (0);
	col = (t_color) { cos(0.8 * (double)i + 2),
						sin(0.3 * (double)i + 3) * 128 + 128,
						sin(0.3 * (double)i + 3) * 128 + 230 };
	return ((col.R << 16) + (col.G << 8) + col.B);
}