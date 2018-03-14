/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 00:55:44 by vgauther          #+#    #+#             */
/*   Updated: 2018/03/14 14:27:09 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"
#include "../libft/includes/libft.h"
#include <stdint.h>
#include <time.h>

void	ft_init(t_sdl *s)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	s->window = SDL_CreateWindow("RT : Ray Tracer", 0, 0, SIZE_X, SIZE_Y,
		SDL_WINDOW_ALLOW_HIGHDPI);
	if (s->window == NULL)
		exit(1);
	if ((s->renderer = SDL_CreateRenderer(s->window, -1, 0)) == NULL)
		ft_error("Renderer error : ", SDL_GetError());
	if ((s->surface = SDL_CreateRGBSurface(0, VIEW_X, VIEW_Y, 32, 0, 0, 0, 0))
	== NULL)
		ft_error("Surface error : ", SDL_GetError());
}

void	display(t_sdl *s)
{
	SDL_Rect dstrect = { 5, 5, VIEW_X, VIEW_Y };
	if ((s->texture = SDL_CreateTextureFromSurface(s->renderer, s->surface))
	== NULL)
		ft_error("Texture error : ", SDL_GetError());
	if (SDL_RenderClear(s->renderer) < 0)
		ft_error("Error clearing renderer : ", SDL_GetError());
	if (SDL_RenderCopy(s->renderer, s->texture, NULL, &dstrect) < 0)
		ft_error("Error copying renderer : ", SDL_GetError());
	SDL_RenderPresent(s->renderer);
}

void	mouv(int key, t_cam *c, t_obj *o, t_sdl *sdl)
{
	if (key == 79)
		c->xr--;
	if (key == 80)
		c->xr++;
	if (key == 81)
		c->yr--;
	if (key == 82)
		c->yr++;
	if (key == 87)
		c->zr++;
	if (key == 86)
		c->zr--;
	raytracing(*o, *sdl, *c);
}

int		main(int ac, char **av)
{
	int running;
	t_sdl s;
	t_obj obj;
	t_cam c;

	c.xr = 0;
	c.yr = 0;
	c.zr = 0;
	if (ac != 2)
		usage();
	running = 1;
	ft_init(&s);
	free(s.surface->pixels);
	if (!(s.pixels = (Uint32*)malloc(sizeof(Uint32) * SIZE_X * SIZE_Y)))
		return (0);
	s.surface->pixels = s.pixels;
	ft_memset(s.pixels, 255, SIZE_X * SIZE_Y * sizeof(Uint32));
	obj = parser(av[1]);
	raytracing(obj, s, c);
	while (running)
	{
		while (SDL_PollEvent(&s.event))
		{
			if ((SDL_QUIT == s.event.type) ||
			(SDL_SCANCODE_ESCAPE == s.event.key.keysym.scancode))
				running = 0;
			else if ((SDL_KEYDOWN == s.event.type))
			{
				mouv(s.event.key.keysym.scancode, &c, &obj, &s);
			}
		}
	}
	SDL_DestroyWindow(s.window);
	SDL_Quit();
	return (0);
}
