#ifndef BATTLE_SCENE_H
#define BATTLE_SCENE_H

#include "scene_manager.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"
#include "bn_array.h"
#include "bn_fixed.h"
#include "bn_optional.h"

struct fighter
{
    bn::string_view name;
    bn::fixed x;
    bn::fixed y;
    int health;
    int max_health;
    bool facing_right;
    int state; // 0=idle, 1=walk, 2=attack, 3=hit, 4=ko
    int state_timer;
    int attack_type; // 0=none, 1=light, 2=medium, 3=heavy
};

class battle_scene : public scene
{
public:
    battle_scene(scene_manager& manager, const bn::array<int, 3>& team, int mode);

    void update() override;

private:
    void update_player();
    void update_cpu();
    void update_physics();
    void check_hits();
    void draw_hud();
    void reset_positions();

    scene_manager& _manager;
    int _mode;
    bn::array<int, 3> _p1_team;

    bn::sprite_text_generator _text_generator;
    bn::vector<bn::sprite_ptr, 64> _text_sprites;

    fighter _p1;
    fighter _p2;

    int _timer = 99 * 60; // ~99 seconds at 60fps
    int _combo = 0;
    bool _paused = false;
};

#endif
