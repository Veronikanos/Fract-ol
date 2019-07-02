/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:55:38 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/01 19:03:09 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		errors_msg(int err)
{
	if (err == 1)
		ft_putendl("\nUsage: ./fdf input_file.fdf\n\n"
				"Choose one of the available fractals below:\n"
	"1. J or Julia\n"
	"2. M or Mandelbrot\n"
	"3. C or Cubic_mandelbrot\n"
	"4. T or Tricorn\n"
	"5. B or Burning_ship\n"
	"6. H or Heart\n"
	"7. P or Perpendicular_mandelbrot\n"
	"8. S or Ship_cuboid.\n");
	else if (err == 4)
		ft_putendl("Impossible to allocate memory.\n");
	else if (err == 5)
		ft_putendl("Program malfunction. Check file 'Init fractals'.\n");
	exit(0);
	return (0);
}
