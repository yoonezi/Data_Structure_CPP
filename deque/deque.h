#include <iostream> // 라이브러리 iostream 불러오기
#include <string> // 라이브러리 string 불러오기
#include <cstdlib> // 라이브러리 cstdlib 불러오기
#include <ctime> // 라이브러리 ctime 불러오기

using namespace std; // 그 공간의 이름은 std(함수들 정의되어있음) 클래스 이름공간을 사용하겠다.


template <class T> //어떠한 데이터 타입의 객체도 저장
class Bag {
public:
    Bag (int bagCapacity = 10); //생성자
    bool IsEmpty() const; //백이 공백상태이면 TURE, 아니면 FALSE를 반환
    T& Top() const;
    void Push(const T& item); //T타입의 원소 하나를 백에 삽입

protected:
    T* stack;
    int top; //배열에서 원소가 들어 있는 가장 높은 위치
    int capacity; //배열의 크기
};

template <class T>
Bag<T>::Bag(int bagCapacity):capacity(bagCapacity)
{
    if (capacity < 1) throw "Stack capacity must be >= 0";
    stack = new T[capacity];
    top = -1;
}

template <class T>
void ChangeSize(T*& arr, const int oldsize, const int newsize)
{
    if (newsize < 0) throw "New length must be >= 0";
    T* temp = new T[newsize];
    int number = min(oldsize, newsize);
    copy(arr, arr + number, temp);
    delete[]arr;
    arr = temp;
}

template <class T>
inline bool Bag<T>::IsEmpty() const { return top == -1; } // stack에 원소가 없다면 true, 있으면 false
template <class T>
inline T& Bag<T>::Top() const
{
    if (IsEmpty()) throw "Stack Empty";
    return stack[top];
}

template <class T>
void Bag<T>::Push(const T& x)
{
    if (top == capacity - 1)
    {
        ChangeSize(stack, capacity, 2 * capacity);
        capacity *= 2;
    }
    stack[++top] = x;
}

class Card //카드는 Card 클래스의 객체 생성
{
    friend class Deque;
public: // 외부 접근이 가능한 부분
    Card(); //생성자
    ~Card(); //파괴자
    void PickCard(); //카드를 랜덤으로 뽑음
    int Priority(Card& one); //우선순위, 차이를 구하여 재배치를 해줌
    int get_num(); //

private: //  private 영역에 멤버 변수 선언을 하여 외부 접근을 막음
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

    while(1) {
        b_num  = (rand()%52)+1;

        for (int i = 0; i < 5; i++) {
            if (b_num / 13 == 0) {
                form = shape[0]; //몫이 0일 때, 스페이드
            } else if (b_num / 13 == 1) {
                form = shape[1]; //몫이 1일 때, 다이아몬드
            } else if (b_num / 13 == 2) {
                form = shape[2]; //몫이 2일 때, 하트
            } else {
                form = shape[3]; //몫이 3일 때, 클로버
            }
            num = b_num % 13;
            if(b_num % 13 == 0){
                num = 13;
            }
        }
        break;
    }
}

int Card::Priority(Card& one){ //우선순위
    int gap = b_num - one.b_num; //차이 = 나 자신의 카드 - 다른 카드

    return gap;
};
int Card::get_num(){

    return this->b_num; //중복확인을 위한 메인에서 card 클래스에 접근하기 위해 만들어 줌
};


class Deque:Bag<Card> {
    friend class Card;
public:
    Deque();
    ~Deque();

    bool isEmpty();
    void F_push(Card&);
    void R_push(Card&);
    void push(Card&);
    int front_search(Card&);
    int rear_search(Card&);
    void left_shift();
    void right_shift();
    void deque_print();

private:

    int rear;
    int front;
};

Deque::Deque()
{
    front = -1;
    rear = -1;
}
Deque::~Deque() {

}

bool Deque::isEmpty() {
    if(front==rear){ //front랑 rear가 같으면
        return true; //비어있음
    }else { //같지 않으면
        return false; //비어있지 않음
    }
}
void Deque::deque_print() { //출력 함수 구현

    for(int i = front+1; i<=rear; i++){
        cout<<stack[i].form //배열의 카드 모양 출력
            <<stack[i].num //배열의 카드 숫자 출력
            <<" ";
    }
    cout<<endl;
};

int Deque::front_search(Card& c){ //앞에서부터 우선순위를 찾는 함수 구현
    int count=0;

    cout<<"front_search"<<c.Priority(stack[front+1])<<endl; //카드비교
    while(c.Priority(stack[front+1]) > 0 ){ //0보다 클 때
       right_shift(); //오른쪽 돌림

        count++;

        if((rear-front) == count){ //다 찼을 때
            break; //멈춤
        }

    }
    for(int i =0; i<count;i++){
        left_shift(); // 오른쪽으로 돌린만큼 왼쪽으로 돌려라
    }


    return count;
}

int Deque::rear_search(Card& c){ //뒤에서부터 우선순위를 찾는 함수 구현

    cout<<"rear_search"<<c.Priority(stack[rear])<<endl; //카드비교
    int count=0;

    while(c.Priority(stack[rear]) < 0 ){ //0보다 작을 때

        left_shift(); //왼쪽으로 돌림
        count++;

        if((rear-front) == count){ //다 찼을 때
            break; //멈춤
        }
    }
    for(int i =0; i<count;i++){
        right_shift(); //왼쪽으로 돌린만큼 오른쪽으로 돌려라
    }

    return count;
}
void Deque::push(Card& c){ //푸시 함수

    cout<<"선택된 카드 : "<<c.form<<c.num<<endl;

    if(isEmpty()== true){ //deque is Empty 만약 비었다면

        R_push(c); //rear 푸쉬
        deque_print(); //출력
    }
    else if(isEmpty()== false) { //만약 안비었다면

        int fs = front_search(c);
        int rs = rear_search(c);
        cout<<"fs : "<<fs<<" rs : "<<rs<<endl; //front search와 rear search 몇 번 진행했는지 출력
        if (fs < rs) { //기준이 되는 키드에서 앞의 카드의 수보다 뒤의 카드의 수가 많다면
            cout<<"front push 채택"<<endl;
            for (int i = 0; i < fs; i++) {
                cout<<"right shift"<<endl;
                right_shift(); //오른쪽으로 돌림
                deque_print(); //deque 출력
            }
            F_push(c); //front psuh
            deque_print();//deque 출력
            for (int i = 0; i < fs; i++) {
                cout<<"left shift"<<endl;

                left_shift(); //왼쪽으로 돌림
                deque_print();//deque 출력
            }
        } else {//rear push
            cout<<"rear push 채택"<<endl;
            for (int i = 0; i < rs; i++) {

                cout<<"left shift"<<endl;
                left_shift();
                deque_print();
            }
            R_push(c);
            deque_print();
            for (int i = 0; i < rs; i++) {
                cout<<"right shift"<<endl;
                right_shift();
                deque_print();
            }
        }
    }
}

void Deque::F_push(Card& c) //front push
{
    for(int i = rear; i>front; i--){
        stack[i+1] = stack[i]; //다음 배열에 현재 배열의 것을 넣음
    }

    stack[front+1] = c;
    rear += 1;
}
void Deque::R_push(Card& c) //rear push
{
    stack[++rear] = c;
}

void Deque::left_shift() { //left shift

    Card temp = stack[rear]; //temp에 배열의 rear의 값을 임시저장
    for(int i = rear-1; i > front; i-- ){
        stack[i+1] = stack[i]; //다음 배열에 현재 배열의 것을 넣음
    }
    stack[front+1] = temp; //배열의 first+1 자리에 임시저장한 temp의 값을 다시 넣음

}
void Deque::right_shift() { //right shift
    Card temp = stack[front+1]; //temp에 배열의 front+1의 값을 임시저장
    for(int i = 0; i <= rear; i++ ){
        stack[i] = stack[i+1];//다음 배열의 것을 현재 배열에 넣음
    }
    stack[rear] = temp; //배열의 rear의 자리에 임시저장한 temp의 값을 다시 넣음

}
