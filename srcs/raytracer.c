/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetit <ppetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 14:34:11 by ppetit            #+#    #+#             */
/*   Updated: 2018/03/28 14:25:54 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void	ft_put_pixel(t_env *e, int x, int y, int color)
{
	e->pixels[(y * SIZE_X + x)] = color;
}

t_inter		shape_redirection(t_env *e, int x, int y, int nbr)
{
	t_inter tmp;

	if (e->obj[nbr].type == 1)
	{
		tmp = ray_sphere(e, x, y, nbr);
	}
	else if (e->obj[nbr].type == 2)
	{
		tmp = ray_cylindre(e, x, y, nbr);
	}
	else//if (e->obj[nbr].type == 3)
	{
		tmp = ray_cone(e, x, y, nbr);
	}
	return (tmp);
}

void	raytracing(t_env *e, t_sdl s)
{
	int			x;
	int			y;
	int			nbr;
	int			token;
	t_inter		pt;
	t_inter		tmp;

	token = 42;
	x = 0;
	while (x != SIZE_X)
	{
		y = 0;
		while (y != SIZE_Y)
		{
			nbr = 0;
			token = 42;
			while (nbr != e->nb)
			{
				tmp = shape_redirection(e, x, y, nbr);
				if (((tmp.dist < pt.dist || pt.dist < 0) && tmp.dist >= 0) || token == 42)
				{
					pt.dist = tmp.dist;
					pt.x = tmp.x;
					pt.y = tmp.y;
					pt.z = tmp.z;
					pt.nb = nbr;
					token = 0;
				}
				nbr++;
			}
			if (pt.dist >= 0)
				ft_put_pixel(e, x, y, lux(e, pt));
			y++;
		}
		x++;
	}
	s.surface->pixels = e->pixels;
	display(&s);
}
