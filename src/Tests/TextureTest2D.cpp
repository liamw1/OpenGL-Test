#include "Precompilied.h"
#include "TextureTest2D.h"

namespace test
{
  TextureTest2D::TextureTest2D()
    : m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
      m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
      m_TranslationA(200, 200, 0),
      m_TranslationB(400, 200, 0)
  {
    float positions[] = { -50.0f, -50.0f, 0.0f, 0.0f,
                           50.0f, -50.0f, 1.0f, 0.0f,
                           50.0f,  50.0f, 1.0f, 1.0f,
                          -50.0f,  50.0f, 0.0f, 1.0f };

    unsigned int indices[] = { 0, 1, 2,
                               2, 3, 0 };

    // Set up blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Create vertex array object
    m_VAO = std::make_unique<VertexArray>();

    // Set up vertex buffer layout for 2 floats
    m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);
    m_VAO->addBuffer(*m_VertexBuffer, layout);

    // Create index buffer to avoid vertex duplication
    m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

    // Setup shaders
    m_Shader = std::make_unique<Shader>("res/Shaders/Basic.shader");
    m_Shader->bind();
    m_Shader->setUniform4f("u_Color", 0.3f, 0.8f, 0.3f, 1.0f);

    // Setup textures
    m_Texture = std::make_unique<Texture>("res/Textures/GrassBlock.png");
    m_Shader->setUniform1i("u_Texture", 0);
  }

  TextureTest2D::~TextureTest2D()
  {
  }

  void TextureTest2D::OnUpdate(float deltaTime)
  {
  }

  void TextureTest2D::OnRender()
  {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Renderer renderer;

    m_Texture->bind(0);

    glm::mat4 modelA = glm::translate(glm::mat4(1.0f), m_TranslationA);
    glm::mat4 mvpA = m_Proj * m_View * modelA;
    m_Shader->bind();
    m_Shader->setUniformMat4f("u_MVP", mvpA);
    renderer.draw(*m_VAO, *m_IndexBuffer, *m_Shader);

    glm::mat4 modelB = glm::translate(glm::mat4(1.0f), m_TranslationB);
    glm::mat4 mvpB = m_Proj * m_View * modelB;
    m_Shader->bind();
    m_Shader->setUniformMat4f("u_MVP", mvpB);
    renderer.draw(*m_VAO, *m_IndexBuffer, *m_Shader);
  }

  void TextureTest2D::OnImGuiRender()
  {
    ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);
    ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  }
}