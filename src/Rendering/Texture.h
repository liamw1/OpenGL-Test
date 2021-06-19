#pragma once
#include "Precompilied.h"

class Texture
{
public:
  Texture(const std::string& filePath);
  ~Texture();

  void bind(unsigned int slot = 0) const;
  void unBind() const;

private:
  unsigned int m_RendererID;
  std::string m_FilePath;
  unsigned char* m_LocalBuffer;
  int m_Width, m_Height, m_BPP;

  inline int getWidth() const { return m_Width; }
  inline int getHeight() const { return m_Height; }
};