/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:42:38 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/06/01 21:59:52 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		change_fractals(t_pix *pix)
{
	pix->fract_num++;
	pix->fract_num = pix->fract_num % 5;
	if (pix->fract_num == 1)
		init_mandelbrot(pix);
	else if (pix->fract_num == 2)
		init_cubic_mandelbrot(pix);
	else if (pix->fract_num == 3)
		init_mandelbrot(pix);
	else if (pix->fract_num == 4)
		init_burning_ship(pix);
	else if (pix->fract_num == 5)
		init_heart(pix);
	if (pix->fract_num == 5)
		init_julia(pix);
	draw_screen(pix);
}

int				kb_press_key(int key, t_pix *pix)
{
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
		pix->zoom += 0.2;
	if (key == MINUS)
		pix->zoom -= 0.2;
	if (key == S)
		change_fractals(pix);
//    if (key == R)
//        reset(map);
//    if (key == SIX || key == FIVE || key == THREE || key == TWO
//        || key == NINE || key == EIGHT || key == I || key == P)
//        kb_press_angle(key, map);
	draw_screen(pix);
	return (0);
}

int				mouse_scroll(int x, int y, t_pix *pix)
{
	if (pix->fract_num == 0)
	{
		pix->real_im.x = (x - H_WIDTH_S) / WIDTH - 0.556;
		pix->real_im.y = (y - H_HEIGHT_S) / HEIGHT + 0.53415;
	}
//	if (key == MOUSE_DOWN)
//	{

//	}
	draw_screen(pix);
	return (0);
}
