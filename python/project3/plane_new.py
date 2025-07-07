import pygame

class SmallEnemy(pygame.sprite.Sprite):
    """
    定义小飞机敌人
    """
    def __init__(self, bg_size):
        super(SmallEnemy, self).__init__()

        # 程序填空一：通过pygame模块读取material/image/enemy1.png的敌机图片
        self.image = pygame.image.load("material/image/enemy1.png").convert_alpha()  # 加载敌机图片并保留透明背景

        self.rect = self.image.get_rect()
        self.width, self.height = bg_size[0], bg_size[1]
        self.mask = pygame.mask.from_surface(self.image)  # 创建掩膜用于碰撞检测
        self.speed = 2  # 定义敌机的速度

        # 定义敌机出现的位置，保证敌机不会在程序一开始就立即出现
        self.rect.left, self.rect.top = (
            randint(0, self.width - self.rect.width),  # 随机生成敌机的初始水平位置
            randint(-5 * self.rect.height, -5)         # 随机生成敌机的初始垂直位置
        )
        self.active = True  # 初始化敌机为活跃状态

    def move(self):
        """
        定义敌机的移动函数
        :return:
        """
        if self.rect.top < self.height:
            self.rect.top += self.speed  # 向下移动
        else:
            self.reset()  # 当敌机移出屏幕时，重置其位置

    def reset(self):
        """
        当敌机移动出屏幕时，或者敌机死亡时，重置敌机
        :return:
        """
        self.rect.left, self.rect.top = (
            randint(0, self.width - self.rect.width),  # 随机生成新的水平位置
            randint(-5 * self.rect.height, 0)          # 随机生成新的垂直位置
        )
        self.active = True  # 恢复敌机为活跃状态

class Bullet(pygame.sprite.Sprite):
    def __init__(self, position):
        super(Bullet, self).__init__()

        # 程序填空三：子弹属性的初始化
        self.image = pygame.image.load("material/image/bullet1.png").convert_alpha()  # 加载子弹图片
        self.rect = self.image.get_rect()  # 获取子弹的矩形区域
        self.rect.left, self.rect.top = position  # 子弹的位置
        self.speed = 10  # 设置子弹的速度
        self.active = True  # 子弹处于活跃状态
        self.mask = pygame.mask.from_surface(self.image)  # 获取子弹的掩膜用于碰撞检测

    def move_left(self):
        """
        飞机向左移动
        """
        self.rect.left -= self.speed  # 向左移动
        if self.rect.right < 0:  # 如果子弹超出屏幕范围
            self.active = False  # 子弹不再活跃
