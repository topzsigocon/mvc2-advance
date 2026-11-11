#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_text_generator.h"
#include "bn_string.h"
#include "bn_vector.h"
#include "bn_optional.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_palettes.h"
#include "bn_memory.h"

#include "scene_manager.h"
#include "main_menu_scene.h"
#include "character_select_scene.h"
#include "battle_scene.h"

int main()
{
    bn::core::init();

    // Basic palette setup for text / UI
    bn::bg_palettes::set_transparent_color(bn::color(0, 0, 0));
    bn::sprite_palettes::set_transparent_color(bn::color(0, 0, 0));

    scene_manager manager;

    // Start at main menu
    // Note: For a real build, copy a font from Butano examples/common
    // and replace the text_generator constructors with a proper font item.
    manager.set_scene(bn::make_unique<main_menu_scene>(manager));

    while(true)
    {
        manager.update();
        bn::core::update();
    }
}
