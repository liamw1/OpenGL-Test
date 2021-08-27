#pragma once
#include "Precompilied.h"

namespace test
{
  class Test
  {
  public:
    Test() {}
    virtual ~Test() {}

    virtual void OnUpdate(float deltaTime) {}
    virtual void OnRender() {}
    virtual void OnImGuiRender() {}
  };

  class TestMenu : public Test
  {
  public:
    TestMenu(Test*& currentTestPointer);

    void OnImGuiRender() override;

    template<typename T>
    void registerTest(const std::string& name)
    {
      std::cout << "Registering test " << name << std::endl;
      m_Tests.emplace_back(std::make_pair(name, []() { return new T(); }));
    }

  private:
    Test*& m_CurrentTest;
    std::vector <std::pair<std::string, std::function<Test*()>>> m_Tests;
  };
}