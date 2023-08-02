#ifndef TESTCLEARCOLOR_H
#define TESTCLEARCOLOR_H
#include <iostream>

#include "Test.h"


namespace test{
    class TestClearColor : public Test
    {
    public:
        TestClearColor();
        virtual ~TestClearColor();

        void OnUpdate(float deltatime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    protected:

    private:
        float m_ClearColor[4];
    };
}
#endif // TESTCLEARCOLOR_H
