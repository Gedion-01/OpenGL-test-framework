#include <iostream>
#include "VertexArray.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
    GLCALL(glGenVertexArrays(1, &m_RendererID));
}
VertexArray::~VertexArray()
{
    GLCALL(glDeleteVertexArrays(0, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
    Bind();
    vb.Bind();
    const auto &elements = layout.GetElement();
    unsigned int offset = 0;
    //std::cout << elements.size();
    for(int i = 0; i < elements.size(); i++)
    {
        std::cout << i << endl;
        const auto &element = elements[i];
        GLCALL(glEnableVertexAttribArray(i)); //Enabled
        GLCALL(glVertexAttribPointer(i, element.Count, element.type, element.normalized, layout.GetStride(), (const void*) offset));
        offset += element.Count * VertexBufferElement::GetSizeofType(element.type);
        std::cout << "Stride: " << layout.GetStride() << std::endl;
        std::cout << "Next-Offset: " << offset << std::endl;
    }

}
void VertexArray::Bind() const
{
    GLCALL(glBindVertexArray(m_RendererID))
}
void VertexArray::UnBind() const
{
    GLCALL(glBindVertexArray(0));
}
