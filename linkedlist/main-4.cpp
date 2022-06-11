#include <iostream>
#include "linked2.h"

using namespace std;

int main() {

    //int check_overlap[5][3]; // Car의 중복을 확인하기 위한 이중배열 선언
    //이중배열의 0자리는 num, 1자리는 rank, 2자리는 변환된 num 저장

    srand((unsigned int)time(NULL));// Run할 때마다 다른 값을 출력하기 위한 srand
    Card c1, c2, c3, c4, c5; //멤버변수
    Card check[5]; //check 5개의 배열
    check[0] = c1; //첫번 째 자리에 c1
    check[1] = c2; //두번 째 자리에 c2
    check[2] = c3; //세번 째 자리에 c3
    check[3] = c4; //네번 째 자리에 c4
    check[4] = c5; //다섯번 째 자리에 c5

    for(int i =0; i < 5; i++) {
        check[i].PickCard(); //랜덤으로 뽑은 숫자를 카드로 구현

        int i_num = check[i].get_num();

        for(int j =0; j<i; j++) { //중복확인
            int j_num = check[j].get_num();

            if (i_num == j_num) { //중복이면
                check[i].PickCard();
                i_num = check[i].get_num();
                j = -1;
            }
        }
    }
    Chain<Card> c;

    c.push(check[0]);
    c.push(check[1]);
    c.push(check[2]);
    c.push(check[3]);
    c.push(check[4]);

    return 0;
}

