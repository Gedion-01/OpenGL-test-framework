#include <iostream>
#include "Renderer.h"

using namespace std;
void debugbreak()
{
    raise(SIGABRT);
}
void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}
bool GLLogCall(const char *func, const char *file, int line)
{
    while(GLenum error = glGetError())
    {
        cout << "OPENGL ERROR [" << error << "] " << func << " " << file << "| ERROR at line " << line << endl;
        return false;
    }
    return true;
}
void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shaders& shaders) const
{
    shaders.Bind();
    va.Bind();
    ib.Bind();
    GLCALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
void Renderer::Clear() const
{
    GLCALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}
