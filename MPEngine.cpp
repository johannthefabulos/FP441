#include "MPEngine.hpp"

#include <CSCI441/objects.hpp>
#include <CSCI441/FreeCam.hpp>

#include "ShaderLocations.hpp"
#include <ctime>
#include <stdio.h>
#include <iostream>
#include <unistd.h>

/// \desc Simple helper function to return a random number between 0.0f and 1.0f.
GLfloat getRand() {
    return (GLfloat)rand() / (GLfloat)RAND_MAX;
}

//*************************************************************************************
//
// Public Interface

MPEngine::MPEngine(int OPENGL_MAJOR_VERSION, int OPENGL_MINOR_VERSION,
                         int WINDOW_WIDTH, int WINDOW_HEIGHT, const char* WINDOW_TITLE)
         : CSCI441::OpenGLEngine(OPENGL_MAJOR_VERSION, OPENGL_MINOR_VERSION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE),
        NUM_SPRITES(20),
        MAX_BOX_SIZE(10.0f) {
    for(auto& _key : _keys) _key = GL_FALSE;

    _mousePosition = glm::vec2(MOUSE_UNINITIALIZED, MOUSE_UNINITIALIZED );
    _leftMouseButtonState = GLFW_RELEASE;
}

MPEngine::~MPEngine() {
    delete cameras;
}

void MPEngine::handleKeyEvent(GLint key, GLint action) {
    if(key != GLFW_KEY_UNKNOWN)
        _keys[key] = ((action == GLFW_PRESS) || (action == GLFW_REPEAT));

    // Only move hero if camera is ARCBALL
    bool shouldMoveHero = this->cameras->getPrimaryCameraType() == ARCBALL;

    if (action == GLFW_RELEASE){
        if ((key == GLFW_KEY_W || key == GLFW_KEY_S) && shouldMoveHero){
            //Only call stopMoving call at end
            this->getCurrentHero()->stopMoving();
        }
    }

    if (action == GLFW_PRESS){
        this->cameras->changeCamera(key);
        if ((key == GLFW_KEY_W || key == GLFW_KEY_S) && shouldMoveHero){
            //Only call start moving call at beginning
            this->getCurrentHero()->startMoving();
        }
    }

    // Cycle through HeroTypes based on number keys
    if ((key >= GLFW_KEY_0 && key <= GLFW_KEY_9)){
        int heroEnumVal = key - GLFW_KEY_0;

        if (heroEnumVal < LAST){
            HeroType heroType = (HeroType) heroEnumVal;
            this->currentlySelectedHero = heroType;
            this->cameras->setHero(this->getCurrentHero());
        }

    }


    if(action == GLFW_PRESS) {
        switch( key ) {
            // quit!
            case GLFW_KEY_Q:
            case GLFW_KEY_ESCAPE:
                setWindowShouldClose();
                break;
            case GLFW_KEY_C:
                _bezierCurve.drawCage = !_bezierCurve.drawCage;
                break;

            case GLFW_KEY_P:
                _bezierCurve.drawPoints = !_bezierCurve.drawPoints;
                break;
            case GLFW_KEY_H:
                _bezierCurve.useNormal = !_bezierCurve.useNormal;
                break;

            // temporary: to test shader changing colors
            case GLFW_KEY_I:
                goldEaten += 1;
                break;
            case GLFW_KEY_K:
                goldEaten -= 1;
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
        this->getCurrentHero()->leftClickAction();
        if (action == GLFW_PRESS){
            this->_keys[GLFW_KEY_SPACE] = true;
        }
        if (action == GLFW_RELEASE){
            this->_keys[GLFW_KEY_SPACE] = false;
        }
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT){
        if (action == GLFW_PRESS){
            this->_keys[GLFW_KEY_SPACE] = true;
            this->_keys[GLFW_KEY_LEFT_SHIFT] = true;
        }
        if (action == GLFW_RELEASE){
            this->_keys[GLFW_KEY_SPACE] = false;
            this->_keys[GLFW_KEY_SPACE] = false;
            this->_keys[GLFW_KEY_LEFT_SHIFT] = false;
        }
    }
}

void MPEngine::handleCursorPositionEvent(glm::vec2 currMousePosition) {
    // if mouse hasn't moved in the window, prevent camera from flipping out
    if(fabs(_mousePosition.x - MOUSE_UNINITIALIZED) <= 0.000001f) {
        _mousePosition = currMousePosition;
    }

    // active motion - if the left mouse button is being held down while the mouse is moving (Only ARCBALL)
    if(_leftMouseButtonState == GLFW_PRESS && this->cameras->getPrimaryCameraType() == ARCBALL) {
        // if shift is held down, update our camera radius
        if( _keys[GLFW_KEY_LEFT_SHIFT] || _keys[GLFW_KEY_RIGHT_SHIFT] ) {
            GLfloat totChgSq = (currMousePosition.x - _mousePosition.x) + (currMousePosition.y - _mousePosition.y);
            this->cameras->getPrimaryCamera()->moveForward(totChgSq * 0.01f );
        }
            // otherwise, update our camera angles theta & phi
        else {
            // rotate the camera by the distance the mouse moved
            this->cameras->getPrimaryCamera()->rotate((currMousePosition.x - _mousePosition.x) * 0.005f,
                                -(_mousePosition.y - currMousePosition.y) * 0.005f);
        }
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
    shaderUniformLocations.modelMatrix      = _shaderProgram->getUniformLocation("modelMatrix");

    shaderUniformLocations.normalMat = _shaderProgram->getUniformLocation("normalMat");
    shaderUniformLocations.cameraPos = _shaderProgram->getUniformLocation("cameraPos");

    shaderUniformLocations.materialColor  = _shaderProgram->getUniformLocation("materialColor");

    shaderUniformLocations.materialShininess  = _shaderProgram->getUniformLocation("materialShininess");

    shaderAttributeLocations.vPos         = _shaderProgram->getAttributeLocation("vPos");

    shaderAttributeLocations.vNormal         = _shaderProgram->getAttributeLocation("vNormal");

    //Light uniforms

    pointLightProperties = new LightProperties(_shaderProgram->getShaderProgramHandle());
    spotLightProperties = new LightProperties(_shaderProgram->getShaderProgramHandle());
    directLightProperties = new LightProperties(_shaderProgram->getShaderProgramHandle());

    pointLightProperties->lightColorUniformLoc = _shaderProgram->getUniformLocation("pointLight.lightColor");
    pointLightProperties->lightPosUniformLoc = _shaderProgram->getUniformLocation("pointLight.lightPos");

    spotLightProperties->lightColorUniformLoc = _shaderProgram->getUniformLocation("spotLight.lightColor");
    spotLightProperties->lightPosUniformLoc = _shaderProgram->getUniformLocation("spotLight.lightPos");

    directLightProperties->lightColorUniformLoc = _shaderProgram->getUniformLocation("directLight.lightColor");
    directLightProperties->lightPosUniformLoc = _shaderProgram->getUniformLocation("directLight.lightPos");

    this->cameras = new HeroCameras(shaderUniformLocations.cameraPos);
    _textureShaderProgram = new CSCI441::ShaderProgram("shaders/lab06.v.glsl", "shaders/lab06.f.glsl" );
    // query uniform locations
    _textureShaderUniformLocations.mvpMatrix      = _textureShaderProgram->getUniformLocation("mvpMatrix");
    // TODO #12A
    _textureShaderUniformLocations.textureMap     = _textureShaderProgram->getUniformLocation("textureMap");
    // query attribute locations
    _textureShaderAttributeLocations.vPos         = _textureShaderProgram->getAttributeLocation("vPos");
    _textureShaderAttributeLocations.vNormal      = _textureShaderProgram->getAttributeLocation("vNormal");
    // TODO #12B
    _textureShaderAttributeLocations.textCoord     = _textureShaderProgram->getAttributeLocation("texCoord");

    // set static uniforms
    // TODO #13
    _textureShaderProgram->setProgramUniform(_textureShaderUniformLocations.textureMap,0);
    _flatShaderProgram = new CSCI441::ShaderProgram( "shaders/flatShader.v.glsl", "shaders/flatShader.f.glsl" );
    // get uniform locations
    _flatShaderProgramUniformLocations.mvpMatrix             = _flatShaderProgram->getUniformLocation("mvpMatrix");
    _flatShaderProgramUniformLocations.color                 = _flatShaderProgram->getUniformLocation("color");
    _billboardShaderProgram = new CSCI441::ShaderProgram( "shaders/billboardQuadShader.v.glsl",
                                                          "shaders/billboardQuadShader.g.glsl",
                                                          "shaders/billboardQuadShader.f.glsl" );
    // LOOKHERE #1 get uniform locations
    _billboardShaderProgramUniforms.mvMatrix            = _billboardShaderProgram->getUniformLocation( "mvMatrix");
    _billboardShaderProgramUniforms.projMatrix          = _billboardShaderProgram->getUniformLocation( "projMatrix");
    _billboardShaderProgramUniforms.image               = _billboardShaderProgram->getUniformLocation( "image");
    _billboardShaderProgramUniforms.goldEaten               = _billboardShaderProgram->getUniformLocation( "goldEaten");

    // get attribute locations
    _billboardShaderProgramAttributes.vPos              = _billboardShaderProgram->getAttributeLocation( "vPos");

    // set static uniforms
    _billboardShaderProgram->setProgramUniform( _billboardShaderProgramUniforms.image, 0 );
}

void MPEngine::_setupBuffers() {
    glGenVertexArrays( NUM_VAOS, _vaos );
    glGenBuffers( NUM_VAOS, _vbos );
    glGenBuffers( NUM_VAOS, _ibos );
    CSCI441::setVertexAttributeLocations(shaderAttributeLocations.vPos, shaderAttributeLocations.vNormal);

    ModelShaderLocations modelLocations = {_shaderProgram->getShaderProgramHandle(),
                                           shaderUniformLocations.mvpMatrix, shaderUniformLocations.modelMatrix,
                                           shaderUniformLocations.normalMat,shaderUniformLocations.materialColor };

    _warrior = new TheWarrior(modelLocations, WORLD_SIZE);

    _eeyore = new eeyore(modelLocations, WORLD_SIZE);

    _JohnReimann = new JohnReimann(_shaderProgram->getShaderProgramHandle(),
                                    shaderUniformLocations.mvpMatrix,
                                   shaderUniformLocations.modelMatrix,
                                    shaderUniformLocations.normalMat,
                                    shaderUniformLocations.materialColor,
                                    WORLD_SIZE);
    this->cameras->setHero(this->getCurrentHero());

    _createGroundBuffers();
    _generateEnvironment(modelLocations);
    fprintf( stdout, "\nEnter filename of Bezier Control Points to load: " );
    char *filename = (char*)malloc(sizeof(char)*256);
    //fscanf( stdin, "%s", filename );
    filename = "data/controlPoints4.csv";
    _loadControlPointsFromFile(filename,
                               &_bezierCurve.numControlPoints, &_bezierCurve.numCurves,
                               _bezierCurve.controlPoints);
    if(!_bezierCurve.controlPoints) {
        fprintf( stderr, "[ERROR]: Error loading control points from file\n" );
    } else {
        fprintf( stdout, "[INFO]: Read in %u points comprising %u curves\n", _bezierCurve.numControlPoints, _bezierCurve.numCurves );

        // generate cage
        _createCage(_vaos[VAO_ID::BEZIER_CAGE], _vbos[VAO_ID::BEZIER_CAGE], _numVAOPoints[VAO_ID::BEZIER_CAGE] );

        // generate curve
        _createCurve( _vaos[VAO_ID::BEZIER_CURVE], _vbos[VAO_ID::BEZIER_CURVE], _numVAOPoints[VAO_ID::BEZIER_CURVE] );
    }
    arcLength();

    _spriteLocations = (glm::vec3*)malloc(sizeof(glm::vec3) * NUM_SPRITES);

    _spriteIndices = (GLushort*)malloc(sizeof(GLushort) * NUM_SPRITES);

    _distances = (GLfloat*)malloc(sizeof(GLfloat) * NUM_SPRITES);

    _numVAOPoints[VAO_ID::PARTICLE_SYSTEM] = NUM_SPRITES;

    for( int i = 0; i < NUM_SPRITES; i++ ) {
        glm::vec3 pos( _randNumber(MAX_BOX_SIZE), _randNumber(MAX_BOX_SIZE), _randNumber(MAX_BOX_SIZE) );
        _spriteLocations[i] = pos;
        _spriteIndices[i] = i;
    }

    glBindVertexArray( _vaos[VAO_ID::PARTICLE_SYSTEM] );

    glBindBuffer( GL_ARRAY_BUFFER, _vbos[VAO_ID::PARTICLE_SYSTEM] );
    glBufferData( GL_ARRAY_BUFFER, _numVAOPoints[VAO_ID::PARTICLE_SYSTEM] * sizeof(glm::vec3), _spriteLocations, GL_STATIC_DRAW );

    glEnableVertexAttribArray( _billboardShaderProgramAttributes.vPos );
    glVertexAttribPointer( _billboardShaderProgramAttributes.vPos, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0 );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibos[VAO_ID::PARTICLE_SYSTEM] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, _numVAOPoints[VAO_ID::PARTICLE_SYSTEM] * sizeof(GLushort), _spriteIndices, GL_STATIC_DRAW );

    fprintf( stdout, "[INFO]: point sprites read in with VAO/VBO/IBO %d/%d/%d\n", _vaos[VAO_ID::PARTICLE_SYSTEM], _vbos[VAO_ID::PARTICLE_SYSTEM], _ibos[VAO_ID::PARTICLE_SYSTEM] );

}
GLfloat MPEngine::_randNumber( const GLfloat MAX ) {
    return rand() / (GLfloat)RAND_MAX * MAX * 2.0 - MAX;
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

void MPEngine::_generateEnvironment(ModelShaderLocations locations) {
    //******************************************************************
    // parameters to make up our grid size and spacing, feel free to
    // play around with this
    const GLfloat GRID_WIDTH = WORLD_SIZE * 1.8f;
    const GLfloat GRID_LENGTH = WORLD_SIZE * 1.8f;
    const GLfloat GRID_RADIUS = GRID_LENGTH/2;
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
    std::cout << "left end:" << LEFT_END_POINT << "right end:" << RIGHT_END_POINT << "top end:" << TOP_END_POINT << "bottom end:" << BOTTOM_END_POINT;
    for(int i = LEFT_END_POINT; i < RIGHT_END_POINT; i += GRID_SPACING_WIDTH) {
        for(int j = BOTTOM_END_POINT; j < TOP_END_POINT; j += GRID_SPACING_LENGTH) {
            // don't just draw a building ANYWHERE.
            float TOLERANCE = GRID_SPACING_WIDTH-1;
            float TOLERANCE1 = GRID_SPACING_LENGTH-1;
            //if( i % 2 && j % 2 && getRand() < 0.1f && sqrt(pow(i,2)+pow(j,2))<GRID_RADIUS-10) {
                //_trees.push_back(new Tree(locations,i,getRand()+1,j));
            //}
            if(i <= LEFT_END_POINT+TOLERANCE || i >= RIGHT_END_POINT - TOLERANCE|| j >= TOP_END_POINT -TOLERANCE1 || j <= BOTTOM_END_POINT+TOLERANCE) {
                _castles.push_back(new Castle(locations, i, j,0));
                collisions.push_back({float(i),float(j)});
            }
        }
    }
    for (int i = 37; i > 13; i-=4) {
        _castles.push_back(new Castle(locations, -37,i,0));
        collisions.push_back({-37,float(i)});
        _castles.push_back(new Castle(locations, 37,i,0));
        collisions.push_back({37,float(i)});
    }
    for (int i = 37; i > 20;i-=4) {
        _castles.push_back(new Castle(locations, -i,13,0));
        collisions.push_back({-float(i),13});
        _castles.push_back(new Castle(locations, i,13,0));
        collisions.push_back({float(i),13});
    }
    for (int i = 12; i < 37; i+=4) {
        _castles.push_back(new Castle(locations, -20,i,0));
        collisions.push_back({20,float(i)});
        _castles.push_back(new Castle(locations, 20,i,0));
        collisions.push_back({20,float(i)});
    }
    for (int i = 20; i < 37;i+=4) {
        _castles.push_back(new Castle(locations, -i,37,0));
        collisions.push_back({-float(i),37});
        _castles.push_back(new Castle(locations, i,37,0));
        collisions.push_back({float(i),37});
    }

    for (int i = 37; i > 13; i-=4) {
        _castles.push_back(new Castle(locations, -5,i,0));
        collisions.push_back({-5,float(i)});
        _castles.push_back(new Castle(locations, 5,i,0));
        collisions.push_back({5,float(i)});
    }
    for (int i = 5; i <20;i+=4) {
        _castles.push_back(new Castle(locations, -i,13,0));
        collisions.push_back({-float(i),13});
        _castles.push_back(new Castle(locations, i,13,0));
        collisions.push_back({-float(i),13});
    }
    for (int i = -45; i <45;i+=4) {
        _castles.push_back(new Castle(locations, -i,-5,0));
        collisions.push_back({-float(i),-5});
        _castles.push_back(new Castle(locations, i,-5,0));
        collisions.push_back({float(i),-5});
    }
    for (int i = -45; i <5;i+=4) {
        _castles.push_back(new Castle(locations, -i,-30,0));
        collisions.push_back({-float(i),-30});
        _castles.push_back(new Castle(locations, i,-30,0));
        collisions.push_back({float(i),-30});
    }
    for (int i = -23; i < -15; i+=4) {
        _castles.push_back(new Castle(locations, -10,i,0));
        collisions.push_back({-10,float(i)});
        _castles.push_back(new Castle(locations, 10,i,0));
        collisions.push_back({10,float(i)});
    }

    /*
    for(float i = 0; i < 2*M_PI;i += M_PI/25){
        _castles.push_back(new Castle(locations, cos(i)*GRID_RADIUS, sin(i)*GRID_RADIUS,i));

    }
     _castles.push_back(new Castle(locations, cos(i)*GRID_RADIUS, sin(i)*GRID_RADIUS,i));

     */
    //_castles.push_back(new Castle(locations, LEFT_END_POINT, TOP_END_POINT,0));

}

void MPEngine::_setupScene() {

    this->pointLightProperties->lightColor = glm::vec3(1, 0, 0);
    this->pointLightProperties->lightPosition = glm::vec3(0, 10, 0);

    this->spotLightProperties->lightColor = glm::vec3(0, 1, 0);
    this->spotLightProperties->lightPosition = glm::vec3(0, 10, 0);

    this->directLightProperties->lightColor = glm::vec3(0, 0, 1);
    this->directLightProperties->lightPosition = glm::vec3(0, 10, 0);

    this->pointLightProperties->sendUniforms();
    this->spotLightProperties->sendUniforms();
    this->directLightProperties->sendUniforms();
}

//*************************************************************************************
//
// Engine Cleanup

void MPEngine::_cleanupShaders() {
    fprintf( stdout, "[INFO]: ...deleting Shaders.\n" );
    delete _shaderProgram;
    delete _textureShaderProgram;
    delete _flatShaderProgram;
    delete _billboardShaderProgram;
    delete pointLightProperties;
    delete spotLightProperties;
    delete directLightProperties;
}

void MPEngine::_cleanupBuffers() {
    fprintf( stdout, "[INFO]: ...deleting VAOs....\n" );
    CSCI441::deleteObjectVAOs();
    glDeleteVertexArrays( 1, &_groundVAO );

    fprintf( stdout, "[INFO]: ...deleting VBOs....\n" );
    CSCI441::deleteObjectVBOs();

    fprintf( stdout, "[INFO]: ...deleting models..\n" );

    delete _warrior;
    delete _eeyore;
}

//*************************************************************************************
//
// Rendering / Drawing Functions - this is where the magic happens!

void MPEngine::_renderScene(glm::mat4 viewMtx, glm::mat4 projMtx) {
    _flatShaderProgram->useProgram();
    glm::vec3 flatColor(1.0f, 0.0f, 0.0f);
    _flatShaderProgram->setProgramUniform(_flatShaderProgramUniformLocations.color, flatColor);
    glm::mat4 modelMatrix = _warrior->getCurrentModelMat();
    _computeAndSendTransformationMatrices(_flatShaderProgram,
                                          modelMatrix, viewMtx, projMtx,
                                          _flatShaderProgramUniformLocations.mvpMatrix);

    // draw the curve control cage
//    if(_bezierCurve.drawPoints) {
//        glm::vec3 flatColor(1.0f, 1.0f, 0.0f);
//        _flatShaderProgram->setProgramUniform(_flatShaderProgramUniformLocations.color, flatColor);
//        glBindVertexArray(_vaos[VAO_ID::BEZIER_CAGE]);
//        glDrawArrays(GL_LINE_STRIP, 0, _numVAOPoints[VAO_ID::BEZIER_CAGE]);
//    }
//    //***************************************************************************
//    // draw the curve
//
//    // LOOKHERE #1 draw the curve itself
//    if(_bezierCurve.drawCage) {
//        glm::vec3 flatColor(0.0f, 0.0f, 1.0f);
//        _flatShaderProgram->setProgramUniform(_flatShaderProgramUniformLocations.color, flatColor);
//        glBindVertexArray(_vaos[VAO_ID::BEZIER_CURVE]);
//        glDrawArrays(GL_LINE_STRIP, 0, _numVAOPoints[VAO_ID::BEZIER_CURVE]);
//    }
//    if (_bezierCurve.drawPoints) {
//        glm::vec3 flatColor(0.0f, 1.0f, 0.0f);
//        _flatShaderProgram->setProgramUniform(_flatShaderProgramUniformLocations.color, flatColor);
//        //_shaderProgram->useProgram();
//        for (int i = 0; i < _bezierCurve.numControlPoints; i++) {
//            glm::mat4 modelMatrix = glm::translate(_warrior->getCurrentModelMat(), _bezierCurve.controlPoints[i]);
//            _computeAndSendMatrixUniforms(modelMatrix, viewMtx, projMtx);
//            CSCI441::drawSolidSphere(0.25f, 16, 16);
//        }
//    }

    //// BEGIN DRAWING THE GROUND PLANE ////
    _shaderProgram->useProgram();
    // draw the ground plane
    //glm::mat4 groundModelMtx = glm::translate(glm::mat4(1.0f), glm::vec3(WORLD_SIZE, 1.0f, WORLD_SIZE));
    glm::mat4 groundModelMtx = glm::scale(glm::mat4(1.0f) , glm::vec3(WORLD_SIZE, 1.0f, WORLD_SIZE));

    _computeAndSendMatrixUniforms(groundModelMtx, viewMtx, projMtx);

    glm::vec3 groundColor(0.3f, 0.8f, 0.2f);
    glUniform3fv(shaderUniformLocations.materialColor, 1, &groundColor[0]);
    glUniform1f(shaderUniformLocations.materialShininess, 100.0f);


    glUniform3fv(shaderUniformLocations.cameraPos, 1, &this->cameras->getPrimaryCamera()->getPosition()[0]);
    //CSCI441::drawWireCube(WORLD_SIZE/4);

    glBindVertexArray(_groundVAO);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLE_STRIP, _numGroundPoints, GL_UNSIGNED_SHORT, (void*)0);
    //// END DRAWING THE GROUND PLANE ////

    //// BEGIN DRAWING THE BUILDINGS ////
    glUniform1f(shaderUniformLocations.materialShininess, 1);
    for( Tree* currentTree : _trees ) {
        currentTree->drawTree(viewMtx,projMtx);
    }
    for(Castle* currentCastle : _castles){
        currentCastle->drawCastle(viewMtx,projMtx);
    }
    //// END DRAWING THE BUILDINGS ////

    glUniform1f(shaderUniformLocations.materialShininess, 1);
    _warrior->drawWarrior(viewMtx, projMtx);

    glUniform1f(shaderUniformLocations.materialShininess, 1);

    _eeyore->drawEeyore(viewMtx, projMtx);


    glUniform1f(shaderUniformLocations.materialShininess, 1);
    _JohnReimann->drawJohn_Reimann(viewMtx, projMtx, collisions);


    int integralPart = floor(_bezierCurve.currPosition);
    float fractionalPart = _bezierCurve.currPosition - integralPart;
    int i = 3*integralPart;
    if (_bezierCurve.useNormal){
        integralPart = floor(_bezierCurve.currPosition);
        fractionalPart = _bezierCurve.currPosition - integralPart;
        i = 3*integralPart;

    }
    else {
        integralPart = floor(Tvalues[_bezierCurve.index]);
        fractionalPart = Tvalues[_bezierCurve.index] - integralPart;
        i = 3*integralPart;
    }

    glm::vec3 p0 = (_bezierCurve.controlPoints[i]);
    glm::vec3 p1 = (_bezierCurve.controlPoints[i+1]);
    glm::vec3 p2 = (_bezierCurve.controlPoints[i+2]);
    glm::vec3 p3 = (_bezierCurve.controlPoints[i+3]);



    glm::vec3 pointInSpace = _evalBezierCurve(p0,p1,p2,p3,fractionalPart);
    glm::mat4 sphereModelMatrix = glm::translate( _warrior->getCurrentModelMat(), pointInSpace );

    _computeAndSendMatrixUniforms(sphereModelMatrix, viewMtx, projMtx);
    //CSCI441::drawSolidSphere(5, 360, 360);
    //_JohnReimann->drawJohn_Reimann(viewMtx, projMtx);
    drawChair(sphereModelMatrix,viewMtx,projMtx);
    _textureShaderProgram->useProgram();
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.1f, 0.0f));
    //modelMatrix = glm::rotate( modelMatrix, _objectAngle, CSCI441::Y_AXIS );
    glm::mat4 mvpMtx = projMtx * viewMtx * modelMatrix;
    _textureShaderProgram->setProgramUniform(_textureShaderUniformLocations.mvpMatrix, mvpMtx);
    CSCI441::setVertexAttributeLocations(_textureShaderAttributeLocations.vPos,
                                         _textureShaderAttributeLocations.vNormal,
                                         _textureShaderAttributeLocations.textCoord
    );
    glBindTexture(GL_TEXTURE_2D, _texHandles[TEXTURE_ID::SKY]);
    CSCI441::drawSolidCubeTextured( 750.0f );
    glBindTexture(GL_TEXTURE_2D, _texHandles[TEXTURE_ID::METAL]);
    float smallestDist = 1000000001;
    for (int i=0; i<goldLocs.size();i++) {
        glm::vec3 currPosition = _JohnReimann->getCurrentPosition();
        float dist = sqrt(pow(currPosition.x-goldLocs[i][0],2)+pow(currPosition.z-goldLocs[i][1],2));
        //std::cout << dist << " " << smallestDist;
        if (dist < smallestDist) {
            closestCoin = goldLocs[i];
        }
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(goldLocs[i][0], 2.1f, goldLocs[i][1]));
        glm::mat4 mvpMtx = projMtx * viewMtx * modelMatrix;
        _textureShaderProgram->setProgramUniform(_textureShaderUniformLocations.mvpMatrix, mvpMtx);
        CSCI441::setVertexAttributeLocations(_textureShaderAttributeLocations.vPos,
                                             _textureShaderAttributeLocations.vNormal,
                                             _textureShaderAttributeLocations.textCoord
        );
        CSCI441::drawSolidSphere( 2.0f,50,50 );
    }



    _billboardShaderProgram->useProgram();

    modelMatrix = glm::translate(glm::mat4(1.0f), _warrior->getCurrentPosition());
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5));
    modelMatrix = glm::rotate(modelMatrix, _particleSystemAngle, CSCI441::Y_AXIS);
    glm::mat4 mvMatrix = viewMtx * modelMatrix;

    _billboardShaderProgram->setProgramUniform( _billboardShaderProgramUniforms.mvMatrix, mvMatrix );
    _billboardShaderProgram->setProgramUniform( _billboardShaderProgramUniforms.projMatrix, projMtx );
    _billboardShaderProgram->setProgramUniform( _billboardShaderProgramUniforms.goldEaten, goldEaten );


    glBindVertexArray( _vaos[VAO_ID::PARTICLE_SYSTEM] );
    glBindTexture(GL_TEXTURE_2D, _texHandles[TEXTURE_ID::PARTICLE_SYSTEM_TEX]);

    // TODO #1 compute distances
    glm::vec3 normalizedViewVector = glm::normalize(this->cameras->getPrimaryCamera()->getLookAtPoint() - this->cameras->getPrimaryCamera()->getPosition());
    for (int i = 0; i < NUM_SPRITES; i++){
        glm::vec3 currentSprite = _spriteLocations[ _spriteIndices[i] ];
        glm::vec4 currentSprite1 = glm::vec4(currentSprite,1);
        glm::vec3 p = modelMatrix * currentSprite1;
        glm::vec3 ep = p - this->cameras->getPrimaryCamera()->getPosition();
        float length = glm::dot(normalizedViewVector, ep);
        _distances[_spriteIndices[i] ] = length;
    }
    // TODO #2 sort indices by distance
    for (int i = 0; i < NUM_SPRITES; i++){
        for (int j = i; j < NUM_SPRITES; j++){
            if (_distances[_spriteIndices[j] ] > _distances[_spriteIndices[i]]) {
                float temp1 = _distances[_spriteIndices[i] ];
                float temp2 = _distances[_spriteIndices[j] ];
                int temp3 = _spriteIndices[i];
                int temp4 = _spriteIndices[j];
                _spriteIndices[i] = temp4;
                _spriteIndices[j] = temp3;
                //_distances[_spriteIndices[i]] = temp2;
                //_distances[_spriteIndices[j]] = temp1;
            }
        }
    }

    // TODO #3 update IBO
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibos[VAO_ID::PARTICLE_SYSTEM] );
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0,sizeof(GLushort) * NUM_SPRITES ,_spriteIndices);

    glDrawElements( GL_POINTS, _numVAOPoints[VAO_ID::PARTICLE_SYSTEM], GL_UNSIGNED_SHORT, (void*)0 );
}
    void MPEngine::_computeAndSendTransformationMatrices(CSCI441::ShaderProgram* shaderProgram,
                                                        glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix,
                                                        GLint mvpMtxLocation, GLint modelMtxLocation, GLint normalMtxLocation) {
    // ensure our shader program is not null
    if( shaderProgram ) {
        // precompute the MVP matrix CPU side
        glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
        // precompute the Normal matrix CPU side
        glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));

        // send the matrices to the shader
        shaderProgram->setProgramUniform(mvpMtxLocation, mvpMatrix);
        shaderProgram->setProgramUniform(modelMtxLocation, modelMatrix);
        shaderProgram->setProgramUniform(normalMtxLocation, normalMatrix);
    }
}
void MPEngine::eatGold(){
    glm::vec3 currentPosition = _JohnReimann->getCurrentPosition();
    allPositions.push_back({currentPosition.x,currentPosition.z});
    this->pointLightProperties->lightColor = glm::vec3(0, 1, 0);

    this->pointLightProperties->lightPosition = glm::vec3(currentPosition.x, 1, currentPosition.z);

    this->pointLightProperties->sendUniforms();

    this->spotLightProperties->lightColor = glm::vec3(1, 0, 0);
    this->spotLightProperties->lightPosition = glm::vec3(closestCoin[0], 2, closestCoin[1]);
    this->directLightProperties->lightColor = glm::vec3(0, 0, 1);
    this->directLightProperties->lightPosition = glm::vec3(closestCoin[0], 2, closestCoin[1]);

    this->spotLightProperties->sendUniforms();
    this->directLightProperties->sendUniforms();

    for (int i = 0; i < goldLocs.size();i++) {
        //std::cout << goldLocs.size();
        if (abs(currentPosition.x - goldLocs[i][0]) < 1 and abs(currentPosition.z - goldLocs[i][1]) < 1) {
            _JohnReimann->setIncrment(1);
            goldEaten++;
            goldLocs[i] = {-1000,-1000};
        }
    }
}
void MPEngine::updateWarrior() {
    //std::cout<<goldEaten;
    if (goldEaten >= 1) {
            _warrior->setCurrentModelMat(
                    _JohnReimann->getCurrentModelMat());
            _warrior->moveHeroForward();
    }
    if (goldEaten >= 2) {
        _warrior->leftClickAction();
    }
    if (goldEaten >= 3) {
        _eeyore->setCurrentModelMat(
                _JohnReimann->getCurrentModelMat());
    }
    if (goldEaten >= 4) {
        _eeyore->setCurrentModelMat(
                _JohnReimann->getCurrentModelMat());
    }

}
void MPEngine::arcLength() {
    int numCurves = _bezierCurve.numCurves;


    float stepLength = 1.0f/200.0f* (float)(_bezierCurve.numCurves);
    for (float i = 0; i < _bezierCurve.numCurves; i+= stepLength) {
        int curveNumber = floor(i);
        int m = 3 * curveNumber;
        glm::vec3 p0 = (_bezierCurve.controlPoints[m]);
        glm::vec3 p1 = (_bezierCurve.controlPoints[m + 1]);
        glm::vec3 p2 = (_bezierCurve.controlPoints[m + 2]);
        glm::vec3 p3 = (_bezierCurve.controlPoints[m + 3]);
        if (i == 0) {
            functionOfT.push_back(0.0);
            step.push_back(i);
            continue;
        } else {
            glm::vec3 pointInSpace1 = _evalBezierCurve(p0, p1, p2, p3, i);
            glm::vec3 pointInSpace2 = _evalBezierCurve(p0, p1, p2, p3, i - stepLength);

            float beforeValue = functionOfT[functionOfT.size() - 1];
            float distance = sqrt(
                    pow(pointInSpace1.x - pointInSpace2.x, 2) + pow(pointInSpace1.y - pointInSpace2.y, 2) +
                    pow(pointInSpace1.z - pointInSpace2.z, 2));
            functionOfT.push_back((distance) + beforeValue);
            step.push_back(i);
            std::cout << functionOfT[i] << ": " << step[i] << std::endl;
        }

    }
    float dx = functionOfT[functionOfT.size()-1]/(200.0f* (float)(_bezierCurve.numCurves));
    for (float j = 0.0f; j < functionOfT[functionOfT.size()-1]; j+=dx) {
        for (int i = 0; i < functionOfT.size(); i++){

            if (i + 1 >= step.size()) {
                break;
            }
            if (j == functionOfT[i]) {
                Tvalues.push_back(step[i]);
            }
            else if (j > functionOfT[i] and j < functionOfT[i+1]) {
                float my = functionOfT[i];
                float my1 = functionOfT[i+1];
                float first = (j - functionOfT[i])/(functionOfT[i+1]-functionOfT[i]);
                float second = first *(step[i+1]-step[i]);

                float third = second+ step[i];
                Tvalues.push_back(third);
                break;

            }
        }
    }

}
void MPEngine::drawChair( glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) {
    modelMtx = glm::translate( modelMtx, glm::vec3( cos(animationAngle), 0, sin(animationAngle) ));
    //modelMtx = glm::translate( modelMtx, glm::vec3( translateX, 0, translateY));
    modelMtx = glm::rotate( modelMtx, 2*correctionAngle, CSCI441::Y_AXIS );
    modelMtx = glm::rotate( modelMtx, chairCurrentAngle, CSCI441::Y_AXIS );
    drawArmRests(modelMtx,viewMtx, projMtx );
    drawCusion(modelMtx,viewMtx,projMtx );
    drawBack(modelMtx,viewMtx, projMtx );
}
void MPEngine::drawArmRests(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) {
    glm::vec3 _colorRed = glm::vec3( 1.0f, 0.0f, 0 );
    modelMtx = glm::scale( modelMtx,glm::vec3( .5, 1, 1 ));
    modelMtx = glm::translate( modelMtx, glm::vec3( 1.5f, 0, 0 ));
    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);
    //glUniform3fv(_lightingShaderUniformLocations.materialColor, 1, &_colorRed[0]);
    CSCI441::drawSolidCube(1);
    modelMtx = glm::translate( modelMtx, glm::vec3( -1.5f, 0, 0 ));
    modelMtx = glm::translate( modelMtx, glm::vec3( -1.5f, 0, 0 ));
    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);
    //glUniform3fv(_lightingShaderUniformLocations.materialColor, 1, &_colorRed[0]);
    CSCI441::drawSolidCube(1);

}
void MPEngine::drawBack(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) {
    glm::vec3 _colorBlue = glm::vec3( 0, 0, 1.0f );
    modelMtx = glm::translate( modelMtx, glm::vec3( 0, .5, .5 ));
    modelMtx = glm::scale( modelMtx,glm::vec3( 1, 1.5, .5 ));
    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);
    //glUniform3fv(_lightingShaderUniformLocations.materialColor, 1, &_colorBlue[0]);
    CSCI441::drawSolidCube(1);
}
void MPEngine::drawCusion(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) {
    glm::vec3 _colorGreen = glm::vec3( 0, 1.0f, 0);
    modelMtx = glm::translate( modelMtx, glm::vec3( 0, 0, 0 ));
    modelMtx = glm::scale( modelMtx,glm::vec3( 1, .5, 1 ));
    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);
    //glUniform3fv(_lightingShaderUniformLocations.materialColor, 1, &_colorGreen[0]);
    CSCI441::drawSolidCube(1);
}
void MPEngine::_createCurve(GLuint vao, GLuint vbo, GLsizei &numVAOPoints) const {
    // TODO #02: generate the Bezier curve
    int x;

    //std::cout << "Enter Resolution";
    //std::cin >> x;
    x = 9;
    float t;
    int y = 0;

    numVAOPoints = _bezierCurve.numCurves * (x + 1);
    glm::vec3 drawPoints[numVAOPoints];
    for (int i = 0; i + 3 < _bezierCurve.numControlPoints; i++) {
        auto p0 = (_bezierCurve.controlPoints[i]);
        auto p1 = (_bezierCurve.controlPoints[i+1]);
        auto p2 = (_bezierCurve.controlPoints[i+2]);
        auto p3 = (_bezierCurve.controlPoints[i+3]);
        i+=2;
        for (int j = 0; j <= x;j++) {
            t = ((float)j/(float)x);
            drawPoints[y] = (_evalBezierCurve(p0, p1, p2, p3, t));
            y++;
        }
    }
    glBindVertexArray( vao );

    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, numVAOPoints * sizeof(glm::vec3), (const void *) drawPoints, GL_STATIC_DRAW );

    glEnableVertexAttribArray( shaderAttributeLocations.vPos );
    glVertexAttribPointer( shaderAttributeLocations.vPos, 3, GL_FLOAT, GL_FALSE, 0, nullptr );
    fprintf( stdout, "[INFO]: bezier curve read in with VAO/VBO %d/%d & %d points\n", vao, vbo, numVAOPoints );
}
void MPEngine::_createCage(GLuint vao, GLuint vbo, GLsizei &numVAOPoints) const {
    numVAOPoints = _bezierCurve.numControlPoints;

    glBindVertexArray( vao );

    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, numVAOPoints * sizeof(glm::vec3), _bezierCurve.controlPoints, GL_STATIC_DRAW );

    glEnableVertexAttribArray( shaderAttributeLocations.vPos );
    glVertexAttribPointer( shaderAttributeLocations.vPos, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    fprintf( stdout, "[INFO]: control points cage read in with VAO/VBO %d/%d & %d points\n", vao, vbo, numVAOPoints );
}
glm::vec3 MPEngine::_evalBezierCurve(const glm::vec3 P0, const glm::vec3 P1, const glm::vec3 P2, const glm::vec3 P3, const GLfloat T) {
    // TODO #01: solve the curve equation
    glm::vec3 bezierPoint = ((-P0+3.0f*P1-3.0f*P2+P3)*(float)(pow(T,3))) + ((3.0f*P0-6.0f*P1 +3.0f*P2) * (float)pow(T,2.0)) + ((-3.0f*P0 + 3.0f*P1) *T) + P0;
    //glm::vec3 bezierPoint = glm::vec3(0,0,0); // temp value to allow code to compile

    return bezierPoint;
}
void MPEngine::_loadControlPointsFromFile(const char* FILENAME, GLuint *numBezierPoints, GLuint *numBezierCurves, glm::vec3* &bezierPoints) {
    // open the file
    FILE *file = fopen(FILENAME, "r");

    // check that the file opened properly
    if(!file) {
        fprintf( stderr, "[ERROR]: Could not open \"%s\"\n", FILENAME );
    } else {
        // first value is the number of points in the file
        fscanf( file, "%u\n", numBezierPoints );

        *numBezierCurves = (*numBezierPoints-1)/3;

        fprintf( stdout, "[INFO]: Reading in %u control points\n", *numBezierPoints );

        // allocate memory
        bezierPoints = (glm::vec3*)malloc( sizeof( glm::vec3 ) * *numBezierPoints );
        if(!bezierPoints) {
            fprintf( stderr, "[ERROR]: Could not allocate space for control points\n" );
        } else {
            // read in all the points
            for( int i = 0; i < *numBezierPoints; i++ ) {
                // each line is formatted as "x,y,z\n" as comma seperated floats
                fscanf( file, "%f,%f,%f\n", &(bezierPoints[i].x), &(bezierPoints[i].y), &(bezierPoints[i].z));
            }
        }
    }
    // close the file
    fclose(file);
}

void MPEngine::_updateScene() {
    glm::vec3 currPos = _JohnReimann->getCurrentPosition();
    if (currPos.y > 40){
        _JohnReimann->setIncrment(-2.0f);
        comingDown = true;

    }
    if (currPos.y <= 3.9 and comingDown) {
        glm::mat4 tempModelMtx = _JohnReimann->getCurrentModelMat();
        glm::translate(tempModelMtx,glm::vec3(currPos.x,-1,currPos.z));
        _JohnReimann->setCurrentModelMat(tempModelMtx);
        _JohnReimann->setIncrment(0.0f);
        comingDown = false;
    }
    _bezierCurve.currPosition += 0.005f;
    if (_bezierCurve.currPosition > _bezierCurve.numCurves) {
        _bezierCurve.currPosition = 0;
    }
    _bezierCurve.index +=1;
    if (_bezierCurve.index > Tvalues.size()-1) {
        _bezierCurve.index = 0;
    }
    //Only the ARCBALL main camera type moves the hero
    bool shouldMoveHero = (this->cameras->getPrimaryCameraType() == ARCBALL);

    // turn right
    if( _keys[GLFW_KEY_D] && shouldMoveHero) {
        this->getCurrentHero()->turnHero(-glm::pi<GLfloat>()/128.0f);

    }
    // turn left
    if( _keys[GLFW_KEY_A] && shouldMoveHero) {
        this->getCurrentHero()->turnHero(glm::pi<GLfloat>()/128.0f);
    }
    // pitch up
    if( _keys[GLFW_KEY_W] && shouldMoveHero) {
        this->getCurrentHero()->moveHeroForward();
    }
    // pitch down
    if( _keys[GLFW_KEY_S] && shouldMoveHero) {
        this->getCurrentHero()->moveHeroBackward();
    }
    //Handle free cam movement or keep arcball pointed at hero
    this->cameras->update(_keys);
    _particleSystemAngle += 0.01f;
    if(_particleSystemAngle >= 6.28f) {
        _particleSystemAngle -= 6.28f;
    }
    eatGold();
    updateWarrior();
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
        glm::mat4 viewMatrix = this->cameras->getPrimaryCamera()->getViewMatrix();

        // draw everything to the window
        _renderScene(viewMatrix, projectionMatrix);

        _updateScene();
        /// End draw main view port
        /// Start draw minimap view port

        if (this->cameras->getViewMatrix() != glm::mat4(1.0f)){
            this->drawPIPView(projectionMatrix);
        }

        glfwSwapBuffers(_window);                       // flush the OpenGL commands and make sure they get rendered!
        glfwPollEvents();				                // check for any events and signal to redraw screen
    }
}
void MPEngine::_setupTextures() {
    // TODO #09
    _texHandles[TEXTURE_ID::METAL] = _loadAndRegisterTexture("assets/textures/gold.png" );
    _texHandles[TEXTURE_ID::SKY] = _loadAndRegisterTexture("assets/textures/skybox.png" );
    _texHandles[TEXTURE_ID::PARTICLE_SYSTEM_TEX] = _loadAndRegisterTexture("assets/textures/spark.png");
}
GLuint MPEngine::_loadAndRegisterTexture(const char* FILENAME) {
    // our handle to the GPU
    GLuint textureHandle = 0;

    // enable setting to prevent image from being upside down
    stbi_set_flip_vertically_on_load(true);

    // will hold image parameters after load
    GLint imageWidth, imageHeight, imageChannels;
    // load image from file
    GLubyte* data = stbi_load( FILENAME, &imageWidth, &imageHeight, &imageChannels, 0);

    // if data was read from file
    if( data ) {
        const GLint STORAGE_TYPE = (imageChannels == 4 ? GL_RGBA : GL_RGB);

        // TODO #01
        glGenTextures(1, &textureHandle);
        // TODO #02
        glBindTexture(GL_TEXTURE_2D, textureHandle);
        // TODO #03
        glTexParameteri( GL_TEXTURE_2D,
                         GL_TEXTURE_MAG_FILTER,
                         GL_LINEAR );

        // TODO #04
        glTexParameteri( GL_TEXTURE_2D,
                         GL_TEXTURE_MIN_FILTER,
                         GL_LINEAR );
        // TODO #05
        glTexParameteri( GL_TEXTURE_2D,
                         GL_TEXTURE_WRAP_S,
                         GL_REPEAT );
        // TODO #06
        glTexParameteri( GL_TEXTURE_2D,
                         GL_TEXTURE_WRAP_T,
                         GL_REPEAT );

        // TODO #07
        glTexImage2D(GL_TEXTURE_2D, 0, STORAGE_TYPE,imageWidth,imageHeight,0,STORAGE_TYPE,GL_UNSIGNED_BYTE,data);

        fprintf( stdout, "[INFO]: %s texture map read in with handle %d\n", FILENAME, textureHandle);

        // release image memory from CPU - it now lives on the GPU
        stbi_image_free(data);
    } else {
        // load failed
        fprintf( stderr, "[ERROR]: Could not load texture map \"%s\"\n", FILENAME );
    }

    // return generated texture handle
    return textureHandle;
}
void MPEngine::drawPIPView(glm::mat4 projectionMatrix) {
    //Width/4 square pip
    GLint framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize( _window, &framebufferWidth, &framebufferHeight );

    glViewport( framebufferWidth - (framebufferWidth/4), framebufferHeight - (framebufferWidth/4), framebufferWidth/4, framebufferWidth/4);

    GLint borderWidth = 2;
    //Add white background (looks like a border)
    glScissor(framebufferWidth - (framebufferWidth/4) - (borderWidth*2), framebufferHeight - (framebufferWidth/4) - (borderWidth*2), (framebufferWidth/4) + (borderWidth*2), (framebufferWidth/4) + (borderWidth*2));
    glEnable(GL_SCISSOR_TEST);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
    //Change clear color back to black
    glClearColor(0, 0, 0, 1);

    // Don't let other objects overlap this
    glScissor(framebufferWidth - (framebufferWidth/4), framebufferHeight - (framebufferWidth/4), framebufferWidth/4, framebufferWidth/4);
    glEnable(GL_SCISSOR_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
    // set up our look at matrix to position our camera
    this->cameras->recalculateViewMatrix();

    // draw everything to the minimap
    _renderScene(this->cameras->getViewMatrix(), projectionMatrix);

    _updateScene();
}

//*************************************************************************************
//
// Private Helper Functions

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
    if (this->cameras->getPrimaryCameraType() == ARCBALL){
        this->cameras->getPrimaryCamera()->moveForward(totChgSq * 0.2f );
    }

}

HeroVirtual * MPEngine::getCurrentHero() {
    switch (this->currentlySelectedHero){
        case WARRIOR:
            return this->_warrior;
        case EEYORE:
            return this->_eeyore;
        case JOHN:
            return this->_JohnReimann;
        default:
            return this->_warrior;
    }
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
