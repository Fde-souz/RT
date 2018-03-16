/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylindre.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 12:53:51 by vgauther          #+#    #+#             */
/*   Updated: 2018/03/16 17:44:32 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_inter		ray_cylindre(t_env *e, int i, int j, t_cam ca, int nbr)
{
	t_inter		pt;
	t_polynome	p;
	t_vec		v;
	double		delta;
	t_vec		unit;
	t_vec		x;
	t_point		o;

	v = vector_init((i - SIZE_X / 2) - ca.xr, (j - SIZE_Y / 2)- ca.yr, (SIZE_X / 2) / tan(30 * RAD) - ca.zr);
	o = init_point(e->obj[nbr].pos.x, e->obj[nbr].pos.y, e->obj[nbr].pos.z);
	x = vector_init(-ca.xr + o.x, -ca.yr + o.y, -ca.zr + o.z);
	unit = vector_init(10, 0,0);
	p.a = (dot(v, v) - dot(v, unit) * dot(v, unit));
	p.b = 2 * (dot(v, x) - (dot(v, unit) * dot(x, unit)));
	p.c = dot(x, x) - dot(x, unit) * dot(x, unit) - (e->obj[nbr].rayon * e->obj[nbr].rayon);
	delta = pow(p.b, 2) - 4 * p.a * p.c;
	if (delta >= 0)
	{
		if (delta > 0)
		{
			p.x1 = (-p.b + sqrt(p.delta)) / (2 * p.a);
			p.x2 = (-p.b - sqrt(p.delta)) / (2 * p.a);
			pt.dist = p.x1 < p.x2 ? p.x1 : p.x2;
			if (pt.dist < 0)
				pt.dist = p.x1 < 0 ? p.x2 : p.x1;
		}
		else
			p.x1 = -p.b / (2 * p.a);
		if (!(p.x1 < 0 && p.x2 < 0))
		{
			pt.x = ca.xr + v.x * pt.dist;
			pt.y = ca.yr + v.y * pt.dist;
			pt.z = ca.zr + v.z * pt.dist;
		}
	}
	else
		pt.dist = -1;
	return (pt);
}
