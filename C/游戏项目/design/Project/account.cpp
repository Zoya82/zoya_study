#include <stdio.h>
#include <easyx.h>
#include <graphics.h>
#include "scene.h"
#include "account.h"

void accountDraw(struct account* s) {
	cleardevice();
	setfillcolor(WHITE);
	rectangle(556, 135, 556 + 510, 135 + 373);
	printf_s("yeah");
	
	settextstyle(50, 0, "黑体");
    drawtext("注册登录", &s->rectHead, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	settextstyle(25, 0, "黑体");
	drawtext("用户名", &s->rectName, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	drawtext("密码", &s->rectRegister, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	settextstyle(10, 0, "黑体");
	drawtext("输入完成后按下回车键即注册成功", &s->rectFinish, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	setcolor(BLACK);
	rectangle(s->rectNametext.left, s->rectNametext.top, s->rectNametext.right, s->rectNametext.bottom);
	rectangle(s->rectRegistertext.left, s->rectRegistertext.top, s->rectRegistertext.right, s->rectRegistertext.bottom);
	
}

void accountUpdate(struct account* s) {

}

void accountControl(struct account* s, ExMessage* msg) {
	switch (msg->message) {
		case WM_LBUTTONDOWN: {                     //按下鼠标左键
			if (s->isNametextHover == true) {
				// 获取用户名输入
				char inputName[100];
				InputBox(inputName, sizeof(inputName), "请输入用户名:", "登录", "", 0, 0, true);
				settextstyle(20, 0, "黑体");
				outtextxy(s->rectNametext.left, s->rectNametext.top, inputName);
			}
			if (s->isRegistertextHover == true) {
				// 获取密码输入
				char inputRegister[100];
				InputBox(inputRegister, sizeof(inputRegister), "请输入密码:", "登录", "", 0, 0, true);
				settextstyle(20, 0, "黑体");
				outtextxy(s->rectRegistertext.left, s->rectRegistertext.top, inputRegister);
			}
			break;
		}
		case WM_MOUSEMOVE: {                       //鼠标移动 鼠标是否在用户名、注册文本框矩形区域内
			if (msg->x > s->rectNametext.left && msg->x < s->rectNametext.right
				&& msg->y<s->rectNametext.bottom && msg->y>s->rectNametext.top)
				s->isNametextHover = true;
			else
				s->isNametextHover = false;
			if (msg->x > s->rectRegistertext.left && msg->x < s->rectRegistertext.right
				&& msg->y<s->rectRegistertext.bottom && msg->y>s->rectRegistertext.top)
				s->isRegistertextHover = true;
			else
				s->isRegistertextHover = false;
			break;
		}
		case WM_KEYUP:{
			s->isFinish = true;
			cleardevice();
			break;
		}
	}
}

bool accountIsFinish(struct account* s) {
	return s->isFinish;
}

void accountInit(struct account* s) {
	s->super.draw = (void(*)(struct scene*))accountDraw;
	s->super.update = (void(*)(struct scene*))accountUpdate;
	s->super.control = (void(*)(struct scene*, ExMessage*))accountControl;
	s->super.isQuit = (bool(*)(struct scene*))accountIsFinish;

	s->isRegistertextHover = false;
	s->isNametextHover = false;

	s->isFinish = false;

	s->rectHead.left = 589;
	s->rectHead.top = 153;
	s->rectHead.right = 1036;
	s->rectHead.bottom = 273;

	s->rectRegister.left = 589;
	s->rectRegister.top = 300;
	s->rectRegister.right = 743;
	s->rectRegister.bottom = 375;

	s->rectRegistertext.left = 156;
	s->rectRegistertext.top = 375;
	s->rectRegistertext.right = 368;
	s->rectRegistertext.bottom = 449;

	s->rectName.left = 589;
	s->rectName.top = 408;
	s->rectName.right = 743;
	s->rectName.bottom = 483;

	s->rectNametext.left = 755;
	s->rectNametext.top = 295;
	s->rectNametext.right = 1036;
	s->rectNametext.bottom = 350;

	s->rectFinish.left = 156;
	s->rectFinish.top = 375;
	s->rectFinish.right = 368;
	s->rectFinish.bottom = 449;

	settextcolor(BLACK);
	LOGFONT fontStyle;
	gettextstyle(&fontStyle);
	fontStyle.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&fontStyle);
	setbkmode(TRANSPARENT);
}
