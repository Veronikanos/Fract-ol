/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:40:15 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/05/27 21:50:24 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

unsigned int	color_breeze(int i, int maxIter, t_color col)
{
	unsigned int c;

	if (i == maxIter)
		return (0);

	col = (t_color) {cos(0.8 * (double) i + 2),
					 sin(0.3 * (double) i + 3) * 128 + 128,
					 sin(0.3 * (double) i + 3) * 128 + 230};
	c = ((col.R << 16) + (col.G << 8) + col.B);
	return (c);
}

//unsigned int	color_breeze(int i, int maxIter, t_color col)
//{
//	unsigned int c;
//
//	if (i == maxIter)
//		return (0);
//
//	col = (t_color) { cos(128 / maxIter + 50),
//					  sin(256 / maxIter) + 50 * 120,
//					cos( (double)i / maxIter) + 320 * 120};
//	c = ((col.R << 16) + (col.G << 8) + col.B);
//	return (c);
//}

unsigned int	get_color_psy(int i, int maxIter)
{
	if (i == maxIter)
		return (0);
	return ((0xFFFFFF / maxIter) * (i + 1000));
}

void			pixel_to_buf(int *buf, int x, int y, int color)
{
//	x += pix->move.x;
//	y += pix->move.y;
	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
		buf[y * WIDTH + x] = color;
}

static void		count_cubic_mandelbrot(t_pix *pix, int x, int y)
{
	size_t i;

	i = UINT64_MAX;
	while (++i <= pix->maxIter)
	{
		pix->old = (t_vec2){ pix->new.x, pix->new.y };
		pix->new = (t_vec2){ (pix->old.x * pix->old.x
					- (pix->old.y * pix->old.y * 3)) * pix->old.x + pix->real_im.x,
					((pix->old.x * pix->old.x * 3)
					- pix->old.y * pix->old.y) * pix->old.y + pix->real_im.y };
		if ((pix->new.x * pix->new.x + pix->new.y * pix->new.y) > 4)
			break;
		pixel_to_buf(pix->buf, x, y, get_color_psy(i, pix->maxIter));
	}
}

static void		count_mandelbrot(t_pix *pix, int x, int y)
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
			pixel_to_buf(pix->buf, x, y, color_breeze(i, pix->maxIter, pix->col));
	}
}

static void		julia_iter(t_pix *pix, int x, int y)
{
	pix->new =
		(t_vec2) { pix->rate * (x - H_WIDTH_S) / (0.5 * pix->zoom * WIDTH ) + pix->move.x,
				(y - H_HEIGHT_S) / (0.5 * pix->zoom * HEIGHT) + pix->move.y };
	count_mandelbrot(pix, x, y);
}

static void		mandelbrot_iter(t_pix *pix, int x, int y)
{
	pix->real_im = (t_vec2) {pix->rate * (x - H_WIDTH_S)
				/ (0.5 * pix->zoom * WIDTH) + pix->move.x,
				(y - H_HEIGHT_S) / (0.5 * pix->zoom * HEIGHT)+ pix->move.y};
	pix->new = (t_vec2) {0, 0};
	pix->old = (t_vec2) {0, 0};
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
				   "MOVE               NONAME");
	mlx_string_put(pix->mlx_ptr, pix->win_ptr, 30, 90, COLOR,
				   "ZOOM               NONAME");
}