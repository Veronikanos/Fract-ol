/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_fractals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:00:02 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/06/22 22:04:57 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


static unsigned int		chose_color(size_t i, int maxIter, t_color col, int color)
{
	if (color == 0)
		return (color_red(i, maxIter, col));
	else if (color == 1)
		return (color_burning_ship(i, maxIter, col));
	else if (color == 2)
		return (color_flame(i, maxIter, col));
	else if (color == 3)
		return (get_color_psy(i, maxIter));
	else if (color == 4)
		return (color_breeze(i, maxIter, col));
	return (0);
}

void		count_heart(t_pix *pix, int x, int y)
{
	size_t			i;

	i = UINT64_MAX;
	while (++i <= pix->maxIter)
	{
		pix->old = (t_vec2){ pix->new.x, pix->new.y };
		pix->new = (t_vec2) { pix->old.x * pix->old.x - pix->new.y * pix->new.y
						+ pix->real_im.x,
						fabs(pix->old.x) * pix->old.y * 2 + pix->real_im.y };
		if ((pix->new.x * pix->new.x + pix->new.y * pix->new.y) > 4)
			break;
		pixel_to_buf(pix->buf, x, y, chose_color(i, pix->maxIter, pix->col, pix->color));
	}
}
void		count_ship(t_pix *pix, int x, int y)
{
	size_t i;

	i = UINT64_MAX;
	while (++i <= pix->maxIter)
	{
		pix->old = (t_vec2){ pix->new.x, pix->new.y };
		pix->new = (t_vec2) { pix->old.x * pix->old.x - pix->new.y * pix->new.y
						+ pix->real_im.x,
						fabs(pix->old.x * pix->old.y) * 2 + pix->real_im.y };
		if ((pix->new.x * pix->new.x + pix->new.y * pix->new.y) > 4)
			break;
		pixel_to_buf(pix->buf, x, y, chose_color(i, pix->maxIter, pix->col, pix->color));
	}
}

void		count_tricorn(t_pix *pix, int x, int y)
{
	size_t i;

	i = UINT64_MAX;
	while (++i <= pix->maxIter)
	{
		pix->old = (t_vec2){ pix->new.x, pix->new.y };
		pix->new = (t_vec2){ pix->old.x * pix->old.x -
							 pix->new.y * pix->new.y + pix->real_im.x,
							 -2 * pix->old.x * pix->old.y + pix->real_im.y };
		if ((pix->new.x * pix->new.x + pix->new.y * pix->new.y) > 4)
			break;
		pixel_to_buf(pix->buf, x, y, chose_color(i, pix->maxIter, pix->col, pix->color));
	}
}

void		count_cubic_mandelbrot(t_pix *pix, int x, int y)
{
	size_t i;

	i = UINT64_MAX;
	while (++i <= pix->maxIter)
	{
		pix->old = (t_vec2){ pix->new.x, pix->new.y };
		pix->new = (t_vec2){ (pix->old.x * pix->old.x
							  - (pix->old.y * pix->old.y * 3)) * pix->old.x
							  + pix->real_im.x,
							 ((pix->old.x * pix->old.x * 3)
							  - pix->old.y * pix->old.y) * pix->old.y
							  + pix->real_im.y };
		if ((pix->new.x * pix->new.x + pix->new.y * pix->new.y) > 4)
			break;
		pixel_to_buf(pix->buf, x, y, chose_color(i, pix->maxIter, pix->col, pix->color));
	}
}

void		count_mandelbrot(t_pix *pix, int x, int y)
{
	size_t i;

	i = UINT64_MAX;
	while (++i <= pix->maxIter)
	{
		pix->old = (t_vec2){ pix->new.x, pix->new.y };
		pix->new = (t_vec2){ pix->old.x * pix->old.x -
							 pix->new.y * pix->new.y + pix->real_im.x,
							 2 * pix->old.x * pix->old.y + pix->real_im.y };
		if ((pix->new.x * pix->new.x + pix->new.y * pix->new.y) > 4)
			break;
//		if (pix->fract_num == 1)
//			pixel_to_buf(pix->buf, x, y, chose_color(i, pix->maxIter, pix->col));
//		else
			pixel_to_buf(pix->buf, x, y, chose_color(i, pix->maxIter, pix->col, pix->color));
	}
}