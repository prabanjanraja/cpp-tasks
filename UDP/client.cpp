#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

#define SERVER "127.0.0.1" //ip address of udp server
#define PORT 8001          //The port on which to listen for incoming data

int main(void)
{
    cout << "\t\t---------UDP CLIENT------" << endl;
    WSADATA Winsockdata;
    int iWsaStartup;
    int iWasCleanup;
    SOCKET UDPClientSocket;
    int iCloseSocket;
    struct sockaddr_in UDPServerAdd;
    struct sockaddr_in UDPClientAdd;
    int iUDPClientAdd = sizeof(UDPClientAdd);
    int iUDPServerAdd = sizeof(UDPServerAdd);
    int iBind;

    int iSend;
    const int bufferlength = 512;
    char SenderBuffer[bufferlength];

    int iRecv;
    char RecvBuffer[bufferlength];
    //int iRecvBuffer = strlen(RecvBuffer) ;

    //WSAStartUp Fun
    iWsaStartup = WSAStartup(MAKEWORD(2, 2), &Winsockdata);
    if (iWsaStartup != 0)
    {
        cout << "WSAStartUp failed" << endl;
    }

    //setup address structure
    memset((char *)&UDPServerAdd, 0, sizeof(UDPServerAdd));
    UDPServerAdd.sin_family = AF_INET;
    UDPServerAdd.sin_port = htons(PORT);
    UDPServerAdd.sin_addr.S_un.S_addr = inet_addr(SERVER);
    //Socket Creation
    UDPClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (UDPClientSocket == INVALID_SOCKET)
    {
        cout << "UDP server socket connection Failed" << WSAGetLastError() << endl;
    }
    cout << "UDP server Socket Connection Success" << endl;

    //start communication
    while (1)
    {
        cout << "Enter message : ";
        cin >> SenderBuffer;

        iSend = sendto(UDPClientSocket, SenderBuffer, bufferlength, 0, (sockaddr *)&UDPServerAdd, iUDPServerAdd);
        if (iSend == SOCKET_ERROR)
        {
            cout << "Sending Failed & Error No->" << WSAGetLastError() << endl;
        }
        cout << "Data Sending Success " << endl;
        memset(RecvBuffer, '\0', bufferlength);
        iRecv = recvfrom(UDPClientSocket, RecvBuffer, bufferlength, 0, (sockaddr *)&UDPServerAdd, &iUDPServerAdd);
        if (iRecv == SOCKET_ERROR)
        {
            cout << "Receive Data Failed & Error No->" << WSAGetLastError() << endl;
        }
        cout << "Received Data-> " << RecvBuffer << endl;
    }

    //cLOSING Socket
    iCloseSocket = closesocket(UDPClientSocket);
    if (iCloseSocket == SOCKET_ERROR)
    {
        cout << "Closing Socket Failed & Error No ->" << WSAGetLastError() << endl;
    }
    cout << "Closing Socket Success" << endl;
    //CleanUp
    iWasCleanup = WSACleanup();
    if (iWasCleanup == SOCKET_ERROR)
    {
        cout << "CleanUp Fun Failed & Error No->" << WSAGetLastError() << endl;
    }
    cout << "CleanUp Success" << endl;
    system("PAUSE");

    return 0;
}