#pragma once // 헤더 파일의 내용을 한 번만 포함하도록 한다
#include <iostream> // iostream 라이브러리 사용

class Rectangle  // Rectangle 객체
{
private: //  private 영역에 멤버 변수 선언을 하여 외부 접근을 막는다
    static int id;  // 몇 번 째 객체인 지 알려줌
    int width;// 길이
    int height;//높이
    int xLow, yLow; // x좌표, y좌표

public:// 외부 접근이 가능한 부분이다.
    Rectangle();
    Rectangle(int, int, int, int); // 생성자를 정의한다
    ~Rectangle(); // 파괴자를 정의한다

    friend std::ostream& operator <<(std::ostream&, Rectangle&); // << 연산자 오버로딩
    friend std::istream& operator >>(std::istream&, Rectangle&);

    static Rectangle getInter(Rectangle& , Rectangle&);
    static int isIntersection(Rectangle&); // 겹치는 지 판별하여 출력이 되는지 안되는지 정한다
    static int showExtent(Rectangle&);

    Rectangle operator +(Rectangle&); // + 연산자 오버로딩
};
