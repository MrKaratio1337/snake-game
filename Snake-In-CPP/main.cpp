#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const int UNIT_SIZE = 25;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class SnakeGame{
public:
    SnakeGame();
    void run();

private:
    void handleInput();
    void update();
    void render();
    void reset();
    void checkCollisions();
    void spawnApple();
    bool isRunning() const;

    sf::RenderWindow window;
    sf::RectangleShape snakeShape;
    sf::RectangleShape appleShape;
    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;

    std::vector<SnakeSegment> snake;
    Direction direction;
    int score;
    int appleX, appleY;
    bool running;
};

SnameGame::SnakeGame()
    :
window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake Game"),
snakeShape(sf::Vector2f(UNIT_SIZE, UNIT_SIZE)),
appleShape(sf::Vector2f(UNIT_SIZE, UNIT_SIZE)),
direction(RIGHT),
score(0),
running(true){
    snakeShape.setFillColor(sf::color::Green);
    appleShape.setFillColor(sf::Color::Red);

    if(!font.loadFromFile("arial.ttf")){
        // handle error
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);

    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);

    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over!");

    gameOverText.setPosition((SCREEN_WIDTH - gameOverText.getLocalBounds().width) / 2, SCREEN_HEIGHT / 2);

    reset();
}

void SnakeGame::reset(){
    snake.clear();
    snake.push_back({5 * UNIT_SIZE, 5 * UNIT_SIZE});
    snake.push_back({4 * UNIT_SIZE, 5 * UNIT_SIZE});
    snake.push_back({3 * UNIT_SIZE, 5 * UNIT_SIZE});

    direction = RIGHT;
    score = 0;
    running = true;

    spawnApple();
}

void SnakeGame::spawnApple(){
    appleX = (std::rand() % (SCREEN_WIDTH / UNIT_SIZE)) * UNIT_SIZE;
    appleY = (std::rand() % (SCREEN_HEIGHT / UNIT_SIZE)) * UNIT_SIZE;   
}

void SnakeGame::run(){
    sf::Clock clock;
    sf::Time elapsedTime;

    while(window.isOpen()){
        handleInput();
        elapsedTime += clock.restart();
        if(elapsedTime.asMilliseconds() >= 100){
            update();
            elapsedTime = sf::Time::Zero;
        }
        render();
    }
}

void SnakeGame::handleInput(){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window.close();
        }

        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Up && direction != DOWN){
                direction = UP;
            } else if(event.key.code == sf::Keyboard::Down && direction != UP){
                direction = DOWN;
            } else if(event.key.code == sf::Keyboard::Left && direction != RIGHT){
                direction = LEFT;
            } else if(event.key.code == sf::Keyboard::Right && direction != LEFT){
                direction = RIGHT;
            }
        }
    }
}

void SnakeGame::update(){
    if(!running) return;

    SnakeSegment newHead = snake.front();

    switch(direction){
        case UP:
            newHead.y -= UNIT_SIZE;
            break;
        case DOWN:
            newHead.y += UNIT_SIZE;
            break;
        case LEFT:
            newHead.x -= UNIT_SIZE;
            break;
        case RIGHT:
            newHead.x += UNIT_SIZE;
            break;
    }

    snake.insert(snake.begin(), newHead);

    if(newHead.x == appleX && newHead.y == appleY){
        score++;
        spawnApple();
    } else{
        snake.pop_back();
    }

    checkCollisions();
}

void SnakeGame::checkCollisions(){
    SnakeSegment head = snake.front();

    iF(head.x < 0 || head.x >= SCREEN_WIDTH || head.y < 0 || head.y >= SCREEN_HEIGHT){
        running = false;
    }

    for(size_t i = 1; i < snake.size(); i++){
        if(head.x == snake[i].x && head.y == snake[i].y){
            running = false;
        }
    }

    if(!running){
        gameOverText.setString("Game Over! Score: " + std::to_string(score));
    }
}

void SnakeGame::render(){
    window.clear();

    for(const auto& segment : snake){
        snakeShape.setPosition(segment.x, segment.y);
        window.draw(snakeShape);
    }

    appleShape.setPosition(appleX, appleY);
    window.draw(appleShape);

    scoreText.setString("Score: " + std::to_string(score));
    window.draw(scoreText);

    if(!running) window.draw(gameOverText);

    window.display();
}

int main{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    SnakeGame game;
    game.run();

    return 0;
}