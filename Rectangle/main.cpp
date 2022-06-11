#include <iostream> // iostream 삽입
#include "Rectangle.h" // 클래스 Rectangle가 있는 헤더파일 삽입

int main() {
    Rectangle r1, r2, r3; // Rectangle 객체인 r1, r2, r3을 생성함

    std::cin >> r1; // r1 멤버 변수를 입력 받음
    std::cout << r1; // r1 멤버 변수를 출력함

    std::cin >> r2; // r2 멤버 변수를 입력 받음
    std::cout << r2; // r2 멤버 변수를 출력함

    r3 = Rectangle::getInter(r1, r2);  // Rectangle 클래스의 메소드를 통해 겹치는 사각형에 대한 객체 r3 생성함
    if(Rectangle::isIntersection(r3)){ // r3가 가로, 세로가 존재한다면
        std::cout << r3; // r3 객체를 출력함
        std::cout << "넓이:" <<Rectangle::showExtent(r3) << std::endl;
    }else std::cout << "겹치는 부분이 존재하지 않습니다." << std::endl; // 가로 혹은 세로가 존재하지 않는다면 겹쳐서 생기는 intersected 박스가 존재하지 않는다는 의미.

}