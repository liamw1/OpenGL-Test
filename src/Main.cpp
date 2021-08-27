#include "Precompilied.h"
#include "Rendering/Renderer.h"
#include "Tests/ClearColorTest.h"
#include "Tests/TextureTest2D.h"

GLFWwindow* windowInit()
{
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit())
    exit(1);

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(960, 540, "Minecraft 2", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    exit(1);
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  glfwSwapInterval(1);

  return window;
}

void openGLInit()
{
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

  // Set up blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void imguiInit(GLFWwindow* window)
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
}

int main(int argc, char** argv)
{
  GLFWwindow* window = windowInit();
  openGLInit();
  imguiInit(window);
  Renderer renderer;

  test::Test* currentTest = nullptr;
  test::TestMenu* testMenu = new test::TestMenu(currentTest);
  currentTest = testMenu;

  testMenu->registerTest<test::ClearColorTest>("Clear Color");
  testMenu->registerTest<test::TextureTest2D>("2D Texture");

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    renderer.clear();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    if (currentTest != nullptr)
    {
      currentTest->OnUpdate(0.0f);
      currentTest->OnRender();
      ImGui::Begin("Test");
      if (currentTest != testMenu && ImGui::Button("<-"))
      {
        delete currentTest;
        currentTest = testMenu;
      }
      currentTest->OnImGuiRender();
      ImGui::End();
    }
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  if (currentTest != testMenu)
    delete testMenu;
  delete currentTest;

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwTerminate();
  return 0;
}