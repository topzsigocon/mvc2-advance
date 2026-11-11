#pragma once
#include <cstdint>

namespace game {

enum class FighterState : uint8_t { idle, walking, jumping, crouching, guarding, attacking, hitstun, knocked_out };

struct Fighter {
    int x;
    int y;
    int vx;
    int vy;
    int health;
    int facing;       // -1 = left, +1 = right
    int attack_timer;
    int hitstun_timer;
    FighterState state;
    bool on_ground;
};

struct Input {
    bool left, right, up, down;
    bool light, heavy, guard, special;
};

void reset_fighter(Fighter& fighter, int x, int facing);
void update_fighter(Fighter& self, Fighter& opponent, const Input& input);
bool overlaps(const Fighter& a, const Fighter& b);

}
