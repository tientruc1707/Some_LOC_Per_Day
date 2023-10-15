#pragma once
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600

#define KEY_LEFT 1 // 00000001
#define KEY_DOWN 2 // 00000010
#define KEY_RIGHT 4 // 00000100
#define KEY_UP 8 // 00001000

constexpr auto PLAYER_SPEED = 150;
constexpr auto timeToSpawn = 5.0f;