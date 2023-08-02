#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED
#include "Renderer.h"
#pragma once
using namespace std;

class Texture
{
private:
    unsigned int m_RendererID;
    string m_FilePath;
    unsigned char *m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
public:
    Texture(const string &path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void UnBind() const;

    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
};

#endif // TEXTURE_H_INCLUDED
