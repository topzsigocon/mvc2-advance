#ifndef MAIN_MENU_SCENE_H
#define MAIN_MENU_SCENE_H

#include "scene_manager.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"
#include "bn_string.h"
#include "bn_keypad.h"
#include "bn_core.h"

class main_menu_scene : public scene
{
public:
    explicit main_menu_scene(scene_manager& manager);

    void update() override;

private:
    scene_manager& _manager;
    bn::sprite_text_generator _text_generator;
    bn::vector<bn::sprite_ptr, 32> _text_sprites;
    int _selected = 0;
    static constexpr int OPTION_COUNT = 3;
};

#endif
