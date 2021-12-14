#ifndef A3_ENGINE_HPP
#define A3_ENGINE_HPP

#include <CSCI441/ArcballCam.hpp>
#include <CSCI441/OpenGLEngine.hpp>
#include <CSCI441/ShaderProgram.hpp>
#include "ShaderLocations.hpp"
#include "the_warrior/TheWarrior.hpp"
#include "Eeyore/eeyore.hpp"
#include "HeroType.hpp"
#include "HeroVirtual.hpp"
#include "john_Reimann/JohnReimann.hpp"
#include "environment/Tree.hpp"
#include "environment/Castle.hpp"
#include "hero_cameras/HeroCameras.hpp"
#include "LightProperties.hpp"
#include <stb_image.h>
#include <vector>
#include <CSCI441/FreeCam.hpp>


class MPEngine : public CSCI441::OpenGLEngine {
public:
    MPEngine(int OPENGL_MAJOR_VERSION, int OPENGL_MINOR_VERSION,
                int WINDOW_WIDTH, int WINDOW_HEIGHT,
                const char* WINDOW_TITLE);
    ~MPEngine();

    void run() final;

    void drawPIPView(glm::mat4 projectionMatrix);

    /// \desc handle any key events inside the engine
    /// \param key key as represented by GLFW_KEY_ macros
    /// \param action key event action as represented by GLFW_ macros
    void handleKeyEvent(GLint key, GLint action);
    void drawChair(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);
    void drawArmRests(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);
    void drawBack(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);
    void drawCusion(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);
    /// \desc handle any mouse button events inside the engine
    /// \param button mouse button as represented by GLFW_MOUSE_BUTTON_ macros
    /// \param action mouse event as represented by GLFW_ macros
    void handleMouseButtonEvent(GLint button, GLint action);
    void arcLength();
    /// \desc handle any cursor movement events inside the engine
    /// \param currMousePosition the current cursor position
    void handleCursorPositionEvent(glm::vec2 currMousePosition);

    void handleScrollEvent(glm::vec2 offset);

    /// \desc value off-screen to represent mouse has not begun interacting with window yet
    static constexpr GLfloat MOUSE_UNINITIALIZED = -9999.0f;
    glm::mat4 chairModelMatrix;
    float correctionAngle = 1.5708;
    float chairCurrentAngle = 0;
    float animationAngle = 0.0f;
private:

    CSCI441::ShaderProgram* _textureShaderProgram = nullptr;   // the wrapper for our shader program
    /// \desc stores the locations of all of our shader uniforms
    struct TextureShaderUniformLocations {
        /// \desc precomputed MVP matrix location
        GLint mvpMatrix;
        // TODO #11
        GLint textureMap;
    } _textureShaderUniformLocations;
    /// \desc stores the locations of all of our shader attributes
    struct TextureShaderAttributeLocations {
        /// \desc vertex position location
        GLint vPos;
        /// \desc vertex normal location
        /// \note not used in this lab
        GLint vNormal;
        // TODO #10
        GLint textCoord;
    } _textureShaderAttributeLocations;
    static constexpr GLuint NUM_TEXTURES = 3;
    void _setupTextures() final;
    /// \desc used to index through our texture array to give named access
    enum TEXTURE_ID {
        /// \desc metal texture
        METAL = 0,
        /// \desc Mines logo texture
        SKY = 1,
        PARTICLE_SYSTEM_TEX = 2
    };
    const GLfloat MAX_BOX_SIZE;
    /// \desc the number of sprites to draw and the size of the _spriteLocations,
    /// \desc _spriteIndices, and _distances arrays
    const GLuint NUM_SPRITES;
    /// \desc the (x,y,z) location of each sprite
    glm::vec3* _spriteLocations = nullptr;
    /// \desc the order to draw the sprites in
    GLushort* _spriteIndices = nullptr;
    /// \desc will be used to store the distance to the camera
    GLfloat* _distances = nullptr;
    /// \desc angle to rotate the particle system by
    GLfloat _particleSystemAngle;
    static GLfloat _randNumber( GLfloat MAX );
    static constexpr GLuint NUM_VAOS = 4;
    /// \desc used to index through our VAO/VBO/IBO array to give named access
    enum VAO_ID {
        /// \desc the platform that represents our ground for everything to appear on
        PLATFORM = 0,
        /// \desc the control points that form the cage for our bezier curve
        BEZIER_CAGE = 1,
        /// \desc the actual bezier curve itself
        BEZIER_CURVE = 2,
        PARTICLE_SYSTEM = 3
    };
    CSCI441::ShaderProgram* _flatShaderProgram = nullptr;
    struct FlatShaderProgramUniformLocations {
        /// \desc precomputed MVP matrix location
        GLint mvpMatrix;
        /// \desc the color to apply location
        GLint color;
    } _flatShaderProgramUniformLocations;
    /// \desc VAO for our objects
    GLuint _vaos[NUM_VAOS];
    /// \desc VBO for our objects
    GLuint _vbos[NUM_VAOS];
    /// \desc IBO for our objects
    GLuint _ibos[NUM_VAOS];
    /// \desc the number of points that make up our VAO
    GLsizei _numVAOPoints[NUM_VAOS];
    void _createCage(GLuint vao, GLuint vbo, GLsizei &numVAOPoints) const;
    void _createCurve(GLuint vao, GLuint vbo, GLsizei &numVAOPoints) const;
    struct BezierCurve {
        /// \desc control points array
        glm::vec3* controlPoints = nullptr;
        /// \desc number of control points in the curve system.
        /// \desc corresponds to the size of controlPoints array
        GLuint numControlPoints;
        /// \desc number of curves in the system
        GLuint numCurves;
        // TODO #03A: make a data member to track the current evaluation parameter
        GLfloat currPosition = 0;
        GLboolean drawCage = false;
        GLboolean drawPoints = true;
        GLboolean useNormal = true;
        GLint index = 0;
    } _bezierCurve;
        std::vector<float> functionOfT;
        std::vector<float> step;
        std::vector<float> Tvalues;
    /// \desc texture handles for our textures
    GLuint _texHandles[NUM_TEXTURES];
    static GLuint _loadAndRegisterTexture(const char* FILENAME);
    void _setupGLFW() final;
    void _setupOpenGL() final;
    void _setupShaders() final;
    void _setupBuffers() final;
    void _setupScene() final;

    void _cleanupBuffers() final;
    void _cleanupShaders() final;
    [[nodiscard]] static glm::vec3 _evalBezierCurve(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, GLfloat t);
    static void _loadControlPointsFromFile(const char* FILENAME, GLuint *numBezierPoints, GLuint *numBezierCurves, glm::vec3* &bezierPoints);
    /// \desc draws everything to the scene from a particular point of view
    /// \param viewMtx the current view matrix for our camera
    /// \param projMtx the current projection matrix for our camera
    void _renderScene(glm::mat4 viewMtx, glm::mat4 projMtx);
    /// \desc handles moving our FreeCam as determined by keyboard input
    void _updateScene();

    void _cycleThroughLights();

    /// \desc tracks the number of different keys that can be present as determined by GLFW
    static constexpr GLuint NUM_KEYS = GLFW_KEY_LAST;
    /// \desc boolean array tracking each key state.  if true, then the key is in a pressed or held
    /// down state.  if false, then the key is in a released state and not being interacted with
    GLboolean _keys[NUM_KEYS];

    /// \desc last location of the mouse in window coordinates
    glm::vec2 _mousePosition;
    /// \desc current state of the left mouse button
    GLint _leftMouseButtonState;

    HeroCameras* cameras;

    // Hero models
    eeyore* _eeyore;
    JohnReimann* _JohnReimann;
    TheWarrior* _warrior;
    bool comingDown= false;
    LightProperties* pointLightProperties;
    LightProperties* spotLightProperties;
    LightProperties* directLightProperties;
    std::vector<std::vector<float>> allPositions;
    void updateWarrior();
    int counter1=0;
    //End Models
    /// \desc the size of the world (controls the ground size and locations of buildings)
    static constexpr GLfloat WORLD_SIZE = 55.0f;
    /// \desc VAO for our ground
    GLuint _groundVAO;
    /// \desc the number of points that make up our ground object
    GLsizei _numGroundPoints;

    /// \desc creates the ground VAO
    void _createGroundBuffers();

    /// \desc information list of all the buildings to draw
    std::vector<Tree*> _trees;
    std::vector<Castle*> _castles;
    std::vector<std::vector<float>> collisions;
    std::vector<std::vector<float>> goldLocs = {{-12.204,21.37},{-0.105,26.36},{40.007,-40.1205},{21.57,7.99},{-1.83,-21.822}};
    /// \desc generates building information to make up our scene
    void _generateEnvironment(ModelShaderLocations locations);
    void eatGold();
    int goldEaten = 0;
    std::vector<float> closestCoin= {-1000,-1000};
    /// \desc shader program
    CSCI441::ShaderProgram* _shaderProgram = nullptr;   // the wrapper for our shader program
    /// \desc stores the locations of all of our shader uniforms
    CSCI441::ShaderProgram* _billboardShaderProgram = nullptr;
    /// \desc stores the locations of all of our shader uniforms
    struct BillboardShaderProgramUniforms {
        /// \desc the ModelView Matrix to apply
        GLint mvMatrix;
        /// \desc the Projection Matrix to apply
        GLint projMatrix;
        /// \desc the texture to apply
        GLint image;

        GLint goldEaten;
    } _billboardShaderProgramUniforms;
    /// \desc stores the locations of all of our shader attributes
    struct BillboardShaderProgramAttributes {
        /// \desc the vertex position
        GLint vPos;
    } _billboardShaderProgramAttributes;
    ShaderUniformLocations shaderUniformLocations;
    void deathCubeLogic();
    bool death = false;
    ShaderAttributeLocations shaderAttributeLocations;
    glm::vec3 color;
    float currentRadius = 0.05;
    float radiusIncrement = 0.0;
    bool immortal = false;
    /// \desc precomputes the matrix uniforms CPU-side and then sends them
    /// to the GPU to be used in the shader for each vertex.  It is more efficient
    /// to calculate these once and then use the resultant product in the shader.
    /// \param modelMtx model transformation matrix
    /// \param viewMtx camera view matrix
    /// \param projMtx camera projection matrix
    void _computeAndSendMatrixUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const;

    HeroVirtual *getCurrentHero();
    bool win = false;
    bool jump = false;
    HeroType currentlySelectedHero = WARRIOR;
    static void _computeAndSendTransformationMatrices(CSCI441::ShaderProgram* shaderProgram,
                                                      glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix,
                                                      GLint mvpMtxLocation, GLint modelMtxLocation = -1, GLint normalMtxLocation = -1);
};

void a3_keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods );
void a3_cursor_callback(GLFWwindow *window, double x, double y );
void a3_mouse_button_callback(GLFWwindow *window, int button, int action, int mods );
void a3_scroll_callback(GLFWwindow *window, double xOffset, double yOffset);


#endif
