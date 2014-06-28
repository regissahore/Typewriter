#include "lex.h"
#include "grammar.h"
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
    return 0;
}
