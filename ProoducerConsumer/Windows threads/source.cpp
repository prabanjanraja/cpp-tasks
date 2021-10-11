// ProducerConsumer2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
using namespace std;
CRITICAL_SECTION cs;
CONDITION_VARIABLE cv;
const int ThreadCount = 15, Producercount = 10, Consumercount = 5;
atomic<int> buffer(0);
atomic<int> producers_working(0);
DWORD WINAPI Producer(void *no)
{
    producers_working++;
    for (int i = 0; i < 2; i++)
    {
        if (i != 0)
        {
            Sleep(1000);
        }
        EnterCriticalSection(&cs);
        while (buffer == 6)
        {
            SleepConditionVariableCS(&cv, &cs, INFINITE);
        }
        buffer++;
        cout << "PRODUCER " << (int)no << " PRODUCED " << buffer << endl;
        LeaveCriticalSection(&cs);
        WakeConditionVariable(&cv);
    }
    producers_working--;
    return 0;
}
DWORD WINAPI Consumer(void *no)
{
    do
    {
        EnterCriticalSection(&cs);
        while (buffer == 0)
        {
            SleepConditionVariableCS(&cv, &cs, INFINITE);
        }
        cout << "\t\t\t Consumer " << (int)no << " CONSUMED " << buffer << endl;
        buffer--;
        LeaveCriticalSection(&cs);
        WakeConditionVariable(&cv);
        Sleep(1000);
    } while (producers_working != 0 || buffer != 0);
    return 0;
}
int main()
{
    HANDLE threads[ThreadCount];
    InitializeCriticalSection(&cs);
    InitializeConditionVariable(&cv);
    for (int i = 0; i < Producercount; i++)
    {
        threads[i] = CreateThread(NULL, 0, &Producer, (int *)i, 0, NULL);
    }
    for (int j = 10, i = 0; i < Consumercount; j++, i++)
    {
        threads[j] = CreateThread(NULL, 0, &Consumer, (int *)i, 0, NULL);
    }
    WaitForMultipleObjects(ThreadCount, threads, TRUE, INFINITE);
    for (int i = 0; i < ThreadCount; i++)
    {
        CloseHandle(threads[i]);
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
