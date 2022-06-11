#include <iostream>
#include "Polynominal.h" //Polynomial 객체를 삽입
using namespace std; // 그 공간의 이름은 std(함수들 정의되어있음) 클래스 이름공간을 사용하겠다

int main(){
    Polynomial A, B, C; // 다항식 객체 A, B, C 생성함
    int x; // 대입할 값을 저장하는 변수

    cout << "다항식 A 입력 : ";
    A.new_poly();
    cout<<A;

    cout<< "\n다항식 B 입력 : ";
    B.new_poly();
    cout<<B;

    cout << "\n입력한 식 A = " << A;
    cout << "\n입력한 식 B = " << B;

    C = Polynomial::mul(A, B); //mul연산을 통해 A와 B다항식을 곱한 다항식 C에 대입

    cout << "\nA X B = "<< C;
    cout << "\n대입할 값 x 입력 : ";
    cin >> x;

    //출력
    cout << "\n결과 : " << "A("<<x<<")= "<< A.eval(x) <<endl << "B(" << x << ")" << B.eval(x) << " C(" << x << ")=" << C.eval(x) << endl;

    return 0;
}