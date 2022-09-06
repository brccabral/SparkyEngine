#pragma once

#ifdef SPARKY_EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#include <FreeImage.h>
#include <FreeImage/Utilities.h>
#else
#include <GL/glew.h> // need to include before GLFW
#endif

#include <GLFW/glfw3.h>