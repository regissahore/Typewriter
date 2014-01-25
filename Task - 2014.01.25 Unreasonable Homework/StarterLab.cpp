// StarterLab.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
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
        fperr.open(fname);
        errorCount = 0;
        return fperr != NULL;
    }
    bool closeLog()
    {
        fperr.close();
        return true;
    }
    bool writeLog(char* errortxt)
    {
        fperr << errortxt << endl;
        errorCount++;
        return true;
    }
    int GetErrorCount()
    {
        return errorCount;
    }
private:
    ofstream fperr;
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
        if (rows)
            delete[] rows;
        if (seats)
            delete[] seats;
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
        ifstream fpini(inifile);
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
                rows = new int[value];
                seats = new int[value];
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
        fpini.close();
        return TRUE;
    }
    int GetErrorCount()
    {
        return errorLog.GetErrorCount();
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
    bool findValue(ifstream &fp, char* section, char* skey, char* svalue)
    {
        bool bfound = FALSE;
        char* ptr = NULL;
        char buffer[SIZE];
        fp.getline(buffer, SIZE);
        while (strstr(buffer,section) == NULL)
        {
            fp.getline(buffer, SIZE);
        }
        while (strstr(buffer,skey) == NULL)
        {
            fp.getline(buffer, SIZE);
        }
        if (strlen(buffer))
        {
            ptr = strtok(buffer,EQUAL);
            ptr = strtok(NULL,EQUAL);
            strcpy(svalue,ptr);
            bfound = TRUE;
        }
        fp.seekg(0);
        return bfound;
    }
    bool getProfileInt(ifstream &fpini, char* psection, char* pfield, int* value)
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
        bool bsuccess = FALSE;
        if ( plast )
        {
            delete[] plast;
            plast = NULL;
            bsuccess = TRUE;
        }
        if ( pfirst )
        {
            delete[] pfirst;
            pfirst = NULL;
            bsuccess = TRUE;
        }
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
        plast = new char[strlen(pl) + 1];
        pfirst = new char[strlen(pf) + 1];
        strcpy( plast, pl );
        strcpy( pfirst, pf );
        row = atoi(pr);
        seatno = *ps;
        flight = atoi(pt);
        return line != NULL;
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
        bool bvalue = false;
        if (passenger)
        {
            delete passenger;
            passenger = NULL;
            bvalue = true;
        }
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
        int s = 0;
        delete[] seats;
    }
    bool initRow(int nrows)
    {
        int s = 0;
        seats = new Seat[nrows];
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
        int r = 0;
        delete[] rows;
    }
    bool initSection(int nr, int ns)
    {
        int r = 0;
        rows = new Row[nr];
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
            delete p;
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
        delete[] sections;
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
        sections = new Section[info.getSections()];
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
            delete p;
        }
        return binserted;
    }
    int readAirline(char* fn)
    {
        Passenger* passenger = NULL;
        char line[SIZE];
        int count = 0;
        ifstream in(fn);
        while ( !in.eof() )
        {
            in.getline(line, SIZE);
            count++;
            passenger = new Passenger(line);
            if ( !insertAirline(passenger) )
                info.getErrorLog()->writeLog(line);
        }
        in.close();
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
    // handle errors
    if ( jet.getInfo()->GetErrorCount() )
        printf("\nNumber of errors in data file:  %d.  See error log data file for details.\n", jet.getInfo()->GetErrorCount());
    return 0;
}
