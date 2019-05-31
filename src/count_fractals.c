/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_fractals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:00:02 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/05/31 21:44:45 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		count_heart(t_pix *pix, int x, int y)
{
	size_t i;

	i = UINT64_MAX;
	while (++i <= pix->maxIter)
	{
		pix->old = (t_vec2){ pix->new.x, pix->new.y };
		pix->new = (t_vec2) { pix->old.x * pix->old.x - pix->new.y * pix->new.y
						+ pix->real_im.x,
						fabs(pix->old.x) * pix->old.y * 2 + pix->real_im.y };
		if ((pix->new.x * pix->new.x + pix->new.y * pix->new.y) > 4)
			break;
		pixel_to_buf(pix->buf, x, y, color_red(i, pix->maxIter, pix->col));
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
		pixel_to_buf(pix->buf, x, y,
				color_burning_ship(i, pix->maxIter, pix->col));
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
		pixel_to_buf(pix->buf, x, y, color_flame(i, pix->maxIter, pix->col));
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
		pixel_to_buf(pix->buf, x, y, get_color_psy(i, pix->maxIter));
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
		if (pix->fract_num == 1)
			pixel_to_buf(pix->buf, x, y,
					color_breeze(i, pix->maxIter, pix->col));
		else
			pixel_to_buf(pix->buf, x, y,
					color_flame(i, pix->maxIter, pix->col));
	}
}