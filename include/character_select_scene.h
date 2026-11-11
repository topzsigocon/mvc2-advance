#ifndef CHARACTER_SELECT_SCENE_H
#define CHARACTER_SELECT_SCENE_H

#include "scene_manager.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"
#include "bn_string.h"
#include "bn_array.h"

class character_select_scene : public scene
{
public:
    character_select_scene(scene_manager& manager, int mode);

    void update() override;

private:
    scene_manager& _manager;
    int _mode; // 0=arcade, 1=versus, 2=training
    bn::sprite_text_generator _text_generator;
    bn::vector<bn::sprite_ptr, 48> _text_sprites;

    // Phase 1: only 2 characters
    static constexpr int CHAR_COUNT = 2;
    bn::array<bn::string_view, CHAR_COUNT> _char_names = {
        "RYU",
        "SPIDER-MAN"
    };

    int _cursor = 0;
    bn::array<int, 3> _team = {-1, -1, -1};
    int _team_slot = 0;
};

#endif
