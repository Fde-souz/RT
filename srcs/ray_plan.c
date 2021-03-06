/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_plan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetit <ppetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 12:31:27 by ppetit            #+#    #+#             */
/*   Updated: 2018/04/27 17:19:12 by fde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_vec	plan_normal_at(t_inter t, t_obj obj, t_vec ori)
{
	t_vec	v;
	double	d;

	(void)t;
	v = normalize_vec(sub_vec(obj.pos, ori));
	d = dot(v, obj.rot);
	if (d < 0.01)
		v = obj.rot;
	else
		v = v_scale(-1, &obj.rot);
	return (v);
}

t_inter	ray_plan(t_env *e, t_vec v, t_vec ori, int nbr)
{
	double	tn;
	double	dv;
	t_vec	dist;
	t_inter t;

	dv = dot(e->obj[nbr].rot, v);
	dist = sub_vec(ori, e->obj[nbr].pos);
	tn = ((-(dot(e->obj[nbr].rot, dist))) / dv);
	t.dist = tn;
	intersection_point(&t, ori, v);
	return (t);
}
