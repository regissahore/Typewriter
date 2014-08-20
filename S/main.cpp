#include "lex.h"
#include "grammar.h"
#include "asm.h"
using namespace std;

int main()
{
    vector<Token> tokens = getTokens();
    #ifdef DEBUG
    printTokens(tokens);
    #endif // DEBUG
    vector<Quaternion> quaternions = getQuaternions(tokens);
    #ifdef DEBUG
    printQuaternions(quaternions);
    #endif // DEBUG
    map<string, int> symbolMap = getSymbolMap();
    vector<SymbolNode> symbolTable = getSymbols();
    map<string, int> labelMap = getLabelMap();
    vector<SymbolNode> labelTable = getLabels();
    printAssembly(quaternions, symbolMap, symbolTable, labelMap, labelTable);
    return 0;
}
