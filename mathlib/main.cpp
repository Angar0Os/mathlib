#include <iostream>
#include <cmath>
#include <math/math.hpp>

using namespace math;

int main()
{
    std::cout << "--- TEST REFLECT 2D ---\n";

    Vec2 I2{ 1.0f, -1.0f };      // vecteur incident
    Vec2 N2{ 0.0f, 1.0f };       // normale unitaire
    Vec2 R2 = Reflect(I2, N2);

    std::cout << "I2: (" << I2[0] << ", " << I2[1] << ")\n";
    std::cout << "R2: (" << R2[0] << ", " << R2[1] << ")\n";
    std::cout << "Dot(R2, N2) = " << Dot(R2, N2) << " (should be " << -Dot(I2, N2) << ")\n";

    std::cout << "\n--- TEST REFLECT 3D ---\n";

    Vec3 I3{ 1.0f, -2.0f, 0.5f };
    Vec3 N3{ 0.0f, 1.0f, 0.0f };
    Vec3 R3 = Reflect(I3, N3);

    std::cout << "I3: (" << I3[0] << ", " << I3[1] << ", " << I3[2] << ")\n";
    std::cout << "R3: (" << R3[0] << ", " << R3[1] << ", " << R3[2] << ")\n";
    std::cout << "Dot(R3, N3) = " << Dot(R3, N3) << " (should be " << -Dot(I3, N3) << ")\n";

    std::cout << "\n--- TEST REFRACT 3D ---\n";

    Vec3 I{ 0.0f, -1.0f, -1.0f };
    Vec3 N{ 0.0f, 0.0f, 1.0f };
    float EtaIn = 1.0f;    // air
    float EtaOut = 1.5f;   // verre

    Vec3 T = Refract(I, N, EtaIn, EtaOut);

    std::cout << "I: (" << I[0] << ", " << I[1] << ", " << I[2] << ")\n";
    std::cout << "T: (" << T[0] << ", " << T[1] << ", " << T[2] << ")\n";

    // Vérification de la loi de Snell
    float cosTheta1 = -Dot(I, N) / I.Length();
    float cosTheta2 = -Dot(T, N) / T.Length();
    float theta1 = std::acos(cosTheta1);
    float theta2 = std::acos(cosTheta2);
    std::cout << "theta1 = " << theta1 << " rad, theta2 = " << theta2 << " rad\n";
    std::cout << "n1*sin(theta1) = " << EtaIn * std::sin(theta1)
        << ", n2*sin(theta2) = " << EtaOut * std::sin(theta2) << "\n";

    return 0;
}
