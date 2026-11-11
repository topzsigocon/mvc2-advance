#include "game/fighter.hpp"

namespace game {
namespace {
constexpr int FLOOR_Y = 132;
constexpr int GRAVITY = 1;
constexpr int MOVE_SPEED = 2;
constexpr int JUMP_SPEED = -10;
constexpr int BODY_W = 18;
constexpr int BODY_H = 30;
}

void reset_fighter(Fighter& f, int x, int facing) {
    f = { x, FLOOR_Y, 0, 0, 100, facing, 0, 0, FighterState::idle, true };
}

bool overlaps(const Fighter& a, const Fighter& b) {
    const int ax0 = a.x - BODY_W / 2, ax1 = a.x + BODY_W / 2;
    const int bx0 = b.x - BODY_W / 2, bx1 = b.x + BODY_W / 2;
    const int ay0 = a.y - BODY_H, ay1 = a.y;
    const int by0 = b.y - BODY_H, by1 = b.y;
    return ax0 < bx1 && ax1 > bx0 && ay0 < by1 && ay1 > by0;
}

void update_fighter(Fighter& f, Fighter& enemy, const Input& in) {
    if(f.health <= 0) { f.state = FighterState::knocked_out; return; }

    if(f.hitstun_timer > 0) {
        --f.hitstun_timer;
        f.x += f.vx;
        f.vx = (f.vx * 3) / 4;
        f.state = FighterState::hitstun;
    } else {
        f.facing = (enemy.x >= f.x) ? 1 : -1;
        if(f.attack_timer > 0) --f.attack_timer;

        if(in.guard && f.on_ground) {
            f.vx = 0;
            f.state = FighterState::guarding;
        } else if(in.down && f.on_ground) {
            f.vx = 0;
            f.state = FighterState::crouching;
        } else {
            f.vx = (in.right ? MOVE_SPEED : 0) - (in.left ? MOVE_SPEED : 0);
            if(f.vx) f.state = FighterState::walking;
            else if(f.on_ground && f.state != FighterState::attacking) f.state = FighterState::idle;
            if(in.up && f.on_ground) {
                f.vy = JUMP_SPEED;
                f.on_ground = false;
                f.state = FighterState::jumping;
            }
        }

        if((in.light || in.heavy || in.special) && f.attack_timer == 0) {
            f.attack_timer = in.special ? 32 : (in.heavy ? 22 : 12);
            f.state = FighterState::attacking;
            if(overlaps(f, enemy) && enemy.hitstun_timer == 0) {
                const int damage = in.special ? 18 : (in.heavy ? 12 : 6);
                if(enemy.state != FighterState::guarding) {
                    enemy.health -= damage;
                    if(enemy.health < 0) enemy.health = 0;
                    enemy.hitstun_timer = 12;
                    enemy.vx = f.facing * 3;
                    enemy.vy = -2;
                    enemy.on_ground = false;
                } else {
                    enemy.health -= damage / 4;
                    if(enemy.health < 0) enemy.health = 0;
                }
            }
        }
    }

    f.x += f.vx;
    if(! f.on_ground) {
        f.y += f.vy;
        f.vy += GRAVITY;
        if(f.y >= FLOOR_Y) {
            f.y = FLOOR_Y;
            f.vy = 0;
            f.on_ground = true;
            if(f.hitstun_timer == 0) f.state = FighterState::idle;
        }
    }
    if(f.x < 12) f.x = 12;
    if(f.x > 228) f.x = 228;
}
}
