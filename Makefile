TOOLPATH = ../z_HighSDK/
INCPATH  = ../z_HighSDK/high/

MAKE     = $(TOOLPATH)make.exe -r
EDIMG    = $(TOOLPATH)edimg.exe
IMGTOL   = $(TOOLPATH)imgtol.com
COPY     = copy
DEL      = del

default :
	$(MAKE) Horizon.img

Horizon.img : Makefile \
		kernel/ipl.bin \
		kernel/kernel.sys \
		ver/ver.hig \
		help/help.hig \
		help-cn/help-cn.hig \
		ver-cn/ver-cn.hig \
		timer/timer.hig \
		HZK16.fnt \
		test/test.hig \
		color/color.hig \
		type/type.hig \
		gview/gview.hig \
		gview/highos.jpg \
		calc/calc.hig \
		tview/tview.hig \
		invader/invader.hig \
		mmlplay/mmlplay.hig \
		mmldata/daigo.mml \
		notepad/notepad.hig \
		about/about.hig \
		README.txt \
		bg2.jpg
	$(EDIMG)   imgin:../z_HighSDK/fdimg0at.tek \
		wbinimg src:kernel/ipl.bin len:512 from:0 to:0 \
		copy from:kernel/kernel.sys to:@: \
		copy from:ver/ver.hig to:@: \
		copy from:help/help.hig to:@: \
		copy from:help-cn/help-cn.hig to:@: \
		copy from:ver-cn/ver-cn.hig to:@: \
		copy from:timer/timer.hig to:@: \
		copy from:HZK16.fnt to:@: \
		copy from:test/test.hig to:@: \
		copy from:color/color.hig to:@: \
		copy from:type/type.hig to:@: \
		copy from:gview/gview.hig to:@: \
		copy from:gview/highos.jpg to:@: \
		copy from:calc/calc.hig to:@: \
		copy from:tview/tview.hig to:@: \
		copy from:invader/invader.hig to:@: \
		copy from:mmlplay/mmlplay.hig to:@: \
		copy from:mmldata/daigo.mml to:@: \
		copy from:notepad/notepad.hig to:@: \
		copy from:about/about.hig to:@: \
		copy from:README.txt to:@: \
		copy from:bg2.jpg to:@: \
		imgout:Horizon.img

run :
	$(MAKE) Horizon.img
	$(COPY) Horizon.img ..\z_HighSDK\qemu\fdimage0.bin
	$(MAKE) -C ../z_HighSDK/qemu

clean :
	$(DEL) Horizon.img
