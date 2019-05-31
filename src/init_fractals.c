/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fractals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 13:24:34 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/05/31 21:40:28 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_heart(t_pix *pix)
{
	if (!pix)
		errors_msg(5);
	pix->zoom = 0.5;
	pix->move = (t_vec2){ 0, 0 };
	pix->maxIter = 250;
	pix->rate = (double)(WIDTH) / HEIGHT;
}
void	init_burning_ship(t_pix *pix)
{
	if (!pix)
		errors_msg(5);
	pix->zoom = 0.5;
	pix->move = (t_vec2){ 0, 0 };
	pix->maxIter = 471;
	pix->rate = (double)(WIDTH) / HEIGHT;
}

void	init_julia(t_pix *pix)
{
	if (!pix)
		errors_msg(5);
	pix->real_im = (t_vec2){ -0.556, 0.53415 };
	pix->zoom = 0.5;
	pix->move = (t_vec2){ 0, 0 };
	pix->maxIter = 50;
	pix->rate = (double)(WIDTH) / HEIGHT;
}

void	init_cubic_mandelbrot(t_pix *pix)
{
	if (!pix)
		errors_msg(5);
	pix->zoom = 0.5;
	pix->move = (t_vec2){ 0, 0 };
	pix->maxIter = 174;
	pix->rate = (double)(WIDTH) / HEIGHT;
}

void	init_mandelbrot(t_pix *pix)
{
	if (!pix)
		errors_msg(5);
	pix->zoom = 0.5;
	pix->move = (t_vec2){ 0, 0 };
	pix->maxIter = 28;
	pix->rate = (double)(WIDTH) / HEIGHT;
}
