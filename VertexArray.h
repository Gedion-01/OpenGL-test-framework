#ifndef VERTEXARRAY_H_INCLUDED
#define VERTEXARRAY_H_INCLUDED



#endif // VERTEXARRAY_H_INCLUDED
#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


class VertexArray
{
private:
    unsigned int m_RendererID;
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

    void Bind() const;
    void UnBind() const;
};
