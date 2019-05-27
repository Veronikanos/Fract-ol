/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:56:21 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/05/27 21:29:04 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//t_vec2		    alignment(size_t width, size_t height)
//{
//	return ((t_vec2){ H_WIDTH_S / 2.0,
//                      H_HEIGHT_S / 2.0 });
//}

//t_vec2			reset_zoom(void)
//{
//    return ((t_vec2){ 20, 20});
//}
//


t_pix	*init_julia(t_pix *pix)
{
	if (!pix)
		return (NULL);
//	pix->color_max = 0xFFFFFF;
	pix->real_im = (t_vec2){ -0.556, 0.53415 };
	pix->zoom = 0.5;
	pix->move = (t_vec2){ 0, 0 };
	pix->maxIter = 120;
	pix->rate = (double)(WIDTH) / HEIGHT;
}

t_pix	*init_cubic_mandelbrot(t_pix *pix)
{
	if (!pix)
		return (NULL);
	pix->zoom = 0.5;
	pix->move = (t_vec2){ 0, 0 };
	pix->maxIter = 91;
	pix->rate = (double)(WIDTH) / HEIGHT;
}

t_pix	*init_mandelbrot(t_pix *pix)
{
	if (!pix)
		return (NULL);
	pix->zoom = 0.5;
	pix->move = (t_vec2){ 0, 0 };
	pix->maxIter = 28;
	pix->rate = (double)(WIDTH) / HEIGHT;
}

static void		which_one_fract(char **argv, t_pix *pix)
{
	if (ft_strcmp(argv[1], "Julia") == 0)
	{
		pix->fract_num = 0;
		init_julia(pix);
	}
	else if (ft_strcmp(argv[1], "Mandelbrot") == 0)
	{
		pix->fract_num = 1;
		init_mandelbrot(pix);
	}
	else if (ft_strcmp(argv[1], "Cubic_Mandelbrot") == 0)
	{
		pix->fract_num = 2;
		init_cubic_mandelbrot(pix);
	}
	else
		errors_msg(2);
}

static t_pix	*init_win(t_pix *pix)
{
	if (!pix)
		return (NULL);
	pix->mlx_ptr = mlx_init();
	pix->win_ptr = mlx_new_window(pix->mlx_ptr, WIDTH, HEIGHT, NAME);
	pix->img_ptr = mlx_new_image(pix->mlx_ptr, WIDTH, HEIGHT);
	pix->buf = (int *)mlx_get_data_addr(pix->img_ptr, &pix->bits_per_pixel,
			&pix->size_line, &pix->endian);
	return (pix);
}

int				main(int argc, char **argv)
{
	t_pix	*pix;

	if (argc != 2)
		errors_msg(2);
	else
		{
			if (!(pix = (t_pix *)malloc(sizeof(t_pix))))
				errors_msg(4);
			init_win(pix);
			which_one_fract(argv, pix);
			draw_screen(pix);


			mlx_hook(pix->win_ptr, 2, 5, kb_press_key, pix);
//			mlx_mouse_hook(pix->win_ptr, mouse_scroll, pix);
			mlx_hook(pix->win_ptr, 6, 8, mouse_scroll, pix);
			mlx_hook(pix->win_ptr, 17, 1L << 17, errors_msg, NULL);
			mlx_loop(pix->mlx_ptr);
			mlx_destroy_window(pix->mlx_ptr, pix->win_ptr);
        }
	return (0);
}
