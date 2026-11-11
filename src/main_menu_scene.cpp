#include "main_menu_scene.h"
#include "character_select_scene.h"
#include "bn_string.h"

main_menu_scene::main_menu_scene(scene_manager& manager) :
    _manager(manager),
    _text_generator(bn::sprite_font::default_font())  // Will use common font once available
{
    _text_generator.set_center_alignment();
    _text_sprites.clear();

    // Title
    bn::string<32> title = "MARVEL VS CAPCOM 2";
    _text_generator.generate(0, -50, title, _text_sprites);

    bn::string<32> subtitle = "GBA FAN EDITION";
    _text_generator.generate(0, -35, subtitle, _text_sprites);

    // Options
    const char* options[OPTION_COUNT] = {
        "ARCADE",
        "VERSUS",
        "TRAINING"
    };

    for(int i = 0; i < OPTION_COUNT; ++i)
    {
        bn::string<16> opt = options[i];
        int y = -5 + i * 16;
        _text_generator.generate(0, y, opt, _text_sprites);
    }

    bn::string<40> hint = "A: Select   START: Confirm";
    _text_generator.generate(0, 55, hint, _text_sprites);
}

void main_menu_scene::update()
{
    if(bn::keypad::up_pressed())
    {
        _selected = (_selected + OPTION_COUNT - 1) % OPTION_COUNT;
    }
    else if(bn::keypad::down_pressed())
    {
        _selected = (_selected + 1) % OPTION_COUNT;
    }

    if(bn::keypad::a_pressed() || bn::keypad::start_pressed())
    {
        // For Phase 1 go to character select for all modes
        _manager.set_scene(bn::make_unique<character_select_scene>(_manager, _selected));
    }

    // Simple visual feedback could be added later (highlight selected)
}
