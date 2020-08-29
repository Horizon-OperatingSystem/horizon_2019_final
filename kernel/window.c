#include "boot.h"

void make_window8(unsigned char *buf, int xsize, int ysize, char *title, char act)
{
	int color=16+(30/51)+(144/51)*6+(255/51)*36;
	boxfill8(buf, xsize, COL8_FFFFFF, 0, 0, xsize - 1, 0);
	boxfill8(buf, xsize, color, 0, 0, xsize - 1, 0);
	boxfill8(buf, xsize, 255, 1, 1, xsize - 2, 1);
	boxfill8(buf, xsize, color, 0, 0, 0, ysize - 1);
	boxfill8(buf, xsize, 255, 1, 1, 1, ysize - 2);
	boxfill8(buf, xsize, color, xsize - 2, 1, xsize - 2, ysize - 2);
	boxfill8(buf, xsize, 255, xsize - 1, 0, xsize - 1, ysize - 1);
	boxfill8(buf, xsize, COL8_FFFFFF, 2, 2, xsize - 3, ysize - 3);
	boxfill8(buf, xsize, COL8_FFFFFF, 3, 3, xsize - 4, 20);
	boxfill8(buf, xsize, color, 1, ysize - 2, xsize - 2, ysize - 2);
	boxfill8(buf, xsize, 255, 0, ysize - 1, xsize - 1, ysize - 1);

    /*
	Old Window ( Haribote )
	boxfill8(buf, xsize, COL8_C6C6C6, 0,         0,         xsize - 1, 0);
    boxfill8(buf, xsize, COL8_FFFFFF, 1,         1,         xsize - 2, 1);
    boxfill8(buf, xsize, COL8_C6C6C6, 0,         0,         0,         ysize - 1);
    boxfill8(buf, xsize, COL8_FFFFFF, 1,         1,         1,         ysize - 2);
    boxfill8(buf, xsize, COL8_848484, xsize - 2, 1,         xsize - 2, ysize - 2);
    boxfill8(buf, xsize, COL8_000000, xsize - 1, 0,         xsize - 1, ysize - 1);
    boxfill8(buf, xsize, COL8_C6C6C6, 2,         2,         xsize - 3, ysize - 3);
    boxfill8(buf, xsize, COL8_848484, 1,         ysize - 2, xsize - 2, ysize - 2);
    boxfill8(buf, xsize, COL8_000000, 0,         ysize - 1, xsize - 1, ysize - 1);
	*/

    make_wtitle8(buf, xsize, title, act);
	
	//左上角
	boxfill8(buf, xsize, 255, 0, 0, 2, 2);
	boxfill8(buf, xsize, 255, 3, 0, 4, 1);
	boxfill8(buf, xsize, color, 3, 1, 4, 1);
	boxfill8(buf, xsize, 255, 0, 3, 1, 4);
	boxfill8(buf, xsize, color, 1, 3, 1, 4);
	put_dot(buf, xsize, color, 2, 2);
	//boxfill8(buf, xsize, color, 1, 1, 2, 2);
	//右上角
	boxfill8(buf, xsize, 255, xsize - 3, 0, xsize - 1, 2);
	boxfill8(buf, xsize, 255, xsize - 5, 0, xsize - 4, 1);
	boxfill8(buf, xsize, color, xsize - 5, 1, xsize - 4, 1);
	boxfill8(buf, xsize, 255, xsize - 2, 3, xsize - 1, 4);
	boxfill8(buf, xsize, color, xsize - 2, 3, xsize - 2, 4);
	put_dot(buf, xsize, color, xsize - 3, 2);
	//左下角
	boxfill8(buf, xsize, 255, 0, ysize - 3, 2, ysize - 1);
	put_dot(buf, xsize, 255, 0, ysize - 4);
	put_dot(buf, xsize, 255, 3, ysize - 1);
	boxfill8(buf, xsize, color, 1, ysize - 3, 2, ysize - 2);
	put_dot(buf, xsize, 255, 1, ysize - 2);
	//右下角
	boxfill8(buf, xsize, 255, xsize - 3, ysize - 3, xsize - 1, ysize - 1);
	put_dot(buf, xsize, 255, xsize - 4, ysize - 1);
	put_dot(buf, xsize, 255, xsize - 1, ysize - 4);
	boxfill8(buf, xsize, color, xsize - 3, ysize - 3, xsize - 2, ysize - 2);
	put_dot(buf, xsize, 255, xsize - 2, ysize - 2);
	
    return;
}

void make_wtitle8(unsigned char *buf, int xsize, char *title, char act)
{
    static char closebtn[14][16] =
    {
        "......QQQQ......",
        "....QQQQQQQQQ...",
        "...QQQQQQQQQQ...",
        "..QQ@@QQQQ@@QQ..",
        "..QQQ@@QQ@@QQQ..",
        ".QQQQQ@@@@QQQQQ.",
        ".QQQQQQ@@QQQQQQ.",
        ".QQQQQQ@@QQQQQQ.",
        ".QQQQQ@@@@QQQQQ.",
        "..QQQ@@QQ@@QQQ..",
        "..QQ@@QQQQ@@QQ..",
        "...QQQQQQQQQQ...",
        "....QQQQQQQQ....",
        "......QQQQ......"
    };
    int x, y;
    char c, tc, tbc;

    if(act != 0)
    {
        tc = COL8_000000;
        tbc = rgb2pal(0x00,0x99,0xFF,0,0);
    }
    else
    {
        tc = COL8_FFFFFF;
        tbc = COL8_848484;
    }

    boxfill8_tp50(buf, xsize, tbc, 1, 1, xsize - 3, 20);
    putfonts8_asc(buf, xsize, xsize / 2 - (sizeof(title) * 8 / 2) - 12, 4, tc, title);
	
    for(y = 0; y < 14; y++)
    {
        for(x = 0; x < 16; x++)
        {
            c = closebtn[y][x];

            if(c == '@')
            {
                c = COL8_FFFFFF;
            }
            else if(c == 'Q')
            {
                c = COL8_FF0000;
            }

            if(c != '.'){
				buf[(5 + y) * xsize + (xsize - 21 + x)] = c;
			}

        }
    }

    return;
}

void putfonts8_asc_sht(struct SHEET *sht, int x, int y, int c, int b, char *s, int l)
{
	struct TASK *task = task_now();
	boxfill8(sht->buf, sht->bxsize, b, x, y, x + l * 8 - 1, y + 15);
	if (task->langbyte1 != 0)
	{
		putfonts8_asc(sht->buf, sht->bxsize, x, y, c, s);
		sheet_refresh(sht, x - 8, y, x + l * 8, y + 16);
	} else
	{
		putfonts8_asc(sht->buf, sht->bxsize, x, y, c, s);
		sheet_refresh(sht, x, y, x + l * 8, y + 16);
	}
	return;
}

void make_textbox8(struct SHEET *sht, int x0, int y0, int sx, int sy, int c)
{
    int x1 = x0 + sx, y1 = y0 + sy;
    boxfill8(sht->buf, sht->bxsize, COL8_848484, x0 - 2, y0 - 3, x1 + 1, y0 - 3);
    boxfill8(sht->buf, sht->bxsize, COL8_848484, x0 - 3, y0 - 3, x0 - 3, y1 + 1);
    boxfill8(sht->buf, sht->bxsize, COL8_FFFFFF, x0 - 3, y1 + 2, x1 + 1, y1 + 2);
    boxfill8(sht->buf, sht->bxsize, COL8_FFFFFF, x1 + 2, y0 - 3, x1 + 2, y1 + 2);
    boxfill8(sht->buf, sht->bxsize, COL8_000000, x0 - 1, y0 - 2, x1 + 0, y0 - 2);
    boxfill8(sht->buf, sht->bxsize, COL8_000000, x0 - 2, y0 - 2, x0 - 2, y1 + 0);
    boxfill8(sht->buf, sht->bxsize, COL8_C6C6C6, x0 - 2, y1 + 1, x1 + 0, y1 + 1);
    boxfill8(sht->buf, sht->bxsize, COL8_C6C6C6, x1 + 1, y0 - 2, x1 + 1, y1 + 1);
    boxfill8(sht->buf, sht->bxsize, c,           x0 - 1, y0 - 1, x1 + 0, y1 + 0);
    return;
}

void change_wtitle8(struct SHEET *sht, char act)
{
    int x, y, xsize = sht->bxsize;
    char c, tc_new, tbc_new, tc_old, tbc_old, *buf = sht->buf;

    if(act != 0)
    {
        tc_new  = COL8_000000;
        tbc_new = rgb2pal(0x00,0x99,0xFF,0,0);
        tc_old  = COL8_C6C6C6;
        tbc_old = COL8_848484;
    }
    else
    {
        tc_new  = COL8_C6C6C6;
        tbc_new = COL8_848484;
        tc_old  = COL8_000000;
        tbc_old = rgb2pal(0x00,0x99,0xFF,0,0);
    }

    for(y = 3; y <= 20; y++)
    {
        for(x = 3; x <= xsize - 4; x++)
        {
            c = buf[y * xsize + x];

            if(c == tc_old && x <= xsize - 22)
            {
                c = tc_new;
            }
            else if(c == tbc_old)
            {
                c = tbc_new;
            }

            buf[y * xsize + x] = c;
        }
    }

    sheet_refresh(sht, 3, 3, xsize, 21);
    return;
}
