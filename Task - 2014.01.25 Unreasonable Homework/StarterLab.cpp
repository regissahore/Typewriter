// StarterLab.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cstdio> // c library
#include <cstdlib> // c library
#include <cstring> // c library
#include "MemTracker.h"

#pragma warning(disable:4996)

using namespace std;

#define INVALID 0xFFFFFFFF
#define SIZE 128
#define EQUAL "="
#define COMMA ", "
#define TRUE 1
#define FALSE 0

struct ErrorLog
{
	FILE* fperr;
	int errorCount;
};

bool openLog(struct ErrorLog* elog,char* fname)
{
	elog->fperr = fopen(fname,"w");
	elog->errorCount = 0;
	return elog->fperr != NULL;
}

bool closeLog(struct ErrorLog* elog)
{
	fclose(elog->fperr);
	return elog != NULL;
}

bool writeLog(struct ErrorLog* elog,char* errortxt)
{
	fputs(errortxt,elog->fperr);
	(elog->errorCount)++;
	return elog != NULL;
}

struct AirlineInfo
{
	int flight;
	int sections;
	int totalRows;
	int* rows;
	int* seats;
	struct ErrorLog errorLog;
};

bool initInfo(struct AirlineInfo* ap,char* ename)
{
	ap->flight = INVALID;
	ap->sections = INVALID;
	ap->totalRows = 0;
	ap->rows = NULL;
	ap->seats = NULL;
	return openLog(&ap->errorLog,ename);
}

bool findValue(FILE* fp, char* section, char* skey, char* svalue)
{
	bool bfound = FALSE;
	char* ptr = NULL;
	char buffer[SIZE];
	fgets(buffer,SIZE,fp);
	while (strstr(buffer,section) == NULL)
	{
		if (!fgets(buffer,SIZE,fp))
			break;
	}
	while (strstr(buffer,skey) == NULL)
	{
		if (!fgets(buffer,SIZE,fp))
			break;
	}
	if (strlen(buffer))
	{
		ptr = strtok(buffer,EQUAL);
		ptr = strtok(NULL,EQUAL);
		strcpy(svalue,ptr);
		bfound = TRUE;
	}
	rewind(fp);
	return bfound;
}

bool getProfileInt(FILE* fpini, char* psection, char* pfield, int* value)
{
	bool bfound = FALSE;
	char buffer[SIZE];
	if ( findValue(fpini,psection,pfield,buffer) )
	{
		*value = atoi(buffer);
		bfound = TRUE;
	}
	return bfound;
}

bool getProfileData(struct AirlineInfo* ap, char* inifile, char* psection)
{
	FILE* fpini = fopen(inifile,"r");
	char buffer[SIZE];
	int value = INVALID;
	int x = 0;
	if ( fpini )
	{
		if ( getProfileInt(fpini,psection,"flight",&value) )
			ap->flight = value;
		if ( getProfileInt(fpini,psection,"sections",&value) )
		{
			ap->sections = value;
			ap->rows = (int*)malloc(sizeof(int)*value);
			ap->seats = (int*)malloc(sizeof(int)*value);
			for (x=0; x<ap->sections; x++)
			{
				sprintf(buffer,"section%d rows",x+1);
				getProfileInt(fpini,psection,buffer,&value);
				ap->rows[x] = value;
				ap->totalRows += value;
			}
			for (x=0; x<ap->sections; x++)
			{
				sprintf(buffer,"section%d seats",x+1);
				getProfileInt(fpini,psection,buffer,&value);
				ap->seats[x] = value;
			}
		}
	}
	fclose( fpini );
	return fpini != NULL;
}

int GetErrorCount(struct AirlineInfo* ap)
{
	return ap->errorLog.errorCount;
}

bool releaseInfo(struct AirlineInfo* ap)
{
	if (ap->rows)
		free(ap->rows);
	if (ap->seats)
		free(ap->seats);
	return ap != NULL;
}

struct Passenger
{
	char* plast;
	char* pfirst;
	int  row;
	char seatno;
	int  flight;
};

bool initPassenger(struct Passenger* p, char* line )
{
	char tstring[SIZE];
	strcpy(tstring,line);
	char* pl = strtok(tstring,",");
	char* pf = strtok(NULL,",");
	char* pr = strtok(NULL,",");
	char* ps = strtok(NULL,",");
	char* pt = strtok(NULL,",");
	p->plast = (char *) malloc( strlen( pl )+1 );
	p->pfirst = (char *) malloc( strlen( pf )+1 );
	strcpy( p->plast, pl );
	strcpy( p->pfirst, pf );
	p->row = atoi(pr);
	p->seatno = *ps;
	p->flight = atoi(pt);
	return line != NULL;
}

bool deletePassenger(struct Passenger* p)
{
	bool bsuccess = FALSE;
	if ( p->plast )
	{
		free( p->plast );
		p->plast = NULL;
		bsuccess = TRUE;
	}
	if ( p->pfirst )
	{
		free( p->pfirst );
		p->pfirst = NULL;
		bsuccess = TRUE;
	}
	return bsuccess == TRUE;
}

char* toString(struct Passenger* p)
{
	static char gbuffer[SIZE];
	char tbuffer[SIZE];
	strcpy(gbuffer,p->plast);
	strcat(gbuffer,COMMA);
	strcat(gbuffer,p->pfirst);
	strcat(gbuffer,COMMA);
	strcat(gbuffer,itoa(p->row,tbuffer,10));
	int slength = strlen(gbuffer);
	gbuffer[slength] = p->seatno;
	gbuffer[slength+1] = NULL;
	return gbuffer;
}

struct Seat
{
	struct Passenger* passenger;
};

bool initSeat(struct Seat* sp)
{
	sp->passenger = NULL;
	return sp->passenger == NULL;
}

bool insertSeat(struct Seat* sp, struct Passenger* p)
{
	bool bsuccess = TRUE;
	if ( p != NULL )
	{
		if (sp->passenger == NULL)
			sp->passenger = p;
		else
			bsuccess = FALSE;
	}
	else
		sp->passenger = NULL;
	return bsuccess;
}

bool outputSeat(struct Seat* sp,int row,int seat)
{
	if (sp->passenger)
		printf("%s\n",toString(sp->passenger));
	else
		printf("Empty %d%c\n",row,seat+'A');
	return sp->passenger != NULL;
}

bool releaseSeat(struct Seat* sp)
{
	bool bvalue = false;
	if (sp->passenger)
	{
		deletePassenger(sp->passenger);
		free(sp->passenger);
		sp->passenger = NULL;
		bvalue = true;
	}
	return bvalue;
}

struct Row
{
	struct Seat* seats;
	int nseats;
};

bool initRow(struct Row* rp, int nrows)
{
	int s = 0;
	rp->seats = (struct Seat*)malloc(sizeof(struct Seat)*nrows);
	rp->nseats = nrows;
	for (s=0; s<rp->nseats; s++)
		insertSeat(&rp->seats[s],NULL);
	return s > 0;
}

bool insertRow(struct Row* rp, int maxSeats, struct Passenger* p)
{
	bool bsuccess = FALSE;
	int seat = p->seatno - 'A';
	if (seat > -1 && seat < maxSeats)
		bsuccess = insertSeat(&rp->seats[seat],p);
	return bsuccess;
}

bool outputRow(struct Row* rp,int row)
{
	int s = 0;
	for (s=0; s<rp->nseats; s++)
		outputSeat(&rp->seats[s],row,s);
	return s > 0;
}

bool releaseRow(struct Row* rp)
{
	int s = 0;
	for (s=0; s<rp->nseats; s++)
		releaseSeat(&rp->seats[s]);
	free(rp->seats);
	return s > 0;
}

struct Section
{
	struct Row* rows;
	int nrows;
};

bool initSection(struct Section* sp, int nr, int ns)
{
	int r = 0;
	sp->rows = (struct Row*) malloc(sizeof(struct Row)*nr);
	sp->nrows = nr;
	for (r=0; r<nr; r++)
		initRow(&sp->rows[r],ns);
	return r > 0;
}

bool insertSection(struct Section* sp, int row, int maxSeats, struct Passenger* p)
{
	bool bsuccess = TRUE;
	Row* prow = &sp->rows[row];
	if (!insertRow(prow,maxSeats,p))
	{
		deletePassenger(p);
		free(p);
		bsuccess = FALSE;
	}
	return bsuccess;
}

bool outputSection(struct Section* sp,int radjust)
{
	int r = 0;
	for (r=0; r<sp->nrows; r++)
	{
		outputRow(&sp->rows[r],r+radjust);
	}
	return r > 0;
}

bool releaseSection(struct Section* sp)
{
	int r = 0;
	for (r=0; r<sp->nrows; r++)
		releaseRow(&sp->rows[r]);
	free(sp->rows);
	return r > 0;
}

struct Airline
{
	struct AirlineInfo info;
	struct Section* sections;
	int nsections;
};

bool initAirline(struct Airline* ap)
{
	int s = 0;
	ap->sections = (struct Section*) malloc(sizeof(struct Section)*ap->info.sections);
	ap->nsections = ap->info.sections;
	for (s=0; s<ap->info.sections; s++)
		initSection(&ap->sections[s],ap->info.rows[s],ap->info.seats[s]);
	return ap->sections != NULL;
}

bool insertAirline(struct Airline* ap, struct Passenger* p)
{
	int index = 0;
	int rowTotal = 0;
	int previous = 0;
	int row = INVALID;
	int maxSeats = INVALID;
	bool binserted = TRUE;
	if (p->flight == ap->info.flight && p->row < ap->info.totalRows)
	{
		while (index < ap->nsections)
		{
			previous = rowTotal;
			rowTotal += ap->info.rows[index];
			maxSeats = ap->info.seats[index];
			if (p->row < rowTotal)
				break;
			index++;
		}
		if ( rowTotal > 0 && p->seatno - 'A' < ap->info.seats[index] )
			row = p->row % rowTotal - previous;
		binserted = insertSection(&ap->sections[index],row,maxSeats,p);
	}
	else
	{
		deletePassenger( p );
		free( p );
	}
	return binserted;
}

int readAirline(struct Airline* ap, char* fn)
{
	struct Passenger* passenger = NULL;
	char line[SIZE];
	int count = 0;
	FILE* in = fopen( fn,"r" );
	if ( in != NULL )
	{
		while ( !feof(in) )
		{
			if ( fgets( line, SIZE, in ) )
			{
				count++;
				passenger = (struct Passenger*) malloc(sizeof(struct Passenger));
				initPassenger(passenger,line);
				if ( !insertAirline(ap,passenger) )
					writeLog(&ap->info.errorLog,line);
			}
		}
	}
	else
	{
		printf("Unable to open file %s\n",fn);
		exit(0);
	}
	fclose(in);
	closeLog(&ap->info.errorLog);
	return count;
}

bool Configure(struct Airline* ap,char* inifile,char* find)
{
	initInfo(&ap->info,"ErrorLog.txt");
	getProfileData(&ap->info,inifile,find);
	initAirline(ap); 
	return TRUE;  // need to return something
}

int showAirline(struct Airline* ap)
{
	int s = 0;
	int nrows = 0;
	for (s=0; s<ap->nsections; s++)
	{
		printf("\n[Section %d]\n",s+1);
		outputSection(&ap->sections[s],nrows);
		nrows += ap->info.rows[s];
	}
	return s;
}

bool Release(struct Airline* ap)
{
	int s=0;
	for (s=0; s<ap->nsections; s++)
		releaseSection(&ap->sections[s]);
	free(ap->sections);
	releaseInfo(&ap->info);
	return s > 0;
}

void main()
{
	// lab constants
	char* inifile = "Airlineinfo.ini";
	char* flight = "[Flight 878]";
	char* csvfile = "Airline0.csv";
	// create, read and manipulate data
	struct Airline jet;
	Configure( &jet, inifile, flight );
	if (readAirline( &jet, csvfile) > 0 )
		showAirline( &jet );
	Release( &jet );
	// handle errors
	if ( GetErrorCount(&jet.info) )
		printf("\nNumber of errors in data file:  %d.  See error log data file for details.\n", GetErrorCount(&jet.info));
}
