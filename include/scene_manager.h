#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "bn_unique_ptr.h"
#include "bn_optional.h"

class scene
{
public:
    virtual ~scene() = default;
    virtual void update() = 0;
};

class scene_manager
{
public:
    void set_scene(bn::unique_ptr<scene> next)
    {
        _next_scene = bn::move(next);
    }

    void update()
    {
        if(_next_scene)
        {
            _current_scene = bn::move(_next_scene);
        }

        if(_current_scene)
        {
            _current_scene->update();
        }
    }

private:
    bn::unique_ptr<scene> _current_scene;
    bn::unique_ptr<scene> _next_scene;
};

#endif
