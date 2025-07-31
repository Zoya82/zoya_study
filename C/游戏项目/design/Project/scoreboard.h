#ifndef SCOREBOARD_H
#define SCOREBOARD_H

// 定义排行榜节点结构
typedef struct ScoreNode {
    int score;
    struct ScoreNode* next;
} ScoreNode;

// 全局变量声明
extern ScoreNode* head;

// 排行榜操作函数声明
void addToScoreboard(int score);
void displayScoreboard();
void clearScoreboard();
void loadScoreboardFromFile(const char* filename);
void saveScoreboardToFile(const char* filename);

#endif /* SCOREBOARD_H */