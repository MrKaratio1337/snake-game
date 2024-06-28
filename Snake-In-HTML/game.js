const canvas = document.getElementById('gameCanvas');
const ctx = canvas.getContext('2d');
const scoreDisplay = document.getElementById('score');
const gameOverDisplay = document.getElementById('gameOver');

const unitSize = 25;
const canvasWidth = 600;
const canvasHeight = 600;
canvas.width = canvasWidth;
canvas.height = canvasHeight;

let snake = [
    { x: 5 * unitSize, y: 5 * unitSize},
    { x: 4 * unitSize, y: 5 * unitSize},
    { x: 3 * unitSize, y: 5 * unitSize},
];

let direction = { x: 1, y: 0};
let apple = { x: getRandomInt(0, canvasWidth / unitSize) * unitSize, y: getRandomInt(0, canvasHeight / unitSize) * unitSize};
let score = 0;
let running = true;

document.addEventListener('keydown', changeDirection);
setInterval(updateGame, 100);

function updateGame(){
    if(!running) return;

    clearCanvas();
    drawApple();
    moveSnake();
    drawSnake();
    checkCollision();
}

function clearCanvas(){
    ctx.fillStyle = 'black';
    ctx.fillRect(0, 0, canvasWidth, canvasHeight);
}

function drawApple(){
    ctx.fillStyle = 'red';
    ctx.fillRect(apple.x, apple.y, unitSize, unitSize);
}

function moveSnake(){
    const head = { x: snake[0].x + direction.x * unitSize, y: snake[0].y + direction.y * unitSize};
    snake.unshift(head);

    if(head.x === apple.x && head.y === apple.y){
        score++;
        scoreDisplay.innerText = `Score: ${score}`;
        apple = { x: getRandomInt(0, canvasWidth / unitSize) * unitSize, y: getRandomInt(0, canvasHeight / unitSize) * unitSize};
    } else{
        snake.pop();
    }
}

function drawSnake(){
    ctx.fillStyle = 'green';
    for(let segment of snake){
        ctx.fillRect(segment.x, segment.y, unitSize, unitSize);
    }
}

function changeDirection(event){
    const keyPressed = event.key;
    const goingUp = direction.y === -1;
    const goingDown = direction.y === 1;
    const goingRight = direction.x === 1;
    const goingLeft = direction.x === -1;

    switch(keyPressed){
        case 'ArrowUp':
            if(!goingDown){
                direction = { x: 0, y: -1};
            }
            break;
        case 'ArrowDown':
            if(!goingUp){
                direction = { x: 0, y: 1};
            }
            break;
        case 'ArrowLeft':
            if(!goingRight){
                direction = { x: -1, y: 0};
            }
            break;
        case 'ArrowRight':
            if(!goingLeft){
                direction = { x: 1, y: 0};
            }
            break;
    }
}

function checkCollision(){
    const head = snake[0];

    if(head.x < 0 || head.x >= canvasWidth || head.y < 0 || head.y >= canvasHeight){
        endGame();
    }

    for(let i = 1; i < snake.length; i++){
        if(head.x === snake[i].x && head.y === snake[i].y){
            endGame();
        }
    }
}

function endGame(){
    running = false;
    gameOverDisplay.style.display = 'block';
}

function getRandomInt(min, max){
    return Math.floor(Math.random() * (max - min) + min);
}