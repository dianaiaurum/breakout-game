#include "collisions.h"

<<<<<<< Updated upstream
bool is_interacting(const entity& e1, const entity& e2) {
    auto box1 = e1.get_bounding_box();
=======
bool is_interacting(const entity& e1, const entity& e2){
    auto box1 = e1.get_bounding_box(); 
>>>>>>> Stashed changes
    auto box2 = e2.get_bounding_box();
    return box1.intersects(box2);
}

<<<<<<< Updated upstream
void handle_collision(ball& b, const paddle& p) {
=======
void handle_collision(ball& b, const paddle& p){
>>>>>>> Stashed changes
    if (is_interacting(b, p)) {
        //make the ball bounce upwards
        b.move_up();

        //make the direction depend on where the collision occurs on the paddle
        if (b.x() < p.x())
            b.move_left();
        else b.move_right();
    }
}
