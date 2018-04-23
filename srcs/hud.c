/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 13:47:14 by vgauther          #+#    #+#             */
/*   Updated: 2018/04/23 11:44:58 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void	empty_rect(t_rect b, t_env *e, int t, int color)
{
	int i;

	i = b.x;
	while (i != b.x + b.len)
	{
		t == 1 ? ft_put_pixel_hud(e->hud, i, b.y, color) :
		ft_put_pixel_winrend(e->pixels, i, b.y, color);
		t == 1 ? ft_put_pixel_hud(e->hud, i, b.y + b.hei, color) :
		ft_put_pixel_winrend(e->pixels, i, b.y + b.hei, color);
		i++;
	}
	i = b.y;
	while (i != b.y + b.hei)
	{
		t == 1 ? ft_put_pixel_hud(e->hud, b.x, i, color) :
		ft_put_pixel_winrend(e->pixels, b.x, i, color);
		t == 1 ? ft_put_pixel_hud(e->hud, b.x + b.len, i, color) :
		ft_put_pixel_winrend(e->pixels, b.x + b.len, i, color);
		i++;
	}
}

void		recup_cam_to_print(t_sdl *s, t_env *e)
{
	s->hud1.cam.title.rect = init_sdl_rect((SIZE_X / 4 - 10) / 2 -
	((SIZE_X / 6 - (WIN_X / 50) - 10) / 2), SIZE_Y / 3 - 10, SIZE_X / 6 -
	(WIN_X / 50) - 10, 20);
	print_text(ft_strdup("Camera"), s->font.color[1], s, &s->hud1.cam.title);
	s->hud1.cam.pos_x.rect = init_sdl_rect(105, 270, 17, 10);
	print_text(ft_itoa(e->ca.pos.x), s->font.color[1], s, &s->hud1.cam.pos_x);
	s->hud1.cam.pos_y.rect = init_sdl_rect(105, 310, 17, 10);
	print_text(ft_itoa(e->ca.pos.y), s->font.color[1], s, &s->hud1.cam.pos_y);
	s->hud1.cam.pos_z.rect = init_sdl_rect(105, 350, 17, 10);
	print_text(ft_itoa(e->ca.pos.z), s->font.color[1], s, &s->hud1.cam.pos_z);
	s->hud1.cam.rot_x.rect = init_sdl_rect(200, 270, 17, 10);
	print_text(ft_itoa(e->ca.rot.x), s->font.color[1], s, &s->hud1.cam.rot_x);
	s->hud1.cam.rot_y.rect = init_sdl_rect(200, 310, 17, 10);
	print_text(ft_itoa(e->ca.rot.y), s->font.color[1], s, &s->hud1.cam.rot_y);
	s->hud1.cam.rot_z.rect = init_sdl_rect(200, 350, 17, 10);
	print_text(ft_itoa(e->ca.rot.z), s->font.color[1], s, &s->hud1.cam.rot_z);
}

void		create_bouton_cam(t_sdl *s)
{
	int x;
	int y;
	int i;
	int t;

	i = 0;
	x = 70;
	y = 265;
	t = 0;
	while (i != 12)
	{
		s->hud1.bouton[i].i = t;
		s->hud1.bouton[i].rect = init_sdl_rect(x, y, 20, 20);
		i++;
		y += 40;
		if (i == 3 || i == 9)
		{
			t = 1;
			x -= 25;
		}
		t = i == 6 ? 0 : t;
		x = i == 6 ? 165 : x;
		if (i == 3 || i == 9 || i == 6)
			y = 265;
	}
}

void	init_info_messages(t_sdl *s)
{
	s->hud1.mess = malloc(sizeof(char *) * 12);
	s->hud1.mess[0] =
	ft_strdup("Last   Info   :   RT   succesfully   launched.");
	s->hud1.mess[1] =
	ft_strdup("Last  Info  :  Camera  just  mooved  on  x  axis");
	s->hud1.mess[2] =
	ft_strdup("Last  Info  :  Camera  just  mooved  on  y  axis");
	s->hud1.mess[3] =
	ft_strdup("Last  Info  :  Camera  just  mooved  on  z  axis");
	s->hud1.mess[4] =
	ft_strdup("Last  Info  :  Your  work  has  been  saved.");
	s->hud1.mess[5] =
	ft_strdup("Last  Info  :  Sepia filter actived.");
	s->hud1.mess[6] =
	ft_strdup("Last  Info  :  Sepia filter disabled.");
	s->hud1.mess[7] =
	ft_strdup("Last  Info  :  Black and white filter actived.");
	s->hud1.mess[8] =
	ft_strdup("Last  Info  :  Black and whit filter disabled.");
	s->hud1.mess[9] =
	ft_strdup("Last  Info  :  Camera just rotated on x axis.");
	s->hud1.mess[10] =
	ft_strdup("Last  Info  :  Camera just rotated on y axis.");
	s->hud1.mess[11] =
	ft_strdup("Last  Info  :  Camera just rotated on z axis.");
}

void	ornement(SDL_Rect p, int color, int size, t_env *e)
{
	t_vec	p1;
	t_vec	p2;
	int		l;

	l = p.h / 2 + p.y;
	p2.y = l;
	p1.y = l;
	p1.x = p.x - size;
	p2.x = p.x - 10;
	horizontal_trait(p1, p2, color, e);
	p1.x = p.x + p.w + 10;
	p2.x = p.x + p.w + size;
	horizontal_trait(p1, p2, color, e);
}

void	bloc_save(t_env *e, t_sdl *s)
{
	t_vec p1;
	t_vec p2;
	t_rect	r1;

	p1 = init_point_2_coord(SIZE_X / 4 + SIZE_X + 10, 0);
	p2 = init_point_2_coord(SIZE_X / 4 + SIZE_X + 10, SIZE_Y / 8);
	vertical_trait(p1, p2, WHITE, e);
	p1 = init_point_2_coord(SIZE_X / 4 + (SIZE_X / 6) * 5 - 5, 0);
	p2 = init_point_2_coord(SIZE_X / 4 + (SIZE_X / 6) * 5 - 5, SIZE_Y / 8);
	vertical_trait(p1, p2, WHITE, e);
	r1 = init_rect(SIZE_X / 4 + (SIZE_X / 6) * 5 + (SIZE_X / 6 + 10) / 6, SIZE_Y / 17,
		(SIZE_X / 6 + 10) / 3 * 2, SIZE_Y / 50);
	print_rect(r1, e, 1, WHITE);
	print_text(ft_strdup("Save"), s->font.color[4], s, &s->hud1.save);
	s->hud1.save.rect = init_sdl_rect(SIZE_X / 4 + (SIZE_X / 6) * 5 + (SIZE_X / 6 + 10) / 8, SIZE_Y / 80,
	((SIZE_X / 6 + 10) / 4) * 3, 15);
	ornement(s->hud1.save.rect, WHITE, 15, e);
}

void	bloc_credits(t_env *e, t_sdl *s)
{
	t_vec p1;
	t_vec p2;

	print_text(ft_strdup("Credits"), s->font.color[4], s, &s->hud1.credits.title);
	s->hud1.credits.title.rect = init_sdl_rect(SIZE_X / 4 / 2 - 40, SIZE_Y + SIZE_Y / 8 - 5, 50, 20);
	print_text(ft_strdup("ebertin/fde-souz/ppetit/vgauther"), s->font.color[4], s, &s->hud1.credits.names);
	s->hud1.credits.names.rect = init_sdl_rect(7, SIZE_Y + SIZE_Y / 6, 230, 18);
	p1 = init_point_2_coord(0, WIN_Y / 8 * 7);
	p2 = init_point_2_coord(SIZE_X / 4, WIN_Y / 8 * 7);
	horizontal_trait(p1, p2, WHITE, e);
	p1 = init_point_2_coord(SIZE_X / 4 - 10, SIZE_Y);
	p2 = init_point_2_coord(SIZE_X / 4 - 10, WIN_Y);
	vertical_trait(p1, p2, WHITE, e);
	ornement(s->hud1.credits.title.rect, WHITE, 20, e);
}

void	create_bouton_tool_bar(t_sdl *s)
{
	s->hud1.bouton[12].i = 8;
	s->hud1.bouton[12].rect = init_sdl_rect(SIZE_X / 2 + SIZE_X / 4,
		SIZE_Y / 16 - 20, 40, 40);
	s->hud1.bouton[13].i = 6;
	s->hud1.bouton[13].rect = init_sdl_rect(SIZE_X / 2 + SIZE_X / 4 + 60,
		SIZE_Y / 16 - 20, 40, 40);
	s->hud1.bouton[14].i = 4;
	s->hud1.bouton[14].rect = init_sdl_rect(SIZE_X / 4 + 60, SIZE_Y / 16 - 20,
		40, 40);
	s->hud1.bouton[15].i = 10;
	s->hud1.bouton[15].rect = init_sdl_rect(SIZE_X / 4 + 120, SIZE_Y / 16 - 20,
		40, 40);
	s->hud1.bouton[16].i = 1;
	s->hud1.bouton[16].rect = init_sdl_rect(SIZE_X / 4 + 180, SIZE_Y / 16 - 20,
			40, 40);
}

void	bloc_camera(t_env *e, t_sdl *s)
{
	t_rect	r1;

	r1 = init_rect(WIN_X / 100, SIZE_Y / 3, SIZE_X / 4 - (WIN_X / 50) - 10,
	SIZE_Y / 3);
	empty_rect(r1, e, 1, CONTRAST);
	r1 = init_rect(WIN_X / 100 + ((SIZE_X / 4 - (WIN_X / 50) - 10) / 8),
	(SIZE_Y / 3) - 2, ((SIZE_X / 4 - (WIN_X / 50) - 10) / 8) * 6, 4);
	print_rect(r1, e, 1, COLOR_BACK);
	(void)s;
}

void	init_add_obj_text_box(t_sdl *s)
{
	s->hud1.text_box[0] = init_sdl_rect(COL + SIZE_X + COL / 11, WIN_Y / 2,
		COL / 9 * 2, COL / 9);
	s->hud1.text_box[1] = init_sdl_rect(COL + SIZE_X + (COL / 11) * 4,
	WIN_Y / 2, COL / 9 * 2, COL / 9);
	s->hud1.text_box[2] = init_sdl_rect(COL + SIZE_X + (COL / 11) * 7,
	WIN_Y / 2, COL / 9 * 2, COL / 9);
	s->hud1.text_box[3] = init_sdl_rect(COL + SIZE_X + COL / 11, WIN_Y / 3 +
		WIN_Y / 4, COL / 9 * 2, COL / 9);
	s->hud1.text_box[4] = init_sdl_rect(COL + SIZE_X + (COL / 11) * 4,
	WIN_Y / 3 + WIN_Y / 4, COL / 9 * 2, COL / 9);
	s->hud1.text_box[5] = init_sdl_rect(COL + SIZE_X + (COL / 11) * 7,
	WIN_Y / 3 + WIN_Y / 4, COL / 9 * 2, COL / 9);
	s->hud1.add_obj_data[0].rect = s->hud1.text_box[0];
	s->hud1.add_obj_data[1].rect = s->hud1.text_box[1];
	s->hud1.add_obj_data[2].rect = s->hud1.text_box[2];
	s->hud1.add_obj_data[3].rect = s->hud1.text_box[3];
	s->hud1.add_obj_data[4].rect = s->hud1.text_box[4];
	s->hud1.add_obj_data[5].rect = s->hud1.text_box[5];
}

void	init_add_obj_selection_rect(t_sdl *s)
{
	s->hud1.r_add_obj[0] = init_sdl_rect(SIZE_X / 4 + SIZE_X + COL / 9, SIZE_Y
		/ 4, COL / 9 * 3, COL / 9 * 3);
	s->hud1.r_add_obj[1] = init_sdl_rect(SIZE_X / 4 + SIZE_X + (COL / 9 * 5),
	SIZE_Y / 4, COL / 9 * 3, COL / 9 * 3);
	s->hud1.r_add_obj[2] = init_sdl_rect(SIZE_X / 4 + SIZE_X + COL / 9, SIZE_Y
		/ 4 + COL / 9 * 4, COL / 9 * 3, COL / 9 * 3);
	s->hud1.r_add_obj[3] = init_sdl_rect(SIZE_X / 4 + SIZE_X + (COL / 9 * 5),
	SIZE_Y / 4 + COL / 9 * 4, COL / 9 * 3, COL / 9 * 3);
}

void	bloc_work_space(t_env *e, t_sdl *s)
{
	t_vec	p1;
	t_vec 	p2;

	p1 = init_point_2_coord(SIZE_X / 4 + SIZE_X, SIZE_Y / 8);
	p2 = init_point_2_coord(WIN_X, SIZE_Y / 8);
	horizontal_trait(p1, p2, CONTRAST, e);
	s->hud1.workspace_text.rect = init_sdl_rect(COL + SIZE_X, (SIZE_Y - 10) / 16 - 10, COL - 20, 20);
	print_text(ft_strdup("Workspace"), s->font.color[4], s, &s->hud1.workspace_text);
}

void	bloc_logo(t_sdl *s)
{
	SDL_Surface *surf;

	surf = SDL_LoadBMP("./img_srcs/rtl.bmp");
	s->hud1.logo.rect = init_sdl_rect(2, 0, (SIZE_X / 4) - (WIN_X / 100) ,SIZE_Y / 4);
	if ((s->hud1.logo.tex = SDL_CreateTextureFromSurface(s->renderer, surf)) == NULL)
		ft_sdl_error("Texture error : ", SDL_GetError());
	SDL_FreeSurface(surf);
}

void	hud_init(t_sdl *s, t_env *e)
{
	t_rect	r1;
	t_vec	p1;
	t_vec 	p2;

	init_font(s);
	open_texture(s);
	create_bouton_cam(s);
	init_info_messages(s);
	create_bouton_tool_bar(s);
	init_add_obj_text_box(s);
	init_add_obj_selection_rect(s);
	s->hud1.shape_img.rect = init_sdl_rect(SIZE_X / 4 + SIZE_X +
		(SIZE_X / 4 / 8), SIZE_Y / 8 + SIZE_Y / 16, SIZE_X / 5, SIZE_X / 5);
	bloc_logo(s);
	if (!(e->hud = (Uint32*)malloc(sizeof(Uint32) * WIN_X * WIN_Y)))
		ft_error("MALLOC ERROR");
	r1 = init_rect(0, 0, WIN_X, WIN_Y);
	print_rect(r1, e, 1, COLOR_BACK);
	r1 = init_rect(SIZE_X / 4 - 10, SIZE_Y / 8 - 10, SIZE_X + 20, SIZE_Y + 20);
	print_rect(r1, e, 1, CONTRAST);
	bloc_camera(e, s);
	bloc_save(e, s);
	bloc_credits(e, s);
	bloc_multiplier(e, s);
	bloc_work_space(e, s);
	p1 = init_point_2_coord(SIZE_X / 4 - 10, 0);
	p2 = init_point_2_coord(SIZE_X / 4 - 10, SIZE_Y / 8);
	vertical_trait(p1, p2, CONTRAST, e);
	p1 = init_point_2_coord(SIZE_X / 4 + SIZE_X + 10, SIZE_Y);
	p2 = init_point_2_coord(SIZE_X / 4 + SIZE_X + 10, WIN_Y);
	vertical_trait(p1, p2, CONTRAST, e);
	s->hud1.s_back->pixels = e->hud;
	if ((s->hud1.t_back = SDL_CreateTextureFromSurface(s->renderer, s->hud1.s_back)) == NULL)
		ft_sdl_error("Texture error : ", SDL_GetError());
	print_text(ft_strdup(s->hud1.mess[0]), s->font.color[4], s, &s->hud1.info);
	s->hud1.info.rect = init_sdl_rect(SIZE_X / 4 + 28, (WIN_Y / 14) * 13.4 , 500, 25);
	s->hud1.color_selector = init_sdl_rect(0 , 0, 999, 999);
	s->hud1.color_selector_surf = SDL_LoadBMP("./img_srcs/color.bmp");
	s->hud1.ok.rect = init_sdl_rect(SIZE_X / 4 + SIZE_X + COL / 2 - 20, WIN_Y - SIZE_Y / 8, 40, 40);
}
