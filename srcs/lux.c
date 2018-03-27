/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 14:30:16 by vgauther          #+#    #+#             */
/*   Updated: 2018/03/27 16:20:17 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

double		lux(t_env *e, t_inter pt)
{
	int		i;
	t_vec	vnorm;
	t_vec	vlux;
	t_color color;
	double	angle;

	color = split_color(e->obj[pt.nb].color);
	i = -1;
	angle = 0;
	while (++i < e->nb_spot)
	{
		vnorm = vector_init((e->obj[pt.nb].pos.x - pt.x),
		(e->obj[pt.nb].pos.y - pt.y), (e->obj[pt.nb].pos.z - pt.z));
		vlux = vector_init((e->spot[i].pos.x - pt.x), (e->spot[i].pos.y - pt.y), (e->spot[i].pos.z - pt.z));
		vnorm = normalize_vec(vnorm);
		vlux = normalize_vec(vlux);
		angle += acos(vnorm.x * vlux.x + vnorm.y * vlux.y + vnorm.z * vlux.z) * 0.42;
	}
	color.r = color.r * angle > 255 ? 255 : color.r * angle;
	color.g = color.g * angle > 255 ? 255 : color.g * angle;
	color.b = color.b * angle > 255 ? 255 : color.b * angle;
	return (color.r * 256 * 256 + color.g * 256 + color.b);
}
