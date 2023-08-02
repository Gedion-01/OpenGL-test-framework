#include "TestClearColor.h"
#include "../Renderer.h"
#include "../vendor/iamgui/imgui.h"

namespace test{

    TestClearColor::TestClearColor() : m_ClearColor {0.000f, 1.000f, 1.000f, 0.000f}
    {
        //ctor
    }

    TestClearColor::~TestClearColor()
    {
        //dtor
    }
    void TestClearColor::OnUpdate(float deltatime)
    {

    }
    void TestClearColor::OnRender()
    {
        GLCALL(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));
    }
    void TestClearColor::OnImGuiRender()
    {
        ImGui::ColorEdit4("Clear Color", m_ClearColor);
    }

}
