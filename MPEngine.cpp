#include "MPEngine.hpp"

#include <CSCI441/objects.hpp>
#include <CSCI441/FreeCam.hpp>

#include "ShaderLocations.hpp"

#include <stdio.h>

/// \desc Simple helper function to return a random number between 0.0f and 1.0f.
GLfloat getRand() {
    return (GLfloat)rand() / (GLfloat)RAND_MAX;
}

//*************************************************************************************
//
// Public Interface

MPEngine::MPEngine(int OPENGL_MAJOR_VERSION, int OPENGL_MINOR_VERSION,
                         int WINDOW_WIDTH, int WINDOW_HEIGHT, const char* WINDOW_TITLE)
         : CSCI441::OpenGLEngine(OPENGL_MAJOR_VERSION, OPENGL_MINOR_VERSION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE) {

    for(auto& _key : _keys) _key = GL_FALSE;

    _mousePosition = glm::vec2(MOUSE_UNINITIALIZED, MOUSE_UNINITIALIZED );
    _leftMouseButtonState = GLFW_RELEASE;
}

MPEngine::~MPEngine() {
    delete _arcballCam;
}

void MPEngine::handleKeyEvent(GLint key, GLint action) {
    if(key != GLFW_KEY_UNKNOWN)
        _keys[key] = ((action == GLFW_PRESS) || (action == GLFW_REPEAT));

    if(action == GLFW_PRESS) {
        switch( key ) {
            // quit!
            case GLFW_KEY_Q:
            case GLFW_KEY_ESCAPE:
                setWindowShouldClose();
                break;

            default: break; // suppress CLion warning
        }
    }
}

void MPEngine::handleMouseButtonEvent(GLint button, GLint action) {
    // if the event is for the left mouse button
    if( button == GLFW_MOUSE_BUTTON_LEFT ) {
        // update the left mouse button's state
        _leftMouseButtonState = action;
    }
}

void MPEngine::handleCursorPositionEvent(glm::vec2 currMousePosition) {
    // if mouse hasn't moved in the window, prevent camera from flipping out
    if(fabs(_mousePosition.x - MOUSE_UNINITIALIZED) <= 0.000001f) {
        _mousePosition = currMousePosition;
    }

    // active motion - if the left mouse button is being held down while the mouse is moving
    if(_leftMouseButtonState == GLFW_PRESS) {
        // if shift is held down, update our camera radius
        if( _keys[GLFW_KEY_LEFT_SHIFT] || _keys[GLFW_KEY_RIGHT_SHIFT] ) {
            GLfloat totChgSq = (currMousePosition.x - _mousePosition.x) + (currMousePosition.y - _mousePosition.y);
            _arcballCam->moveForward( totChgSq * 0.01f );
        }
            // otherwise, update our camera angles theta & phi
        else {
            // rotate the camera by the distance the mouse moved
            _arcballCam->rotate((currMousePosition.x - _mousePosition.x) * 0.005f,
                                -(_mousePosition.y - currMousePosition.y) * 0.005f);
        }
    }
        // passive motion
    else {

    }

    // update the mouse position
    _mousePosition = currMousePosition;
}

//*************************************************************************************
//
// Engine Setup

void MPEngine::_setupGLFW() {
    CSCI441::OpenGLEngine::_setupGLFW();

    // set our callbacks
    glfwSetKeyCallback(_window, a3_keyboard_callback);
    glfwSetMouseButtonCallback(_window, a3_mouse_button_callback);
    glfwSetCursorPosCallback(_window, a3_cursor_callback);
    glfwSetScrollCallback(_window, a3_scroll_callback);
}

void MPEngine::_setupOpenGL() {
    glEnable( GL_DEPTH_TEST );					                    // enable depth testing
    glDepthFunc( GL_LESS );							                // use less than depth test

    glEnable(GL_BLEND);									            // enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	            // use one minus blending equation

    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );	// clear the frame buffer to black
}

void MPEngine::_setupShaders() {
    _shaderProgram = new CSCI441::ShaderProgram("shaders/a3.v.glsl", "shaders/a3.f.glsl" );
    shaderUniformLocations.mvpMatrix      = _shaderProgram->getUniformLocation("mvpMatrix");

    shaderUniformLocations.lightColor = _shaderProgram->getUniformLocation("lightColor");
    shaderUniformLocations.lightPos = _shaderProgram->getUniformLocation("lightPos");
    shaderUniformLocations.normalMat = _shaderProgram->getUniformLocation("normalMat");
    shaderUniformLocations.cameraPos = _shaderProgram->getUniformLocation("cameraPos");

    shaderUniformLocations.materialColor  = _shaderProgram->getUniformLocation("materialColor");

    shaderUniformLocations.materialShininess  = _shaderProgram->getUniformLocation("materialShininess");

    shaderAttributeLocations.vPos         = _shaderProgram->getAttributeLocation("vPos");

    shaderAttributeLocations.vNormal         = _shaderProgram->getAttributeLocation("vNormal");

}

void MPEngine::_setupBuffers() {

    CSCI441::setVertexAttributeLocations(shaderAttributeLocations.vPos, shaderAttributeLocations.vNormal);

    _car = new eeyore(_shaderProgram->getShaderProgramHandle(),
                      shaderUniformLocations.mvpMatrix,
                      shaderUniformLocations.normalMat,
                      shaderUniformLocations.materialColor,
                      WORLD_SIZE);

    ModelShaderLocations modelLocations = {_shaderProgram->getShaderProgramHandle(),
                                           shaderUniformLocations.mvpMatrix, shaderUniformLocations.normalMat,
                                           shaderUniformLocations.materialColor };

    _warrior = new TheWarrior(&modelLocations);
    _car = new eeyore(_shaderProgram->getShaderProgramHandle(),
                   shaderUniformLocations.mvpMatrix,
                   shaderUniformLocations.normalMat,
                   shaderUniformLocations.materialColor,
                   WORLD_SIZE);

    _createGroundBuffers();
    _generateEnvironment();
}

void MPEngine::_createGroundBuffers() {

    struct Vertex {
        GLfloat x, y, z;
        GLfloat normX, normY, normZ;
    };


    Vertex groundQuad[4] = {
            {-1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f},
            { 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f},
            {-1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f},
            { 1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f}
    };

    GLushort indices[4] = {0,1,2,3};

    _numGroundPoints = 4;

    glGenVertexArrays(1, &_groundVAO);
    glBindVertexArray(_groundVAO);

    GLuint vbods[2];       // 0 - VBO, 1 - IBO
    glGenBuffers(2, vbods);
    glBindBuffer(GL_ARRAY_BUFFER, vbods[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(groundQuad), groundQuad, GL_STATIC_DRAW);

    glEnableVertexAttribArray(shaderAttributeLocations.vPos);
    glVertexAttribPointer(shaderAttributeLocations.vPos, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(shaderAttributeLocations.vNormal);
    glVertexAttribPointer(shaderAttributeLocations.vNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbods[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void MPEngine::_generateEnvironment() {
    //******************************************************************
    // parameters to make up our grid size and spacing, feel free to
    // play around with this
    const GLfloat GRID_WIDTH = WORLD_SIZE * 1.8f;
    const GLfloat GRID_LENGTH = WORLD_SIZE * 1.8f;
    const GLfloat GRID_SPACING_WIDTH = 4;
    const GLfloat GRID_SPACING_LENGTH = 4;
    // precomputed parameters based on above
    const GLfloat LEFT_END_POINT = glm::round(-GRID_WIDTH / 2.0f - 5.0f);
    const GLfloat RIGHT_END_POINT = glm::round(GRID_WIDTH / 2.0f + 5.0f);
    const GLfloat BOTTOM_END_POINT = glm::round(-GRID_LENGTH / 2.0f - 5.0f);
    const GLfloat TOP_END_POINT = glm::round(GRID_LENGTH / 2.0f + 5.0f);
    //******************************************************************

    srand( time(0) );                                                   // seed our RNG

    // psych! everything's on a grid.
    for(int i = LEFT_END_POINT; i < RIGHT_END_POINT; i += GRID_SPACING_WIDTH) {
        for(int j = BOTTOM_END_POINT; j < TOP_END_POINT; j += GRID_SPACING_LENGTH) {
            // don't just draw a building ANYWHERE.
            if( i % 2 && j % 2 && getRand() < 0.4f ) {
                // translate to spot
                glm::mat4 transToSpotMtx = glm::translate( glm::mat4(1.0), glm::vec3(i, 0.0f, j) );

                // compute random height
                GLdouble height = powf(getRand(), 2.5)*5 + 1;
                // scale to building size
                glm::mat4 scaleToHeightMtx = glm::scale( glm::mat4(1.0), glm::vec3(1, height, 1) );

                // translate up to grid
                glm::mat4 transToHeight = glm::translate( glm::mat4(1.0), glm::vec3(0, height/2.0f, 0) );

                // compute full model matrix
                glm::mat4 modelMatrix = transToHeight * scaleToHeightMtx * transToSpotMtx;

                // compute random color
                glm::vec3 color( getRand(), getRand(), getRand() );
                // store building properties
                BuildingData currentBuilding = {modelMatrix, color};
                _buildings.emplace_back( currentBuilding );
            }
        }
    }
}

void MPEngine::_setupScene() {
    _arcballCam = new CSCI441::ArcballCam();
    _arcballCam->setLookAtPoint(glm::vec3(0.0f, 2.1f, 0.0f) );
    _arcballCam->setTheta(3.52f );
    _arcballCam->setPhi(1.9f );
    _arcballCam->setRadius( 15.0f );
    _arcballCam->recomputeOrientation();


    glm::vec3 lightPos(-1, -1, -1);
    glm::vec3 lightColor(1, 1, 1);

    glProgramUniform3fv(_shaderProgram->getShaderProgramHandle(), shaderUniformLocations.lightPos,
                        1, &lightPos[0]);

    glProgramUniform3fv(_shaderProgram->getShaderProgramHandle(), shaderUniformLocations.lightColor,
                        1, &lightColor[0]);
}

//*************************************************************************************
//
// Engine Cleanup

void MPEngine::_cleanupShaders() {
    fprintf( stdout, "[INFO]: ...deleting Shaders.\n" );
    delete _shaderProgram;
}

void MPEngine::_cleanupBuffers() {
    fprintf( stdout, "[INFO]: ...deleting VAOs....\n" );
    CSCI441::deleteObjectVAOs();
    glDeleteVertexArrays( 1, &_groundVAO );

    fprintf( stdout, "[INFO]: ...deleting VBOs....\n" );
    CSCI441::deleteObjectVBOs();

    fprintf( stdout, "[INFO]: ...deleting models..\n" );
    delete _car;
}

//*************************************************************************************
//
// Rendering / Drawing Functions - this is where the magic happens!

void MPEngine::_renderScene(glm::mat4 viewMtx, glm::mat4 projMtx) {

    _shaderProgram->useProgram();

    //// BEGIN DRAWING THE GROUND PLANE ////
    // draw the ground plane
    glm::mat4 groundModelMtx = glm::scale( glm::mat4(1.0f), glm::vec3(WORLD_SIZE, 1.0f, WORLD_SIZE));
    _computeAndSendMatrixUniforms(groundModelMtx, viewMtx, projMtx);

    glm::vec3 groundColor(0.3f, 0.8f, 0.2f);
    glUniform3fv(shaderUniformLocations.materialColor, 1, &groundColor[0]);
    glUniform1f(shaderUniformLocations.materialShininess, 0.0f);
    glUniform3fv(shaderUniformLocations.cameraPos, 1, &this->_arcballCam->getPosition()[0]);
    glBindVertexArray(_groundVAO);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glDrawElements(GL_TRIANGLE_STRIP, _numGroundPoints, GL_UNSIGNED_SHORT, (void*)0);
    //// END DRAWING THE GROUND PLANE ////

    //// BEGIN DRAWING THE BUILDINGS ////
    glUniform1f(shaderUniformLocations.materialShininess, 1);
    for( const BuildingData& currentBuilding : _buildings ) {
        _computeAndSendMatrixUniforms(currentBuilding.modelMatrix, viewMtx, projMtx);

        glUniform3fv(shaderUniformLocations.materialColor, 1, &currentBuilding.color[0]);

        CSCI441::drawSolidCube(1.0);
    }
    //// END DRAWING THE BUILDINGS ////
    //Draw eeyore
    glUniform1f(shaderUniformLocations.materialShininess, 1);
    _car->drawCar(viewMtx, projMtx);

    this->_arcballCam->setLookAtPoint(this->_car->getCurrentPosition());
    this->_arcballCam->recomputeOrientation();
    glUniform3fv(shaderUniformLocations.cameraPos, 1, &this->_arcballCam->getPosition()[0]);
}

void MPEngine::_updateScene() {
    // turn right
    if( _keys[GLFW_KEY_D] ) {
        _car->turnCar(-glm::pi<GLfloat>() / 128.0f);
    }
    // turn left
    if( _keys[GLFW_KEY_A] ) {
        _car->turnCar(glm::pi<GLfloat>() / 128.0f);
    }
    // pitch up
    if( _keys[GLFW_KEY_W] ) {
        _car->driveForward();
    }
    // pitch down
    if( _keys[GLFW_KEY_S] ) {
        _car->driveBackward();
    }
}

void MPEngine::run() {
    //  This is our draw loop - all rendering is done here.  We use a loop to keep the window open
    //	until the user decides to close the window and quit the program.  Without a loop, the
    //	window will display once and then the program exits.
    while( !glfwWindowShouldClose(_window) ) {	        // check if the window was instructed to be closed
        glDrawBuffer( GL_BACK );				        // work with our back frame buffer
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	// clear the current color contents and depth buffer in the window

        // Get the size of our framebuffer.  Ideally this should be the same dimensions as our window, but
        // when using a Retina display the actual window can be larger than the requested window.  Therefore,
        // query what the actual size of the window we are rendering to is.
        GLint framebufferWidth, framebufferHeight;
        glfwGetFramebufferSize( _window, &framebufferWidth, &framebufferHeight );

        /// Start draw main view port
        // update the viewport - tell OpenGL we want to render to the whole window
        glViewport( 0, 0, framebufferWidth, framebufferHeight );

        // set the projection matrix based on the window size
        // use a perspective projection that ranges
        // with a FOV of 45 degrees, for our current aspect ratio, and Z ranges from [0.001, 1000].
        glm::mat4 projectionMatrix = glm::perspective( 45.0f, (GLfloat) framebufferWidth / (GLfloat) framebufferHeight, 0.001f, 1000.0f );

        // set up our look at matrix to position our camera
        glm::mat4 viewMatrix = this->_arcballCam->getViewMatrix();

        // draw everything to the window
        _renderScene(viewMatrix, projectionMatrix);

        _updateScene();
        /// End draw main view port
        /// Start draw minimap view port

        //Width/4 square minimap
        glViewport( framebufferWidth - (framebufferWidth/4), framebufferHeight - (framebufferWidth/4), framebufferWidth/4, framebufferWidth/4);

        // Don't let other objects overlap this
        glScissor(framebufferWidth - (framebufferWidth/4), framebufferHeight - (framebufferWidth/4), framebufferWidth/4, framebufferWidth/4);
        glEnable(GL_SCISSOR_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDisable(GL_SCISSOR_TEST);

        // set up our look at matrix to position our camera
        GLfloat minimapCamHeight = 20;
        glm::vec3 minimapCamPos = this->_car->getCurrentPosition();
        minimapCamPos.y = minimapCamHeight;

        glm::vec3 carForwardVec = glm::transpose(glm::inverse(this->_car->currentModelMatrix)) * glm::vec4(0, 0, -1, 1);
        carForwardVec = glm::normalize(carForwardVec);

        glm::mat4 minimapViewMat = glm::lookAt(minimapCamPos, this->_car->getCurrentPosition(), carForwardVec);

        // draw everything to the minimap
        _renderScene(minimapViewMat, projectionMatrix);

        _updateScene();
        /// End draw minimap view port

        glfwSwapBuffers(_window);                       // flush the OpenGL commands and make sure they get rendered!
        glfwPollEvents();				                // check for any events and signal to redraw screen
    }
}

//*************************************************************************************
//
// Private Helper FUnctions

void MPEngine::_computeAndSendMatrixUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const {
    // precompute the Model-View-Projection matrix on the CPU
    glm::mat4 mvpMtx = projMtx * viewMtx * modelMtx;
    // then send it to the shader on the GPU to apply to every vertex
    _shaderProgram->setProgramUniform(shaderUniformLocations.mvpMatrix, mvpMtx);

    glm::mat3 normalMtx = glm::mat3(glm::transpose(glm::inverse(modelMtx)));
    _shaderProgram->setProgramUniform(shaderUniformLocations.normalMat, normalMtx);



}

void MPEngine::handleScrollEvent(glm::vec2 offset) {
    // update the camera radius in/out
    GLfloat totChgSq = offset.y;
    _arcballCam->moveForward( totChgSq * 0.2f );
}

//*************************************************************************************
//
// Callbacks

void a3_keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods ) {
    auto engine = (MPEngine*) glfwGetWindowUserPointer(window);

    // pass the key and action through to the engine
    engine->handleKeyEvent(key, action);
}

void a3_cursor_callback(GLFWwindow *window, double x, double y ) {
    auto engine = (MPEngine*) glfwGetWindowUserPointer(window);

    // pass the cursor position through to the engine
    engine->handleCursorPositionEvent(glm::vec2(x, y));
}

void a3_mouse_button_callback(GLFWwindow *window, int button, int action, int mods ) {
    auto engine = (MPEngine*) glfwGetWindowUserPointer(window);

    // pass the mouse button and action through to the engine
    engine->handleMouseButtonEvent(button, action);
}

void a3_scroll_callback(GLFWwindow *window, double xOffset, double yOffset) {
    auto engine = (MPEngine*) glfwGetWindowUserPointer(window);

    // pass the scroll offset through to the engine
    engine->handleScrollEvent(glm::vec2(xOffset, yOffset));
}
