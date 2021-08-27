#pragma once
#include "Precompilied.h"
#include "Test.h"

namespace test
{
  class ClearColorTest : public Test
  {
  public:
    ClearColorTest();
    ~ClearColorTest();

    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnImGuiRender() override;

  private:
    float m_Color[4];
  };
}