#include "raylib.h"
#include<iostream>
#include<deque>

Color green={173 , 204 , 96 , 255};
Color darkgreen={43 , 51 , 24, 255};
using namespace std;
int cellSize=30;
int cellCount=25;

class Food{
  public:
  Vector2 position;
  Texture2D texture;
  Food()
  {
    // Image is type of data structure in raylib that contains the pixels data of the graphical image 
    Image image= LoadImage("Graphics/Images.jpg");
    ImageResize(&image, cellSize, cellSize); // I resizes it before converting it to the window
    texture =LoadTextureFromImage(image); // Image loaded into gpu so that i could be diapled on screen 
    UnloadImage(image); 
    position=GetRandomPosition();
  }
  ~Food()
  {
    UnloadTexture(texture);
  }
  
  void draw()
  {
    // DrawRectangle(position.x * cellSize , position.y * cellSize , cellSize , cellSize ,WHITE);
    DrawTexture(texture , position.x * cellSize , position.y * cellSize , WHITE);
  }
  Vector2 GetRandomPosition()
  {
    float x=GetRandomValue(0 , cellCount-1);
    float y=GetRandomValue(0 , cellCount-1);
    return Vector2{x , y};
  }
  
};

class snake{
  public:
  deque<Vector2> body={Vector2{6, 9} , Vector2{5 , 9} , Vector2{4 , 9}};

  void draw()
  {
   for(int i=0; i<body.size(); i++)
   {
    float x=body[i].x;
    float y=body[i].y;
    DrawRectangle(x*cellCount , y*cellCount , cellSize , cellSize,darkgreen);
   }
  }
};
int main()
{
    int screen_wdith=750; int screen_height=750;
    SetTargetFPS(60);
  InitWindow(cellSize * cellCount , cellSize *cellCount , "My snake game");

  Food food;
  snake Snake;
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(green);
    food.draw();
    Snake.draw();
    EndDrawing();
  }
  
  CloseWindow();

    return 0;
}