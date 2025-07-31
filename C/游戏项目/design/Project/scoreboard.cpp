#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include "scoreboard.h"

ScoreNode* head = NULL; // 初始化排行榜的头指针为空

// 添加得分到排行榜，按照从大到小的顺序插入
void addToScoreboard(int score) {
    ScoreNode* newNode = (ScoreNode*)malloc(sizeof(ScoreNode));
    if (newNode == NULL) {
        return;
    }
    newNode->score = score;
    newNode->next = NULL;

    if (head == NULL || score > head->score) {
        newNode->next = head;
        head = newNode;
    }
    else {
        ScoreNode* current = head;
        while (current->next != NULL && current->next->score > score) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// 显示排行榜
void displayScoreboard() {
    int x = 380; // 屏幕中央 x 坐标
    int y = 47; // 屏幕中央 y 坐标
    int rank = 1;
    char rankScore[20];
    setfillcolor(WHITE);
    rectangle(x, y, x + 466, y + 634); // 绘制白色长方形作为背景
    outtextxy(x+113, y, "Scoreboard"); // 绘制标题

    ScoreNode* current = head;
    while (current != NULL && rank <= 10) {
        sprintf_s(rankScore, sizeof(rankScore), "%d   %d", rank, current->score);
        outtextxy(x + 50, y + 50 + (rank - 1) * 50, rankScore); // 调整输出位置
        current = current->next;
        rank++;
    }
}

// 清空排行榜
void clearScoreboard() {
    ScoreNode* current = head;
    while (current != NULL) {
        ScoreNode* temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
}

// 保存排行榜到文件
void saveScoreboardToFile(const char* filename) {
    FILE* file;
    errno_t err = fopen_s(&file, filename, "w");
    if (err != 0) {
        //printf("Error opening file for writing.\n");
        return;
    }


    ScoreNode* current = head;
    while (current != NULL) {
        fprintf(file, "%d\n", current->score);
        current = current->next;
    }

    fclose(file);
}

// 从文件加载排行榜
void loadScoreboardFromFile(const char* filename) {
    FILE* file;
    errno_t err = fopen_s(&file, filename, "r");
    if (err != 0) {
        //printf("Error opening file for writing.\n");
        return;
    }


    clearScoreboard(); // 清空当前排行榜数据

    int score;
    while (fscanf_s(file, "%d", &score) != EOF) {
        addToScoreboard(score);
    }

    fclose(file);
}
