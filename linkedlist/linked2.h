#include <iostream> // 라이브러리 iostream 불러오기
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std; // 그 공간의 이름은 std(함수들 정의되어있음) 클래스 이름공간을 사용하겠다.

class Card //카드는 Card 클래스의 객체 생성
{

public: // 외부 접근이 가능한 부분
    Card(); //생성자
    ~Card(); //파괴자
    void PickCard(); //카드를 랜덤으로 뽑음
    int Priority(Card& one); //우선순위, 차이를 구하여 재배치를 해줌
    int get_num();
    int num; //숫자
    char form; //모양
    int b_num; //숫자+모양
};

Card::Card()
{
    num = 0; //초기화
    form = NULL; //초기화
    b_num = 0; //초기화

}
Card::~Card() {

}

void Card::PickCard() //카드를 고르는 함수 생성
{
    int shape[4]={'S','D','H','C'} ;
    srand((unsigned int)time(NULL));

        b_num  = (rand()%52)+1;

            num = b_num % 13;
            form = shape[b_num/13];

            if(b_num % 13 == 0){
                num = 13;
                form = shape[(b_num%13)-1];
            }
}

int Card::get_num(){

    return this->b_num; //중복확인을 위한 메인에서 card 클래스에 접근하기 위해 만들어 줌
};

template<class T> class Chain; //전방선언


template<class T> // Node class을 tamplate로 구현
class Node {
    friend class Chain<T>; //Chain class에서 Node class 멤버에 접근하기 위함
private:
    T data;
    Node<T>* link; //next link
};


template<class T>//template Node를 사용하기 때문에 template 선언
class Chain {
    friend class Card; //Card class 멤버 변수에 접근하기 위함
    friend class Node<T>; // Node class 멤버에 접근하기 위함

private:
    Node<T> *front;//Chain의 가장 앞 Node를 가리키는 것

public:
    Chain() {//Chain에 Node가 없을 경우 front는 0을 가리킴
        front = 0;
    }

    ~Chain() {

    }

    void order() {
        Node<T> *current = front; //iterator current 구현함
        Node<T> *pre = 0; // current를 가리키고 있는 Node를 가리킴

        while (current->link != 0) { //마지막까지 반복


            if (current->data.b_num > current->link->data.b_num) { //current와 current 다음의 data를 비교함
                Node<T> *temp; //current 다음 Node를 가리킴
                temp = current->link;


                current->link = temp->link;
                temp->link = current;

                if (current != front) {// current가 front가 아니면 pre가 존재함
                    pre->link = temp;
                }

                if (current == front) {
                    front = temp;
                }

                pre = temp;

            } else {
                break;
            }

            cout << "swap : ";
            allprint();
        }
    }

    void allprint() {
        Node<T> *current = front;  //iterator current 구현함, front부터 시작

        while (current != 0) {//마지막까지 반복
            cout << current->data.form
                 << current->data.num
                 << " ";
            current = current->link; //현재 노드 출력하고 iterator를 다음 노드로 변경함

        }
        cout << endl;

    };

    void push(T &o) {
        Node<T> *temp = new Node<T>; //새로운 Node 동적할당
        temp->data = o; //새로운 Node의 data설정
        temp->link = front; //새로운 Node의 link 설정
        front = temp;
        cout << "New Card : "
             << temp->data.form
             << temp->data.num
             << endl;

        cout << "push : ";
        allprint();

        order();
    }
};