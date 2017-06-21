nclude <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define CLOCKS_PER_SEC 1000

void gotoxy(int x, int y);

int main(void)
{
    int horse_num, rank[10]={0},i,number=0,score=0,x,y,ran; //horse_num : 경주 참여 말 수rank[] : 순위를 저장
    int horse[10]={0}, race;// horse[i] i의 말이 움직이는 거리
    char horse_name[10][10];//경주마의 이름
    clock_t start, end;//소요되는 시간을 파악
    double pst;//소요시간
    srand((unsigned)time(NULL));
    printf("경마게임\n\n");
    printf("경주할 말의 숫자(최대 10)를 입력하고 Enter>");
    scanf("%d", &horse_num);
    printf("\n\n");
    printf("%d개 말의 이름(최대 한글 3자)을 입력하고 Enter하세요.\n", horse_num);
    printf("\n");
    //말의 이름을 입력
    for(i=0 ; i<horse_num ; i++)
    {
        printf("%d번 말 이름 : ",i+1);
        scanf("%s", horse_name[i]);
    }
    //경마 경기장 화면 설계
    system("cls");
    printf("                                                   소요시간 :          초\n");
    printf("start               10        20        30        40(end)  등수  시간(초)\n");
    printf("-------------------------------------------------------------------------\n");
        for(i=0 ; i<horse_num ; i++)
            printf("%s :\n\n", horse_name[i]);
    // 아무키 입력하면 경기시작
            printf("-------------------------------------------------------------------------\n");
            printf("아무키나 누르면 경주를 시작합니다.");
            i=getch();
    for(i=5 ; i>=0 ; i--)
    {
        gotoxy(37,12); printf("%d!!", i);
        gotoxy(37,12); printf("%d!!", i);
        Sleep(1000);
    }
    gotoxy(37,12); printf("   ");
    gotoxy(37,12); printf("   ");
    x=rand()%30+20;
    y=rand()%horse_num*2+4;
    gotoxy(x,y);printf("item");
    //경기시작 시간
    start=clock();
    while(rank[number]!=horse_num)//등수와 말의 수가 같으면 경기종료
    {
    //램덤하게 (움직여야 할) 말을 선택
        number=rand()%horse_num;
    if (rank[number]!=0)//선택한 말의 등수가 0이 아니면 while 문으로
    continue;
    //한번에 움직인 거리는 1이나 2로 지정
    race=rand()%5+1;
    //말이 움직이는 거리= 이전거리+ 이번에 움직인 거리
    horse[number]+=race;
    Sleep(100+90*rank[number]);//0.3초마다 대기
    if (horse[number]>=40)//결승점 도착하면 등수표시(경기장 거리)
    {
        horse[number]=40;
        if (!rank[number]) //등수가 입력되지 않았다면 아래에서 현재 등수를 입력
        {
            //등수를 위한 변수 ++
            score++;
            //결승점에 도착한 해당 말의 등수을 저장
            rank[number]=score;
            //도착지점표시 및 등수 표기
            gotoxy(45,4+number*2), printf("      ");
            gotoxy(51,4+number*2), printf(">40       %d등", rank[number]);
            //결승점에 도착한 말의 시간을 계산
            end=clock();
            pst=(double)(end-start)/CLOCKS_PER_SEC;
            //clock()를 통해 얻는 값을 초 단위로 환산
            //해당 말의 소요시간 표기
            gotoxy(67,4+number*2); printf("%.2f", pst);
        }

    }
    else//결승점을 도착하기 이전이면
    {
        //말의 현재 위치에 >25 처럼 >와 움직인거리를 표시한다.gotoxy(10,5+number*2);
        for(i=1 ; i<horse[number] ; i++)
            gotoxy(10+i, 4+number*2), putchar(' ');
            gotoxy(10+horse[number],4+number*2); printf(">%d", horse[number]);
            if(x<=10+horse[number] && y==4+number*2)
            {
                gotoxy(10+horse[number], 4+number*2), printf("     ");
                ran=rand()%4;
                if(ran==0)
                {
                    gotoxy(28,13); printf("<< 너만 출발선으로!!>>");
                    Sleep(1000);
                    horse[number]=0;
                }
                else if(ran==1)
                {
                    gotoxy(28,13); printf("<< 모두 출발선으로!!>>");
                    Sleep(1000);
                    for(i=0 ; i<horse_num ; i++)
                    {
                        if(horse[i]!=40)
                        {
                            gotoxy(10+horse[i], 4+i*2), printf("     ");
                            horse[i]=0;
                        }
                    }
                    gotoxy(28,13); printf("                            ");
                }
                else if(ran==2)
                {
                    gotoxy(28,13); printf("<< 앞으로 앞으로 앞으로!!>>");
                    Sleep(1000);
                    gotoxy(28,13); printf("                            ");
                    horse[number]+=10;
                }
                else
                {
                    gotoxy(28,13); printf("<< P  A U  S E >>");
                    Sleep(4000);
                    gotoxy(28,13); printf("<< S  T A  R T >>");
                    Sleep(1000);
                    gotoxy(28,13); printf("                            ");
                }
                x=rand()%30+20;
                y=rand()%horse_num*2+4;
                gotoxy(x,y);printf("item");
            }

        }
    //모든 말이 다 도착하면 전체 소요시간표시
        end=clock();
        pst=(double)(end-start)/CLOCKS_PER_SEC;
        gotoxy(63,1);
        printf("%.2f", pst);
    }
    //경기 종료를 표시한다.
        gotoxy(1,28);
        printf("게임 종료!!\n");
        return 0;
    }
        void gotoxy(int x, int y)
    {
        COORD Pos = {x - 1, y - 1};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
    }

