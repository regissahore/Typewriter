// StarterLab.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

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

class ErrorLog
{
public:
    bool openLog(char* fname)
    {
        fperr = fopen(fname,"w");
        errorCount = 0;
        return fperr != NULL;
    }
    bool closeLog()
    {
        fclose(fperr);
        return true;
    }
    bool writeLog(char* errortxt)
    {
        fputs(errortxt, fperr);
        errorCount++;
        return true;
    }
    int GetErrorCount()
    {
        return errorCount;
    }
private:
    FILE* fperr;
    int errorCount;
};

class AirlineInfo
{
public:
    AirlineInfo()
    {
    }
    AirlineInfo(char *ename)
    {
        initInfo(ename);
    }
    ~AirlineInfo()
    {
        releaseInfo();
    }
    bool initInfo(char* ename)
    {
        flight = INVALID;
        sections = INVALID;
        totalRows = 0;
        rows = NULL;
        seats = NULL;
        return errorLog.openLog(ename);
    }
    bool getProfileData(char* inifile, char* psection)
    {
        FILE* fpini = fopen(inifile,"r");
        char buffer[SIZE];
        int value = INVALID;
        int x = 0;
        if ( fpini )
        {
            if ( getProfileInt(fpini,psection,"flight",&value) )
                flight = value;
            if ( getProfileInt(fpini,psection,"sections",&value) )
            {
                sections = value;
                rows = (int*)malloc(sizeof(int)*value);
                seats = (int*)malloc(sizeof(int)*value);
                for (x=0; x<sections; x++)
                {
                    sprintf(buffer,"section%d rows",x+1);
                    getProfileInt(fpini,psection,buffer,&value);
                    rows[x] = value;
                    totalRows += value;
                }
                for (x=0; x<sections; x++)
                {
                    sprintf(buffer,"section%d seats",x+1);
                    getProfileInt(fpini,psection,buffer,&value);
                    seats[x] = value;
                }
            }
        }
        fclose( fpini );
        return fpini != NULL;
    }
    int GetErrorCount()
    {
        return errorLog.GetErrorCount();
    }
    bool releaseInfo()
    {
        if (rows)
            free(rows);
        if (seats)
            free(seats);
        return TRUE;
    }
    int getFlight()
    {
        return flight;
    }
    int getSections()
    {
        return sections;
    }
    int getTotalRows()
    {
        return totalRows;
    }
    int* getRows()
    {
        return rows;
    }
    int* getSeats()
    {
        return seats;
    }
    class ErrorLog* getErrorLog()
    {
        return &errorLog;
    };
private:
    int flight;
    int sections;
    int totalRows;
    int* rows;
    int* seats;
    class ErrorLog errorLog;
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
};

class Passenger
{
public:
    Passenger()
    {
    }
    Passenger(char* line)
    {
        initPassenger(line);
    }
    ~Passenger()
    {
        deletePassenger();
    }
    bool initPassenger(char* line )
    {
        char tstring[SIZE];
        strcpy(tstring,line);
        char* pl = strtok(tstring,",");
        char* pf = strtok(NULL,",");
        char* pr = strtok(NULL,",");
        char* ps = strtok(NULL,",");
        char* pt = strtok(NULL,",");
        plast = (char *) malloc( strlen( pl )+1 );
        pfirst = (char *) malloc( strlen( pf )+1 );
        strcpy( plast, pl );
        strcpy( pfirst, pf );
        row = atoi(pr);
        seatno = *ps;
        flight = atoi(pt);
        return line != NULL;
    }
    bool deletePassenger()
    {
        bool bsuccess = FALSE;
        if ( plast )
        {
            free( plast );
            plast = NULL;
            bsuccess = TRUE;
        }
        if ( pfirst )
        {
            free( pfirst );
            pfirst = NULL;
            bsuccess = TRUE;
        }
        return bsuccess == TRUE;
    }
    char* toString()
    {
        static char gbuffer[SIZE];
        char tbuffer[SIZE];
        strcpy(gbuffer,plast);
        strcat(gbuffer,COMMA);
        strcat(gbuffer,pfirst);
        strcat(gbuffer,COMMA);
        strcat(gbuffer,itoa(row,tbuffer,10));
        int slength = strlen(gbuffer);
        gbuffer[slength] = seatno;
        gbuffer[slength+1] = NULL;
        return gbuffer;
    }
    int getRow()
    {
        return row;
    }
    char getSeatNo()
    {
        return seatno;
    }
    int getFlight()
    {
        return flight;
    }
private:
    char* plast;
    char* pfirst;
    int  row;
    char seatno;
    int  flight;
};

class Seat
{
public:
    Seat()
    {
        passenger = NULL;
    }
    ~Seat()
    {
        releaseSeat();
    }
    bool insertSeat(Passenger* p)
    {
        bool bsuccess = TRUE;
        if ( p != NULL )
        {
            if (passenger == NULL)
                passenger = p;
            else
                bsuccess = FALSE;
        }
        else
            passenger = NULL;
        return bsuccess;
    }

    bool outputSeat(int row,int seat)
    {
        if (passenger)
            printf("%s\n",passenger->toString());
        else
            printf("Empty %d%c\n",row,seat+'A');
        return passenger != NULL;
    }

    bool releaseSeat()
    {
        bool bvalue = false;
        if (passenger)
        {
            passenger->deletePassenger();
            free(passenger);
            passenger = NULL;
            bvalue = true;
        }
        return bvalue;
    }
private:
    Passenger* passenger;
};

class Row
{
public:
    Row()
    {
    }
    Row(int nrows)
    {
        initRow(nrows);
    }
    ~Row()
    {
        releaseRow();
    }
    bool initRow(int nrows)
    {
        int s = 0;
        seats = (Seat*)malloc(sizeof(Seat)*nrows);
        nseats = nrows;
        for (s=0; s<nseats; s++)
            seats[s].insertSeat(NULL);
        return s > 0;
    }
    bool insertRow(int maxSeats, Passenger* p)
    {
        bool bsuccess = FALSE;
        int seat = p->getSeatNo() - 'A';
        if (seat > -1 && seat < maxSeats)
            bsuccess = seats[seat].insertSeat(p);
        return bsuccess;
    }
    bool outputRow(int row)
    {
        int s = 0;
        for (s=0; s<nseats; s++)
            seats[s].outputSeat(row,s);
        return s > 0;
    }
    bool releaseRow()
    {
        int s = 0;
        for (s=0; s<nseats; s++)
            seats[s].releaseSeat();
        free(seats);
        return s > 0;
    }
private:
    Seat* seats;
    int nseats;
};

class Section
{
public:
    Section()
    {
    }
    Section(int nr, int ns)
    {
        initSection(nr, ns);
    }
    ~Section()
    {
        releaseSection();
    }
    bool initSection(int nr, int ns)
    {
        int r = 0;
        rows = (Row*) malloc(sizeof(Row)*nr);
        nrows = nr;
        for (r=0; r<nr; r++)
            rows[r].initRow(ns);
        return r > 0;
    }
    bool insertSection(int row, int maxSeats, Passenger* p)
    {
        bool bsuccess = TRUE;
        Row* prow = &rows[row];
        if (!prow->insertRow(maxSeats,p))
        {
            p->deletePassenger();
            free(p);
            bsuccess = FALSE;
        }
        return bsuccess;
    }
    bool outputSection(int radjust)
    {
        int r = 0;
        for (r=0; r<nrows; r++)
        {
            rows[r].outputRow(r+radjust);
        }
        return r > 0;
    }
    bool releaseSection()
    {
        int r = 0;
        for (r=0; r<nrows; r++)
            rows[r].releaseRow();
        free(rows);
        return r > 0;
    }
private:
    Row* rows;
    int nrows;
};

class Airline
{
public:
    Airline()
    {
    }
    Airline(char* inifile,char* find)
    {
        Configure(inifile, find);
    }
    ~Airline()
    {
        Release();
    }
    bool Configure(char* inifile,char* find)
    {
        info.initInfo("ErrorLog.txt");
        info.getProfileData(inifile,find);
        initAirline();
        return TRUE;  // need to return something
    }
    bool initAirline()
    {
        int s = 0;
        sections = (Section*) malloc(sizeof(Section)*info.getSections());
        nsections = info.getSections();
        for (s=0; s<info.getSections(); s++)
            sections[s].initSection(info.getRows()[s],info.getSeats()[s]);
        return sections != NULL;
    }
    bool insertAirline(Passenger* p)
    {
        int index = 0;
        int rowTotal = 0;
        int previous = 0;
        int row = INVALID;
        int maxSeats = INVALID;
        bool binserted = TRUE;
        if (p->getFlight() == info.getFlight() && p->getRow() < info.getTotalRows())
        {
            while (index < nsections)
            {
                previous = rowTotal;
                rowTotal += info.getRows()[index];
                maxSeats = info.getSeats()[index];
                if (p->getRow() < rowTotal)
                    break;
                index++;
            }
            if ( rowTotal > 0 && p->getSeatNo() - 'A' < info.getSeats()[index] )
                row = p->getRow() % rowTotal - previous;
            binserted = sections[index].insertSection(row,maxSeats,p);
        }
        else
        {
            p->deletePassenger();
            free( p );
        }
        return binserted;
    }
    int readAirline(char* fn)
    {
        Passenger* passenger = NULL;
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
                    passenger = (Passenger*) malloc(sizeof(Passenger));
                    passenger->initPassenger(line);
                    if ( !insertAirline(passenger) )
                        info.getErrorLog()->writeLog(line);
                }
            }
        }
        else
        {
            printf("Unable to open file %s\n",fn);
            exit(0);
        }
        fclose(in);
        info.getErrorLog()->closeLog();
        return count;
    }
    int showAirline()
    {
        int s = 0;
        int nrows = 0;
        for (s=0; s<nsections; s++)
        {
            printf("\n[Section %d]\n",s+1);
            sections[s].outputSection(nrows);
            nrows += info.getRows()[s];
        }
        return s;
    }
    bool Release()
    {
        int s=0;
        for (s=0; s<nsections; s++)
            sections[s].releaseSection();
        free(sections);
        info.releaseInfo();
        return s > 0;
    }
    AirlineInfo* getInfo()
    {
        return &info;
    };
private:
    AirlineInfo info;
    Section* sections;
    int nsections;
};

int main()
{
    // lab constants
    char* inifile = "Airlineinfo.ini";
    char* flight = "[Flight 878]";
    char* csvfile = "Airline0.csv";
    // create, read and manipulate data
    Airline jet;
    jet.Configure( inifile, flight );
    if (jet.readAirline( csvfile) > 0 )
        jet.showAirline();
    jet.Release();
    // handle errors
    if ( jet.getInfo()->GetErrorCount() )
        printf("\nNumber of errors in data file:  %d.  See error log data file for details.\n", jet.getInfo()->GetErrorCount());
    return 0;
}
