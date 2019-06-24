/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:40:15 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/06/24 21:44:45 by vtlostiu         ###   ########.fr       */
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

static void		iter_julia_mand(t_pix *pix, int x, int y)
{
	if (pix->fract_num == 0)
	{
		pix->new =
			calc_real_imag((t_vec2) {x, y}, pix->move, pix->rate, pix->zoom);
		count_mandelbrot(pix, x, y);
	}
	else
	{
		pix->real_im =
			calc_real_imag((t_vec2){ x, y }, pix->move, pix->rate, pix->zoom);
		pix->new = (t_vec2) { 0, 0 };
		pix->old = (t_vec2) { 0, 0 };
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

static void		draw_part(t_pix *pix, size_t y_from, size_t y_to)
{
	size_t x;
	size_t y;

	y = y_from;
	while (++y < y_to)
	{
		x = UINT64_MAX;
		while (++x < WIDTH)
			iter_julia_mand(pix, x, y);
	}
}

static void		draw_n_parts(t_pix *pix, size_t n_of_sectors)
{
	int i;

	i = 0;
	while( i < n_of_sectors) {
//		pid_t newp;
//
//		newp = fork();
//		if (newp < 0)
//			errors_msg(1);
//		if (newp == 0)
//		{
			size_t shift = (HEIGHT/n_of_sectors) * i;
			draw_part(pix, UINT64_MAX + shift, (HEIGHT/n_of_sectors) + shift);
//		}
		i++;
	}

}


void draw_fork(t_pix *pix, size_t from, size_t to) {
	pid_t	newp;
	newp = fork();
	if (newp < 0)
		errors_msg(5);
	if (newp == 0) {
		write(1, "Drawing....\n", 12);
		draw_part(pix, from, to);
		return;
	}

}


static void		draw_fract(t_pix *pix)
{
	size_t  n_of_sectors;
	int i;
	size_t shift;

	i = 1;
	n_of_sectors = 2;
//	draw_n_parts(pix, 5);

	shift = (HEIGHT/n_of_sectors) * i;
	draw_fork(pix, UINT64_MAX + shift, (HEIGHT/n_of_sectors) + shift);
	while( i < n_of_sectors) {
		shift = (HEIGHT/n_of_sectors) * i;
		draw_fork(pix, UINT64_MAX + shift, (HEIGHT/n_of_sectors) + shift);
		i++;
	}

}

void				draw_screen(t_pix *pix)
{
	mlx_clear_window(pix->mlx_ptr, pix->win_ptr);
		draw_fract(pix);
//	errors_msg(5);
	mlx_put_image_to_window(pix->mlx_ptr, pix->win_ptr, pix->img_ptr, 0, 0);
	clear_img(pix);
	mlx_string_put(pix->mlx_ptr, pix->win_ptr, 30, 30, COLOR,
				   "EXIT               ESC");
	mlx_string_put(pix->mlx_ptr, pix->win_ptr, 30, 50, COLOR,
				   "CHANGE FRACTAL     S");
	mlx_string_put(pix->mlx_ptr, pix->win_ptr, 30, 70, COLOR,
				   "CHANGE COLOR       C");
	mlx_string_put(pix->mlx_ptr, pix->win_ptr, 30, 90, COLOR,
				   "ZOOM               MOUSE SCROLL (UP, DOWN)");
	mlx_string_put(pix->mlx_ptr, pix->win_ptr, 30, 110, COLOR,
				   "MOVE               ARROWS: LEFT, RIGHT");
	mlx_string_put(pix->mlx_ptr, pix->win_ptr, 30, 130, COLOR,
				   "ADD ITERATIONS     I");
	mlx_string_put(pix->mlx_ptr, pix->win_ptr, 30, 150, COLOR,
				   "RESET              R");
}