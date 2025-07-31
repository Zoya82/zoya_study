#include <time.h>
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include "gameloop.h"
#include "scene.h"
#include "mainScene.h"
#include "menuscene.h"
#include "account.h"
#include "scoreboard.h"

int main() {
	initgraph(1280,720);
	setbkcolor(WHITE);
	cleardevice();

	loadScoreboardFromFile("scoreboard.txt");                            //加载文件

	RECT n = { 589, 425, 743, 500 };
	char inputName[100];
	InputBox(inputName, sizeof(inputName), "请输入用户名:", "登录", "", 400, 100, true);
	settextstyle(50, 0, "黑体");
	drawtext(inputName, &n, DT_SINGLELINE | DT_VCENTER);
	RECT p = { 589, 458, 743, 583 };
	char inputRegister[100];
	InputBox(inputRegister, sizeof(inputRegister), "请输入密码:", "登录", "", 400, 100, true);
	drawtext(inputRegister, &p, DT_SINGLELINE | DT_VCENTER);

	FILE* file;                                                         // 打开文件以写入用户名和密码
	errno_t err = fopen_s(&file, "password.txt", "r");
	if (file == NULL) {
		printf("无法打开文件.\n");
		return 1;
	}
	bool userFound = false;
	char existingName[100], existingPassword[100];
	while (fscanf_s(file, "用户名: %99[^,], 密码: %99[^\n]\n", existingName, sizeof(existingName), existingPassword, sizeof(existingPassword)) == 2) {
		if (strcmp(inputName, existingName) == 0) {
			userFound = true;
			if (strcmp(inputRegister, existingPassword) == 0) {
				// 密码匹配，登录成功
				printf("登录成功！\n");
			}
			else {
				// 密码不匹配，退出程序
				printf("密码错误！\n");
				fclose(file);
				closegraph();
				return 1;
			}
			break; // 已找到用户名，退出循环
		}
	}
	if (!userFound) {
		// 没有相同的用户名，写入新的用户名和密码到文件
		fclose(file);
		errno_t err = fopen_s(&file, "password.txt", "a");
		fprintf(file, "用户名: %s, 密码: %s\n", inputName, inputRegister);
	}
	fclose(file);                                                       // 关闭文件

	while (1) {
		
		menuScene menuscene;
		menuSceneInit(&menuscene);
		gameLoop((scene*)&menuscene, 60);
		menuSceneDestroy(&menuscene);
		
		mainScene mainscene;
		mainSceneInit(&mainscene);
		gameLoop((scene*)&mainscene, 60);
		mainSceneDestroy(&mainscene);

		settextcolor(WHITE);
		settextstyle(100, 0, "微软雅黑");

		//  游戏结束
		const char* pStr = "游戏结束";
		RECT r = { 0, 200, 422, 300 };
		drawtext(pStr, &r, DT_CENTER);

		//  计分板
		char buff[10];
		sprintf_s(buff, sizeof(buff), "得分:%d", mainscene.mark);
		r = { 0, 300, 422, 400 };
		drawtext(buff, &r, DT_CENTER);

		settextstyle(50, 0, "微软雅黑");
		addToScoreboard(mainscene.mark);                           // 将得分添加到排行榜中
		displayScoreboard();                                       // 显示排行榜

		saveScoreboardToFile("scoreboard.txt");                    //写入文件

		Sleep(5000);

		cleardevice();
	}

	clearScoreboard();                                             // 清除画面并重置游戏状态
	closegraph();
	return 0;
}