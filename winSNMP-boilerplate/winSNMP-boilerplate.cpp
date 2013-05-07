// winSNMP-boilerplate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
struct SNMP_worker
{
	void run(/* params */) {}
};

SNMPAPI_STATUS CALLBACK SNcallback(
        HSNMP_SESSION SNsession
    , HWND          hWnd
    , UINT          wMsg
    , WPARAM        wParam
    , LPARAM        lParam
    , LPVOID        lpClientData
)
{

	if (SNMP_worker* p_worker = static_cast<SNMP_worker*>(lpClientData))
	{
		p_worker->run(/* params */);
	}
	return 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	unsigned long majorVal = 1;
	unsigned long *major = &majorVal;
	unsigned long minorVal = 1;
	unsigned long *minor = &minorVal;
	unsigned long levelVal = 1;
	unsigned long *level = &levelVal;
	unsigned long translateModeVal = 1;
	unsigned long *translateMode = &translateModeVal;
	unsigned long retransmitModeVal = 1;
	unsigned long *retransmitMode = &retransmitModeVal;
	SnmpStartup(major, minor, level, translateMode, retransmitMode);
	HSNMP_SESSION sess;
	HWND hsession;
	HSNMP_ENTITY entity;
	SNMPAPI_STATUS status;
	LPCSTR string = "entityName";
	UINT msg;

	SNMP_worker worker;

	HSNMP_SESSION session = SnmpCreateSession(NULL, 0, &SNcallback, (void*)&worker);

	entity = SnmpStrToEntity(session, string);
	status = SnmpListen(entity, status);
	printf("%lu, %lu\n", *major, *minor);
	printf("%p, %p\n", (void *)major, (void *)minor);
	/*
	char *ip = "192.168.1.174";
	char *community = "public";
	LPSNMP_MGR_SESSION ptr;
	ptr = SnmpMgrOpen(ip, community, 10000, 3);
	SnmpRecvMsg(
	SnmpMgrClose(ptr);
	*/

	SnmpCleanup();
	return 0;
}