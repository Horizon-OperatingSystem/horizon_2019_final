//Made by Ryan

#include <string.h>		
#include "apilib.h"

void HighMain(void)
{
	int win;
	int ix=0,iy=0,last_end[25]={0};
	int i;
	char winbuf[820 * 470],s[2];
	
	win = api_openwin(winbuf, 820, 25*16+40, "Notepad");
	api_boxfilwin(win, 8, 28, 812, 25*16+32, 0);
	api_boxfilwin(win, 9, 29, 811, 25*16+31, 7);
	for(;;){
		do{
			api_boxfilwin(win, ix*8+10, iy*16+30, ix*8+10, iy*16+46, 0);
			i = api_getkey(0);
		}while(i == -1);

		if(i==8){
			if(ix>0){
				api_boxfilwin(win, ix*8+10, iy*16+30, ix*8+10, iy*16+46, 7);
				ix--;
				api_boxfilwin(win, ix*8+10, iy*16+30, ix*8+18, iy*16+46, 7);
				api_boxfilwin(win, ix*8+10, iy*16+30, ix*8+10, iy*16+46, 0);
			}else if(ix==0){
				if(iy>0){
					api_boxfilwin(win, ix*8+10, iy*16+30, ix*8+10, iy*16+46, 7);
					s[0]=i;
					s[1]=0;
					iy--;
					ix=last_end[iy];
					api_boxfilwin(win, ix*8+10, iy*16+30, ix*8+10, iy*16+46, 0);
				}
			}
		}
        else if(i == 0x0a){
			if(iy<24){
				api_boxfilwin(win, ix*8+10, iy*16+30, ix*8+10, iy*16+46, 7);
				last_end[iy]=ix;
				ix=0;
				iy++;
				api_boxfilwin(win, ix*8+10, iy*16+30, ix*8+10, iy*16+46, 0);
			}
		}
        else{
			api_boxfilwin(win, ix*8+10, iy*16+30, ix*8+10, iy*16+46, 7);
			if(ix==100){
				if(iy<24){
					last_end[iy]=ix;
					ix=0;
					iy++;
				}
			}
			if(iy==24){
				if(ix<100){
					s[0]=i;
					s[1]=0;
					api_putstrwin(win, ix*8+10, iy*16+30, 0, 1, s);
					ix++;
				}
			}else if(iy<24){
				s[0]=i;
				s[1]=0;
				api_putstrwin(win, ix*8+10, iy*16+30, 0, 1, s);
				ix++;
			}
			api_boxfilwin(win, ix*8+10, iy*16+30, ix*8+10, iy*16+46, 0);
        }
	}

}


