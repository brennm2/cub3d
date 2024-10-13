#include "../includes/cub3d.h"

void show_fps_debug(void)
{
	static clock_t	old_time = 0;
	clock_t			time;
	clock_t			frametime;
	double			fps;

	//old_time = 0; // Usar static para manter o valor entre chamadas
	time = clock();
	frametime = time - old_time;
	old_time = time; // Atualizar old_time após calcular frametime

	//ft_putstr_fd("\rFPS:", 1);
	if (frametime > 0)
		fps = CLOCKS_PER_SEC / (double)frametime;
	else
		fps = 0.0; // Evitar divisão por zero
	if (fps >= 36)
		printf("\033[0;32mFPS: %.2f\033[0;37m\n", fps);
	else if (fps <= 34)
		printf("\033[0;31mFPS: %.2f\033[0;37m\n", fps);
	else
		printf("FPS: %.2f\n", fps);
}