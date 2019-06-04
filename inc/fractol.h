/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:54:23 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/06/04 18:38:51 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

//# include <stdlib.h>
//# include <unistd.h>
# include <stdio.h>
//# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "get_next_line.h"
# include "libft.h"

# define WIDTH			1024
# define HEIGHT			768
# define H_WIDTH		WIDTH / 2.0
# define H_HEIGHT	    HEIGHT / 2.0

# define COLOR			0xFAEFEF
//# define ZOOMZ			1
//# define RAD			2 * M_PI / 180.0
# define NAME			"FRACTOL BY VTLOSTIU"

enum					e_keys
{
	ESC = 53, LEFT_ARROW = 123, RIGHT_ARROW = 124, R = 15,
	I = 34, UP_ARROW = 126, DOWN_ARROW = 125, PLUS = 69, MINUS = 78,
	S = 1, MOUSE_UP = 4, MOUSE_DOWN = 5,
//	SIX = 88, FIVE = 87, THREE = 85,
//	TWO = 84, NINE = 92, EIGHT = 91, P = 35,
	// I = 34, PLUS2 = 24, MINUS2 = 27
};

typedef struct			s_vector2
{
	double	x;
	double	y;
}						t_vec2;

typedef struct			s_mouse
{
	int		x;
	int		y;
}						t_mouse;


typedef struct			s_color
{
	unsigned int		R;
	unsigned int		G;
	unsigned int		B;
}						t_color;

typedef struct			s_pix
{
	double		zoom;
	int 		maxIter;
	double 		rate;
	t_vec2		move;
	t_vec2		new;
	t_vec2		old;
	t_vec2		real_im;

	t_mouse		mouse;


//	t_draw		d_xy;
//	t_draw		length;
//	t_draw		point;
	int 		fract_num;
	t_color		col;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			bits_per_pixel;
	int			*buf;
	int			size_line;
	int			endian;
}						t_pix;
//
//typedef struct			s_lines
//{
//	char				*str;
//	struct s_lines		*next;
//}						t_lines;

int				errors_msg(int err);
int				kb_press_key(int key, t_pix *pix);
int				mouse_julia(int x, int y, t_pix *pix);
int				mouse_zoom(int key, int x, int y, t_pix *pix);
void			draw_screen(t_pix *pix);
void			init_mandelbrot(t_pix *pix);
void			init_cubic_mandelbrot(t_pix *pix);
void			init_julia(t_pix *pix);
void			count_tricorn(t_pix *pix, int x, int y);
void			count_cubic_mandelbrot(t_pix *pix, int x, int y);
void			count_mandelbrot(t_pix *pix, int x, int y);
void			pixel_to_buf(int *buf, int x, int y, int color);
void			count_ship(t_pix *pix, int x, int y);
void			count_heart(t_pix *pix, int x, int y);
void			init_burning_ship(t_pix *pix);
void			init_heart(t_pix *pix);
unsigned int	color_breeze(int i, int maxIter, t_color col);
unsigned int	get_color_psy(int i, int maxIter);
unsigned int	color_flame(int i, int maxIter, t_color col);
unsigned int	color_burning_ship(int i, int maxIter, t_color col);
unsigned int	color_red(int i, int maxIter, t_color col);

#endif
