#include <apilib.h>

int HighMain()
{
	int win;
	char winbuf[200 * 70];
	win = api_openwin(winbuf, 200, 70, "About");
	api_putstrwin(win, 10, 30, 0, 19, "Mind Group  Horizon");
	api_putstrwin(win, 10, 50, 0, 15, "ver 1.3.18.0816");
	api_getkey(1);
	api_end();
}
