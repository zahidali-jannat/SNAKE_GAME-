#include "raylib.h"

#include<iostream>

using namespace std;

int main()
{
    int screen_wdith=1200; int screen_height=1000;
  InitWindow(screen_wdith , screen_height , "My snake game");
  while (!WindowShouldClose())
  {
    BeginDrawing();
    EndDrawing();
  }
  
  CloseWindow();

    return 0;
}