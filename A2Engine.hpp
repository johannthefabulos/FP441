/*
 *  CSCI 441, Computer Graphics, Fall 2021
 *
 *  Project: A2
 *  File: A2Engine.hpp
 *
 *      Original Author: Dr. Jeffrey Paone
 *
 *  Description:
 *      Engine implementation that draws a world map to the window, changes the map image when
 *      the move methods are called, and draws an animated hero to the window.  The hero is
 *      passively and actively animated.  As the hero wraps around the window edges, the world
 *      map is updated.
 */

#ifndef A2_A2_ENGINE_HPP
#define A2_A2_ENGINE_HPP

#include "WorldMapEngine.hpp"
#include "player/Player.hpp"

class A2Engine : public WorldMapEngine {
public:
    A2Engine(const int OPENGL_MAJOR_VERSION, const int OPENGL_MINOR_VERSION,
             const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
             const char *WINDOW_TITLE);

    void run() final;

    Player player;

private:
    void _setupGLFW() final;
    void _setupOpenGL() final;
    void _setupShaders() final;
    void _setupBuffers() final;

    void _renderScene();
    void _updateScene();
};

// TODO Declare Your Callbacks Here
void keyboard_callback( GLFWwindow *win, int key, int scancode, int action, int mods);
void cursor_callback( GLFWwindow *window, double x, double y );
void mouse_button_callback( GLFWwindow *window, int button, int action, int mods);
#endif //A2_A2_ENGINE_HPP