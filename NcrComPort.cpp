#include "NcrComPort.h"

NcrComPort::NcrComPort()
{
}

NcrComPort::NcrComPort(const char *port)
{
    Open(port);
}


NcrComPort::~NcrComPort()
{
    //dtor
}

void NcrComPort::Open(const char *port)
{
    this->Port = port;
}

void NcrComPort::FillDcb(DCB &dcb)
{
    dcb.BaudRate = CBR_9600; //9600 Baud
    dcb.ByteSize = 8; //8 data bits
    dcb.Parity = NOPARITY; //no parity
    dcb.StopBits = ONESTOPBIT; //1 stop
}

bool NcrComPort::SendData(const char *data)
{
    DWORD byteswritten;

    hPort = CreateFileA(
        this->Port,
        GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (!GetCommState(hPort, &dcb))
        return false;

    FillDcb(dcb);

    if (!SetCommState(hPort, &dcb))
        return false;

    bool retVal = WriteFile(hPort, data, 1, &byteswritten, NULL);
    CloseHandle(hPort); //close the handle
    return retVal;
}

int NcrComPort::ReadByte()
{
    DCB dcb;
    int retVal;
    BYTE Byte;
    DWORD dwBytesTransferred;
    DWORD dwCommModemStatus;

    HANDLE hPort = CreateFileA(
        this->Port,
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (!GetCommState(hPort, &dcb))
        return 0x100;

    FillDcb(dcb);

    if (!SetCommState(hPort,&dcb))
        return 0x100;

    SetCommMask (hPort, EV_RXCHAR | EV_ERR); //receive character event
    WaitCommEvent (hPort, &dwCommModemStatus, 0); //wait for character

    if (dwCommModemStatus & EV_RXCHAR) {
        ReadFile (hPort, &Byte, 1, &dwBytesTransferred, 0); //read 1
        retVal = Byte;
    } else if (dwCommModemStatus & EV_ERR)
        retVal = 0x101;

    CloseHandle(hPort);
    return retVal;

}

void NcrComPort::SetDeviceName(const std::wstring &name)
{
    m_DeviceName = name;
}
const std::wstring &NcrComPort::GetDeviceName() const
{
    return m_DeviceName;
}


void NcrComPort::SetModel(int model)
{
    m_model = model;
}

int NcrComPort::GetModel() const
{
    return m_model;
}

NcrDeviceList::NcrDeviceList()
    : m_CurrentDeviceNumber(0)
{

}

int NcrDeviceList::GetCurrentDeviceNumber() const
{
    return m_CurrentDeviceNumber;
}

void NcrDeviceList::AddDevice()
{
    push_back(NcrComPort());
    m_CurrentDeviceNumber = size() - 1;
}

NcrComPort &NcrDeviceList::Current()
{
    if (m_CurrentDeviceNumber == -1)
        throw std::exception();
    return at(m_CurrentDeviceNumber);
}
const NcrComPort &NcrDeviceList::Current() const
{
    if (m_CurrentDeviceNumber == -1)
        throw std::exception();
    return at(m_CurrentDeviceNumber);
}
