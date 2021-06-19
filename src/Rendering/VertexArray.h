#pragma once
#include "Precompilied.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
  VertexArray();
  ~VertexArray();

  void bind() const;
  void unBind() const;

  void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

private:
  unsigned int m_RendererID;
};