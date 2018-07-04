#ifndef SERIALPORTV2_H
#define SERIALPORTV2_H
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>


class SerialPortV2
{
    public:
        SerialPortV2(std::string comPort, std::string baudRate)
        {
            open(comPort, baudRate);
        }
        SerialPortV2()
        {
            printf("New serial port created");
        }

        void open(std::string comx, std::string baud)
        {
            std::string com = comx;
            std::wstring com0(com.length(), L' ');
            std::copy(com.begin(), com.end(), com0.begin());
            hComm = CreateFile(com0.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
            if (hComm == INVALID_HANDLE_VALUE)
            {
                std::cout<<"Error in opening serial port"<<std::endl;
                opened = false;
            }
            else
            {
                std::cout<<"opening serial port successful"<<std::endl;
                opened = true;
                DCB dcbSerialParams = { 0 }; // Initializing DCB structure
                dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
                GetCommState(hComm, &dcbSerialParams);
                dcbSerialParams.BaudRate = CBR_9600;
                dcbSerialParams.ByteSize = 8;         // Setting ByteSize = 8
                dcbSerialParams.StopBits = ONESTOPBIT;// Setting StopBits = 1
                dcbSerialParams.Parity   = NOPARITY;  // Setting Parity = None
                SetCommState(hComm, &dcbSerialParams);
            }
        }

        void close()
        {
            CloseHandle(hComm);
            opened = false;
        }

        bool isOpen()
        {
            return opened;
        }

        std::string readSerialPort()
        {
            std::string buff;
            char temp;
            DWORD bytesRead;
            std::cout<<"Reading from arduino..."<<std::endl;
            do
            {
                ReadFile(hComm, &temp, sizeof(temp), &bytesRead, NULL);
                std::cout<<"From serial reader: "<<temp<<std::endl;
                buff += temp;
            }
            while(bytesRead > 0);
            std::cout<<"Reading from arduino done"<<std::endl;
            buff.pop_back();
            return buff;
        }
        void writeSerialPort(std::string msg)
        {
            char buff[64];
            strcpy(buff, msg.c_str());
            DWORD dNoOFBytestoWrite;
            DWORD dNoOfBytesWritten = 0;
            dNoOFBytestoWrite = sizeof(buff);
            std::cout<<"TEST: "<<buff<<std::endl;
            WriteFile(hComm, buff, dNoOFBytestoWrite, &dNoOfBytesWritten, NULL);
        }

    private:
        HANDLE hComm;
        bool opened;

    protected:


};
#endif // SERIALPORTV2_H
