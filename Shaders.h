#ifndef SHADERS_H
#define SHADERS_H
#include <string>
#include <iostream>
#include <unordered_map>
#include <glm/glm.hpp>
#pragma once

using namespace std;
struct ShaderProgramSource
{
    string VertexSource;
    string FragmentSource;
};
class Shaders
{
private:
    unordered_map<string, int> m_UniformLocationCache;
    string m_FilePath;
    unsigned int m_RendererID;
    bool CompileShader();
    ShaderProgramSource ParseShader(const string &filepath);
    unsigned int CompileShader(unsigned int type, const string &source);
    unsigned int CreateShader(const string &vertexShader, const string &fragmentShader);

    unsigned int getUniformLocation(const string& name);
public:
    Shaders(const string &filepath);
    ~Shaders();

    void Bind() const;
    void UnBind() const;
    void SetUniform4f(const string &name, float v0, float v1, float v2, float v3);
    void SetUniformMat4f(const string& name, const glm::mat4& matrix);
    void SetUniform1i(const string &name, int value);
    // caching for uniform
};

#endif // SHADERS_H
