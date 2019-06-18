/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:40:15 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/06/11 20:03:55 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "fractol.h"

static void		clear_img(t_pix *pix)
{
	size_t y;
	size_t x;

	y = UINT64_MAX;
	while (++y < HEIGHT)
	{
		x = UINT64_MAX;
		while (++x < WIDTH)
		{
			pix->buf[y * WIDTH + x] = 0x0;
		}
	}
}

void			pixel_to_buf(int *buf, int x, int y, int color)
{
//	x += pix->move.x;
//	y += pix->move.y;
	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
		buf[y * WIDTH + x] = color;
}

static void		julia_iter(t_pix *pix, int x, int y)
{
	pix->new = (t_vec2) {pix->rate
					* (x - H_WIDTH) / (pix->zoom * WIDTH ) + pix->move.x,
					(y - H_HEIGHT) / (pix->zoom * HEIGHT) + pix->move.y };
	count_mandelbrot(pix, x, y);
}

static void		mandelbrot_iter(t_pix *pix, int x, int y)
{
	pix->real_im = (t_vec2) { pix->rate
						* (x - H_WIDTH) / (pix->zoom * WIDTH) + pix->move.x,
						(y - H_HEIGHT) / (pix->zoom * HEIGHT) + pix->move.y };
	pix->new = (t_vec2) { 0, 0 };
	pix->old = (t_vec2) { 0, 0 };
}

static void		draw_fract(t_pix *pix)
{
	size_t x;
	size_t y;

	y = UINT64_MAX;
	while (++y < HEIGHT)
	{
		x = UINT64_MAX;
		while (++x < WIDTH)
		{
			if (pix->fract_num == 0)
				julia_iter(pix, x, y);
			else
			{
				mandelbrot_iter(pix, x, y);
				if (pix->fract_num == 1)
					count_mandelbrot(pix, x, y);
				else if (pix->fract_num == 2)
					count_cubic_mandelbrot(pix, x, y);
				else if (pix->fract_num == 3)
					count_tricorn(pix, x, y);
				else if (pix->fract_num == 4)
					count_ship(pix, x, y);
				else if (pix->fract_num == 5)
					count_heart(pix, x, y);
			}
		}
	}
}

void				draw_screen(t_pix *pix)
{
	mlx_clear_window(pix->mlx_ptr, pix->win_ptr);
		draw_fract(pix);
	mlx_put_image_to_window(pix->mlx_ptr, pix->win_ptr, pix->img_ptr, 0, 0);
	clear_img(pix);
	mlx_string_put(pix->mlx_ptr, pix->win_ptr, 30, 30, COLOR,
				   "EXIT               ESC");
	mlx_string_put(pix->mlx_ptr, pix->win_ptr, 30, 50, COLOR,
				   "CHANGE             S");
	mlx_string_put(pix->mlx_ptr, pix->win_ptr, 30, 70, COLOR,
				   "MOVE               ARROWS: LEFT, RIGHT");
	mlx_string_put(pix->mlx_ptr, pix->win_ptr, 30, 90, COLOR,
				   "ZOOM               NONAME");
	mlx_string_put(pix->mlx_ptr, pix->win_ptr, 30, 110, COLOR,
				   "RESET              R");
}