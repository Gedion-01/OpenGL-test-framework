#ifndef VERTEXBUFFERLAYOUT_H_INCLUDED
#define VERTEXBUFFERLAYOUT_H_INCLUDED



#endif // VERTEXBUFFERLAYOUT_H_INCLUDED
#pragma once

#include <iostream>
#include <vector>
#include <GL/glew.h>

template <typename T>
struct identity{ typedef T type; };

struct VertexBufferElement
{
    unsigned int type;
    unsigned int Count;
    unsigned char normalized;

    static unsigned int GetSizeofType(unsigned int type)
    {
        switch(type)
        {
            case GL_FLOAT           :return 4;
            case GL_UNSIGNED_INT    :return 4;
            case GL_UNSIGNED_BYTE   :return 1;
        }
    }
};
class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_stride;
public:
    VertexBufferLayout() : m_stride(0) {};

    // template declaration
    template <typename T>
    void Push(unsigned int Count)
    {
        Push(Count, identity<T>());
    }
private:
    /* template specialization of function Push(unsigned int); */
    void Push(unsigned int Count, identity<float>)
    {
        std::cout << "float" << std::endl;
        m_Elements.push_back({ GL_FLOAT, Count, GL_FALSE });
        m_stride += Count * VertexBufferElement::GetSizeofType(GL_FLOAT);
        std::cout << Count << std::endl;
    }
    void Push(unsigned int Count, identity<unsigned int>)
    {
        m_Elements.push_back({ Count, GL_UNSIGNED_INT, GL_FALSE });
        m_stride += Count * VertexBufferElement::GetSizeofType(GL_UNSIGNED_INT);
    }
    void Push(unsigned int Count, identity<unsigned char>)
    {
        m_Elements.push_back({ GL_UNSIGNED_BYTE, Count, GL_TRUE });
        m_stride += Count * VertexBufferElement::GetSizeofType(GL_UNSIGNED_BYTE);
    }
public:
    inline const std::vector<VertexBufferElement> GetElement()const { return m_Elements; } // Should return cons&
    inline unsigned int GetStride() const { return m_stride; }
};
