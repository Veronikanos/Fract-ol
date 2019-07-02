/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fractals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 13:24:34 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/01 19:06:40 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_heart(t_pix *pix)
{
	if (!pix)
		errors_msg(5);
	pix->zoom = 0.25;
	pix->move = (t_vec2){ 0, 0 };
	pix->maxiter = 250;
	pix->color = 0;
	pix->rate = (double)(WIDTH) / HEIGHT;
}

void	init_burning_ship(t_pix *pix)
{
	if (!pix)
		errors_msg(5);
	pix->zoom = 0.25;
	pix->move = (t_vec2){ 0, 0 };
	pix->maxiter = 41;
	pix->color = 1;
	pix->rate = (double)(WIDTH) / HEIGHT;
}

void	init_julia(t_pix *pix)
{
	if (!pix)
		errors_msg(5);
	pix->real_im = (t_vec2){ -0.556, 0.53415 };
	pix->zoom = 0.25;
	pix->move = (t_vec2){ 0, 0 };
	pix->maxiter = 85;
	pix->color = 2;
	pix->rate = (double)(WIDTH) / HEIGHT;
}

void	init_cubic_mandelbrot(t_pix *pix)
{
	if (!pix)
		errors_msg(5);
	pix->zoom = 0.25;
	pix->move = (t_vec2){ 0, 0 };
	pix->maxiter = 174;
	pix->color = 3;
	pix->rate = (double)(WIDTH) / HEIGHT;
}

void	init_mandelbrot(t_pix *pix)
{
	if (!pix)
		errors_msg(5);
	pix->zoom = 0.25;
	pix->move = (t_vec2){ 0, 0 };
	pix->maxiter = 28;
	pix->color = 4;
	pix->rate = (double)(WIDTH) / HEIGHT;
}
