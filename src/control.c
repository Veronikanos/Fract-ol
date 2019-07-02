/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:42:38 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/01 19:41:26 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			change_reset(t_pix *pix)
{
	if (pix->fract_num == 0)
		init_julia(pix);
	else if (pix->fract_num == 1)
		init_mandelbrot(pix);
	else if (pix->fract_num == 2 || pix->fract_num == 7)
		init_cubic_mandelbrot(pix);
	else if (pix->fract_num == 3)
		init_mandelbrot(pix);
	else if (pix->fract_num == 4)
		init_burning_ship(pix);
	else if (pix->fract_num == 5 || pix->fract_num == 6)
		init_heart(pix);
	draw_screen(pix);
}

int				kb_press_key(int key, t_pix *pix)
{
	if (key == ESC)
		exit(0);
	if (key == I && pix->maxiter + 3 <= 1000)
		pix->maxiter += 3;
	if (key == U && pix->maxiter > 3)
		pix->maxiter -= 3;
	if (key == LEFT_ARROW)
		pix->move.x += 0.05;
	if (key == RIGHT_ARROW)
		pix->move.x -= 0.05;
	if (key == UP_ARROW)
		pix->move.y += 0.05;
	if (key == DOWN_ARROW)
		pix->move.y -= 0.05;
	if (key == S)
	{
		pix->fract_num = ++pix->fract_num % 8;
		change_reset(pix);
	}
	if (key == C)
		pix->color = ++pix->color % 6;
	if (key == R)
		change_reset(pix);
	draw_screen(pix);
	return (0);
}

t_vec2			calc_real_imag(t_vec2 coord, t_vec2 move,
								double rate, double zoom)
{
	return ((t_vec2){ rate * (coord.x - H_WIDTH) / (zoom * WIDTH) + move.x,
							(coord.y - H_HEIGHT) / (zoom * HEIGHT) + move.y });
}

int				mouse_zoom(int key, int x, int y, t_pix *pix)
{
	pix->mouse =
			calc_real_imag((t_vec2) { x, y }, pix->move, pix->rate, pix->zoom);
	pix->move.x -= pix->move.x - pix->mouse.x;
	pix->move.y -= pix->move.y - pix->mouse.y;
	if (key == MOUSE_UP && pix->zoom <= MAX_ZOOM)
		pix->zoom *= 1.5;
	else if (key == MOUSE_DOWN && pix->zoom >= MIN_ZOOM)
		pix->zoom *= 0.5;
	pix->mouse =
			calc_real_imag((t_vec2) { x, y }, pix->move, pix->rate, pix->zoom);
	pix->move.x += pix->move.x - pix->mouse.x;
	pix->move.y += pix->move.y - pix->mouse.y;
	draw_screen(pix);
	return (0);
}

int				mouse_julia(int x, int y, t_pix *pix)
{
	pix->julia_move = 0;
	if (pix->fract_num == 0 && pix->zoom == 0.25)
	{
		pix->julia_move = 1;
		pix->real_im.x = 10 * ((x - H_WIDTH) / WIDTH - 0.556) + CENTERING;
		pix->real_im.y = 10 * ((y - H_HEIGHT) / HEIGHT + 0.53415) - CENTERING;
		draw_screen(pix);
	}
	return (0);
}
