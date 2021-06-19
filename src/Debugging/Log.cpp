#include "Precompilied.h"
#include "Log.h"

static std::vector<std::pair<std::string, int>> errors;
static std::vector<std::string> glErrors;

void logError(std::string message, LogLevel logLevel, std::string file, int line)
{
  bool uniqueError = true;
  for (int i = 0; i < errors.size(); ++i)
  {
    if (line == errors[i].second && file == errors[i].first)
    {
      uniqueError = false;
      break;
    }
  }

  if (uniqueError)
  {
    switch (logLevel)
    {
    case LogLevel::Error:
      std::cout << "[Error] ";
      break;
    case LogLevel::Warning:
      std::cout << "[Warning] ";
      break;
    case LogLevel::Info:
      std::cout << "[Info] ";
      break;
    }

    std::pair<std::string, int> error = { file, line };
    errors.emplace_back(error);
    std::cout << message << " ---> " << file << " line " << line << std::endl;
  }
}

void openGLLogMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
  std::string glMessage = message;

  bool uniqueError = true;
  for (int i = 0; i < glErrors.size(); ++i)
  {
    if (glErrors[i] == glMessage)
    {
      uniqueError = false;
      break;
    }
  }

  if (uniqueError)
  {
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
      std::cout << "[OpenGL Error] ";
      break;
    case GL_DEBUG_SEVERITY_MEDIUM:
      std::cout << "[OpenGL Warning] ";
      break;
    case GL_DEBUG_SEVERITY_LOW:
      std::cout << "[OpenGL Info] ";
      break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      break;
    }

    glErrors.emplace_back(glMessage);
    std::cout << message << std::endl;
  }
}
