/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:56:21 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/05/19 20:04:57 by vtlostiu         ###   ########.fr       */
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
static void			clear_img(t_pix *pix)
{
	size_t y;
	size_t x;

	y = UINT64_MAX;
	while (++y < HEIGHT)
	{
		 x = UINT64_MAX;
		while (++x < WIDTH)
		{
			pix->buf[y * WIDTH + x] = 0x0;
		}
	}
}




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



//void			psychedelic(t_pix *pix)
//{
//	pix->color_max += 10000;
//	if (pix->color_max >= 0xffffff)
//		pix->color_max = 0x000000;
//	pix->color_value += 1;
//}

unsigned int	get_color (int i, int maxIter)
{
		if (i == maxIter)
			return (0xFFFFFF);
//	double t = (double)i / maxIter;
//	int r = (int)(9 * (1 - t) * t * 255);
//	int g = (int)(15 * (1 - t) * (1 - t) * 255);
//	int b = (int)(8.5 * (1 - t) * (1 - t) * 255);
//	unsigned int c = (r << 16) + (g << 8) + b;
//	return (c);
	return ((0xFFFFFF / maxIter) * (i+1000));
}

//unsigned int	get_color(int i, t_pix *pix, int maxIter)
//{
//	unsigned int	c;
//	unsigned char	r;
//	unsigned char	g;
//	unsigned char	b;
//
//	if (i == maxIter)
//		return (0xFFFFFF);
//	r = (i * 5) * pix->color_value;
//	g = (255 - (i * 10)) * pix->color_value;
//	b = (255 - (i * 2)) * pix->color_value;
//	c = (r << 16) + (g << 8) + b;
//	return (c);
//}

void				pixel_to_buf(int *buf, t_pix *pix, int x, int y, int color)
{
//	x += pix->move.x;
//	y += pix->move.y;
	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
		buf[y * WIDTH + x] = color;
}

static void     draw_fract(t_pix *pix)
{
	double pr;
	double pi;
	size_t x;
	size_t y;
	size_t i;

//	maxIter = 30;
	y = UINT64_MAX;
	while (++y < HEIGHT)
	{
		x = UINT64_MAX;
		while (++x < WIDTH)
		{
			pr = pix->rate * (x - H_WIDTH_S) / (0.5 * pix->zoom * WIDTH ) + pix->move.x;
			pi =             (y - H_HEIGHT_S) / (0.5 * pix->zoom * HEIGHT) + pix->move.y;
				pix->new = (t_vec2){ 0, 0 };
				pix->old = (t_vec2){ 0, 0 };
			i = UINT64_MAX;
			while (++i < pix->maxIter)
			{
				pix->old = (t_vec2){ pix->new.x, pix->new.y };
				pix->new = (t_vec2){ pix->old.x * pix->old.x -
									pix->new.y * pix->new.y + pr,
								2 * pix->old.x * pix->old.y + pi };
				if ((pix->new.x * pix->new.x + pix->new.y * pix->new.y) > 4)
					break;
				pixel_to_buf(pix->buf, pix, x, y, get_color(i, pix->maxIter));
			}
		}
    }
//    draw_screen(pix);
}


void				draw_screen(t_pix *pix)
{
	mlx_clear_window(pix->mlx_ptr, pix->win_ptr);
	draw_fract(pix);
	mlx_put_image_to_window(pix->mlx_ptr, pix->win_ptr, pix->img_ptr, 0, 0);
	clear_img(pix);
	mlx_string_put(pix->mlx_ptr, pix->win_ptr, 30, 30, COLOR,
				   "EXIT               ESC");
}

int				kb_press_key(int key, t_pix *pix)
{
	if (key == ESC)
		exit(0);
	if (key == I)
		pix->maxIter += 10;
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
//    if (key == R)
//        reset(map);
//    if (key == SIX || key == FIVE || key == THREE || key == TWO
//        || key == NINE || key == EIGHT || key == I || key == P)
//        kb_press_angle(key, map);
	draw_screen(pix);
	return (0);
}

static int		which_one_fract(char **argv, t_pix *pix)
{
	if (ft_strcmp(argv[1], "Julia") == 0)
	{
		pix->fract_num = 0;
//		julia_init(pix);
//		calc_fract(pix);
		return (0);
	}
	else if (ft_strcmp(argv[1], "Mandelbrot") == 0)
	{
		pix->fract_num = 1;
		return (1);
		//read_screen(pix);
	}
	else
		errors_msg(2);
}

static t_pix    *init_win(t_pix *pix)
{
	if (!pix)
		return (NULL);
	pix->mlx_ptr = mlx_init();
	pix->win_ptr = mlx_new_window(pix->mlx_ptr, WIDTH, HEIGHT, NAME);
	pix->img_ptr = mlx_new_image(pix->mlx_ptr, WIDTH, HEIGHT);
	pix->buf = (int *)mlx_get_data_addr(pix->img_ptr, &pix->bits_per_pixel,
			&pix->size_line, &pix->endian);
	pix->color_max = 0x000000;
	pix->color_value = 1;
	pix->zoom = 1;
	pix->move = (t_vec2){ 0, 0 };
	pix->maxIter = 172;
	pix->rate = (double)(WIDTH) / HEIGHT;
//	pix->new = (t_vec2){ 0, 0 };
//	pix->old = (t_vec2){ 0, 0 };
//	pix->zoom = reset_zoom();

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
			if (which_one_fract(argv, pix))
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
