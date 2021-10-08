#include "A2Engine.hpp"
#include <CSCI441/SimpleShader.hpp>

// include GLM libraries and matrix functions
#include <glm/gtc/matrix_transform.hpp>

A2Engine::A2Engine(const int OPENGL_MAJOR_VERSION, const int OPENGL_MINOR_VERSION,
                   const int WINDOW_WIDTH, const int WINDOW_HEIGHT, const char*WINDOW_TITLE)
       : WorldMapEngine(OPENGL_MAJOR_VERSION, OPENGL_MINOR_VERSION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE),player(WINDOW_WIDTH, WINDOW_HEIGHT) {

}

//*************************************************************************************
//
// Setup Functions - register everything with OpenGL / GLFW

void A2Engine::_setupGLFW() {
    CSCI441::OpenGLEngine::_setupGLFW();

    // TODO Register Your Callbacks Here
    glfwSetKeyCallback(_window, keyboard_callback);
    glfwSetCursorPosCallback(_window, cursor_callback);
    glfwSetMouseButtonCallback(_window, mouse_button_callback);
}

void A2Engine::_setupOpenGL() {
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );     // set the clear color to black
}

void A2Engine::_setupShaders() {
    WorldMapEngine::_setupShaders();
    CSCI441::SimpleShader2::setupSimpleShader();
}

void A2Engine::_setupBuffers() {
    WorldMapEngine::_setupBuffers();
    this->player.setupPlayerBuffers();
    // TODO Add Your Vertex Registration Here

    std::vector<glm::vec2> points;
    points.emplace_back(-1*50, -1*50);
    points.emplace_back(1*50, -1*50);
    points.emplace_back(0, 1*50);
}

//*************************************************************************************
//
// Rendering / Drawing Functions - this is where the magic happens!

// void _renderScene()
//   This method will contain the draw call for all objects to be drawn.
void A2Engine::_renderScene() {
    // TODO Add Your Drawing Here
    glm::mat4 mainTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(this->player.playerCenterX, this->player.playerCenterY, 0.0f));
    CSCI441::SimpleShader2::pushTransformation(mainTransMat);
    this->player.drawPlayer();
    CSCI441::SimpleShader2::popTransformation();

    this->player.tryDrawLasers();
}

// void _updateScene()
//   This method will update any parameters used to draw an object
//   and thus create animation over time
void A2Engine::_updateScene() {
    //**********************************
    // TODO Add Your Idle Animation Here
    //**********************************
}

// void run()
//   Responsible for running the draw loop and keeping our engine open
void A2Engine::run() {
    //  This is our draw loop - all rendering is done here.  We use a loop to keep the window open
    //  until the user decides to close the window and quit the program.  Without a loop, the
    //  window will display once and then the program exits.
    while( !glfwWindowShouldClose(_window) ) {  // check if the window was instructed to be closed
        glClear( GL_COLOR_BUFFER_BIT ); // clear the current color contents in the window

        WorldMapEngine::_drawMap();     // draw the world map first so it appears behind anything we else we draw

        // update the projection matrix based on the window size
        // the GL_PROJECTION matrix governs properties of the view coordinates;
        // i.e. what gets seen - use an Orthographic projection that ranges
        // from [0, windowWidth] in X and [0, windowHeight] in Y. (0,0) is the lower left.
        glm::mat4 projMtx = glm::ortho( 0.0f, (GLfloat)getWindowWidth(), 0.0f, (GLfloat)getWindowHeight() );
        CSCI441::SimpleShader2::setProjectionMatrix(projMtx);

        // Get the size of our framebuffer.  Ideally this should be the same dimensions as our window, but
        // when using a Retina display the actual window can be larger than the requested window.  Therefore
        // query what the actual size of the window we are rendering to is.
        GLint framebufferWidth, framebufferHeight;
        glfwGetFramebufferSize( _window, &framebufferWidth, &framebufferHeight );

        // update the viewport - tell OpenGL we want to render to the whole window
        glViewport( 0, 0, framebufferWidth, framebufferHeight );

        // ensure the model matrix is reset to the identity to start drawing
        CSCI441::SimpleShader2::resetTransformationMatrix();

        _renderScene();                                 // draw everything to the window

        // LOOK HERE #2
        glfwSwapBuffers(_window);               // flush the OpenGL commands and make sure they get rendered!
        glfwPollEvents();                               // check for any events and signal to redraw screen

        _updateScene();                 // update everything in the window
    }
}

//*************************************************************************************
//
// Callbacks

// TODO Define Your Callbacks Here

void keyboard_callback( GLFWwindow *window, int key, int scancode, int action, int mods){
    A2Engine *engine = (A2Engine*) glfwGetWindowUserPointer(window);

    GLfloat movementSpeed = 10;

    bool wPressed = (key == GLFW_KEY_W) || glfwGetKey(window, GLFW_KEY_W);
    bool aPressed = (key == GLFW_KEY_A) || glfwGetKey(window, GLFW_KEY_A);
    bool sPressed = (key == GLFW_KEY_S) || glfwGetKey(window, GLFW_KEY_S);
    bool dPressed = (key == GLFW_KEY_D) || glfwGetKey(window, GLFW_KEY_D);

    bool escPressed = (key == GLFW_KEY_ESCAPE) || glfwGetKey(window, GLFW_KEY_ESCAPE);

    //If statements are used to help recognize simultaneous key presses
    if (escPressed){
        engine->setWindowShouldClose();
        return;
    }

    if (wPressed){
        engine->player.playerCenterY += movementSpeed;
        if (engine->player.playerCenterY > engine->getWindowHeight()){
            engine->moveUp();
            engine->player.playerCenterY = 0;
        }
    }
    if (aPressed){
        engine->player.playerCenterX -= movementSpeed;
        if (engine->player.playerCenterX < 0){
            engine->moveLeft();
            engine->player.playerCenterX = engine->getWindowWidth();
        }
    }
    if (sPressed){
        engine->player.playerCenterY -= movementSpeed;
        if (engine->player.playerCenterY < 0){
            engine->moveDown();
            engine->player.playerCenterY = engine->getWindowHeight();
        }
    }
    if (dPressed){
        engine->player.playerCenterX += movementSpeed;
        if (engine->player.playerCenterX > engine->getWindowWidth()){
            engine->moveRight();
            engine->player.playerCenterX = 0;
        }
    }
}

void mouse_button_callback( GLFWwindow *window, int button, int action, int mods){
    A2Engine *engine = (A2Engine*) glfwGetWindowUserPointer(window);

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        if (action == GLFW_RELEASE){
            engine->player.shootLaser();
        }
    }

}

void cursor_callback( GLFWwindow *window, double x, double y ){
    A2Engine *engine = (A2Engine*) glfwGetWindowUserPointer(window);

    engine->player.eyePointLocation.x = x;
    engine->player.eyePointLocation.y = engine->getWindowHeight() - y;
}