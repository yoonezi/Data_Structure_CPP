#include <iostream> // iostream 라이브러리 사용
#include <string> // string 라이브러리 사용
#include <cmath> // math 라이브러리 사용

using namespace std; // 그 공간의 이름은 std(함수들 정의되어있음) 클래스 이름공간을 사용하겠다.



class Polynomial; //전방선언

class Term //Term 객체 생성
        {
    friend Polynomial;

private: //외부접근 불가
    float theCoeff=0; //계수
    int theExp=0; //지수
    friend class Polynomial; //friend로 Polynomial 클래스의 해당 멤버변수에 접근 가능함

public:
    Term(): theCoeff(0), theExp(0){}; // Term이라는 객체에 변수 theCoeff와 theExp를 추가
    Term(float a, int b){ // 인자있는 경우를 위해 constructor overloading 선언
        theCoeff = a;
        theExp = b;
    }
    ~Term()=default; //파괴자 선언 및 정리
};
///끝

class Polynomial {
private:
    Term *termArray; //Term 포인터로 Term을 담을 배열을 선언함
    int capacity; //배열의 공간
    int terms;  //항의 갯수
public:
    Polynomial() {
        capacity = 1;//1로 초기화
        terms = 0; //저장된 항의 수로 0으로 초기화
        termArray = new Term[capacity]; //포인터 변수 termarray에 new를 통해 배열을 할당해주고 초기화함

    };//끝

    static Polynomial mul(const Polynomial &A, const Polynomial &B) //다항식 A와 B의 곱셈, static으로 해당 객체 없이 호출 가능하게 선언
    {
        Polynomial C;
        float nCof = 0;
        int nExp = 0;
        for (int i = 0; i < A.terms; i++){ // A다항식의 길이만큼 반복
            for (int j = 0; j < B.terms; j++){ //B 다항식의 길이만큼 반복
                nCof= A.termArray[i].theCoeff*B.termArray[j].theCoeff; //A다항식의 i번째 계수 x B다항식의 j번째 계수를 한 값을 nCof에 저장
                nExp = A.termArray[i].theExp+B.termArray[j].theExp; //A다항식의 i번째 지수 x B다항식의 j번째 지수를 한 값을 nExp에 저장
                 C.newTerm(nCof,nExp); //새로 만들어진 nCof,nExp를 newTerm로 새로운 항 추가
            }
        }
        C.sum(); //정렬 및 정리

        return C;
    }



    int eval(const int &X) { //정상
        int sumOfPol = 0; //각 항들에 x를 대입한 값을 저장
        for (int i = 0; i < this->terms; i++) {
            sumOfPol += this->termArray[i].theCoeff * pow(X, this->termArray[i].theExp);
        }
        return sumOfPol; // 반환
    }


    void newTerm(const float theCoeff, const int theExp) { //Poly배열에 Term추가
        if (terms == capacity) // termArrary가 꽉 차면 두배로 확장
        {
            capacity *= 2;
            Term *temp = new Term[capacity]; //새로운 배열
            copy(termArray, termArray + terms, temp); //기존 termArray에 있던 내용을 새로 확장된 termArray로 옮겨줌
            delete[]termArray; //예전 term 배열 삭제
            termArray = temp; // 기존에 있던 배열에 복사한 배열을 할당
        }
        //termArraydml 크기에 문제 없으면, 배열 끝에 값들 첨가함
        termArray[terms].theCoeff = theCoeff;
        termArray[terms++].theExp = theExp;
    };
    void sum() { //해당 다항식 객체에서 같은 지수에 대하여 식을 정리하는 함수
        for (int i = 0; i < terms; i++) { // 기준 인덱스
            for (int j = i + 1; j < terms; j++) { // 비교 인덱스, i보다 한칸 뒤여야 한다
                if (termArray[i].theExp == termArray[j].theExp) {// 두 항의 지수가 같다면
                    float tmpCoef = termArray[i].theCoeff + termArray[j].theCoeff; // 계수를 합하고
                    termArray[i] = Term(tmpCoef, termArray[i].theExp); // 합한 계수 및 지수에 대한 term을 생성하여 기준 인덱스에 삽입함

                    for (int k = j; k < terms; k++) { // 비교인덱스에 대해
                        termArray[k] = termArray[k + 1]; //두 항을 합해주었으니 비교 인덱스에 있는 항을 제거하고, 그 뒤 항들을 앞으로 당겨온다.
                    }
                    terms--;// 항이 하나 줄었으니 총 항의 개수도 감소
                }
            }
        }
        for (int i = 0; i < terms; i++) {
            if (termArray[i].theCoeff == 0) {// 항을 합친 이후 계수가 0인 항에 대해서는
                for (int k = i; k < terms; k++) {
                    termArray[k] = termArray[k + 1];//0인 항들은 지우고 각 항들을 앞으로 당겨온다
                }
                terms--; //항 개수 감소
            }
        }
    };
//H/W
    friend ostream &operator<<(ostream& os, Polynomial& poly) {
        for (int i = 0; i < poly.terms; i++) {
            if (poly.termArray[i].theCoeff > 1) os << poly.termArray[i].theCoeff; // possible the 1~9 중 1보다 큰 계수만 출력
            if (poly.termArray[i].theCoeff < 1) os << poly.termArray[i].theCoeff;// possible the 1~9 중 1보다 작은 계수만 출력
            if ((poly.termArray[i].theCoeff == 1) && (poly.termArray[i].theExp == 0)) os << poly.termArray[i].theCoeff; // 상수항이 1일 때의 예외처리
            if (poly.termArray[i].theExp > 1 || poly.termArray[i].theExp < 1) os << "x^"; // 지수가 2 이상이어야 x^num 꼴로 출력
            if (poly.termArray[i].theExp == 1) os << "x"; // 지수가 1일땐 x만 출력
            if (poly.termArray[i].theExp > 1) os << poly.termArray[i].theExp; // 지수가 2 이상일 때만 지수 따로 출력
            if (i != poly.terms - 1) os << " + ";
        }
        return  os;
    }
    void new_poly(){ //입력을 함수로
        int n;
        //int polyarray[100];
        float Ncoeff;
        int Nexp;

        int count = 0;

        do{
            cin >> n; //입력 받은 값을 n에 저장
            count += 1; //계수인지 지수인지 판단, 1과 2만 반복
            if(count == 1){ //만약 1이라면
                Ncoeff = n; //계수

            }else { //만약 1이 아닌 즉, 2라면
                Nexp = n; //지수

                this->newTerm(Ncoeff, Nexp); //계수와 지수로 이루어진 한 항이 생성되면 newTerm으로 줌
                count = 0;
            }

        }while(getchar() == ' '); //공백을 기준으로 한줄로 받은 숫자를 구분함
        this->sum(); //정렬 및 정리
    }

    Polynomial& operator=(const Polynomial &A){ //할당 연산자 오버로딩
        this->termArray = A.termArray; // 인자로 들어온 객체를 바인딩 하기 위해 할당함
        this->terms = A.terms;
        this->capacity = A.capacity;

        return *this;
    }

};