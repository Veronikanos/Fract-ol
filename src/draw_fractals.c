/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:40:15 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/05/21 20:57:35 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void			clear_img(t_pix *pix)
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

//unsigned int	get_color(int i, t_pix *pix, int maxIter)
//{
//	double t = (double)i / maxIter;
//	int r = (int)(9 * (1 - t) * t * 255);
//	int g = (int)(15 * (1 - t) * (1 - t) * 255);
//	int b = (int)(8.5 * (1 - t) * (1 - t) * 255);
//	unsigned int c = (r << 16) + (g << 8) + b;
//	return (c);
//}

unsigned int	get_color (int i, int maxIter)
{
	if (i == maxIter)
		return (0xFFFFFF);
	return ((0xFFFFFF / maxIter) * (i + 1000));
}

void			pixel_to_buf(int *buf, t_pix *pix, int x, int y, int color)
{
//	x += pix->move.x;
//	y += pix->move.y;
	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
		buf[y * WIDTH + x] = color;
}

//static void		count_mandelbrot(t_pix *pix, int x, int y, double pr, double pi)
//{
//	//CUBIC MANDELBROT
//	size_t i;
//
//
//	i = UINT64_MAX;
//	while (++i < pix->maxIter)
//	{
//		pix->old = (t_vec2){ pix->new.x, pix->new.y };
//		pix->new = (t_vec2){ (pix->old.x * pix->old.x - (pix->old.y * pix->old.y * 1.7)) * pix->old.x + pr,
//							 ((pix->old.x * pix->old.x * 1.7) * 0.42 - pix->old.y * pix->old.y) * pix->old.y + pi };
//		if ((pix->new.x * pix->new.x + pix->new.y * pix->new.y) > 4)
//			break;
//		pixel_to_buf(pix->buf, pix, x, y, get_color(i, pix->maxIter));
//	}
//}

static void		count_cubic_mandelbrot(t_pix *pix, int x, int y, double pr, double pi)
{
	//CUBIC MANDELBROT
	size_t i;


	i = UINT64_MAX;
	while (++i < pix->maxIter)
	{
		pix->old = (t_vec2){ pix->new.x, pix->new.y };
		pix->new = (t_vec2){ (pix->old.x * pix->old.x - (pix->old.y * pix->old.y * 3)) * pix->old.x + pr,
							 ((pix->old.x * pix->old.x * 3) - pix->old.y * pix->old.y) * pix->old.y + pi };
		if ((pix->new.x * pix->new.x + pix->new.y * pix->new.y) > 4)
			break;
		pixel_to_buf(pix->buf, pix, x, y, get_color(i, pix->maxIter));
	}
}

//static void		count_mandelbrot(t_pix *pix, int x, int y, double pr, double pi)
//{
//	size_t i;
//
//
//	i = UINT64_MAX;
//	while (++i < pix->maxIter)
//	{
//		pix->old = (t_vec2){ pix->new.x, pix->new.y };
//		pix->new.x = pix->old.x * pix->old.x - pix->new.y * pix->new.y + pr;
//		pix->old.x < 0 ? pix->old.x * -1 : pix->old.x * 1;
//		pix->new.y = pix->old.x * pix->old.y * -2 + pi;
//		if ((pix->new.x * pix->new.x + pix->new.y * pix->new.y) > 4)
//			break;
//		pixel_to_buf(pix->buf, pix, x, y, get_color(i, pix->maxIter));
//	}
//}

static void		count_mandelbrot(t_pix *pix, int x, int y, double pr, double pi)
{
	size_t i;


	i = UINT64_MAX;
	while (++i < pix->maxIter)
	{
		pix->old = (t_vec2){ pix->new.x, pix->new.y };
		pix->new = (t_vec2){ pix->old.x * pix->old.x -
							 pix->new.y * pix->new.y + pr,
							 2 * pix->old.x * pix->old.y + pi };
		if ((pix->new.x * pix->new.x + pix->new.y * pix->new.y) > 4)
			break;
		pixel_to_buf(pix->buf, pix, x, y, get_color(i, pix->maxIter));
	}
}

static void		draw_fract(t_pix *pix)
{
	double pr;
	double pi;
	size_t x;
	size_t y;

	y = UINT64_MAX;
	while (++y < HEIGHT)
	{
		x = UINT64_MAX;
		while (++x < WIDTH)
		{
			pr = pix->rate * (x - H_WIDTH_S) / (0.5 * pix->zoom * WIDTH ) + pix->move.x;
			pi =             (y - H_HEIGHT_S) / (0.5 * pix->zoom * HEIGHT) + pix->move.y;
			pix->new = (t_vec2){ 0, 0 };
			pix->old = (t_vec2){ 0, 0 };
			if (pix->fract_num == 1)
				count_mandelbrot(pix, x, y, pr, pi);
			else if (pix->fract_num == 2)
				count_cubic_mandelbrot(pix, x, y, pr, pi);
//			if (pix->fract_num = 0)
//				count_smth();
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