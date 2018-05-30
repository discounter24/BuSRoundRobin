#include "Main.h"


int main(void) 
{
	int length = LENGTH;
	Process* plist = createList();

	simulate(plist, length);
	printProcessList(plist, length);


	getchar();
}



Process* createList()
{
	int length = LENGTH;
	Process* plist = malloc(sizeof(Process) * length);
	Process p1 = { 1,0,6,6 };
	Process p2 = { 2,0,13,13 };
	Process p3 = { 3,0,7,7 };
	Process p4 = { 4,0,3,3 };
	Process p5 = { 5,0,4,4 };
	Process p6 = { 6,0,9,9 };
	Process p7 = { 7,0,10,10 };
	Process p8 = { 8,0,11,11 };
	plist[0] = p1;
	plist[1] = p2;
	plist[2] = p3;
	plist[3] = p4;
	plist[4] = p5;
	plist[5] = p6;
	plist[6] = p7;
	plist[7] = p8;
	return plist;
}



void simulate(Process* plist, int length)
{
	int current = -1;
	int next = getNextProcess(plist, current, length);
	while (next != -1)
	{
		current = next;

		Process* p = &plist[current];
		if (p->AKTUELLE_BEARBEITUNGSZEIT >= QUANTUM)
		{
			increaseWaitTime(QUANTUM, plist, length);
			p->AKTUELLE_BEARBEITUNGSZEIT -= QUANTUM;
		}
		else
		{
			increaseWaitTime(p->AKTUELLE_BEARBEITUNGSZEIT, plist,length);
			p->AKTUELLE_BEARBEITUNGSZEIT = 0;
		}

		next = getNextProcess(plist, current, length);
	}
}

void increaseWaitTime(int time, Process* plist, int length)
{
	for (int i = 0; i < length; i++)
	{
		if (plist[i].AKTUELLE_BEARBEITUNGSZEIT>0)
		{
			plist[i].WARTEZEIT += time;
		}
	}
}

int getNextProcess(Process* plist, int current, int length)
{
	if (current == -1)
	{
		for (int i = 0; i < length; i++)
		{
			if (plist[i].AKTUELLE_BEARBEITUNGSZEIT > 0)
			{
				return i;
			}
		}
		return -1;
	}
	else
	{
		for (int i = current+1; i < length; i++)
		{
			
			if (plist[i].AKTUELLE_BEARBEITUNGSZEIT > 0)
			{
				return i;
			}

		}
		for (int i = 0; i <= current; i++)
		{
			if (plist[i].AKTUELLE_BEARBEITUNGSZEIT > 0)
			{
				return i;
			}
		}
		return -1;
	}

}


void printProcessList(Process* plist, int length)
{
	printf("\n");
	printf("# Q | P1 | P2 | P3 | P4 | P5 | P6 | P6 | P8 | Avg. Time\n");
	printf("#------------------------------------------------------\n");
	printf("  %d | ", QUANTUM);
	for (int i = 0; i < length; i++)
	{
		printf(" %d | ", plist[i].WARTEZEIT);
	}

	double average = averageWaitTime(plist, length);
	printf(" %f", average);

	printf("\n\n");
}

double averageWaitTime(Process* plist, int length)
{
	double time = 0;
	for (int i = 0; i < length; i++)
	{
		double pwait = plist[i].WARTEZEIT - plist[i].BEARBEITUNGSZEIT;
		time = time + pwait;
	}
	time = time / length;
	return time;
}