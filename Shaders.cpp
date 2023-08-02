#include "Shaders.h"
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.h"

using namespace std;


bool Shaders::CompileShader()
{

}
ShaderProgramSource Shaders::ParseShader(const string &filepath)
{
    ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    string line;
    stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line))
    {
        if(line.find("#shader") != string::npos)
        {
            if(line.find("vertex") != string::npos){
                cout << line << endl;
                type = ShaderType::VERTEX;
            }

            else if(line.find("fragment") != string::npos){
                type = ShaderType::FRAGMENT;
            }
        }
        else{
                cout << line << endl;
            ss[(int) type] << line << "\n";
        }
    }
    return {ss[0].str(), ss[1].str()};
}
unsigned int Shaders::CompileShader(unsigned int type, const string &source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    GLCALL(glShaderSource(id, 1, &src, nullptr));
    GLCALL(glCompileShader(id));

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length*sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        cout << "Failed to compile " <<(type == GL_VERTEX_SHADER ? "vertex" : "fragment") << endl;
        cout << message << endl;
    }

    return id;
}
unsigned int Shaders::CreateShader(const string &vertexShader, const string &fragmentShader)
{
    unsigned int program = glCreateProgram(); // create program
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    //
    //
    return program;
}
Shaders::Shaders(const string& filepath) : m_FilePath(filepath), m_RendererID(0)
{
    //
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shaders::~Shaders()
{
    GLCALL(glDeleteProgram(m_RendererID));
}

void Shaders::Bind() const
{
    GLCALL(glUseProgram(m_RendererID));//using current shader
}

void Shaders::UnBind() const
{
    GLCALL(glUseProgram(0));
}

void Shaders::SetUniform4f(const string& name, float v0, float v1, float v2, float v3)
{
    GLCALL(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}
void Shaders::SetUniform1i(const string& name, int value)
{
    GLCALL(glUniform1i(getUniformLocation(name), value));
}
void Shaders::SetUniformMat4f(const string& name, const glm::mat4& matrix)
{
    GLCALL(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}
unsigned int Shaders::getUniformLocation(const string& name)
{
    if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end()){
        return m_UniformLocationCache[name];
    }
    GLCALL(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if(location == -1)
    {
        cout << "Warning: uniform " << name << " doesn't exist!" << endl;
    }
    m_UniformLocationCache[name] = location;
    return location;
}
