#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

// Code for a "breakout" game
// Final Project for Modern C++ Course
// Uses the SFML graphics library

struct constants {
	static constexpr int window_width{ 520 };
	static constexpr int window_height{ 450 };
	static constexpr float ball_speed{ 6.0f };
	static constexpr float paddle_speed{ 8.0f };
	static constexpr float paddle_width{ 60.0f };
	static constexpr float paddle_height{ 20.0f };
	static constexpr float no_speed{ 0.0f };
	static constexpr float brick_width{ 43.0f };
	static constexpr float brick_height{ 20.0f };
	static constexpr float brick_offset{ brick_width/2.0f };
	static constexpr int brick_collumns{ 10 };
	static constexpr int brick_rows{ 4 };

};

#endif // CONSTANTS_H
