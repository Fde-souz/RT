/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_add_obj_menu.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 19:23:48 by vgauther          #+#    #+#             */
/*   Updated: 2018/04/23 19:27:30 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void			add_obj_selection_display(t_sdl *s)
{
	SDL_RenderCopy(s->renderer, s->tex[12], NULL, &s->hud1.r_add_obj[0]);
	SDL_RenderCopy(s->renderer, s->tex[13], NULL, &s->hud1.r_add_obj[1]);
	SDL_RenderCopy(s->renderer, s->tex[14], NULL, &s->hud1.r_add_obj[2]);
	SDL_RenderCopy(s->renderer, s->tex[15], NULL, &s->hud1.r_add_obj[3]);
}

static void		add_obj_print_text(t_sdl *s, t_env *e, int nb)
{
	print_text(ft_itoa(e->obj[nb].pos.x), s->font.color[1], s,
	&s->hud1.add_obj_data[0]);
	print_text(ft_itoa(e->obj[nb].pos.y), s->font.color[1], s,
	&s->hud1.add_obj_data[1]);
	print_text(ft_itoa(e->obj[nb].pos.z), s->font.color[1], s,
	&s->hud1.add_obj_data[2]);
	print_text(ft_itoa(e->obj[nb].rot_to_print.x), s->font.color[1], s,
	&s->hud1.add_obj_data[3]);
	print_text(ft_itoa(e->obj[nb].rot_to_print.y), s->font.color[1], s,
	&s->hud1.add_obj_data[4]);
	print_text(ft_itoa(e->obj[nb].rot_to_print.z), s->font.color[1], s,
	&s->hud1.add_obj_data[5]);
}

static void		display_add_obj_menu_bloc(t_sdl *s)
{
	int i;

	i = 0;
	while (i < 6)
	{
		if ((SDL_RenderCopy(s->renderer, s->tex[0], NULL,
			&s->hud1.text_box[i])) < 0)
			ft_sdl_error("Texture error : ", SDL_GetError());
		i++;
	}
}

static void		display_add_obj_menu_data(t_sdl *s)
{
	int i;

	i = 0;
	while (i < 6)
	{
		if ((SDL_RenderCopy(s->renderer, s->hud1.add_obj_data[i].tex, NULL,
			&s->hud1.add_obj_data[i].rect)) < 0)
			ft_sdl_error("Texture error : ", SDL_GetError());
		i++;
	}
}

void			add_obj_menu(t_sdl *s, t_env *e, int nb)
{
	add_obj_print_text(s, e, nb);
	display_add_obj_menu_bloc(s);
	display_add_obj_menu_data(s);
	SDL_RenderCopy(s->renderer, s->tex[s->hud1.ok.i], NULL, &s->hud1.ok.rect);
}