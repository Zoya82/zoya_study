#include "menuscene.h"
#include "account.h"

void menuSceneDraw(struct menuScene* s) {
	putimage(0, 0, s->bk);                   //���Ʊ���ͼƬ
	settextcolor(WHITE);
	settextstyle(135, 0, "����");
	const char* pStr = "̫������";
	RECT r = { 465, 16, 465 + 642, 16 + 235 };
	drawtext(pStr, &r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	settextcolor(RGB(4, 20, 28));
	settextstyle(131, 0, "����");
	r = { 465, 16, 465 + 642, 16 + 235 };
	drawtext(pStr, &r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	settextcolor(WHITE);
	settextstyle(35, 0, "����");
	RECT t{ 489,363,689 + 538,761 + 36 };
	drawtext("�����ﱻ������̫�գ���������������\n���ｫ����ķ�Ĺ\n��ʼ�����;��\n\n��������ķɴ�\n����ײ�����ˣ��������Ǹ���һ", &t,  DT_VCENTER);

	settextcolor(BLACK);
	settextstyle(40, 0, "����");
	if (s->isStartGameHover == true)
		settextcolor(WHITE);
	else
		settextcolor(BLACK);
	drawtext("��ʼ��Ϸ", &s->rectStartGame, DT_SINGLELINE|DT_CENTER|DT_VCENTER);  //��������  
	if (s->isEndGameHover == true)
		settextcolor(WHITE);
	else
		settextcolor(BLACK);
	drawtext("������Ϸ", &s->rectEndGame, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	if (s->isRegisterHover == true)
		settextcolor(WHITE);
	else
		settextcolor(BLACK);
	drawtext("����", &s->rectRegister, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

}

void menuSceneUpdate(struct menuScene* s) {

}

void menuSceneControl(struct menuScene* s, ExMessage* msg) {
	switch (msg->message) {
		case WM_LBUTTONDOWN: {                     //����������
			if (s->isEndGameHover == true)         //����Ƿ���ͣ�ڿ�ʼ��������ť��
				exit(0);                           //����������Ϸ
			if (s->isStartGameHover == true)
				s->isQuit = true;
			if (s->isRegisterHover == true)
				s->isWindow = true;
			break;
		}
		case WM_MOUSEMOVE: {                       //����ƶ� ����Ƿ��ڿ�ʼ��������ť����������
			if (msg->x > s->rectStartGame.left && msg->x < s->rectStartGame.right
				&& msg->y<s->rectStartGame.bottom && msg->y>s->rectStartGame.top)
				s->isStartGameHover = true;
			else
				s->isStartGameHover = false;
			if (msg->x > s->rectEndGame.left && msg->x < s->rectEndGame.right
				&& msg->y<s->rectEndGame.bottom && msg->y>s->rectEndGame.top)
				s->isEndGameHover = true;
			else
				s->isEndGameHover = false;
			if (msg->x > s->rectRegister.left && msg->x < s->rectRegister.right
				&& msg->y<s->rectRegister.bottom && msg->y>s->rectRegister.top)
			{
				s->isRegisterHover = true;
			}
			else
				s->isRegisterHover = false;
			break;
		}
	}
}

bool menuSceneIsQuit(struct menuScene* s) {
	return s->isQuit;
}

bool menuSceneIsRegister(struct menuScene* s) {
	return s->isWindow;
}

void menuSceneInit(struct menuScene* s) {
	s->super.draw = (void(*)(struct scene*))menuSceneDraw;
	s->super.update = (void(*)(struct scene*))menuSceneUpdate;
	s->super.control = (void(*)(struct scene*, ExMessage*))menuSceneControl;
	s->super.isQuit = (bool(*)(struct scene*))menuSceneIsQuit;
	s->super.isWindow = (bool(*)(struct scene*))menuSceneIsRegister;

	s->isStartGameHover = false;
	s->isEndGameHover = false;
	s->isRegisterHover = false;

	s->isQuit = false;
	s->isWindow = false;

	s->bk = new IMAGE;
	loadimage(s->bk, "gamepicture\\background\\background_start.png");

	s->rectStartGame.left = 168;
	s->rectStartGame.top = 270;
	s->rectStartGame.right = 380;
	s->rectStartGame.bottom = 344;

	s->rectEndGame.left = 156;
	s->rectEndGame.top = 375;
	s->rectEndGame.right = 368;
	s->rectEndGame.bottom = 449;

	s->rectRegister.left = 144;
	s->rectRegister.top = 480;
	s->rectRegister.right = 356;
	s->rectRegister.bottom = 554;

	settextcolor(BLACK);
	LOGFONT fontStyle;
	gettextstyle(&fontStyle);
	fontStyle.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&fontStyle);
	settextstyle(40, 0, "����");
	setbkmode(TRANSPARENT);
}

void menuSceneDestroy(struct menuScene* s) {
	delete s->bk;
}