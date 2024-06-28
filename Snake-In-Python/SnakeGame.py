import pygame
import random
import sys

pygame.init()

SCREEN_WIDTH = 600
SCREEN_HEIGHT = 600
UNIT_SIZE = 25
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption('Snake Game')

BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)

font = pygame.font.SysFont('arial', 24)
game_over_font = pygame.font.SysFont('arial', 50)

class SnakeGame:
    def __init__(self):
        self.reset()
    
    def reset(self):
        self.snake = [{'x': 5 * UNIT_SIZE, 'y': 5 * UNIT_SIZE},
        {'x': 4 * UNIT_SIZE, 'y': 5 * UNIT_SIZE},
        {'x': 3 * UNIT_SIZE, 'y': 5 * UNIT_SIZE}]
        self.direction = 'RIGHT'
        self.score = 0
        self.running = True
        self.spawn_apple()
    
    def spawn_apple(self){
        self.apple = {'x': random.randint(0, (SCREEN_WIDTH // UNIT_SIZE) - 1) * UNIT_SIZE, 'y': random.randint(0, (SCREEN_HEIGHT // UNIT_SIZE) - 1) * UNIT_SIZE}
    }

    def move_snake(self):
        if not self.running:
            return
        
        head = self.snake[0].copy()

        if self.direction == 'UP':
            head['y'] -= UNIT_SIZE
        elif self.direction == 'DOWN':
            head['y'] += UNIT_SIZE
        elif self.direction == 'LEFT':
            head['x'] -= UNIT_SIZE
        elif self.direction == 'RIGHT':
            head['x'] += UNIT_SIZE
        
        self.snake.insert(0, head)

        if head['x'] == self.apple['x'] and head['y'] == self.apple['y']:
            self.score += 1
            self.spawn_apple()
        else:
            self.snake.pop()
    
    def check_collisions(self):
        head = self.snake[0]

        if head['x'] < 0 or head['x'] >= SCREEN_WIDTH or head['y'] < 0 or head['y'] >= SCREEN_WIDTH:
            self.running = False
        
        for segment in self.snake[1:]:
            if head['x'] == segment['x'] and head['y'] == segment['y']:
                self.running = False
    
    def change_direction(self, new_direction):
        if new_direction == 'UP' and self.direction != 'DOWN':
            self.direction = new_direction
        if new_direction == 'DOWN' and self.direction != 'UP':
            self.direction = new_direction
        if new_direction == 'LEFT' and self.direction != 'RIGHT':
            self.direction = new_direction
        if new_direction == 'RIGHT' and self.direction != 'LEFT':
            self.direction = new_direction
    
    def draw_elements(self):
        screen.fill(BLACK)

        for segment in self.snake:
            pygame.draw.rect(screen, GREEN, (segment['x'], segment['y'], UNIT_SIZE, UNIT_SIZE))

            pygame.draw.rect(screen, RED, (self.apple['x'], self.apple['y'], UNIT_SIZE, UNIT_SIZE))

            score_text = font.render(f'Score: {self.score}', True, WHITE)
            screen.blit(score_text, (10, 10))

            if not self.running:
                game_over_text = game_over_font.render('Game Over!', True, RED)

                screen.blit(game_over_text, ((SCREEN_WIDTH - game_over_text.get_width()) // 2, SCREEN_HEIGHT // 2))

    def run(self):
        clock = pygame.time.clock()

        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()
                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_UP:
                        self.change_direction('UP')
                    elif event.key == pygame.K_DOWN:
                        self.change_direction('DOWN')
                    elif event.key == pygame.K_LEFT:
                        self.change_direction('LEFT')
                    elif event.key == pygame.K_RIGHT:
                        self.change_direction('RIGHT')
                if self.running:
                    self.move_snake()

self.check_collisions()

self.draw_elements()
pygame.display.flip()
clock.tick(10)

if __name == "__main__":
    game = SnakeGame()
    game.run()