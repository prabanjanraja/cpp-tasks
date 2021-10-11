#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")

using namespace std;
#define BUFLEN 512
int main()
{
    cout << "\t\t---------TCP CLIENT------" << endl;
    WSADATA Winsockdata;
    int iWsaStartup;
    int iWasCleanup;
    SOCKET TCPClientSocket;
    int iCloseSocket;
    struct sockaddr_in TCPServerAdd;
    struct sockaddr_in TCPClientAdd;
    int iTCPClientAdd = sizeof(TCPClientAdd);

    int iConnect;

    int iSend;
    char SenderBuffer[BUFLEN];
    int iSenderBuffer = BUFLEN;

    int iRecv;
    char RecvBuffer[BUFLEN];
    int iRecvBuffer = BUFLEN;
    memset(RecvBuffer, '\0', iRecvBuffer);

    //WSAStartUp Fun
    iWsaStartup = WSAStartup(MAKEWORD(2, 2), &Winsockdata);
    if (iWsaStartup != 0)
    {
        cout << "WSAStartUp failed" << endl;
    }
    cout << "WSAStartUp Success";

    //Fill the Structure
    TCPServerAdd.sin_family = AF_INET;
    TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
    TCPServerAdd.sin_port = htons(8000);

    //Socket Creation
    TCPClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (TCPClientSocket == INVALID_SOCKET)
    {
        cout << "TCP server socket connection Failed" << WSAGetLastError() << endl;
    }
    cout << "TCP server Socket Connection Success" << endl;
    //Connect

    cout << "Connection Success" << endl;
    iConnect = connect(TCPClientSocket, (SOCKADDR *)&TCPServerAdd, sizeof(TCPServerAdd));
    if (iConnect == SOCKET_ERROR)
    {
        cout << "Connection Failed & Error No->" << WSAGetLastError() << endl;
    }
    cout << "Enter message : ";
    cin >> SenderBuffer;
    iSend = send(TCPClientSocket, SenderBuffer, iSenderBuffer, 0);
    if (iSend == SOCKET_ERROR)
    {
        cout << "Sending Failed & Error No->" << WSAGetLastError() << endl;
    }
    cout << "Data Sending Success " << endl;
    memset(RecvBuffer, '\0', iRecvBuffer);
    //Receive from Client
    iRecv = recv(TCPClientSocket, RecvBuffer, iRecvBuffer, 0);
    if (iRecv == SOCKET_ERROR)
    {
        cout << "Receive Data Failed & Error No->" << WSAGetLastError() << endl;
    }
    cout << "Received Data-> " << RecvBuffer << endl;

    //cLOSING Socket
    iCloseSocket = closesocket(TCPClientSocket);

    if (iCloseSocket == SOCKET_ERROR)
    {
        cout << "Closing Socket Failed & Error No ->" << WSAGetLastError() << endl;
    }
    cout << "Closing Socket Success";
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