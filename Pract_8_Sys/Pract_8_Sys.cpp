#include <iostream>
#include <Windows.h>
#include <random>
#include <iomanip>


const int turtle_count = 11;
volatile int n[turtle_count] = {0};
volatile int w = 0;
volatile int T[50] = {0};


DWORD WINAPI Add(LPVOID iNum) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 2);
    std::uniform_int_distribution<> dist_2(1000, 3000);
    int gap = 0;
    while (gap <50){
        T[gap] = 0;
        int time = (dist_2(gen));
        gap += (dist(gen));
        T[gap] = (int)iNum;
        Sleep(100);
    }
    n[(int)iNum] += w;
    w++;
    return 0;
}


int main()
{
    srand(time(NULL));
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
    while (w != turtle_count) {
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
