/*
 *  CSCI 441, Computer Graphics, Fall 2021
 *
 *  Project: A2
 *  File: main.cpp
 *
 *      Author: Dr. Jeffrey Paone
 *
 *  Description:
 *      Contains the shell code for moving an animated character across a world map.
 */

#include "A2Engine.hpp"

//*************************************************************************************
//
// Our main function

int main() {

    auto a2Engine = new A2Engine(4, 1, 512, 512, "A2: An Unexpected Journey");
    a2Engine->initialize();
    if( a2Engine->getError() == CSCI441::OpenGLEngine::OPENGL_ENGINE_ERROR_NO_ERROR ) {
        a2Engine->run();
    }
    a2Engine->shutdown();
    delete a2Engine;

    return EXIT_SUCCESS;                            // exit our program successfully!
}