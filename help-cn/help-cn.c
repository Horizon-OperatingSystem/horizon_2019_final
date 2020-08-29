#include <apilib.h>
#include <stdio.h>

int HighMain()
{
	printf("欢迎来到Horizon操作系统内核命令助手\n");
	printf("*.hig 是Horizon操作系统可执行文件\n");
	printf("fl - 显示文件列表\n");
	printf("mem - 显示内存状态\n");
	printf("cls - 清除屏幕\n");
	printf("exit - 退出命令行\n");
	printf("start [Hig Name] - 用一个新窗口开始应用程序\n");
	printf("ncst [Hig Name] - 不用新窗口开始应用程序\n");
	printf("[Hig Name] - 在当前命令行开始应用程序\n");
	exit(0);
}
