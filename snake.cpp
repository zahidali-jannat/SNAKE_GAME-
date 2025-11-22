#include "raylib.h"
#include<iostream>
#include<deque>
#include<raymath.h>
Color green={173 , 204 , 96 , 255};
Color darkgreen={43 , 51 , 24, 255};
using namespace std;
int cellSize=30;
int cellCount=25;

double LastUpdateTime=0;


bool eventTriggered(double interval){
  double CURRENT_TIME=GetTime(); // get the current time with this function
  if(CURRENT_TIME-LastUpdateTime>=interval)
  { 
    LastUpdateTime=CURRENT_TIME; 
    return true; 
  }
  return false;
}

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
  Vector2 direction={1,0};
 
  void draw()
  {
   for(int i=0; i<body.size(); i++)
   {
    float x=body[i].x;
    float y=body[i].y;
    Rectangle rec=Rectangle{x*cellSize , y*cellSize , (float)cellSize, (float)cellSize}; 
    /*
    We have given struct Rectangle rec and pass it through DrawRectangleRounded(rec,0.5,6,darkgreen);
    */
    DrawRectangleRounded(rec,0.5,6,darkgreen);
   }
  }

  void update()
  {
    body.pop_back();
    
    body.push_front(Vector2Add(body[0] , direction));
     
    
    
  }
};
int main()
{
  int screen_wdith=750; int screen_height=750;
  SetTargetFPS(60);
  InitWindow(cellSize * cellCount , cellSize *cellCount , "My snake game");

  Food food=Food();
  snake Snake=snake();
  while (!WindowShouldClose())
  {
    BeginDrawing();
   
   if(eventTriggered(0.3)){
    Snake.update();
   }
   if(IsKeyPressed(KEY_UP)) Snake.direction={0 ,-1};
   if(IsKeyPressed(KEY_DOWN))Snake.direction={0, 1};
   if(IsKeyPressed(KEY_RIGHT)) Snake.direction={1 ,0};
   if(IsKeyPressed(KEY_LEFT)) Snake.direction={-1 , 0};
   if(Snake.body[0]==food.position) break; 
    ClearBackground(green);
    food.draw();
    Snake.draw();
    
    EndDrawing();
  }
  
  CloseWindow();

    return 0;
}