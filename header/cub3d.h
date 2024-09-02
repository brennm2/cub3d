#ifndef		CUB3D_H
# define	CUB3D_H

# include "../libs/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	*map_name;
}	t_game;



int		key_handler(int key, t_game *game);
void	free_all(t_game *game);
int		ft_quit_game(t_game *game);

#endif