#include "collisions.h"
#include "brick.h"

bool is_interacting(const entity& e1, const entity& e2){
    auto box1 = e1.get_bounding_box(); 
    auto box2 = e2.get_bounding_box();
    return box1.intersects(box2);
}

void handle_collision(ball& b, const paddle& p){
    if (is_interacting(b, p)) {
        //make the ball bounce upwards
        b.move_up();

        //make the direction depend on where the collision occurs on the paddle
        if (b.x() < p.x())
            b.move_left();
        else b.move_right();
    }
}

void handle_collision(ball& ball, brick& block){
    if (is_interacting(block, ball)) {
        //The brick is destroyed
        block.destroy();

        //Make the new direction depend on the collision of the brick

        //First find the amount of overlap in each direction
        //The smaller the left overlap, the closer the ball is to the left side of the brick
        float left_overlap = ball.right() - block.left();
        float right_overlap = block.right() - ball.left();
        float top_overlap = ball.bottom() - block.top();
        float bottom_overlap = ball.top() - block.bottom();

        //If the right overlap is smaller than the left overlap, the ball hit the right side and viceversa
        //Same for top and bottom
        bool from_left = std::abs(left_overlap) < std::abs(right_overlap);
        bool from_top = std::abs(top_overlap) < std::abs(bottom_overlap);

        //Use the right or left overlap as appropriate
        float min_x_overlap = from_left ? left_overlap : right_overlap;
        float min_y_overlap = from_top ? top_overlap : bottom_overlap;

        //Change direction according to overlap
        if (std::abs(min_x_overlap) < std::abs(min_y_overlap)) {
            if (from_left)
                ball.move_left();
            else
                ball.move_right();
        }
        else{
            if (from_top)
                ball.move_up();
            else
                ball.move_down();
        }
    }
}
