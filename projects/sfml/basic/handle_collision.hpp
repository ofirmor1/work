#ifndef HANDLE_COLLISION_HPP
#define HANDLE_COLLISION_HPP

#include <vector>
#include <thread>
#include <algorithm>
#include "ball.hpp"
#include "brick.hpp"

namespace game
{

class HandleCollision
{

public:
    HandleCollision(Ball& a_ball, std::vector<Brick>    * a_bricks);
    bool isCollisionWithBrick(std::pair<size_t, size_t> a_coordinates);
    bool isCollisionWithOtherBall(std::pair<size_t, size_t> a_coordinates);
    bool isCollisionWithWall(std::pair<size_t, size_t> a_coordinates);
    bool isCollisionWithFloor(std::pair<size_t, size_t> a_coordinates);
private:
    size_t m_brickCollisions;
    bool m_isCollision;

};

HandleCollision::HandleCollision(Ball& a_ball, std::vector<Brick> * a_bricks)
{
}


} // namespace game

#endif HANDLE_COLLISION_HPP