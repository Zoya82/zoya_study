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

	loadScoreboardFromFile("scoreboard.txt");                            //�����ļ�

	RECT n = { 589, 425, 743, 500 };
	char inputName[100];
	InputBox(inputName, sizeof(inputName), "�������û���:", "��¼", "", 400, 100, true);
	settextstyle(50, 0, "����");
	drawtext(inputName, &n, DT_SINGLELINE | DT_VCENTER);
	RECT p = { 589, 458, 743, 583 };
	char inputRegister[100];
	InputBox(inputRegister, sizeof(inputRegister), "����������:", "��¼", "", 400, 100, true);
	drawtext(inputRegister, &p, DT_SINGLELINE | DT_VCENTER);

	FILE* file;                                                         // ���ļ���д���û���������
	errno_t err = fopen_s(&file, "password.txt", "r");
	if (file == NULL) {
		printf("�޷����ļ�.\n");
		return 1;
	}
	bool userFound = false;
	char existingName[100], existingPassword[100];
	while (fscanf_s(file, "�û���: %99[^,], ����: %99[^\n]\n", existingName, sizeof(existingName), existingPassword, sizeof(existingPassword)) == 2) {
		if (strcmp(inputName, existingName) == 0) {
			userFound = true;
			if (strcmp(inputRegister, existingPassword) == 0) {
				// ����ƥ�䣬��¼�ɹ�
				printf("��¼�ɹ���\n");
			}
			else {
				// ���벻ƥ�䣬�˳�����
				printf("�������\n");
				fclose(file);
				closegraph();
				return 1;
			}
			break; // ���ҵ��û������˳�ѭ��
		}
	}
	if (!userFound) {
		// û����ͬ���û�����д���µ��û��������뵽�ļ�
		fclose(file);
		errno_t err = fopen_s(&file, "password.txt", "a");
		fprintf(file, "�û���: %s, ����: %s\n", inputName, inputRegister);
	}
	fclose(file);                                                       // �ر��ļ�

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
		settextstyle(100, 0, "΢���ź�");

		//  ��Ϸ����
		const char* pStr = "��Ϸ����";
		RECT r = { 0, 200, 422, 300 };
		drawtext(pStr, &r, DT_CENTER);

		//  �Ʒְ�
		char buff[10];
		sprintf_s(buff, sizeof(buff), "�÷�:%d", mainscene.mark);
		r = { 0, 300, 422, 400 };
		drawtext(buff, &r, DT_CENTER);

		settextstyle(50, 0, "΢���ź�");
		addToScoreboard(mainscene.mark);                           // ���÷���ӵ����а���
		displayScoreboard();                                       // ��ʾ���а�

		saveScoreboardToFile("scoreboard.txt");                    //д���ļ�

		Sleep(5000);

		cleardevice();
	}

	clearScoreboard();                                             // ������沢������Ϸ״̬
	closegraph();
	return 0;
}