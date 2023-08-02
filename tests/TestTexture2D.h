#ifndef TESTTEXTURE2D_H
#define TESTTEXTURE2D_H
#include "Test.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
//custom class
#include "../Shaders.h"
#include "../Renderer.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../VertexArray.h"
#include "../Texture.h"
// iamgui
#include "../vendor/iamgui/imgui.h"
//
#include "../vendor/stb_image/stb_image.h"
#include <memory>

namespace test{
    class TestTexture2D :public Test
    {
        public:
            TestTexture2D();
            virtual ~TestTexture2D();
            void OnUpdate(float deltatime) override;
            void OnRender() override;
            void OnImGuiRender() override;

        protected:

        private:
            unsigned int indices[6];
            // This will be changed to Unique pointer in the future.
            std::unique_ptr<VertexArray> m_VAO;
            std::unique_ptr<IndexBuffer> m_IndexBuffer;
            std::unique_ptr<VertexBuffer> m_VertexBuffer;
            std::unique_ptr<Shaders> m_Shaders;
            std::unique_ptr<Texture> m_Texture;
            //****************************************************
            glm::vec3 m_translationA;
            glm::vec3 m_translationB;
            glm::vec3 m_scaleA;
            glm::vec3 m_scaleB;
            glm::mat4 m_proj;
            glm::mat4 m_view;
            glm::mat4 m_Rotate;
};
}
#endif // TESTTEXTURE2D_H
