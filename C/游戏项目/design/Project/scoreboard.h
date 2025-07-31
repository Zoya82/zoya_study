#ifndef SCOREBOARD_H
#define SCOREBOARD_H

// �������а�ڵ�ṹ
typedef struct ScoreNode {
    int score;
    struct ScoreNode* next;
} ScoreNode;

// ȫ�ֱ�������
extern ScoreNode* head;

// ���а������������
void addToScoreboard(int score);
void displayScoreboard();
void clearScoreboard();
void loadScoreboardFromFile(const char* filename);
void saveScoreboardToFile(const char* filename);

#endif /* SCOREBOARD_H */