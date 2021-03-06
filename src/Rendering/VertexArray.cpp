#include "Precompilied.h"
#include "VertexArray.h"

VertexArray::VertexArray()
  : m_RendererID(0)
{
  glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
  glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::bind() const
{
  glBindVertexArray(m_RendererID);
}

void VertexArray::unBind() const
{
  glBindVertexArray(0);
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
  this->bind();
  vb.bind();
  const auto& elements = layout.getElements();
  unsigned int offset = 0;
  for (unsigned int i = 0; i < elements.size(); ++i)
  {
    const auto& element = elements[i];
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
    offset += element.count * element.getSizeOfType();
  }
}
