#include "boot.h"
#include<stdio.h>

void init_palette(void)
{
    static unsigned char table_rgb[16 * 3] =
    {
        0x00, 0x00, 0x00,	/*  0:�� */
        0xff, 0x00, 0x00,	/*  1:���� */
        0x00, 0xff, 0x00,	/*  2:���� */
        0xff, 0xff, 0x00,	/*  3:���� */
        0x00, 0x00, 0xff,	/*  4:���� */
        0xff, 0x00, 0xff,	/*  5:���� */
        0x00, 0xff, 0xff,	/*  6:ǳ���� */
        0xff, 0xff, 0xff,	/*  7:�� */
        0xc6, 0xc6, 0xc6,	/*  8:���� */
        0x84, 0x00, 0x00,	/*  9:���� */
        0x00, 0x84, 0x00,	/* 10:���� */
        0x84, 0x84, 0x00,	/* 11:���� */
        0x00, 0x00, 0x84,	/* 12:���� */
        0x84, 0x00, 0x84,	/* 13:���� */
        0x00, 0x84, 0x84,	/* 14:ǳ���� */
        0x84, 0x84, 0x84	/* 15:���� */
    };
    unsigned char table2[216 * 3];
    int r, g, b;
    set_palette(0, 15, table_rgb);

    for(b = 0; b < 6; b++)
    {
        for(g = 0; g < 6; g++)
        {
            for(r = 0; r < 6; r++)
            {
                table2[(r + g * 6 + b * 36) * 3 + 0] = r * 51;
                table2[(r + g * 6 + b * 36) * 3 + 1] = g * 51;
                table2[(r + g * 6 + b * 36) * 3 + 2] = b * 51;
            }
        }
    }

    set_palette(16, 231, table2);
    return;
}

void set_palette(int start, int end, unsigned char *rgb)
{
    int i, eflags;
    eflags = io_load_eflags();
    io_cli();
    io_out8(0x03c8, start);

    for(i = start; i <= end; i++)
    {
        io_out8(0x03c9, rgb[0] / 4);
        io_out8(0x03c9, rgb[1] / 4);
        io_out8(0x03c9, rgb[2] / 4);
        rgb += 3;
    }

    io_store_eflags(eflags);
    return;
}

void boxfill8(unsigned char *vram, int xsize, int c, int x0, int y0, int x1, int y1)
{
    int x, y;

    for(y = y0; y <= y1; y++)
    {
        for(x = x0; x <= x1; x++)
			vram[y * xsize + x] = c;
    }

    return;
}

void boxfill8_tp75(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1)
{
    int x, y;

    for(y = y0; y <= y1; y++)
    {
        for(x = x0; x <= x1; x++)
            if (!(x%2 && y%2)) vram[y*xsize+x] = c;
			vram[y * xsize + x] += 2;
    }

    return;
}

void boxfill8_tp50(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1)
{
    int x, y;

    for(y = y0; y <= y1; y++)
    {
        for(x = x0; x <= x1; x++)
            if (!(x%2 && y%2)) vram[y*xsize+x] = c;
			else vram[y*xsize+x] = 255;
			vram[y * xsize + x] += 1;
    }

    return;
}

void put_dot(char *vram, int xsize, unsigned char c, int x, int y)
{
	vram[y * xsize + x] = c;
	return;
}

void putfont8(char *vram, int xsize, int x, int y, char c, char *font)
{
    int i;
    char *p, d /* data */;

    for(i = 0; i < 16; i++)
    {
        p = vram + (y + i) * xsize + x;
        d = font[i];

        if((d & 0x80) != 0) p[0] = c;
        if((d & 0x40) != 0) p[1] = c;
        if((d & 0x20) != 0) p[2] = c;
        if((d & 0x10) != 0) p[3] = c;
        if((d & 0x08) != 0) p[4] = c;
        if((d & 0x04) != 0) p[5] = c;
        if((d & 0x02) != 0) p[6] = c;
        if((d & 0x01) != 0) p[7] = c;
    }

    return;
}

void init_mouse_cursor8(char *mouse)
{
    static char cursor[16][16] =
    {
		"*...............",
		"*O*.............",
		"*OO*............",
		"*OOO*...........",
		"*OOOO*..........",
		"*OOOOO*.........",
		"*OOOOOO*........",
		"*OOOOOOO*.......",
		"*OOOOOOOO*......",
		"*OOOOOOOOO*.....",
		"*OOOOOOOOOO*....",
		"*OOOOOOOOOOO*...",
		"*OOOOOOOOO****..",
		"*OOOOO***.......",
		"*OO***..........",
		"***............."
    };
    int x, y;

    for(y = 0; y < 16; y++)
    {
        for(x = 0; x < 16; x++)
        {
            if(cursor[y][x] == '*')
            {
                mouse[y * 16 + x] = COL8_000000;
            }

            if(cursor[y][x] == 'O')
            {
                mouse[y * 16 + x] = COL8_FFFFFF;
            }

            if(cursor[y][x] == '.')
            {
                mouse[y * 16 + x] = 255;
            }
        }
    }

    return;
}

void putblock8_8(char *vram, int vxsize, int pxsize,
                 int pysize, int px0, int py0, char *buf, int bxsize)
{
    int x, y;

    for(y = 0; y < pysize; y++)
    {
        for(x = 0; x < pxsize; x++)
        {
            vram[(py0 + y) * vxsize + (px0 + x)] = buf[y * bxsize + x];
        }
    }

    return;
}

/* jpeg.c */
int info_JPEG(struct DLL_STRPICENV *env, int *info, int size, char *fp);
int decode0_JPEG(struct DLL_STRPICENV *env, int size, char *fp, int b_type, char *buf, int skip);

struct DLL_STRPICENV
{	/* 64KB */
	int work[64 * 1024 / 4];
};

struct RGB
{
	unsigned char b, g, r, t;
};


void init_screen8(struct MEMMAN *memman,char *vram,int xsize, int ysize)
{
    static char logo[13][44] = {
		"************......................**********",
		".**************..................**********.",
		".....************...............**********..",
		"........***********...........*********.....",
		"............********.......***********......",
		".............*********..*********...........",
		"...............**************...............",
		"...........*********..*********.............",
		".......***********......*********...........",
		"....**********...........***********........",
		"..**********..............*************.....",
		".**********.................***************.",
		"**********.....................*************"
	};
	struct DLL_STRPICENV *env;
	char *filebuf;
	char s[32], *p;
	int i, j, info[8],x,y;
	struct RGB *picbuf, *q;

	int *fat;
	fat = (int *) memman_alloc_4k(memman, 4 * 2880);
	file_readfat(fat, (unsigned char *) (ADR_DISKIMG + 0x000200));

	picbuf=(struct RGB *) memman_alloc_4k(memman, 1024 * 768 * 4);
	env=(struct DLL_STRPICENV *) memman_alloc_4k(memman, 64 * 1024);

	struct FILEINFO *finfo;

	filebuf = (unsigned char *) memman_alloc_4k(memman, 1024 * 768);
	finfo = file_search("bg2.jpg", (struct FILEINFO *) (ADR_DISKIMG + 0x002600), 224);
	if (finfo==0)
	{
		memman_free_4k(memman, (int *)picbuf, 1024*768*4);
		memman_free_4k(memman, (int *)env, 64*1024);
		memman_free_4k(memman, (int *)filebuf, 1024*768);
		int x , y , x1 , y1;

		for (y = 0; y < 128; y++)
			for (x = 0; x < 128; x++)
				for (y1 = y * 6; y1 < (y + 1) * 6; y1++)
					for (x1 = x * 8; x1 < (x + 1) * 8; x1++)
						vram[x1 + y1 * xsize] = rgb2pal(0, x * 2, y * 2, x, y);
		return;
	}
	file_loadfile(finfo->clustno, finfo->size, filebuf, fat, (char *) (ADR_DISKIMG + 0x003e00));

	info_JPEG(env, info, finfo->size, filebuf);

	i = decode0_JPEG(env, finfo->size, filebuf, 4, (char *) picbuf, 0);

	for (i = 0; i < info[3]; i++)
	{
		p = vram + i * xsize;
		q = picbuf + i * info[2];
		for (j = 0; j < info[2]; j++)
		{
			p[j] = rgb2pal(q[j].r, q[j].g, q[j].b, j, i);
		}
	}

	memman_free_4k(memman, (int *)picbuf, 1024*768*4);
	memman_free_4k(memman, (int *)env, 64*1024);
	memman_free_4k(memman, (int *)filebuf, 1024*768);

	boxfill8(vram, xsize, COL8_C6C6C6,           2, ysize - 26, xsize -   3, ysize -  3);
	boxfill8(vram, xsize, COL8_848484, xsize - 154, ysize - 24, xsize -   5, ysize - 24);
	boxfill8(vram, xsize, COL8_848484, xsize - 154, ysize - 23, xsize - 154, ysize -  4);
	boxfill8(vram, xsize, COL8_FFFFFF, xsize - 154, ysize -  4, xsize -   5, ysize -  4);
	boxfill8(vram, xsize, COL8_FFFFFF, xsize -   4, ysize - 24, xsize -   4, ysize -  3);
	boxfill8(vram, xsize, COL8_FFFFFF,           5, ysize - 24,          61, ysize - 24);
	boxfill8(vram, xsize, COL8_FFFFFF,           4, ysize - 24,           4, ysize -  4);
	boxfill8(vram, xsize, COL8_848484,           5, ysize -  4,          61, ysize -  4);
	boxfill8(vram, xsize, COL8_848484,          61, ysize - 23,          61, ysize -  5);
	boxfill8(vram, xsize, COL8_000000,           5, ysize -  3,          61, ysize -  3);
	boxfill8(vram, xsize, COL8_000000,          62, ysize - 24,          62, ysize -  3);
    for(y = 0; y < 13; y++)
    {
        for(x = 0; x < 44; x++)
        {
            if(logo[y][x] == '*')
            {
				vram[(ysize - 20 + y) * xsize + (9 + x)] = COL8_848484;
			}
        }
    }
	return;
}

unsigned char rgb2pal(int r, int g, int b, int x, int y)
{
	static int table[4] = { 3, 1, 0, 2 };
	int i;
	x &= 1;
	y &= 1;
	i = table[x + y * 2];
	r = (r * 21) / 256;
	g = (g * 21) / 256;
	b = (b * 21) / 256;
	r = (r + i) / 4;
	g = (g + i) / 4;
	b = (b + i) / 4;
	return 16 + r + g * 6 + b * 36;
}

void putfont32(char *vram, int xsize, int x, int y, char c, char *font1, char *font2)
{
	int i,k,j,f;
	char *p, d ;
	j = 0;
	p = vram + (y + j) * xsize + x;
	j ++;
	//�ϰ벿��
	for (i = 0; i < 16; i ++)
	{
		for (k = 0; k < 8; k ++)
		{
			if (font1[i] & (0x80 >> k))
			{
				p[k + (i % 2) * 8] = c;
			}
		}
		for (k = 0; k < 8 / 2; k ++)
		{
			f = p[k + (i % 2) * 8];
			p[k + (i % 2) * 8] = p[8 - 1 - k + (i % 2) * 8];
			p[8 - 1 - k + (i % 2) * 8] = f;
		}
		if (i % 2)
		{
			p = vram + (y + j) * xsize + x;
			j ++;
		}
	}
	//�°벿��
	for (i = 0; i < 16; i ++)
	{
		for (k = 0; k < 8; k ++)
		{
			if (font2[i] & (0x80 >> k))
			{
				p[k + (i % 2) * 8] = c;
			}
		}
		for (k = 0; k < 8 / 2; k ++)
		{
			f = p[k + (i % 2) * 8];
			p[k + (i % 2) * 8] = p[8 - 1 - k + (i % 2) * 8];
			p[8 - 1 - k + (i % 2) * 8] = f;
		}
		if (i % 2)
		{
			p = vram + (y + j) * xsize + x;
			j ++;
		}
	}
	return;
}

void putfonts8_asc(char *vram, int xsize, int x, int y, char c, unsigned char *s)
{
	extern char fonts[4096];
	struct TASK *task = task_now();
	char *chinese = (char *) *((int *) 0x0fe8), *font;
	int k, t;

	for (; *s != 0x00; s++)
	{
		if (task->langbyte1 == 0)
		{
			if (0xa1 <= *s && *s <= 0xfe)
			{
				task->langbyte1 = *s;
			} else
			{
				putfont8(vram, xsize, x, y, c, fonts + *s * 16);
			}
		} else
		{
			k = task->langbyte1 - 0xa1;
			t = *s - 0xa1;
			task->langbyte1 = 0;
			font = chinese + (k * 94 + t) * 32;
			putfont32(vram, xsize, x-8, y, c, font, font + 16);
		}
		x += 8;
	}
	return;
}

void open_menu(char *buf_back, char *buf_menu,int xsize, int ysize)
{
	int x,y;
    static char logo[13][44] = {
		"************......................**********",
		".**************..................**********.",
		".....************...............**********..",
		"........***********...........*********.....",
		"............********.......***********......",
		".............*********..*********...........",
		"...............**************...............",
		"...........*********..*********.............",
		".......***********......*********...........",
		"....**********...........***********........",
		"..**********..............*************.....",
		".**********.................***************.",
		"**********.....................*************"
	};
	boxfill8(buf_back, xsize, COL8_C6C6C6,           4, ysize - 24,          62, ysize -  3);
	boxfill8(buf_back, xsize, COL8_000000,           5, ysize - 24,          61, ysize - 24);
	boxfill8(buf_back, xsize, COL8_000000,           4, ysize - 24,           4, ysize -  4);
	boxfill8(buf_back, xsize, COL8_848484,           5, ysize - 23,          61, ysize - 23);
	boxfill8(buf_back, xsize, COL8_848484,           5, ysize - 23,           5, ysize -  5);
	boxfill8(buf_back, xsize, COL8_FFFFFF,           5, ysize -  3,          61, ysize -  3);
	boxfill8(buf_back, xsize, COL8_FFFFFF,          62, ysize - 24,          62, ysize -  3);
	boxfill8(buf_menu, 100, COL8_C6C6C6,  0, 0, 100, 20);
	
    for(y = 0; y < 13; y++)
    {
        for(x = 0; x < 44; x++)
        {
            if(logo[y][x] == '*')
            {
				buf_back[(ysize - 19 + y) * xsize + (10 + x)] = COL8_848484;
			}
        }
    }
}

void close_menu(char *buf_back, char *buf_menu,int xsize, int ysize)
{
	int x,y;
    static char logo[13][44] = {
		"************......................**********",
		".**************..................**********.",
		".....************...............**********..",
		"........***********...........*********.....",
		"............********.......***********......",
		".............*********..*********...........",
		"...............**************...............",
		"...........*********..*********.............",
		".......***********......*********...........",
		"....**********...........***********........",
		"..**********..............*************.....",
		".**********.................***************.",
		"**********.....................*************"
	};
	boxfill8(buf_back, xsize, COL8_C6C6C6,           4, ysize - 24,          62, ysize -  3);
	boxfill8(buf_back, xsize, COL8_FFFFFF,           5, ysize - 24,          61, ysize - 24);
	boxfill8(buf_back, xsize, COL8_FFFFFF,           4, ysize - 24,           4, ysize -  4);
	boxfill8(buf_back, xsize, COL8_848484,           5, ysize -  4,          61, ysize -  4);
	boxfill8(buf_back, xsize, COL8_848484,          61, ysize - 23,          61, ysize -  5);
	boxfill8(buf_back, xsize, COL8_000000,           5, ysize -  3,          61, ysize -  3);
	boxfill8(buf_back, xsize, COL8_000000,          62, ysize - 24,          62, ysize -  3);
	boxfill8(buf_menu, 100, 255, 0, 0, 100, 20);
	
    for(y = 0; y < 13; y++)
    {
        for(x = 0; x < 44; x++)
        {
            if(logo[y][x] == '*')
            {
				buf_back[(ysize - 20 + y) * xsize + (9 + x)] = COL8_848484;
			}
        }
    }
}
