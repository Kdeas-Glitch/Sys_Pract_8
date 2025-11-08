#include <iostream>
#include <Windows.h>
#include <random>
#include <iomanip>


const int turtle_count = 11;
volatile int n[turtle_count] = {0};
volatile int w = 0;


DWORD WINAPI Add(LPVOID iNum) {
    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
    std::uniform_int_distribution<> dist(0, 2);
    std::uniform_int_distribution<> dist_2(1000, 3000);
    int Turtle_Id=(int)iNum;
    int i=n[Turtle_Id];
    while (n[Turtle_Id] <50){
        int gap = (dist(gen));
        int time = (dist_2(gen));
        n[Turtle_Id] += gap;
        Sleep(50);
    }
    n[Turtle_Id] += w;
    w++;
    return 0;

}


int main()
{
    srand(time(NULL));
    int T[50];
    setlocale(0, "rus");

    HANDLE hThread[turtle_count];
    DWORD IDThread[turtle_count];
    int count = 0;
    for (int f = 0; f < turtle_count; f++) {
        hThread[f] = CreateThread(NULL, 0, Add, (void*)count, 0, &IDThread[f]);
        if (hThread == NULL) {
            return GetLastError();
        }
        count++;
    }
    count++;
    while (w != turtle_count) {
        for (int j = 0; j < 50; j++) {
            T[j] = 0;
        }
        for (int i = 0; i < turtle_count; i++) {
            if (n[i] < 50) {
                if (T[n[i]] == 0) {
                    T[n[i]] = i + 1;
                }
                else
                {
                    T[n[i]] = T[n[i]] + i+1;
                }
            }
        }
        for (int j = 0; j < 50; j++) {
            std::cout<< std::setw(2) << T[j] << "\t";
        }
        Sleep(500);
        system("cls");
    }
    for (int f = 0; f < turtle_count; f++) {
        CloseHandle(hThread[f]);
    }
    for (int j = 0; j < turtle_count; j++) {
        std::cout << (n[j] % 50) + 1 << "-й Пришла "<< j+1 <<" череха" << std::endl;
    }
    return 0;
}
