#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include "scoreboard.h"

ScoreNode* head = NULL; // ��ʼ�����а��ͷָ��Ϊ��

// ��ӵ÷ֵ����а񣬰��մӴ�С��˳�����
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

// ��ʾ���а�
void displayScoreboard() {
    int x = 380; // ��Ļ���� x ����
    int y = 47; // ��Ļ���� y ����
    int rank = 1;
    char rankScore[20];
    setfillcolor(WHITE);
    rectangle(x, y, x + 466, y + 634); // ���ư�ɫ��������Ϊ����
    outtextxy(x+113, y, "Scoreboard"); // ���Ʊ���

    ScoreNode* current = head;
    while (current != NULL && rank <= 10) {
        sprintf_s(rankScore, sizeof(rankScore), "%d   %d", rank, current->score);
        outtextxy(x + 50, y + 50 + (rank - 1) * 50, rankScore); // �������λ��
        current = current->next;
        rank++;
    }
}

// ������а�
void clearScoreboard() {
    ScoreNode* current = head;
    while (current != NULL) {
        ScoreNode* temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
}

// �������а��ļ�
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

// ���ļ��������а�
void loadScoreboardFromFile(const char* filename) {
    FILE* file;
    errno_t err = fopen_s(&file, filename, "r");
    if (err != 0) {
        //printf("Error opening file for writing.\n");
        return;
    }


    clearScoreboard(); // ��յ�ǰ���а�����

    int score;
    while (fscanf_s(file, "%d", &score) != EOF) {
        addToScoreboard(score);
    }

    fclose(file);
}
