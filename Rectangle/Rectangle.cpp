#include "Rectangle.h" // Rectangle 헤더 불러오기
#include <iostream> // 라이브러리 iostream 불러오기
//using namespace std;

int Rectangle::id = 0;  //Rectangle 객체가 몇 번 생성 되었는지 나타낸다.

Rectangle::Rectangle(int x, int y, int w, int h) { //생성자가 int 매개변수 4개를 받음
    xLow = x;
    yLow = y;
    width = w;
    height = h;

    std::cout << ++id << "번째 Rectangle 객체 생성\n\n"; //생성자 실행 시 호출되게 함
}

Rectangle::Rectangle(){
    xLow = 0;
    yLow = 0;
    width = 0;
    height = 0;
}

Rectangle::~Rectangle() { // 파괴자 생성
    std::cout << "좌표 (" << xLow << ',' << yLow << ')' // 객체 소멸시 호출됨
              << " Rectangle 객체 소멸\n\n";
}

std::ostream& operator<<(std::ostream& os, Rectangle& r) { // << 연산자 오버로딩 ostream의 객체와 rectangle 객체의 참조를 받는다
    os << "height : " << r.height << std::endl
       << "width : " << r.width << std::endl
       << "x : " << r.xLow << std::endl
       << "y : " << r.yLow << std::endl << std::endl;

    return os;
}
std::istream& operator ㅇ2>>(std::istream& is, Rectangle& r) { // cin의 역할을 하는 is 참조를 인자로 받음, Rectangle 객체에서만 오버로딩이 실행되기 위해 Rectangle객체의 참조를 전달함

    is >> r.xLow>>r.yLow>>r.width>>r.height;

    return is;
}


Rectangle Rectangle::operator+(Rectangle& r) { //>> 연산자 오버로딩 istream의 객체와 rectangle 객체의 참조를 받는다

    int sum_x, sum_y, sum_w, sum_h;

    sum_x = xLow + r.xLow;
    sum_y = yLow + r.yLow;
    sum_w = this->width + r.width;  //this를 통해 피연산되는 객체의 멤버변수에 접근
    sum_h = this->height + r.height;

    return Rectangle(sum_x, sum_y, sum_w, sum_h);
}

int Rectangle::isIntersection(Rectangle &r){ //  width 혹은 height가 없으면 겹치는 부분이 존재하지 않는다는 것
    if(r.height == 0 or r.width == 0){
        return 0;
    } else return 1;
}

int Rectangle::showExtent(Rectangle& r3){
    return (r3.width * r3.height);
}

Rectangle Rectangle::getInter(Rectangle& r1, Rectangle& r2){ //두 사각형이 겹칠 때
    if(r1.xLow > r2.xLow+r2.width){
        return Rectangle(0,0,0,0);

    };
    if(r1.xLow + r1.width < r2.xLow){
        return Rectangle(0,0,0,0);

    };
    if(r1.yLow > r2.yLow+r2.height){
        return Rectangle(0,0,0,0);

    };
    if(r1.yLow + r1.height < r2.yLow){
        return Rectangle(0,0,0,0);

    };
    int x_r3=0, y_r3=0, height_r3=0, width_r3=0;

    if(r1.xLow - r2.xLow > 0){
        x_r3=r1.xLow;
    }
    else{
        x_r3=r2.xLow;
    };

    if((r1.xLow + r1.width) - (r2.xLow + r2.width) > 0){

        width_r3 = (r2.xLow + r2.width) - x_r3;
    }
    else{
        width_r3 = (r1.xLow + r1.width) - x_r3;
    };

    if(r1.yLow - r2.yLow > 0){
        y_r3=r1.yLow;
    }
    else{
        y_r3=r2.yLow;
    };

    if((r1.yLow + r1.height) - (r2.yLow + r2.height) > 0){
        height_r3 = (r2.yLow + r2.height) - y_r3;
    }
    else{
        height_r3 = (r1.yLow + r1.height) - y_r3;
    }
    return Rectangle(x_r3, y_r3, width_r3, height_r3);
}



