#ifndef SCENECONTROLLER_H
#define SCENECONTROLLER_H

#include <map>
#include "Scene.h"

class SceneController
{
public:
    SceneController();
    virtual ~SceneController();
    void bindScene(const int index, Scene *scene);
    void setFirstScene(const int index);

    void act(int milliseconds);
    void render();
    void keyPressEvent(KeyState::Key key);
    void keyReleaseEvent(KeyState::Key key);
    void mousePressEvent(MouseState::Key key, int x, int y);
    void mouseReleaseEvent(MouseState::Key key, int x, int y);
    void mouseMoveEvent(int x, int y);

private:
    std::map<int, Scene*> _scenes;
    int _currentIndex;
    Scene* _currentScene;

    void setScene(const int index);
};

#endif
