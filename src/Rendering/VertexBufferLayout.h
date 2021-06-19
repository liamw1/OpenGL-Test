#pragma once
#include "Precompilied.h"

struct VertexBufferElement
{
  unsigned int type;
  unsigned int count;
  unsigned char normalized;

  unsigned int getSizeOfType() const
  {
    switch (type)
    {
      case GL_FLOAT:         return sizeof(GLfloat);
      case GL_UNSIGNED_INT:  return sizeof(GLuint);
      case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
    }
    ASSERT(false, "Invalid GL type");
    return 0;
  }
};

class VertexBufferLayout
{
public:
  VertexBufferLayout()
    : m_Stride(0) {}

  template<typename T>
  void push(unsigned int count)
  {
    static_assert(false);
  }

  inline unsigned int getStride() const { return m_Stride; }
  inline const std::vector<VertexBufferElement>& getElements() const { return m_Elements; }

private:
  unsigned int m_Stride;
  std::vector<VertexBufferElement> m_Elements;
};



template<>
inline void VertexBufferLayout::push<float>(unsigned int count)
{
  m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
  m_Stride += count * sizeof(GLfloat);
}
template<>
inline void VertexBufferLayout::push<unsigned int>(unsigned int count)
{
  m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
  m_Stride += count * sizeof(GLuint);
}
template<>
inline void VertexBufferLayout::push<unsigned char>(unsigned int count)
{
  m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
  m_Stride += count * sizeof(GLubyte);
}