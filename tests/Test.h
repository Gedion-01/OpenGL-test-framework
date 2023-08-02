#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED
#include <vector>
#include <functional>
#include <iostream>

namespace test
{
    class Test
    {
    public:
        Test(){}
        virtual ~Test(){}
        virtual void OnUpdate(float deltatime){}
        virtual void OnRender(){}
        virtual void OnImGuiRender(){}
        void hello(){std::cout << "Hello\n"; }
    };
    class TestMenu :public Test
    {
    private:
        Test*& m_CurrentTest;
        std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
    public:
        TestMenu(Test*& currentTestPointer);

        template<typename T>
        void RegisterTest(const std::string &name)
        {
            m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
            std::cout << "Registering " << name << std::endl;
        }
        void OnImGuiRender() override;
    };
}

#endif // TEST_H_INCLUDED
