/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 12:53:51 by vgauther          #+#    #+#             */
/*   Updated: 2018/03/27 17:23:33 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_inter		ray_cone(t_env *e, int i, int j, t_cam ca, int nbr)
{
	t_inter		pt;
	t_polynome	p;
	t_vec		d;
	t_vec		v;
	t_vec		x;
	t_point		o;
	double		angle;

	angle = tan((e->obj[nbr].angle / 2) * RAD);
	d = vector_init((i - SIZE_X / 2), (j - SIZE_Y / 2),
	(SIZE_X / 2) / tan(30 * RAD));
	o = init_point(e->obj[nbr].pos.x, e->obj[nbr].pos.y, e->obj[nbr].pos.z);
	x = vector_init(ca.xr - o.x, ca.yr - o.y, ca.zr - o.z);
	v = normalize_vec(e->obj[nbr].rot);
	p.a = dot(d, d) - ((angle * angle + 1) * dot(d, v) * dot(d, v));
	p.b = 2 * (dot(d, x) - ((angle * angle + 1) * dot(d, v) * dot(v, x)));
	p.c = dot(x, x) - ((angle * angle + 1) * dot(x, v) * dot(x, v));
	p.delta = (p.b * p.b) - (4 * p.a * p.c);
	if (p.delta >= 0)
	{
		if (p.delta > 0)
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
			pt.x = ca.xr + d.x * pt.dist;
			pt.y = ca.yr + d.y * pt.dist;
			pt.z = ca.zr + d.z * pt.dist;
		}
	}
	else
		pt.dist = -1;
	return (pt);
}
