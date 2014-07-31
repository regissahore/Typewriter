#include <fstream>
#include <iostream>
#include <io.h>
#include <Windows.h>
#include <cassert>
#include "SettingControl.h"
using namespace std;

SettingControl *SettingControl::control = nullptr;

SettingControl::SettingControl()
{
}


SettingControl::~SettingControl()
{
}

SettingControl& SettingControl::getInstance()
{
    if (nullptr == SettingControl::control)
    {
        SettingControl::control = new SettingControl();
    }
    return *SettingControl::control;
}

void SettingControl::finishExperiment()
{
    int exp = 0;
    if (_access("expriment.txt", 0) != -1)
    {
        fstream fin;
        fin.open("expriment.txt", ios::in);
        fin >> exp;
        fin.close();
    }
    ++exp;
    if (!CreateDirectory("Experiment", NULL))
    {
        assert("Unable to create folder.");
    }
    cout << "Experiment " << exp << endl;
    string outputPath = string("Experiment/") + to_string(exp) + string(".txt");
    fstream fout;
    fout.open(outputPath.c_str(), ios::out);
    fout.close();
    readAndPrint(this->detect.getFolderName() + "parameter.txt", outputPath);
    readAndPrint(this->feature.getFolderName() + "parameter.txt", outputPath);
    readAndPrint(this->ranking.getFolderName() + "parameter.txt", outputPath);
    readAndPrint(this->evaluate.getFolderName() + "parameter.txt", outputPath);
    readAndPrint(this->evaluate.getFolderName() + "result.txt", outputPath);
    fout.open("expriment.txt", ios::out);
    fout << exp << endl;
    fout.flush();
    fout.close();
}

void SettingControl::readAndPrint(string inputPath, string outputPath)
{
    fstream fin, fout;
    fin.open(inputPath.c_str(), ios::in);
    fout.open(outputPath.c_str(), ios::app);
    string line;
    while (!fin.eof())
    {
        getline(fin, line);
        fout << line << endl;
        cout << line << endl;
    }
    fin.close();
    fout.close();
}