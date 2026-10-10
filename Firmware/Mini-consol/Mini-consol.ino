#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int btnUp = 4;
const int btnDown = 5;
const int btnLeft = 6;
const int btnRight = 7;
const int btnA = 8;
const int btnB = 9;
const int buzzerPin = 2;

int gameState = 0;
int menuSelection = 0;

float birdY = 32;
float birdVelocity = 0;
float gravity = 0.6;
float jumpForce = -4.5;
int pipeX = 128;
int pipeGap = 26;
int pipeY = 20;
int pipeWidth = 14;
int score = 0;

int snakeX[100];
int snakeY[100];
int snakeLength = 3;
int dirX = 1;
int dirY = 0;
int fruitX = 40;
int fruitY = 40;
unsigned long lastSnakeMove = 0;
int snakeSpeed = 120;

int soundEnabled = 1;

void setup() {
  pinMode(btnUp, INPUT_PULLUP);
  pinMode(btnDown, INPUT_PULLUP);
  pinMode(btnLeft, INPUT_PULLUP);
  pinMode(btnRight, INPUT_PULLUP);
  pinMode(btnA, INPUT_PULLUP);
  pinMode(btnB, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  Wire.begin(8, 10);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  if (gameState == 0) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(30, 5);
    display.print("MINI CONSOLE");

    display.setCursor(10, 25);
    display.print(menuSelection == 0 ? "> Flappy Bird" : "  Flappy Bird");

    display.setCursor(10, 40);
    display.print(menuSelection == 1 ? "> Snake" : "  Snake");

    display.setCursor(10, 55);
    display.print(menuSelection == 2 ? "> Settings" : "  Settings");

    display.display();

    if (digitalRead(btnUp) == LOW) {
      menuSelection--;
      if (menuSelection < 0) menuSelection = 2;
      delay(200);
    }
    if (digitalRead(btnDown) == LOW) {
      menuSelection++;
      if (menuSelection > 2) menuSelection = 0;
      delay(200);
    }
    if (digitalRead(btnA) == LOW) {
      if (menuSelection == 0) {
        gameState = 1;
        resetFlappy();
      } else if (menuSelection == 1) {
        gameState = 2;
        resetSnake();
      } else if (menuSelection == 2) {
        gameState = 3;
      }
      delay(200);
    }
  } else if (gameState == 1) {
    if (digitalRead(btnA) == LOW || digitalRead(btnUp) == LOW) {
      birdVelocity = jumpForce;
      if (soundEnabled) tone(buzzerPin, 800, 50);
    }

    birdVelocity += gravity;
    birdY += birdVelocity;

    pipeX -= 2;
    if (pipeX < -pipeWidth) {
      pipeX = 128;
      pipeY = random(10, 35);
      score++;
    }

    if (birdY > 64 || birdY < 0 || (pipeX < 30 && pipeX > 10 && (birdY < pipeY || birdY > pipeY + pipeGap))) {
      if (soundEnabled) {
        tone(buzzerPin, 200, 200);
      }
      gameState = 0;
      delay(500);
    }

    display.clearDisplay();
    display.fillRect(15, (int)birdY, 6, 6, SSD1306_WHITE);
    display.fillRect(pipeX, 0, pipeWidth, pipeY, SSD1306_WHITE);
    display.fillRect(pipeX, pipeY + pipeGap, pipeWidth, 64 - (pipeY + pipeGap), SSD1306_WHITE);

    display.setCursor(2, 2);
    display.print(score);
    display.display();
    delay(30);

  } else if (gameState == 2) {
    if (digitalRead(btnUp) == LOW && dirY == 0) { dirX = 0; dirY = -1; }
    if (digitalRead(btnDown) == LOW && dirY == 0) { dirX = 0; dirY = 1; }
    if (digitalRead(btnLeft) == LOW && dirX == 0) { dirX = -1; dirY = 0; }
    if (digitalRead(btnRight) == LOW && dirX == 0) { dirX = 1; dirY = 0; }

    if (millis() - lastSnakeMove > snakeSpeed) {
      lastSnakeMove = millis();
      for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
      }
      snakeX[0] += dirX * 4;
      snakeY[0] += dirY * 4;

      if (snakeX[0] < 0 || snakeX[0] >= 128 || snakeY[0] < 0 || snakeY[0] >= 64) {
        if (soundEnabled) tone(buzzerPin, 150, 300);
        gameState = 0;
        delay(500);
      }

      for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
          if (soundEnabled) tone(buzzerPin, 150, 300);
          gameState = 0;
          delay(500);
        }
      }

      if (abs(snakeX[0] - fruitX) < 4 && abs(snakeY[0] - fruitY) < 4) {
        snakeLength++;
        if (snakeLength > 95) snakeLength = 95;
        fruitX = (random(4, 30) * 4);
        fruitY = (random(4, 14) * 4);
        if (soundEnabled) tone(buzzerPin, 1200, 50);
      }
    }

    display.clearDisplay();
    display.fillRect(fruitX, fruitY, 3, 3, SSD1306_WHITE);
    for (int i = 0; i < snakeLength; i++) {
      display.fillRect(snakeX[i], snakeY[i], 3, 3, SSD1306_WHITE);
    }
    display.setCursor(2, 2);
    display.print(snakeLength - 3);
    display.display();
    delay(10);

  } else if (gameState == 3) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(20, 10);
    display.print("SETTINGS");

    display.setCursor(10, 30);
    display.print(soundEnabled ? "Sound: ON" : "Sound: OFF");

    display.setCursor(10, 50);
    display.print("Press B to Back");
    display.display();

    if (digitalRead(btnA) == LOW) {
      soundEnabled = !soundEnabled;
      delay(200);
    }
    if (digitalRead(btnB) == LOW) {
      gameState = 0;
      delay(200);
    }
  }
}

void resetFlappy() {
  birdY = 32;
  birdVelocity = 0;
  pipeX = 128;
  pipeY = 20;
  score = 0;
}

void resetSnake() {
  snakeLength = 3;
  snakeX[0] = 32;
  snakeY[0] = 32;
  snakeX[1] = 28;
  snakeY[1] = 32;
  snakeX[2] = 24;
  snakeY[2] = 32;
  dirX = 1;
  dirY = 0;
  fruitX = 64;
  fruitY = 32;
