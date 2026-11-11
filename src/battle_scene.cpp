#include "battle_scene.h"
#include "main_menu_scene.h"
#include "bn_keypad.h"
#include "bn_string.h"
#include "bn_math.h"

namespace
{
    constexpr bn::fixed STAGE_LEFT = -100;
    constexpr bn::fixed STAGE_RIGHT = 100;
    constexpr bn::fixed GROUND_Y = 40;
    constexpr int LIGHT_DAMAGE = 8;
    constexpr int MEDIUM_DAMAGE = 12;
    constexpr int HEAVY_DAMAGE = 18;
    constexpr int ATTACK_DURATION = 20;
}

battle_scene::battle_scene(scene_manager& manager, const bn::array<int, 3>& team, int mode) :
    _manager(manager),
    _mode(mode),
    _p1_team(team),
    _text_generator(bn::sprite_font::default_font())
{
    // Phase 1 characters
    const char* names[] = { "RYU", "SPIDER-MAN" };

    _p1.name = names[bn::max(0, bn::min(1, team[0]))];
    _p1.x = -50;
    _p1.y = GROUND_Y;
    _p1.health = 100;
    _p1.max_health = 100;
    _p1.facing_right = true;
    _p1.state = 0;
    _p1.state_timer = 0;
    _p1.attack_type = 0;

    _p2.name = "CPU";
    _p2.x = 50;
    _p2.y = GROUND_Y;
    _p2.health = 100;
    _p2.max_health = 100;
    _p2.facing_right = false;
    _p2.state = 0;
    _p2.state_timer = 0;
    _p2.attack_type = 0;

    draw_hud();
}

void battle_scene::draw_hud()
{
    _text_sprites.clear();

    // Health bars (text approximation)
    bn::string<48> p1_hp = bn::string<16>(_p1.name) + " HP:" + bn::to_string<8>(_p1.health);
    _text_generator.generate(-80, -70, p1_hp, _text_sprites);

    bn::string<48> p2_hp = "HP:" + bn::to_string<8>(_p2.health) + " " + bn::string<16>(_p2.name);
    _text_generator.generate(40, -70, p2_hp, _text_sprites);

    // Timer
    int secs = _timer / 60;
    bn::string<8> timer_str = bn::to_string<4>(secs);
    _text_generator.generate(0, -70, timer_str, _text_sprites);

    // Combo
    if(_combo > 1)
    {
        bn::string<16> combo_str = bn::to_string<4>(_combo) + " HIT!";
        _text_generator.generate(0, -50, combo_str, _text_sprites);
    }

    // Positions (simple representation)
    bn::string<24> p1_pos = "P1";
    _text_generator.generate(_p1.x.integer(), _p1.y.integer() - 20, p1_pos, _text_sprites);

    bn::string<24> p2_pos = "P2";
    _text_generator.generate(_p2.x.integer(), _p2.y.integer() - 20, p2_pos, _text_sprites);

    // Controls hint
    bn::string<40> hint = "A=Light B=Med L=Heavy START=Pause";
    _text_generator.generate(0, 70, hint, _text_sprites);
}

void battle_scene::update_player()
{
    if(_p1.state == 4) return; // KO

    if(_p1.state == 2) // attacking
    {
        _p1.state_timer--;
        if(_p1.state_timer <= 0)
        {
            _p1.state = 0;
            _p1.attack_type = 0;
        }
        return;
    }

    if(_p1.state == 3) // hitstun
    {
        _p1.state_timer--;
        if(_p1.state_timer <= 0)
        {
            _p1.state = 0;
        }
        return;
    }

    // Movement
    bn::fixed speed = 1.5;
    if(bn::keypad::left_held())
    {
        _p1.x -= speed;
        _p1.facing_right = false;
        _p1.state = 1;
    }
    else if(bn::keypad::right_held())
    {
        _p1.x += speed;
        _p1.facing_right = true;
        _p1.state = 1;
    }
    else
    {
        _p1.state = 0;
    }

    // Clamp
    if(_p1.x < STAGE_LEFT) _p1.x = STAGE_LEFT;
    if(_p1.x > STAGE_RIGHT) _p1.x = STAGE_RIGHT;

    // Attacks
    if(bn::keypad::a_pressed())
    {
        _p1.state = 2;
        _p1.state_timer = ATTACK_DURATION;
        _p1.attack_type = 1; // light
    }
    else if(bn::keypad::b_pressed())
    {
        _p1.state = 2;
        _p1.state_timer = ATTACK_DURATION + 5;
        _p1.attack_type = 2; // medium
    }
    else if(bn::keypad::l_pressed())
    {
        _p1.state = 2;
        _p1.state_timer = ATTACK_DURATION + 10;
        _p1.attack_type = 3; // heavy
    }
}

void battle_scene::update_cpu()
{
    if(_p2.state == 4) return;

    if(_p2.state == 2 || _p2.state == 3)
    {
        _p2.state_timer--;
        if(_p2.state_timer <= 0)
        {
            _p2.state = 0;
            _p2.attack_type = 0;
        }
        return;
    }

    // Very simple AI: approach and occasionally attack
    bn::fixed dx = _p1.x - _p2.x;
    if(bn::abs(dx) > 30)
    {
        if(dx > 0)
        {
            _p2.x += 1.0;
            _p2.facing_right = true;
        }
        else
        {
            _p2.x -= 1.0;
            _p2.facing_right = false;
        }
        _p2.state = 1;
    }
    else
    {
        _p2.state = 0;
        // Random-ish attack (use frame counter for variety)
        if((_timer % 90) == 0)
        {
            _p2.state = 2;
            _p2.state_timer = ATTACK_DURATION;
            _p2.attack_type = 1 + (_timer % 3);
        }
    }

    if(_p2.x < STAGE_LEFT) _p2.x = STAGE_LEFT;
    if(_p2.x > STAGE_RIGHT) _p2.x = STAGE_RIGHT;
}

void battle_scene::check_hits()
{
    bn::fixed dist = bn::abs(_p1.x - _p2.x);

    // P1 hits P2
    if(_p1.state == 2 && _p1.state_timer > ATTACK_DURATION - 8 && dist < 25)
    {
        if(_p2.state != 3 && _p2.state != 4)
        {
            int dmg = LIGHT_DAMAGE;
            if(_p1.attack_type == 2) dmg = MEDIUM_DAMAGE;
            if(_p1.attack_type == 3) dmg = HEAVY_DAMAGE;

            _p2.health -= dmg;
            if(_p2.health < 0) _p2.health = 0;
            _p2.state = 3;
            _p2.state_timer = 15;
            _combo++;

            if(_p2.health <= 0)
            {
                _p2.state = 4;
            }
        }
    }

    // P2 hits P1
    if(_p2.state == 2 && _p2.state_timer > ATTACK_DURATION - 8 && dist < 25)
    {
        if(_p1.state != 3 && _p1.state != 4)
        {
            int dmg = LIGHT_DAMAGE;
            if(_p2.attack_type == 2) dmg = MEDIUM_DAMAGE;
            if(_p2.attack_type == 3) dmg = HEAVY_DAMAGE;

            _p1.health -= dmg;
            if(_p1.health < 0) _p1.health = 0;
            _p1.state = 3;
            _p1.state_timer = 15;
            _combo = 0;

            if(_p1.health <= 0)
            {
                _p1.state = 4;
            }
        }
    }
}

void battle_scene::update()
{
    if(bn::keypad::start_pressed())
    {
        _paused = !_paused;
    }

    if(_paused)
    {
        // Simple pause - could show pause menu later
        return;
    }

    if(_timer > 0)
    {
        _timer--;
    }

    update_player();
    update_cpu();
    check_hits();
    draw_hud();

    // Win / lose / time up
    if(_p1.health <= 0 || _p2.health <= 0 || _timer <= 0)
    {
        // For Phase 1 just return to menu after a short delay could be added
        // For now, press SELECT to go back
        if(bn::keypad::select_pressed())
        {
            _manager.set_scene(bn::make_unique<main_menu_scene>(_manager));
        }
    }
}
