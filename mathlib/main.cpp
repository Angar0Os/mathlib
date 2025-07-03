#include <iostream>
#include <vector.h>

#include <vector/vector3.h>
#include <vector/vector2.h>

int main(int argc, char** argv)
{
    Vector3<float> v(1.0f, 2.0f, 3.0f);
    Vector2<float> xy = v.xy;
    v.xy = Vector2<float>(5.0f, 6.0f);

    std::cout << xy.x << "||||"<< xy.y << std::endl;
    return 0;
}	