/*
	Simple UDP Server
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <winsock2.h>

using namespace std;

#pragma comment(lib, "ws2_32.lib") //Winsock Library
int main()
{
    cout << "\t\t---------UDP SERVER-------" << endl;
    WSADATA Winsockdata;
    int iWsaStartup;
    int iWasCleanup;
    SOCKET UDPServerSocket;
    int iCloseSocket;
    struct sockaddr_in UDPServerAdd;
    struct sockaddr_in UDPClientAdd;
    int iUDPClientAdd = sizeof(UDPClientAdd);
    int iBind;

    int iSend;
    const int BUFLEN = 512;
    char buf[BUFLEN];
    int iRecv;

    //WSAStartUp Fun
    iWsaStartup = WSAStartup(MAKEWORD(2, 2), &Winsockdata);
    if (iWsaStartup != 0)
    {
        cout << "WSAStartUp failed" << endl;
    }
    cout << "WSAStartUp Success" << endl;
    //Fill the Structure
    UDPServerAdd.sin_family = AF_INET;
    UDPServerAdd.sin_addr.s_addr = INADDR_ANY;
    UDPServerAdd.sin_port = htons(8001);

    //Socket Creation
    UDPServerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (UDPServerSocket == INVALID_SOCKET)
    {
        cout << "UDP server socket connection Failed" << WSAGetLastError() << endl;
    }
    cout << "UDP server Socket Connection Success" << endl;
    //Bind Fun
    iBind = bind(UDPServerSocket, (SOCKADDR *)&UDPServerAdd, sizeof(UDPServerAdd));
    if (iBind == SOCKET_ERROR)
    {
        cout << "Binding Failed & Error No-> " << WSAGetLastError() << endl;
    }
    cout << "Binding Success" << endl;

    while (1)
    {
        cout << "Waiting for Data";
        fflush(stdout);

        //clear the buffer by filling null, it might have previously received data
        memset(buf, '\0', BUFLEN);
        iRecv = recvfrom(UDPServerSocket, buf, BUFLEN, 0, (SOCKADDR *)&UDPClientAdd, &iUDPClientAdd);

        if (iRecv == SOCKET_ERROR)
        {
            cout << "Receive Data Failed & Error No->" << WSAGetLastError() << endl;
        }
        cout << "Received packet from " << inet_ntoa(UDPClientAdd.sin_addr) << ntohs(UDPClientAdd.sin_port) << endl;
        cout << "Received Data-> " << buf << endl;

        iSend = sendto(UDPServerSocket, buf, BUFLEN, 0, (sockaddr *)&UDPClientAdd, iUDPClientAdd);

        if (iSend == SOCKET_ERROR)
        {
            cout << "Sending Failed & Error No->" << WSAGetLastError() << endl;
        }
        cout << "Data Sending Success " << endl;
    }

    //cLOSING Socket
    iCloseSocket = closesocket(UDPServerSocket);
    if (iCloseSocket == SOCKET_ERROR)
    {
        cout << "Closing Socket Failed & Error No ->" << WSAGetLastError() << endl;
    }
    cout << "Closing Socket Success" << endl;
    ;
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
