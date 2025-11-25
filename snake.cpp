#include "raylib.h"
#include <iostream>
#include <deque>
#include <raymath.h>

Color green = {173, 204, 96, 255};

Color darkgreen = {43, 51, 24, 255};

Color purple = {128, 0, 128, 255};
using namespace std;

int cellSize = 30;
int cellCount = 25;

double LastUpdateTime = 0;

bool a = false;
bool check = false;

bool ElementInDeque(Vector2 element, deque<Vector2> dq)
{
  for (int i; i < dq.size(); i++)
  {
    if (Vector2Equals(dq[i], element))
      return true;
  }
  return false;
}

bool eventTriggered(double interval)
{
  double CURRENT_TIME = GetTime(); // get the current time with this function
  if (CURRENT_TIME - LastUpdateTime >= interval)
  {
    LastUpdateTime = CURRENT_TIME;
    return true;
  }
  return false;
}

class Food
{
public:
  Vector2 position;
  Texture2D texture;
  Food(deque<Vector2> dq)
  {
    // Image is type of data structure in raylib that contains the pixels data of the graphical image
    Image image = LoadImage("Graphics/Images.jpg");
    ImageResize(&image, cellSize, cellSize); // I resizes it before converting it to the window
    texture = LoadTextureFromImage(image);   // Image loaded into gpu so that i could be diapled on screen
    UnloadImage(image);
    position = Generation_of_random_position(dq);
  }
  ~Food()
  {
    UnloadTexture(texture);
  }

  void draw()
  {
    // DrawRectangle(position.x * cellSize , position.y * cellSize , cellSize , cellSize ,WHITE);
    DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
  }
  Vector2 GetRandomPosition()
  {
    float x = GetRandomValue(0, cellCount - 1);
    float y = GetRandomValue(0, cellCount - 1);

    return Vector2{x, y};
  }

  Vector2 Generation_of_random_position(deque<Vector2> SnakeBody)
  {
    Vector2 position = GetRandomPosition();

    while (ElementInDeque(position, SnakeBody))
    {
      position = GetRandomPosition();
    }
    return position;
  }
};

class snake
{
public:
  deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
  Vector2 direction = {1, 0};
  bool segment = false;
  void draw()
  {
    for (unsigned int i = 0; i < body.size(); i++)
    {
      float x = body[i].x;
      float y = body[i].y;
      Rectangle rec = Rectangle{x * cellSize, y * cellSize, (float)cellSize, (float)cellSize};
      /*
      We have given struct Rectangle rec and pass it through DrawRectangleRounded(rec,0.5,6,darkgreen);
      */
      DrawRectangleRounded(rec, 0.5, 6, darkgreen);
    }
  }

  void update()
  {
    body.push_front(Vector2Add(body[0], direction));
    if (segment)
    {
      segment = false;
    }
    else
    {
      body.pop_back();
      
    }
    // check whther snake head touches the end of the window
  }

  void RESET()
  {
    body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    direction={1,0};
  }
};

class Game
{

public:
  snake Snake = snake();
  Food food = Food(Snake.body);

  // create a draw function into it
  bool running=true;

  void Draw()
  {
    food.draw();
    Snake.draw();
  }

  void update()
  {
    if(running)
    {
      Snake.update();
    Check_Collision_with_edges();
    checkCollision();
    }
   
    
  }

  // void randomposition()
  // {
  //   if (Snake.body[0] == food.position)
  //   {
  //     // increase the size of the snake

  //     Snake.body.push_front(Vector2Add(food.position, Snake.direction)); // idhar aapka Sequence matter krta hai why check it why
  //     food.position = food.Generation_of_random_position(Snake.body);
  //   }
  // }
  void checkCollision()
  {
    if (Vector2Equals(Snake.body[0], food.position))
    {
      food.position = food.Generation_of_random_position(Snake.body);
      Snake.segment = true;
    }
  }
  
  void Check_Collision_with_edges(){
     if(Snake.body[0].x==cellCount || Snake.body[0].x==-1){
      GameOver();
     }
     if(Snake.body[0].y==cellCount || Snake.body[0].y==-1)
     {
      GameOver();
     }
  }
  void GameOver()
  {
    Snake.RESET();
    food.position=food.Generation_of_random_position(Snake.body);
    running=false;
  }
};

int main()
{

  int screen_wdith = 750;
  int screen_height = 750;
  SetTargetFPS(60);
  InitWindow(cellSize * cellCount, cellSize * cellCount, "My snake game");

  // Food food=Food();
  // snake Snake=snake();
  Game game = Game();
  while (!WindowShouldClose())
  {
    BeginDrawing();
    if (a)
    {
      CloseWindow();
    }
    if (eventTriggered(0.1))
    {

      game.update();
    }
    if (IsKeyPressed(KEY_UP) && game.Snake.direction.y != 1)
    {
       game.Snake.direction = {0, -1}; game.running=true;
    }
     
    if (IsKeyPressed(KEY_DOWN) && game.Snake.direction.y != -1)
      {game.Snake.direction = {0, 1};game.running=true;}
    if (IsKeyPressed(KEY_RIGHT) && game.Snake.direction.x != -1)
     { game.Snake.direction = {1, 0};game.running=true;}
    if (IsKeyPressed(KEY_LEFT) && game.Snake.direction.x != 1)
     { game.Snake.direction = {-1, 0};game.running=true;}

    ClearBackground(purple);
    if (game.Snake.body[0] == game.food.position)
    {
      check = true;
    }
    DrawText("SZALI", 5, 20, 40, BLACK);
    
    game.food.draw();
    game.Snake.draw();
    // game.randomposition();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}