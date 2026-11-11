#include "character_select_scene.h"
#include "battle_scene.h"
#include "bn_keypad.h"
#include "bn_string.h"

character_select_scene::character_select_scene(scene_manager& manager, int mode) :
    _manager(manager),
    _mode(mode),
    _text_generator(bn::sprite_font::default_font())
{
    _text_generator.set_center_alignment();
    refresh_ui();
}

void character_select_scene::refresh_ui()
{
    _text_sprites.clear();

    bn::string<32> title = "CHARACTER SELECT";
    _text_generator.generate(0, -60, title, _text_sprites);

    // Character list
    for(int i = 0; i < CHAR_COUNT; ++i)
    {
        bn::string<20> name = _char_names[i];
        if(i == _cursor)
        {
            name = "> " + name + " <";
        }
        _text_generator.generate(0, -30 + i * 14, name, _text_sprites);
    }

    // Team slots
    bn::string<40> team_line = "TEAM: ";
    for(int i = 0; i < 3; ++i)
    {
        if(_team[i] >= 0)
        {
            team_line += _char_names[_team[i]];
        }
        else
        {
            team_line += "---";
        }
        if(i < 2) team_line += " / ";
    }
    _text_generator.generate(0, 20, team_line, _text_sprites);

    bn::string<40> hint = "A: Pick  B: Back  START: Fight";
    _text_generator.generate(0, 50, hint, _text_sprites);
}

void character_select_scene::update()
{
    bool dirty = false;

    if(bn::keypad::up_pressed() || bn::keypad::left_pressed())
    {
        _cursor = (_cursor + CHAR_COUNT - 1) % CHAR_COUNT;
        dirty = true;
    }
    else if(bn::keypad::down_pressed() || bn::keypad::right_pressed())
    {
        _cursor = (_cursor + 1) % CHAR_COUNT;
        dirty = true;
    }

    if(bn::keypad::a_pressed())
    {
        if(_team_slot < 3)
        {
            _team[_team_slot] = _cursor;
            _team_slot++;
            dirty = true;
        }
    }

    if(bn::keypad::b_pressed())
    {
        if(_team_slot > 0)
        {
            _team_slot--;
            _team[_team_slot] = -1;
            dirty = true;
        }
    }

    if(bn::keypad::start_pressed() && _team_slot >= 1)
    {
        // Fill remaining slots with first character if needed (Phase 1)
        for(int i = _team_slot; i < 3; ++i)
        {
            _team[i] = 0;
        }
        _manager.set_scene(bn::make_unique<battle_scene>(_manager, _team, _mode));
        return;
    }

    if(dirty)
    {
        refresh_ui();
    }
}
