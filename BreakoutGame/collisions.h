#pragma once
#ifndef COLLISIONS_H
#include "ball.h"
#include "paddle.h"

//Determine if two entities overlap
bool is_interacting(const entity& e1, const entity& e2);

//Resolve potential collision between ball and paddle
void handle_collision(ball& b, const paddle& p);

#endif // !COLLISIONS_H
