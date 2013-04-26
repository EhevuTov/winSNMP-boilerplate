// winSNMP-boilerplate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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
	return 0;
}