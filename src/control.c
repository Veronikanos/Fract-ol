/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:42:38 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/05/22 20:39:37 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		change_fractals(t_pix *pix)
{
	if (pix->fract_num = 0)
	{
		pix->fract_num++;
		init_mandelbrot(pix);
	}
	else if (pix->fract_num = 1)
	{
		pix->fract_num++;
		init_cubic_mandelbrot(pix);
	}
	else
		pix->fract_num = 0;

	//init????
	draw_screen(pix);
}

int				kb_press_key(int key, t_pix *pix)
{
	if (key == ESC)
		exit(0);
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