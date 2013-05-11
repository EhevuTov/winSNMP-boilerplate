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
	HWND hsession;
	HSNMP_ENTITY entDest; char destIP[] = "192.168.1.1";
	HSNMP_ENTITY entSrc; char srcIP[] = "192.168.1.2";
	HSNMP_CONTEXT hContext;char Ctx[]="public";
	SNMPAPI_STATUS status = 0;
	LPCSTR string = "entityName";
	UINT msg;
	LPHSNMP_PDU PDU = 0;
	LPHSNMP_VBL varbind_lst;
	LPHSNMP_CONTEXT context;
	smiLPINT PDU_typ, r_id, error_stat, error_index;
	smiOCTETS dContext;
	smiOID dName;
	smiVALUE dValue;
	SNMP_worker worker;

	HSNMP_SESSION session = SnmpCreateSession(NULL, 0, &SNcallback, (void*)&worker);

	entDest = SnmpStrToEntity(session, destIP);
	entSrc  = SnmpStrToEntity(session, srcIP);
	dContext.ptr=(smiLPBYTE)Ctx;
	dContext.len=strlen(Ctx);
	hContext= SnmpStrToContext(session,&dContext);
	printf("entity return: %i\n", entDest);
	status = SnmpListen(entDest, status);
	printf("listen return: %i\n", status);
	while (status = SnmpRecvMsg(session, &entSrc, &entDest, context, PDU) ) {
		printf("recv return: %i\n", status);
		printf("PDU: %s\n", PDU);
	};
	SnmpGetPduData(PDU, PDU_typ, r_id, error_stat, error_index, varbind_lst);
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