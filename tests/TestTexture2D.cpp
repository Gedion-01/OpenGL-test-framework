#include "TestTexture2D.h"
#include <iostream>


namespace test{
    TestTexture2D::TestTexture2D()
    :m_translationA(400.0f, 400.0f, 0.0f), m_translationB(200.0f, 200.0f, 0.0f),
     m_scaleA(1.0f, 1.0f, 1.0f), m_scaleB(1.0f, 1.0f, 1.0f)

     {
        float positions[]
        {
            -50.0f,  -50.0f, 0.0f, 0.0f,
            50.0f,  -50.0f, 1.0f, 0.0f,
            50.0f,   50.0f, 1.0f, 1.0f,
            -50.0f,   50.0f, 0.0f, 1.0f
        };
        unsigned int indices[6] =
        {
            0, 1, 2,
            2, 3, 0
        };
        /***************************************/
        // Index Object
        /***************************************/

        m_Shaders = std::make_unique<Shaders>("./Resource/Basic.shader");
        m_VAO = std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 16*sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

        m_proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        m_view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        m_Shaders->Bind();
        std::cout << "f" << std::endl;
        m_Shaders->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        m_Texture = std::make_unique<Texture>("./Resource/textures/splash.png");
        m_Shaders->SetUniform1i("u_Texture", 0);

    }

    TestTexture2D::~TestTexture2D()
    {
        //dtor
    }
    void TestTexture2D::OnUpdate(float deltatime)
    {

    }

    void TestTexture2D::OnRender()
    {
        m_Shaders->Bind();
        m_Texture->Bind();
        Renderer renderer;
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
            glm::mat4 others = glm::scale(glm::mat4(1.0f), m_scaleA);
            glm::mat4 mvp = m_proj * m_view * model * others;
            m_Shaders->Bind();
            m_Shaders->SetUniformMat4f("u_MVP", mvp);
            //Bind
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shaders);
        }
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationB);
            glm::mat4 others = glm::scale(glm::mat4(1.0f), m_scaleB);
            glm::mat4 mvp = m_proj * m_view * model * others;
            m_Shaders->Bind();
            m_Shaders->SetUniformMat4f("u_MVP", mvp);
            //Bind
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shaders);
        }

    }

    void TestTexture2D::OnImGuiRender()
    {
        ImGui::SliderFloat3("Translation Obj1", &m_translationA.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("Translation Obj2", &m_translationB.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("Scale Obj1", &m_scaleA.x, 0.0f, 10.0f);
        ImGui::SliderFloat3("Scale Obj2", &m_scaleB.x, 0.0f, 10.0f);        // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }

}
