//
// Created by oyster on 24-10-10.
//

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.h"

extern Scene* menu_scene;
extern Scene* game_scene;

class SceneManager {
public:
    enum class SceneType {
        MenuMenu,
        GameScene,
    };

    SceneManager() = default;
    ~SceneManager() = default;

    void set_current_scene(Scene* scene) {
        current_scene = scene;
        current_scene->on_enter();
    }

    void switch_to(SceneType type) {
        current_scene->on_exit();
        switch (type) {
            case SceneType::MenuMenu:
                current_scene = menu_scene;
                break;
            case SceneType::GameScene:
                current_scene = game_scene;
                break;
            default:
                break;
        }
        current_scene->on_enter();
    }

    void on_input(const ExMessage& msg) {
        current_scene->on_input(msg);
    }

    void on_update(int delta) {
        current_scene->on_update(delta);
    }

    void on_draw() {
        current_scene->on_draw();
    }

private:
    Scene* current_scene = nullptr;
};



#endif //SCENEMANAGER_H
