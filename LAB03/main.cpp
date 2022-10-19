#include <iostream>
#include <math.h>

float bealeF (float x, float y) {

    if(x>=-4.5 && x<=4.5 && y>=-4.5 && y<=4.5) {
        float a = pow((1.5 - x + x*y),2);
    float b = pow((2.25 - x + x*pow(y,2)), 2);
    float c = pow((2.625 - x + x*pow(y,3)),2);

    float f = a + b + c;

    return f;
    } else {
        return -999.99;
    }
}

float gpF (float x, float y) {

    if(x>=-2 && x<=2 && y>=-2 && y<=2) {
        float a = (pow((x+y+1),2));
    float b = (19 - 14*x + 3*pow(x,2) - 14*y + 6*x*y + 3*pow(y,2));
    float c = pow((2*x - 3*y),2);
    float d = (18 - 32*x + 12*pow(x,2) + 48*y - 36*x*y + 27*pow(y,2));

    float f = (1 + a*b) * (30 + c*d);

    return f;
    } else {
        return -999999999.99;
    }
}

float matyasF (float x, float y) {

    if(x>=-10 && x<=10 && y>=-10 && y<=10) {
        float f = 0.26*(pow(x,2)*pow(y,2)) - 0.48*x*y;

    return f;
    } else {
        return -999999999.99;
    }

    
}

void wypisz(int a, float x, float y) {


    switch(a) {
        case 1:
        if(bealeF(x,y) == -999.99) { std::cout << "Zmienna poza dziedziną."; break; }
        std::cout << "f(x,y) = (1.5 - x + xy)^2 + (2.25 - x +xy^2)^2 + (2.625 - x +xy^2)^2" << std::endl;
        std::cout << "x: " << x << std::endl;
        std::cout << "y: " << y << std::endl;
        std::cout << bealeF(x,y) << std::endl;
        break;

        case 2:
        if(gpF(x,y) == -999.99) { std::cout << "Zmienna poza dziedziną."; break; }
        std::cout << "f(x,y) = [1 + (x + y +1)^2 * (19 - 14x + 6xy + 3x^2)] [30 + (2x -3y)^2 (18 - 32x + 12x^2 +48y - 36xy +27x^2)]" << std::endl;
        std::cout << "x: " << x << std::endl;
        std::cout << "y: " << y << std::endl;
        std::cout << gpF(x,y) << std::endl;
        break;

        case 3:
        if(matyasF(x,y) == -999.99) { std::cout << "Zmienna poza dziedziną."; break; }
        std::cout << "f(x,y) = 0.26(x^2 + y^2) - 0.48xy" << std::endl;
        std::cout << "y: " << y << std::endl;
        std::cout << "x: " << x << std::endl;
        std::cout << matyasF(x,y) << std::endl;
        break;
    }

}

int main() {

    wypisz(1,-5,5);

    return 0;
}