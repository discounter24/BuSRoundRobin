#include <stdio.h>

#define LENGTH 8
#define QUANTUM 1

typedef struct Process
{
	int PID;
	int WARTEZEIT;
	int BEARBEITUNGSZEIT;
	int AKTUELLE_BEARBEITUNGSZEIT;
} Process;


Process* createList();
void simulate(Process* plist, int length);
void printProcessList(Process* plist, int length);
int getNextProcess(Process* plist, int current, int length);
void increaseWaitTime(int time, Process* plist, int length);
double averageWaitTime(Process* plist, int length);