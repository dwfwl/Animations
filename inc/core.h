#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sprite/sprite.h>
#include <memory>
#include <opengl/shaders/Shader.h>

class Core
{
public:
	Core()
	{
		initGlfw();
		initOpengl();
		Setup();
		run();
		cleanUp();
	}

private:
	void initGlfw();
	void initOpengl();
	void Setup();
	void run();
	void cleanUp();

	GLFWwindow* window;
	std::shared_ptr<Shader> shader;

	Sprite mountain;
	Sprite glow;

};

void Core::initGlfw()
{
	glfwInit();
	window = glfwCreateWindow(800, 800, "Animation", nullptr, nullptr);
	glfwMakeContextCurrent(window);
}

void Core::initOpengl()
{
	gladLoadGL();
}

void Core::Setup()
{
	shader = std::make_shared<Shader>();
	shader_create(shader.get(), "inc/opengl/shaders/default/default.vert", "inc/opengl/shaders/default/default.frag");

	mountain.setData(Geometry{
			std::vector<Vertex>{
				//	   pos		    texture Coordinates
				Vertex{glm::vec3(-0.5f, 0.5f, 1.0f), glm::vec2(0, 0)},
				Vertex{glm::vec3(-0.5f,-0.5f, 1.0f), glm::vec2(0, 1)},
				Vertex{glm::vec3( 0.5f,-0.5f, 1.0f), glm::vec2(1, 1)},
				Vertex{glm::vec3( 0.5f, 0.5f, 1.0f), glm::vec2(1, 0)}
			},
			std::vector<uint32_t>{
					0, 3, 2, 
					0, 1, 2
			}
		}, "assets/mountain.png");
	
	glow.setData(Geometry{
			std::vector<Vertex>{
				//	   pos		    texture Coordinates
				Vertex{glm::vec3(-0.45f, 0.8f, 1.0f), glm::vec2(0, 0)},
				Vertex{glm::vec3(-0.45f,-0.1f, 1.0f), glm::vec2(0, 1)},
				Vertex{glm::vec3( 0.45f,-0.1f, 1.0f), glm::vec2(1, 1)},
				Vertex{glm::vec3( 0.45f, 0.8f, 1.0f), glm::vec2(1, 0)}
			},
			std::vector<uint32_t>{
				0, 3, 2,
				0, 1, 2
			}
		}, "assets/glow.png");
}

void Core::run()
{
	double prev = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		double current = glfwGetTime();
		float deltaTime = prev - current;
		prev = current;

		glfwPollEvents();
		
		shader_use(shader.get());
		mountain.draw();

		float time = glfwGetTime();
		for (auto& vertex : glow.m_geometry->vertices)
		{
			float c = vertex.pos.y;

			vertex.pos.y = c + 0.0005f * sin(2.0f * time + vertex.pos.x);
			std::cout << vertex.pos.y << "\n";
		}

		glow.update();
		glow.draw();

		glfwSwapBuffers(window);
	}
}

void Core::cleanUp()
{
	glfwDestroyWindow(window);
}