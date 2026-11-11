#include "bn_core.h"
#include "bn_keypad.h"
#include "game/fighter.hpp"

// Phase 1 logic harness. Rendering is deliberately isolated from combat state;
// original sprite sheets and tile assets will replace the temporary display layer.
namespace {
game::Fighter player;
game::Fighter cpu;
bool paused = false;
int frame = 0;

game::Input read_player_input() {
    return {
        bn::keypad::left_held(), bn::keypad::right_held(),
        bn::keypad::up_pressed(), bn::keypad::down_held(),
        bn::keypad::a_pressed(), bn::keypad::b_pressed(),
        bn::keypad::l_held(), bn::keypad::r_pressed()
    };
}

void update_game() {
    if(bn::keypad::start_pressed()) paused = ! paused;
    if(paused) return;

    game::Input p = read_player_input();
    game::Input c = {};
    // Simple deterministic CPU: approaches and attacks at close range.
    c.left = cpu.x > player.x + 28;
    c.right = cpu.x < player.x - 28;
    c.light = (++frame % 45 == 0);
    c.guard = (frame % 90 < 18);

    game::update_fighter(player, cpu, p);
    game::update_fighter(cpu, player, c);

    if(player.health == 0 || cpu.health == 0) {
        // Press A to restart the test round.
        if(bn::keypad::a_pressed()) {
            game::reset_fighter(player, 62, 1);
            game::reset_fighter(cpu, 178, -1);
        }
    }
}
}

int main() {
    bn::core::init();
    game::reset_fighter(player, 62, 1);
    game::reset_fighter(cpu, 178, -1);

    while(true) {
        update_game();
        bn::core::update();
    }
}
