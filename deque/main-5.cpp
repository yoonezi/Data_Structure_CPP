#include <iostream>
#include <ctime>
#include <cstdlib>
#include "deque.h"

using namespace std;

int main()
{
    srand(time(NULL)); //랜덤으로 뽑기

    Card c1, c2, c3, c4, c5; //멤버변수
    Card check[5]; //check 5개의 배열
    check[0] = c1; //첫번 째 자리에 c1
    check[1] = c2; //두번 째 자리에 c2
    check[2] = c3; //세번 째 자리에 c3
    check[3] = c4; //네번 째 자리에 c4
    check[4] = c5; //다섯번 째 자리에 c5

    for(int i =0; i < 5; i++) {
        check[i].PickCard(); //랜덤으로 뽑은 숫자를 카드로 구현

        for(int j =0; j<5; j++) { //중복확인
            int i_num = check[i].get_num();
            int j_num = check[j].get_num();

            if (i_num == j_num) { //중복이면
                check[i].PickCard();
                break;; //멈춤
            }
        }
    }

    Deque d;
    d.push(check[0]); //카드 push
    d.push(check[1]);
    d.push(check[2]);
    d.push(check[3]);
    d.push(check[4]);

    d.deque_print(); //출력

    return 0;
}


