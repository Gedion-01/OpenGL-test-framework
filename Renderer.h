#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include <GL/glew.h>
#include <signal.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shaders.h"

void debugbreak();

//
#define ASSERT(x) if (!(x)) debugbreak();
#define GLCALL(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char *func, const char *file, int line);

class Renderer
{
public:
    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shaders &shaders) const;
    void Clear() const;
};



#endif // RENDERER_H_INCLUDED
