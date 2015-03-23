#include "TSEngine.h"
#include <stdlib.h>

#ifdef WIN32
    #include <Windows.h>
	#include <wtypes.h>
#endif

int TSEngine::TST_StringFilt(std::string& lpszString, char szSeps, std::vector<std::string>& tArray)
{
    char* pTok = NULL;
    char* sz = new char[lpszString.length() + 2];	
    strcpy(sz, lpszString.c_str());
    pTok = strtok(sz, &szSeps);
    while ( pTok )
    {
        tArray.push_back(pTok);
        pTok = strtok(NULL, &szSeps);
    }

    if (tArray.size() == 0)
    {
        tArray.push_back(lpszString);
    }

    delete [] sz;
    return 0;
}

void TSEngine::ConvertUtf8ToGBK( std::string &strUtf8 )
{
#ifdef WIN32
    int len = MultiByteToWideChar(CP_UTF8, 0, (LPCCH)strUtf8.c_str(), -1, NULL,0);
    wchar_t * wszGBK = new wchar_t[len];
    memset(wszGBK,0,len);
	MultiByteToWideChar(CP_UTF8, 0, (LPCCH)strUtf8.c_str(), -1, wszGBK, len);

    len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
    char *szGBK=new char[len + 1];
    memset(szGBK, 0, len + 1);
    WideCharToMultiByte (CP_ACP, 0, wszGBK, -1, szGBK, len, NULL,NULL);

    strUtf8 = szGBK;
    delete[] szGBK;
    delete[] wszGBK;
#endif
}

void TSEngine::ConvertGBKToUtf8( std::string &strGBK )
{
#ifdef WIN32
    int len = MultiByteToWideChar(CP_ACP, 0, (LPCCH)strGBK.c_str(), -1, NULL,0);
    wchar_t * wszUtf8 = new wchar_t [len];
    memset(wszUtf8, 0, len);
	MultiByteToWideChar(CP_ACP, 0, (LPCCH)strGBK.c_str(), -1, wszUtf8, len);

    len = WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, NULL, 0, NULL, NULL);
    char *szUtf8=new char[len + 1];
    memset(szUtf8, 0, len + 1);
    WideCharToMultiByte (CP_UTF8, 0, wszUtf8, -1, szUtf8, len, NULL,NULL);

    strGBK = szUtf8;
    delete[] szUtf8;
    delete[] wszUtf8;
#endif
}

int TSEngine::toInt( std::string str )
{
    return atoi(str.c_str());
}

std::string TSEngine::toString(int id){

    char buf[512]={0};
    sprintf(buf,"%d",id);
    return std::string(buf);
}
