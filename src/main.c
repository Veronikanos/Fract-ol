/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:56:21 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/05/21 19:58:52 by vtlostiu         ###   ########.fr       */
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


//int				mouse_scroll(int key, int x, int y, t_pix *pix)
//{
////    x = x + 1;
////    y = y + 1;
////    if (key == MOUSE_UP && map->zoom.x < 142 && map->zoom.y < 142)
////    {
////        map->zoom.x *= 1.1;
////        map->zoom.y *= 1.1;
////        map->zoom.z *= 1.1;
////    }
////    if (key == MOUSE_DOWN && map->zoom.x > 1 && map->zoom.y > 1)
////    {
////        map->zoom.x *= 0.9;
////        map->zoom.y *= 0.9;
////        map->zoom.z *= 0.9;
////    }
////    draw_screen(map);
//    return (0);
//}

static t_pix    *init_mandelbrot(t_pix *pix)
{
	if (!pix)
		return (NULL);
	pix->color_max = 0x000000;
	pix->color_value = 1;
	pix->zoom = 1;
	pix->move = (t_vec2){ -0.65, 0 };
	pix->maxIter = 172;
	pix->rate = (double)(WIDTH) / HEIGHT;
	//	pix->new = (t_vec2){ 0, 0 };
//	pix->old = (t_vec2){ 0, 0 };
//	pix->zoom = reset_zoom();
}

static void		which_one_fract(char **argv, t_pix *pix)
{
	if (ft_strcmp(argv[1], "Julia") == 0)
	{
		pix->fract_num = 0;
//		julia_init(pix);
//		calc_fract(pix);
	}
	else if (ft_strcmp(argv[1], "Mandelbrot") == 0)
	{
		pix->fract_num = 1;
		init_mandelbrot(pix);
	}
	else if (ft_strcmp(argv[1], "Cubic_Mandelbrot") == 0)
	{
		pix->fract_num = 2;
		init_mandelbrot(pix);
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

//			init_frac()

//			read_screen(frac);
//			draw_screen(frac);


			mlx_hook(pix->win_ptr, 2, 5, kb_press_key, pix);
//			mlx_mouse_hook(frac->win_ptr, mouse_scroll, frac);
			mlx_hook(pix->win_ptr, 17, 1L << 17, errors_msg, NULL);
			mlx_loop(pix->mlx_ptr);
			mlx_destroy_window(pix->mlx_ptr, pix->win_ptr);
        }
	return (0);
}
