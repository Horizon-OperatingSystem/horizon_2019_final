OBJS_BOOT = boot.obj func.obj fonts.obj graphic.obj dsctbl.obj \
	    int.obj fifo.obj keyboard.obj mouse.obj memory.obj sheet.obj timer.obj \
	    mtask.obj window.obj console.obj file.obj jpeg.obj cmos.obj

TOOLPATH = ../../z_HighSDK/
INCPATH  = ../../z_HighSDK/kernel/
APILIBPATH   = ../../z_HighSDK/kernel/

MAKE     = $(TOOLPATH)make.exe -r
NASK     = $(TOOLPATH)nask.exe
CC1      = $(TOOLPATH)cc1.exe -I$(INCPATH) -Os -Wall -quiet -I../
GAS2NASK = $(TOOLPATH)gas2nask.exe -a
OBJ2BIM  = $(TOOLPATH)obj2bim.exe
MAKEFONT = $(TOOLPATH)makefont.exe
BIN2OBJ  = $(TOOLPATH)bin2obj.exe
BIM2HIG  = $(TOOLPATH)bim2hig.exe
RULEFILE = ../horizon.rul
EDIMG    = $(TOOLPATH)edimg.exe
IMGTOL   = $(TOOLPATH)imgtol.com
GOLIB    = $(TOOLPATH)golib00.exe
COPY     = copy
DEL      = del

default :
	$(MAKE) ipl.bin
	$(MAKE) kernel.sys

ipl.bin : ipl.asm Makefile
	$(NASK) ipl.asm ipl.bin ipl.lst

asmhead.bin : asmhead.asm Makefile
	$(NASK) asmhead.asm asmhead.bin asmhead.lst

fonts.bin : fonts.txt Makefile
	$(MAKEFONT) fonts.txt fonts.bin

fonts.obj : fonts.bin Makefile
	$(BIN2OBJ) fonts.bin fonts.obj _fonts

boot.bim : $(OBJS_BOOT) Makefile
	$(OBJ2BIM) @$(RULEFILE) out:boot.bim stack:4000k map:boot.map \
		$(OBJS_BOOT)

boot.hig : boot.bim Makefile
	$(BIM2HIG) boot.bim boot.hig 0

kernel.sys : asmhead.bin boot.hig Makefile
	copy /B asmhead.bin+boot.hig kernel.sys

%.gas : %.c boot.h Makefile
	$(CC1) -o $*.gas $*.c

%.asm : %.gas Makefile
	$(GAS2NASK) $*.gas $*.asm

%.obj : %.asm Makefile
	$(NASK) $*.asm $*.obj $*.lst

clean :
	-$(DEL) asmhead.bin
	-$(DEL) fonts.bin
	-$(DEL) *.lst
	-$(DEL) *.obj
	-$(DEL) *.map
	-$(DEL) *.bim
	-$(DEL) *.hig

src_only :
	$(MAKE) clean
	-$(DEL) ipl.bin
	-$(DEL) kernel.sys
