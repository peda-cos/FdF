/*
** mlx_init.c for MiniLibX in 
** 
** Made by Charlie Root
** Login   <ol@epitech.net>
** 
** Started on  Mon Jul 31 16:52:42 2000 Charlie Root
** Last update Fri Jan 28 17:05:09 2005 Olivier Crouzet
*/


#include	"mlx_int.h"



void	*mlx_init()
{
	t_xvar	*xvar;
	
	if (!(xvar = malloc(sizeof(*xvar))))
		return ((void*)0);
	if ((xvar->display = XOpenDisplay("")) == 0)
	{
		free(xvar);
		return ((void*)0);
	}
	xvar->screen = DefaultScreen(xvar->display);
	xvar->root = DefaultRootWindow(xvar->display);
	xvar->cmap = DefaultColormap(xvar->display,xvar->screen);
	xvar->depth = DefaultDepth(xvar->display,xvar->screen);
	if (mlx_int_get_visual(xvar)==-1)
	{
		XCloseDisplay(xvar->display);
		free(xvar);
		return ((void*)0);
	}
	xvar->win_list = 0;
	xvar->win_count = 0;
	xvar->loop_hook = 0;
	xvar->loop_param = (void *)0;
	xvar->do_flush = 1;
	xvar->wm_delete_window = XInternAtom (xvar->display, "WM_DELETE_WINDOW", False);
	xvar->wm_protocols = XInternAtom (xvar->display, "WM_PROTOCOLS", False);
	mlx_int_deal_shm(xvar);
	if (xvar->private_cmap)
		xvar->cmap = XCreateColormap(xvar->display,xvar->root,
				 xvar->visual,AllocNone);
	mlx_int_rgb_conversion(xvar);
	xvar->end_loop = 0;
	return (xvar);
}


/*
** pshm_format of -1 :	Not XYBitmap|XYPixmap|ZPixmap
** alpha libX need a check of the DISPLAY env var, or shm is allowed
** in remote Xserver connections.
*/

int		mlx_int_deal_shm(t_xvar *xvar)
{
	int		use_pshm;
	int		shm_dummy;
	char	*dpy;
	char	buff[33];

	xvar->use_xshm = XShmQueryVersion(xvar->display,&shm_dummy,&shm_dummy,&(use_pshm));
	if (xvar->use_xshm && use_pshm)
		xvar->pshm_format = XShmPixmapFormat(xvar->display);
	else
		xvar->pshm_format = -1;
	gethostname(buff,32);
	dpy = getenv(ENV_DISPLAY);
	if (dpy && strlen(dpy) && *dpy!=':' && strncmp(dpy,buff,strlen(buff)) &&
			strncmp(dpy,LOCALHOST,strlen(LOCALHOST)) )
	{
		xvar->pshm_format = -1;
		xvar->use_xshm = 0;
	}
	return (0);
}

/*
** TrueColor Visual is needed to have *_mask correctly set
*/

int		mlx_int_rgb_conversion(t_xvar *xvar)
{
	unsigned long	red_mask;
	unsigned long	green_mask;
	unsigned long	blue_mask;

	red_mask = xvar->visual->red_mask;
	green_mask = xvar->visual->green_mask;
	blue_mask = xvar->visual->blue_mask;
	bzero(xvar->decrgb,sizeof(int)*6);
	while (!(red_mask&1))
		{ red_mask >>= 1; xvar->decrgb[0] ++; }
	while (red_mask&1)
		{ red_mask >>= 1; xvar->decrgb[1] ++; }
	while (!(green_mask&1))
		{ green_mask >>= 1; xvar->decrgb[2] ++; }
	while (green_mask&1)
		{ green_mask >>= 1; xvar->decrgb[3] ++; }
	while (!(blue_mask&1))
		{ blue_mask >>= 1; xvar->decrgb[4] ++; }
	while (blue_mask&1)
		{ blue_mask >>= 1; xvar->decrgb[5] ++; }
	return (0);
}
