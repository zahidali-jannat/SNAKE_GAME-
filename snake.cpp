#include "raylib.h"

#include<iostream>
Color green={173 , 204 , 96 , 255};
Color darkgreen={43 , 51 , 24, 255};
using namespace std;
int cellSize=30;
int cellCount=25;

class Food{
  public:
  Vector2 position={5 , 6};
  Texture2D texture;
  Food()
  {
    // Image is type of data structure in raylib that contains the pixels data of the graphical image 
    Image image= LoadImage("./Graphics/Images.jpg");
    texture =LoadTextureFromImage(image);
    UnloadImage(image); 
  }
  void draw()
  {
    DrawRectangle(position.x * cellSize , position.y * cellSize , cellSize , cellSize ,WHITE);
  }
};
Food food;
int main()
{
    int screen_wdith=750; int screen_height=750;
    SetTargetFPS(60);
  InitWindow(cellSize * cellCount , cellSize *cellCount , "My snake game");
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(green);
    food.draw();
    
    EndDrawing();
  }
  
  CloseWindow();

    return 0;
}