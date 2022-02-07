#pragma once

#include "Libs.h"
#include "Camera.h"
#include "Target.h"
#include "AudioManager.h"

//ENUMERATIONS
enum shader_enum { SHADER_CORE_PROGRAM = 0, POST_FX_PROGRAM, SHADER_MOVE_PROGRAM };
enum texture_enum { TEX_PUSHEEN = 0, TEX_PUSHEEN_SPECULAR, TEX_STONE, TEX_STONE_SPECULAR };
enum material_enum { MAT_1 = 0 };
enum mesh_enum { MESH_QUAD = 0 };

class Game
{
public:
	
//Variables
	//Window
	GLFWwindow* window;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int framebufferWidth;
	int framebufferHeight;


	//OpenGL Context
	const int GL_VERSION_MAJOR;
	const int GL_VERSION_MINOR;

	//Delta time
	float dt;
	float curTime;
	float lastTime;

	//Mouse input
	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;
	bool moving = false;

	//Camera
	Camera camera;
	Target* QuadTarget;

	//Matrices
	glm::mat4 ViewMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;

	glm::mat4 ProjectionMatrix;
	float fov;
	float nearPlane;
	float farPlane;

	unsigned int framebuffer;
	unsigned int texColorBuffer;
	unsigned int rbo;

	//Shaders
	std::vector<Shader*> shaders;

	//Textures
	std::vector<Texture*> textures;

	//Materials
	std::vector<Material*> materials;

	//Models
	std::vector<Model*> models;
	std::vector<PlanetModel*> pmodels;

	//Lights
	std::vector<PointLight*> pointLights;

//Private functions
	void initGLFW();
	void initWindow(const char* title, bool resizable);
	void initGLEW(); //AFTER openGL CONTEXT CREATION
	void initOpenGLOptions();
	void initMatrices(); 
	void initShaders();
	void initTextures();
	void initMaterials();
	void initFrameBuffer();
	void initModels();
	void initPointLights();
	void initLights();
	void initUniforms();

	void updateUniforms();
	


public:

//Constructors/Destructors
	Game(const Game&) = delete;
	static Game& Get()
	{
		static Game Game("PROJECT",
			1920, 1080,
			4, 4,
			false);;
		return Game;
	}

	Game(const char* title,
		const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
		const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
		bool resizable);
	virtual ~Game();

//Accessors
	int getWindowShouldClose();

//Modifiers
	void setWindowShouldClose();

//Functions
	void updateDt();
	void updateMouseInput();
	void updateKeyboardInput();
	void updateInput();
	void update();
	void render();

//Static functions
	static void framebuffer_resize_callback(GLFWwindow* window, int fbw, int fbh);

};

