#include "Precompilied.h"
#include "Rendering/Renderer.h"

int main(int argc, char** argv)
{
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Minecraft 2", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  glfwSwapInterval(1);

  // Initialize GLEW
  if (glewInit() != GLEW_OK)
  {
    std::cout << "GLEW initialization failed" << std::endl;
    exit(1);
  }

  // Initialize OpenGL debugging
  glDebugMessageCallback(openGLLogMessage, nullptr);
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

  std::cout << glGetString(GL_VERSION) << std::endl;

  float positions[] = { -0.5f, -0.5f, 0.0f, 0.0f,
                         0.5f, -0.5f, 1.0f, 0.0f,
                         0.5f,  0.5f, 1.0f, 1.0f,
                        -0.5f,  0.5f, 0.0f, 1.0f  };

  unsigned int indices[] = { 0, 1, 2,
                             2, 3, 0 };

  // Create vertex array object
  VertexArray va;
  VertexBuffer vb(positions, 4 * 4 * sizeof(float));

  // Set up vertex buffer layout for 2 floats
  VertexBufferLayout layout;
  layout.push<float>(2);
  layout.push<float>(2);
  va.addBuffer(vb, layout);

  // Create index buffer to avoid vertex duplication
  IndexBuffer ib(indices, 6);

  // Setup shaders
  Shader shader("res/Shaders/Basic.shader");
  shader.bind();

  // Add a uniform
  shader.setUniform4f("u_Color", 0.2f, 0.5f, 0.2f, 1.0f);

  // Unbind everything
  va.unBind();
  shader.unBind();
  vb.unBind();
  ib.unBind();

  // Create renderer
  Renderer renderer;

  float g = 0.0f;
  float increment = 0.02f;
  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    /* Render here */
    renderer.clear();

    shader.bind();
    shader.setUniform4f("u_Color", 0.2f, g, 0.2f, 1.0f);

    Texture texture("res/Textures/GrassBlock.png");
    texture.bind(0);
    shader.setUniform1i("u_Texture", 0);

    va.bind();
    ib.bind();

    renderer.draw(va, ib, shader);

    if (g > 1.0f || g < 0.0f)
      increment *= -1;
    g += increment;

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}