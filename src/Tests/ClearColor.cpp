#include "Precompilied.h"
#include "ClearColor.h"

namespace test
{
  ClearColor::ClearColor()
    : m_Color{ 0.2f, 0.3f, 0.8f, 1.0f }
  {
  }

  ClearColor::~ClearColor()
  {
  }

  void ClearColor::OnUpdate(float deltaTime)
  {
  }

  void ClearColor::OnRender()
  {
    glClearColor(m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void ClearColor::OnImGuiRender()
  {
    ImGui::ColorEdit4("Clear Color", m_Color);
  }
}
