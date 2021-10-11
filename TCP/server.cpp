#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")

#define BUFLEN 512 //Max length of buffer

using namespace std;
int main()
{
    cout << "\t\t---------TCP SERVER-------" << endl;
    WSADATA Winsockdata;
    int iWsaStartup;
    int iWasCleanup;
    SOCKET TCPServerSocket;
    int iCloseSocket;
    struct sockaddr_in TCPServerAdd;
    struct sockaddr_in TCPClientAdd;
    int iTCPClientAdd = sizeof(TCPClientAdd);
    int iBind;
    int iListen;
    SOCKET sAcceptSocket;

    int iSend;
    char buf[BUFLEN];
    int iRecv;

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
    TCPServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (TCPServerSocket == INVALID_SOCKET)
    {
        cout << "TCP server socket connection Failed" << WSAGetLastError() << endl;
    }
    cout << "TCP server Socket Connection Success" << endl;
    //Bind Fun
    iBind = bind(TCPServerSocket, (SOCKADDR *)&TCPServerAdd, sizeof(TCPServerAdd));
    if (iBind == SOCKET_ERROR)
    {
        cout << "Binding Failed & Error No-> " << WSAGetLastError() << endl;
    }
    cout << "Binding Success" << endl;
    //Listen
    iListen = listen(TCPServerSocket, 2);
    if (iListen == SOCKET_ERROR)
    {
        cout << "Listen Fun Failed & Error No->" << WSAGetLastError() << endl;
    }
    cout << "Listen Fun Success" << endl;
    //Accept

    sAcceptSocket = accept(TCPServerSocket, (SOCKADDR *)&TCPClientAdd, &iTCPClientAdd);
    if (sAcceptSocket == INVALID_SOCKET)
    {
        cout << "Accept Failed & Error No->" << WSAGetLastError() << endl;
    }
    cout << "Connection Accepted" << endl;
    memset(buf, '\0', BUFLEN);
    //Receive from Client
    iRecv = recv(sAcceptSocket, buf, BUFLEN, 0);
    if (iRecv == SOCKET_ERROR)
    {
        cout << "Receive Data Failed & Error No->" << WSAGetLastError() << endl;
    }
    cout << "Received Data-> " << buf << endl;

    //Send Data To Client
    iSend = send(sAcceptSocket, buf, BUFLEN, 0);
    if (iSend == SOCKET_ERROR)
    {
        cout << "Sending Failed & Error No->" << WSAGetLastError() << endl;
    }
    cout << "Data Sending Success " << endl;

    //cLOSING Socket
    iCloseSocket = closesocket(TCPServerSocket);
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