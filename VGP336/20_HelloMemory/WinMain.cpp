#include <CASTLE_Engine/Inc/CASTLE_Engine.h>

using namespace CASTLEEngine;
using namespace CASTLEEngine::Core;

class Student
{
public:
    Student() = default;
    Student(const std::string& name, int classMark = 0)
        : mName(name)
        , mClassMark(classMark)
    {

    }

    void SetName(const std::string& name) { mName = name; }
    void SetGrade(int classMark) { mClassMark = classMark; }

private:
    std::string mName;
    int mClassMark;
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    // Memory poopl we want to create and the max numbe rof that type we will have
    TypedAllocator studentPool = TypedAllocator<Student>("StudentPool", 100);

    // Default constructor
    Student* a = studentPool.New();
    Student* b = studentPool.New();
    a->SetName("Frank");
    b->SetName("Leon");
    b->SetName("Leonidas");

    // Custom constructor
    Student* c = studentPool.New("Leo", 1);
    Student* d = studentPool.New("Andriy");

    // Do stuff with students
    // Run game

    studentPool.Delete(d);
    studentPool.Delete(c);
    studentPool.Delete(b);
    studentPool.Delete(a);

    return 0;
}