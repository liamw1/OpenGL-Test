#pragma once
#include "StdLib.h"

enum class LogLevel
{
  Error,
  Warning,
  Info
};

void logError(std::string message, LogLevel logLevel, std::string file, int line);

void openGLLogMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);