/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/20 15:57:31 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/11 18:07:15 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

int		main(int ac, char **av)
{
	t_mlx	*mlx;

	srand(getpid());
	if (ac == 2)
	{
		if (!(mlx = mlx_init_all("RTv1")))
			exit(1);
		if (!open_file(mlx, av[1]))
		{
			ft_printf("line: %d\n", mlx->line_cnt + 1);
			ft_printf("a problem occured while parsing: exiting..\n");
			return (0);
		}
		init_camera(mlx);
		render(mlx);
		display_interface(mlx);
		mlx_hook(mlx->win, 2, 1l, &key_func, mlx);
		mlx_mouse_hook(mlx->win, mouse_func, mlx);
		mlx_hook(mlx->win, 6, 0, motion_func, mlx);
		mlx_loop(mlx->mlx);
	}
	else
		usage();
	return (0);
}