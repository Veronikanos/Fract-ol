/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 21:55:24 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/06/27 21:57:55 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void			*draw_threads(void *thread_data)
{
	size_t shift;
	size_t num;
	t_pix *pix;

	shift = ((t_threads *) thread_data)->shift;
	pix = ((t_threads *) thread_data)->pix;
	num = ((t_threads *) thread_data)->thrd;

	choose_fract(pix, num * shift - 1, ((num + 1) * shift));
	return (NULL);
}

void			create_threads(t_pix *pix)
{
	int				num;
	t_threads		part_arr[THREADS];
	pthread_t		threads_arr[THREADS];

	num = 0;
	while (num < THREADS)
	{
		part_arr[num] = (t_threads){ pix, HEIGHT / THREADS, num};
		pthread_create(&threads_arr[num], NULL, draw_threads, &part_arr[num]);
		++num;
	}
	num = THREADS - 1;
	while (num >= 0)
	{
		pthread_join(threads_arr[num], NULL);
		num--;
	}
}