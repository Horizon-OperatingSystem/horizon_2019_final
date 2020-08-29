#include <stdio.h> 
#include <apilib.h>
#include <string.h>

int win;
char *buf;

void ShineString (char *st)
{
	api_boxfilwin(win, 28, 27, 115, 41, 7);
	api_putstrwin(win, 28, 27, 0, 14, st);
}

int HighMain()
{
	api_initmalloc();
	buf = api_malloc(200 * 50);
	win = api_openwin(buf, 200, 50, "Test");

	ShineString("Hello OS World");

	for (;;)
		if (api_getkey(1) != 128)
		{
			break;
		}
	api_end();
}
