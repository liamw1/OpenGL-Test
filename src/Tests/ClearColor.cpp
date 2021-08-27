#include "Precompilied.h"
#include "ClearColorTest.h"

namespace test
{
  ClearColorTest::ClearColorTest()
    : m_Color{ 0.2f, 0.3f, 0.8f, 1.0f }
  {
  }

  ClearColorTest::~ClearColorTest()
  {
  }

  void ClearColorTest::OnUpdate(float deltaTime)
  {
  }

  void ClearColorTest::OnRender()
  {
    glClearColor(m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void ClearColorTest::OnImGuiRender()
  {
    ImGui::ColorEdit4("Clear Color", m_Color);
  }
}
