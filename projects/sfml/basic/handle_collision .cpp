#include "handle_collision.hpp"

namespace game
{

// HandleCollision(Ball& a_ball, std::vector<Brick> * a_bricks);
bool HandleCollision::isCollisionWithBrick(std::pair<size_t, size_t> a_coordinates)
{
    m_isCollision = true;
    std::for_each()
}
// bool isCollisionWithOtherBall(std::pair<size_t, size_t> a_coordinates);
// bool isCollisionWithWall(std::pair<size_t, size_t> a_coordinates);
// bool isCollisionWithFloor(std::pair<size_t, size_t> a_coordinates);

} // namespace game

#endif HANDLE_COLLISION_HPP