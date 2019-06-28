/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:40:15 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/06/28 22:57:14 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stddef.h>
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

void		choose_fract(t_pix *pix, size_t start, size_t end)
{
	size_t x;
	size_t y;

	y = start;
	while (++y < end)
	{
		x = UINT64_MAX;
		while (++x < WIDTH)
		{
			if (pix->fract_num == 0)
				count_julia(pix, x, y);
			else  if (pix->fract_num == 1)
				count_mandelbrot(pix, x, y);
			else if (pix->fract_num == 2 || pix->fract_num == 7)
				count_cubic_mandelbrot(pix, x, y);
			else if (pix->fract_num == 3)
				count_tricorn(pix, x, y);
			else if (pix->fract_num == 4)
				count_ship(pix, x, y);
			else if (pix->fract_num == 5 || pix->fract_num == 6)
				count_heart(pix, x, y);
		}
	}
}

static char 				*name_fractal(int num)
{
	if (num == 0)
		return ("Julia");
	else if (num == 1)
		return ("Mandelbrot");
	else if (num == 2)
		return ("Cubic_mandelbrot");
	else if (num == 3)
		return ("Tricorn");
	else if (num == 4)
		return ("Burning_ship");
	else if (num == 5)
		return ("Heart");
	else if (num == 6)
		return ("Perpendicular_mandelbrot");
	else if (num == 7)
		return ("Ship_cuboid");
	return (0);
}

void				draw_screen(t_pix *pix)
{
	char *iter;
	char *name;

	name = name_fractal(pix->fract_num);
	iter = ft_itoa(pix->maxIter);
	mlx_clear_window(pix->mlx_ptr, pix->win_ptr);
	create_threads(pix);
	mlx_put_image_to_window(pix->mlx_ptr, pix->win_ptr, pix->img_ptr, 0, 0);
	clear_img(pix);
	mlx_string_put(pix->mlx_ptr, pix->win_ptr, 30, 70, COLOR,
			"Change fractal:   <S>      Reset:  <R>");
	mlx_string_put(pix->mlx_ptr, pix->win_ptr, 30, 90, COLOR,
			"Change color:     <C>      Exit:   <ESC>");
	mlx_string_put(pix->mlx_ptr, pix->win_ptr, 30, 30, COLOR,
			"Add iterations:   <I>      Move:   ARROWS (LEFT, RIGHT)");
	mlx_string_put(pix->mlx_ptr, pix->win_ptr, 30, 50, COLOR,
			"Decrease iter:    <U>      Zoom:   MOUSE SCROLL (UP, DOWN)");
	mlx_string_put(pix->mlx_ptr, pix->win_ptr, 650, 70, COLOR, "Iterations:");
	mlx_string_put(pix->mlx_ptr, pix->win_ptr, 820, 70, COL, iter);
	mlx_string_put(pix->mlx_ptr, pix->win_ptr, 650, 50, COLOR, name);
	free(iter);
}