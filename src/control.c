/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:42:38 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/06/22 22:44:14 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		change_reset(t_pix *pix)
{
	if (pix->fract_num == 0)
		init_julia(pix);
	else if (pix->fract_num == 1)
		init_mandelbrot(pix);
	else if (pix->fract_num == 2)
		init_cubic_mandelbrot(pix);
	else if (pix->fract_num == 3)
		init_mandelbrot(pix);
	else if (pix->fract_num == 4)
		init_burning_ship(pix);
	else if (pix->fract_num == 5)
		init_heart(pix);
	draw_screen(pix);
}

static void		change_color_scheme(t_pix *pix)
{
	pix->color = ++pix->color % 5;
	draw_screen(pix);
}

int				kb_press_key(int key, t_pix *pix) {
	if (key == ESC)
//	{
//		system("leaks -q fractol");
		exit(0);
//	}
	if (key == I)
		pix->maxIter += 5;
	if (key == LEFT_ARROW)
		pix->move.x += 0.05;
	if (key == RIGHT_ARROW)
		pix->move.x -= 0.05;
	if (key == UP_ARROW)
		pix->move.y += 0.05;
	if (key == DOWN_ARROW)
		pix->move.y -= 0.05;
	if (key == PLUS)
		pix->zoom += 0.005;
	if (key == MINUS)
		pix->zoom -= 0.005;
	if (key == S)
	{
		pix->fract_num = ++pix->fract_num % 6;
		change_reset(pix);
	}
	if (key == C)
		change_color_scheme(pix);
	if (key == R)
	{
//		if (pix->fract_num == 0)
//			pix->fract_num = 5;
//		else
//			pix->fract_num--;
		change_reset(pix);
	}
	draw_screen(pix);
	return (0);
}

t_vec2			calc_real_imag(t_vec2 coord, t_vec2 move,
								double rate, double zoom)
{
	return ((t_vec2) { rate * (coord.x - H_WIDTH) / (zoom * WIDTH ) + move.x,
							(coord.y - H_HEIGHT) / (zoom * HEIGHT) + move.y });
}

int				mouse_zoom(int key, int x, int y, t_pix *pix)
{
	pix->mouse =
		calc_real_imag((t_vec2){ x, y }, pix->move, pix->rate, pix->zoom);
	if ((key == MOUSE_UP || key == MOUSE_DOWN) &&
	(pix->zoom >= MIN_ZOOM && pix->zoom <= MAX_ZOOM))
	{
		pix->move.x -= pix->move.x - pix->mouse.x;
		pix->move.y -= pix->move.y - pix->mouse.y;
		if (key == MOUSE_UP)
			pix->zoom *= 1.5;
		else
			pix->zoom *= 0.5;
		pix->mouse =
			calc_real_imag((t_vec2){ x, y }, pix->move, pix->rate, pix->zoom);
		pix->move.x += pix->move.x - pix->mouse.x;
		pix->move.y += pix->move.y - pix->mouse.y;
	}
	draw_screen(pix);
	return (0);
}

int				mouse_julia(int x, int y, t_pix *pix)
{
	if (pix->fract_num == 0)
	{
		pix->real_im.x = 10 * ((x - H_WIDTH) / WIDTH - 0.556) + 1.7;
		pix->real_im.y = 10 * ((y - H_HEIGHT) / HEIGHT + 0.53415) + 1.0;
		draw_screen(pix);
	}
	return (0);
}
