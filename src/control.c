/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:42:38 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/06/04 22:00:00 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		change_reset(t_pix *pix)
{
	pix->fract_num++;
	pix->fract_num = pix->fract_num % 6;
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
		pix->zoom += 0.05;
	if (key == MINUS)
		pix->zoom -= 0.05;
	if (key == S)
		change_reset(pix);
	if (key == R)
	{
		if (pix->fract_num == 0)
			pix->fract_num = 5;
		else
			pix->fract_num--;
		change_reset(pix);
	}
	draw_screen(pix);
	return (0);
}

//int 		mouse(int key, int x, int y, t_pix *pix)
//{
//	if (key == 4 || key == 5)
//		mouse_zoom(key, x, y, pix);
//}


int				mouse_zoom(int key, int x, int y, t_pix *pix)
{
	if (key == MOUSE_UP)
	{
		pix->zoom += 0.05;
	}
	if (key == MOUSE_DOWN)
	{
		pix->zoom -= 0.05;
	}
	draw_screen(pix);
	return (0);
}

int				mouse_julia(int x, int y, t_pix *pix)
{
	if (pix->fract_num == 0)
	{
		pix->real_im.x = (x - H_WIDTH) / WIDTH - 0.556;
		pix->real_im.y = (y - H_HEIGHT) / HEIGHT + 0.53415;
		draw_screen(pix);
	}
	return (0);
}
