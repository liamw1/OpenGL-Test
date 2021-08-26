#include "Precompilied.h"
#include "Rendering/Renderer.h"

int main(int argc, char** argv)
{
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(960, 540, "Minecraft 2", NULL, NULL);
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

  float positions[] = { -50.0f, -50.0f, 0.0f, 0.0f,
                         50.0f, -50.0f, 1.0f, 0.0f,
                         50.0f,  50.0f, 1.0f, 1.0f,
                        -50.0f,  50.0f, 0.0f, 1.0f  };

  unsigned int indices[] = { 0, 1, 2,
                             2, 3, 0 };

  // Set up blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

  // Create mvp matrix
  glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
  glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

  // Setup shaders
  Shader shader("res/Shaders/Basic.shader");
  shader.bind();

  // Setup textures
  Texture texture("res/Textures/GrassBlock.png");
  texture.bind(0);
  shader.setUniform1i("u_Texture", 0);

  // Unbind everything
  va.unBind();
  vb.unBind();
  ib.unBind();
  shader.unBind();

  // Create renderer
  Renderer renderer;

  // Setup ImGui
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  glm::vec3 translationA(200, 200, 0);
  glm::vec3 translationB(400, 200, 0);

  float g = 0.0f;
  float increment = 0.02f;
  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    /* Render here */
    renderer.clear();

    // Start ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    {
      glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
      glm::mat4 mvp = proj * view * model;
      shader.bind();
      shader.setUniformMat4f("u_MVP", mvp);
      renderer.draw(va, ib, shader);
    }

    {
      glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
      glm::mat4 mvp = proj * view * model;
      shader.bind();
      shader.setUniformMat4f("u_MVP", mvp);
      renderer.draw(va, ib, shader);
    }

    if (g > 1.0f || g < 0.0f)
      increment *= -1;
    g += increment;

    // Create ImGui window
    {
      ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 960.0f);
      ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 960.0f);
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }

    // ImGui rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwTerminate();
  return 0;
}