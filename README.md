# MATHLIB

Here is a little mathematic librarie to learn maths.

Features that are already in the code : 

 - Vectors (Vector<type, size>())
 - Cross & Dot product
 - Calling as many properties as you want

 ### EXAMPLE


```c++

int main(int argc, char** argv)
{
    Vector3<float> myVector3(1.0f, 2.0f, 3.0f);
    Vector2<float> myVectorXY = myVector3.xy;

    std::cout << myVectorXY.x << "||" << myVectorXY.y << std::endl;
    return 0;
}

result = 1 || 2

```