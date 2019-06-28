/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:54:23 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/06/28 22:47:12 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

//# include <stdlib.h>
//# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
//# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "get_next_line.h"
# include "libft.h"

# define WIDTH		1024
# define HEIGHT		768
# define H_WIDTH	WIDTH / 2.0
# define H_HEIGHT	HEIGHT / 2.0
# define MIN_ZOOM	0.0005
# define MAX_ZOOM	100
# define CENTERING	5.0
# define THREADS	10
# define COLOR		0xFAEFEF
# define COL		0xFF0000
# define NAME		"FRACTOL BY VTLOSTIU"

enum				e_keys
{
	ESC = 53, LEFT_ARROW = 123, RIGHT_ARROW = 124, R = 15, C = 8,
	I = 34, U = 32, UP_ARROW = 126, DOWN_ARROW = 125,
	S = 1, MOUSE_UP = 4, MOUSE_DOWN = 5,
//	SIX = 88, FIVE = 87, THREE = 85,
//	TWO = 84, NINE = 92, EIGHT = 91, P = 35, PLUS = 69, MINUS = 78,
	// I = 34, PLUS2 = 24, MINUS2 = 27
};

typedef struct		s_vector2
{
	double			x;
	double			y;
}					t_vec2;

typedef struct		s_color
{
	unsigned int	R;
	unsigned int	G;
	unsigned int	B;
}					t_color;

typedef struct		s_pix
{
	double			zoom;
	double 			rate;
	t_vec2			move;
//	t_vec2			new;
//	t_vec2			old;
	t_vec2			real_im;
	t_vec2			mouse;
	t_color			col;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				julia_move;
	int				color;
	int 			fract_num;
	int 			maxIter;
	int				bits_per_pixel;
	int				*buf;
	int				size_line;
	int				endian;
}					t_pix;

typedef struct		s_threads
{
	t_pix			*pix;
	size_t			shift;
	size_t			thrd;
}					t_threads;

int					errors_msg(int err);
int					kb_press_key(int key, t_pix *pix);
int					mouse_julia(int x, int y, t_pix *pix);
int					mouse_zoom(int key, int x, int y, t_pix *pix);
void				draw_screen(t_pix *pix);
void				pixel_to_buf(int *buf, int x, int y, int color);
void				count_julia(t_pix *pix, int x, int y);
void				count_tricorn(t_pix *pix, int x, int y);
void				count_cubic_mandelbrot(t_pix *pix, int x, int y);
void				count_mandelbrot(t_pix *pix, int x, int y);
void				count_ship(t_pix *pix, int x, int y);
void				count_heart(t_pix *pix, int x, int y);
void				init_burning_ship(t_pix *pix);
void				init_mandelbrot(t_pix *pix);
void				init_cubic_mandelbrot(t_pix *pix);
void				init_julia(t_pix *pix);
void				init_heart(t_pix *pix);
void				change_reset(t_pix *pix);
void				create_threads(t_pix *pix);
void				choose_fract(t_pix *pix, size_t start, size_t end);
unsigned int		color_yellow(int i, int maxIter, t_color col);
unsigned int		color_breeze(int i, int maxIter, t_color col);
unsigned int		color_psy(int i, int maxIter);
unsigned int		color_flame(int i, int maxIter, t_color col);
unsigned int		color_burning_ship(int i, int maxIter, t_color col);
unsigned int		color_red(int i, int maxIter, t_color col);
unsigned int		chose_color(size_t i, int maxIter, t_color col, int color);
t_vec2				calc_real_imag(t_vec2 coord, t_vec2 move,
						double rate, double zoom);

#endif
