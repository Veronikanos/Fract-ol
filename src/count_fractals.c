/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_fractals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:00:02 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/06/22 22:15:39 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
			pixel_to_buf(pix->buf, x, y, chose_color(i, pix->maxIter, pix->col, pix->color));
	}
}