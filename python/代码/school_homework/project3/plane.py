import pygame
import sys

# 初始化pygame
pygame.init()

# 设置屏幕大小
SCREEN_WIDTH, SCREEN_HEIGHT = 800, 600
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("飞机移动示例")

# 定义颜色
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

# 定义飞机类
class Airplane:
    def __init__(self, x, y, width, height):
        self.rect = pygame.Rect(x, y, width, height)
        self.speed_x = 0  # 水平速度
        self.speed_y = 0  # 垂直速度

    def move(self):
        # 更新飞机的位置
        self.rect.x += self.speed_x
        self.rect.y += self.speed_y
        # 边界检查
        if self.rect.left < 0:
            self.rect.left = 0
        if self.rect.right > SCREEN_WIDTH:
            self.rect.right = SCREEN_WIDTH
        if self.rect.top < 0:
            self.rect.top = 0
        if self.rect.bottom > SCREEN_HEIGHT:
            self.rect.bottom = SCREEN_HEIGHT

    def draw(self, screen):
        # 在屏幕上绘制飞机
        pygame.draw.rect(screen, WHITE, self.rect)

# 创建飞机实例
airplane = Airplane(400, 300, 50, 50)

# 游戏主循环
clock = pygame.time.Clock()
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LEFT:
                airplane.speed_x = -5  # 飞机向左移动
            elif event.key == pygame.K_RIGHT:
                airplane.speed_x = 5   # 飞机向右移动
            elif event.key == pygame.K_UP:
                airplane.speed_y = -5  # 飞机向上移动
            elif event.key == pygame.K_DOWN:
                airplane.speed_y = 5   # 飞机向下移动
        elif event.type == pygame.KEYUP:
            if event.key in (pygame.K_LEFT, pygame.K_RIGHT):
                airplane.speed_x = 0   # 停止水平移动
            if event.key in (pygame.K_UP, pygame.K_DOWN):
                airplane.speed_y = 0   # 停止垂直移动

    # 移动飞机并检查边界
    airplane.move()

    # 填充背景色
    screen.fill(BLACK)

    # 绘制飞机
    airplane.draw(screen)

    # 更新屏幕显示
    pygame.display.flip()

    # 控制帧率
    clock.tick(60)

# 退出pygame
pygame.quit()
sys.exit()