/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:44:37 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/01 19:47:43 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int	color_flame(int i, int maxiter, t_color col)
{
	if (i == maxiter)
		return (0);
	col = (t_color) { sin(0.3 * (double)i + 2.5) * 128 + 128,
					sin(0.3 * (double)i + 3.5) * 128 + 128,
					sin(0.3 * (double)i + 4.5) * 128 + 190 };
	return ((col.R << 16) + (col.G << 8) + col.B);
}

void			count_julia(t_pix *pix, int x, int y)
{
	size_t		i;
	t_vec2		new;
	t_vec2		old;
	t_vec2		real_im;

	real_im = (t_vec2){ pix->real_im.x, pix->real_im.y };
	new = calc_real_imag((t_vec2){ x, y }, pix->move, pix->rate, pix->zoom);
	i = UINT64_MAX;
	while (++i <= pix->maxiter)
	{
		old = (t_vec2){ new.x, new.y };
		new = (t_vec2){ old.x * old.x -
						new.y * new.y + real_im.x,
						2 * old.x * old.y + real_im.y };
		if ((new.x * new.x + new.y * new.y) > 4)
			break ;
		pixel_to_buf(pix->buf, x, y,
				chose_color(i, pix->maxiter, pix->col, pix->color));
	}
}
