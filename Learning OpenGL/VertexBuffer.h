#ifndef VERTEXBUFFER_H_INCLUDED
#define VertexBUFFER_H_INCLUDED



#endif // VertexBUFFER_H_INCLUDED
#pragma once
class VertexBuffer
{
private:
    unsigned int m_RendererID;
public:
    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;
};
