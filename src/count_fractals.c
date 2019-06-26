/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_fractals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:00:02 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/06/26 22:17:23 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		count_heart(t_pix *pix, int x, int y)
{
	size_t			i;
	t_vec2			new;
	t_vec2			old;
	t_vec2			real_im;

	real_im =
			calc_real_imag((t_vec2){ x, y }, pix->move, pix->rate, pix->zoom);
//	new = (t_vec2) { 0, 0 };
//	old = (t_vec2) { 0, 0 };
	i = UINT64_MAX;
	while (++i <= pix->maxIter)
	{
		old = (t_vec2){ new.x, new.y };
		new = (t_vec2) { old.x * old.x - new.y * new.y
						+ real_im.x,
						fabs(old.x) * old.y * 2 + real_im.y };
		if ((new.x * new.x + new.y * new.y) > 4)
			break;
		pixel_to_buf(pix->buf, x, y, chose_color(i, pix->maxIter, pix->col, pix->color));
	}
}
void		count_ship(t_pix *pix, int x, int y)
{
	size_t			i;
	t_vec2			new;
	t_vec2			old;
	t_vec2			real_im;

	real_im =
			calc_real_imag((t_vec2){ x, y }, pix->move, pix->rate, pix->zoom);
//	new = (t_vec2) { 0, 0 };
//	old = (t_vec2) { 0, 0 };
	i = UINT64_MAX;
	while (++i <= pix->maxIter)
	{
		old = (t_vec2){ new.x, new.y };
		new = (t_vec2) { old.x * old.x - new.y * new.y
						+ real_im.x,
						fabs(old.x * old.y) * 2 + real_im.y };
		if ((new.x * new.x + new.y * new.y) > 4)
			break;
		pixel_to_buf(pix->buf, x, y, chose_color(i, pix->maxIter, pix->col, pix->color));
	}
}

void		count_tricorn(t_pix *pix, int x, int y)
{
	size_t			i;
	t_vec2			new;
	t_vec2			old;
	t_vec2			real_im;

	real_im =
			calc_real_imag((t_vec2){ x, y }, pix->move, pix->rate, pix->zoom);
//	new = (t_vec2) { 0, 0 };
//	old = (t_vec2) { 0, 0 };
	i = UINT64_MAX;
	while (++i <= pix->maxIter)
	{
		old = (t_vec2){ new.x, new.y };
		new = (t_vec2){ old.x * old.x - new.y * new.y + real_im.x,
						-2 * old.x * old.y + real_im.y };
		if ((new.x * new.x + new.y * new.y) > 4)
			break;
		pixel_to_buf(pix->buf, x, y, chose_color(i, pix->maxIter, pix->col, pix->color));
	}
}

void		count_cubic_mandelbrot(t_pix *pix, int x, int y)
{
	size_t			i;
	t_vec2			new;
	t_vec2			old;
	t_vec2			real_im;

	real_im =
			calc_real_imag((t_vec2){ x, y }, pix->move, pix->rate, pix->zoom);
//	new = (t_vec2) { 0, 0 };
//	old = (t_vec2) { 0, 0 };
	i = UINT64_MAX;
	while (++i <= pix->maxIter)
	{
		old = (t_vec2){ new.x, new.y };
		new = (t_vec2){ (old.x * old.x - (old.y * old.y * 3))
				* old.x + real_im.x, ((old.x * old.x * 3) - old.y * old.y)
				* old.y + real_im.y };
		if ((new.x * new.x + new.y * new.y) > 4)
			break;
		pixel_to_buf(pix->buf, x, y, chose_color(i, pix->maxIter, pix->col, pix->color));
	}
}

void		count_mandelbrot(t_pix *pix, int x, int y)
{
	size_t			 i;
	t_vec2			new;
	t_vec2			old;
	t_vec2			real_im;

	i = UINT64_MAX;
	if (pix->fract_num == 0)
	{
		real_im = (t_vec2){ -0.556, 0.53415 };
		new = calc_real_imag((t_vec2) {x, y}, pix->move, pix->rate, pix->zoom);
	}
	else
	{
		real_im = calc_real_imag((t_vec2) {x, y}, pix->move, pix->rate, pix->zoom);
//		new = (t_vec2) { 0, 0 };
//		old = (t_vec2) { 0, 0 };
	}
	while (++i <= pix->maxIter)
	{
		old = (t_vec2){ new.x, new.y };
		new = (t_vec2){ old.x * old.x - new.y * new.y + real_im.x,
						2 * old.x * old.y + real_im.y };
		if ((new.x * new.x + new.y * new.y) > 4)
			break;
			pixel_to_buf(pix->buf, x, y, chose_color(i, pix->maxIter, pix->col, pix->color));
	}
}