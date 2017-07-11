#include <stdio.h>
#include <winsock2.h>
#include <string>
#include <iostream>
using namespace std;
  
#pragma comment(lib,"ws2_32.lib")  
  
int main(int argc, char* argv[])  
{  
    //初始化WSA  
    WORD sockVersion = MAKEWORD(2,2);  
    WSADATA wsaData;  
     
  
    //创建套接字  
    SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
    if(slisten == INVALID_SOCKET)  
    {  
        printf("socket error !");  
        return 0;  
    }  
  
    //绑定IP和端口  
    sockaddr_in sin;  
    sin.sin_family = AF_INET;  
    sin.sin_port = htons(8889);  
    sin.sin_addr.S_un.S_addr = INADDR_ANY;   
    if(bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)  
    {  
        printf("bind error !");  
    }  
  
    //开始监听  
    if(listen(slisten, 5) == SOCKET_ERROR)  
    {  
        printf("listen error !");  
        return 0;  
    }  
  
    //循环接收数据  
    SOCKET sClient;  
    sockaddr_in remoteAddr;  
    int nAddrlen = sizeof(remoteAddr);  
    char revData[255];   
    while (true)  
    {  
        //printf("等待连接...\n");  
        sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);  
        if(sClient == INVALID_SOCKET)  
        {  
            printf("accept error !");  
            continue;  
        }  
       // printf("接受到一个连接：%s \r\n", inet_ntoa(remoteAddr.sin_addr));  
          
        //接收数据  
        int ret = recv(sClient, revData, 255, 0);
        char * uriFlag;
        if(ret > 0)  
        {  
            revData[ret] = 0x00;  
            printf(revData);
            *uriFlag = revData[5];
            char seg[] = "url=";
            //string s(&revData[0],&revData[strlen(revData)]);  
                //cout<<"xxxxx"<<s.substr(2,10)<<"xxxxx"<<endl;
            
            //string cc(revData);
            
           // printf("xxxxxxxxxxxxx,%s,%c,%s,yyyyyyyyyy",aa,aa[1],uriFlag);
        }  
        printf("-------------,%s,----------------------\r\n",uriFlag);
        
        //发送数据  
        const char * sendData = "HTTP/1.1 200 OK \r\n";
       
        if(strcmp(uriFlag,"f") == 0)
        {
            printf("哈哈哈哈哈哈哈哈哈哈\r\n");
            sendData = "HTTP/1.1 200 FAIL \r\n";
            send(sClient, sendData, strlen(sendData), 0);
        }
        else{
            char cc[255];
             //memcpy(cc, revData, 255);
             //string s(&cc[0],&cc[strlen(cc)]); 
            char vv[255];
             for (int i = 10; i < sizeof(revData); i++)  
            {  
                 if(isblank(revData[i])){
                     break;
                 }
                 vv[i-10]=revData[i];
                cout<<revData[i]<<" ";
            }  
            printf("vv%svv",vv);
            send(sClient, sendData, strlen(sendData), 0);
            char uu[]="https://github.com/iamzken";
            ShellExecute(NULL,"open","IExplore.EXE",vv,NULL,SW_SHOW);
        }
         
        
       //closesocket(sClient); 
        shutdown(sClient,1);
        
    }  
      
    closesocket(slisten);  
    WSACleanup();  
    return 0;  
} 