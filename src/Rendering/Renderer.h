#pragma once
#include "Precompilied.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

class Renderer
{
public:
  void clear() const;

  void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

};