APP      = gview
STACK    = 4480k
MALLOC   = 0k

TOOLPATH = ../../z_HighSDK/
INCPATH  = ../../z_HighSDK/apps/
APILIBPATH   = ../../z_HighSDK/apps/

MAKE     = $(TOOLPATH)make.exe -r
NASK     = $(TOOLPATH)nask.exe
CC1      = $(TOOLPATH)cc1.exe -I$(INCPATH) -I../ -Os -Wall -quiet
GAS2NASK = $(TOOLPATH)gas2nask.exe -a
OBJ2BIM  = $(TOOLPATH)obj2bim.exe
MAKEFONT = $(TOOLPATH)makefont.exe
BIN2OBJ  = $(TOOLPATH)bin2obj.exe
BIM2HIG  = $(TOOLPATH)bim2hig.exe
RULEFILE = ../high.rul
EDIMG    = $(TOOLPATH)edimg.exe
IMGTOL   = $(TOOLPATH)imgtol.com
GOLIB    = $(TOOLPATH)golib00.exe 
COPY     = copy
DEL      = del

default :
	$(MAKE) $(APP).hig

$(APP).bim : $(APP).obj bmp.obj jpeg.obj Makefile
	$(OBJ2BIM) @$(RULEFILE) out:$(APP).bim map:$(APP).map stack:$(STACK) \
		$(APP).obj jpeg.obj bmp.obj

%.gas : %.c Makefile
	$(CC1) -o $*.gas $*.c

%.asm : %.gas Makefile
	$(GAS2NASK) $*.gas $*.asm

%.obj : %.asm Makefile
	$(NASK) $*.asm $*.obj $*.lst

%.hig : %.bim Makefile
	$(BIM2HIG) $*.bim $*.hig $(MALLOC)

clean :
	-$(DEL) *.lst
	-$(DEL) gview.obj
	-$(DEL) jpeg.obj
	-$(DEL) *.map
	-$(DEL) *.bim

src_only :
	$(MAKE) clean
	-$(DEL) $(APP).hig
