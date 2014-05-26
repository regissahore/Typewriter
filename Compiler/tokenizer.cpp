#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
const int BUFFER_SIZE = 1024;

class Stream
{
public:
    Stream()
    {
        first = 0;
        index = 0;
        current = 0;
        other = 1;
        this->read();
    }
    char getCurrent()
    {
        return buffer[current][index];
    }
    char getNext()
    {
        if (buffer[current][index] == EOF)
        {
            return EOF;
        }
        if (++index >= BUFFER_SIZE)
        {
            swap(current, other);
            this->read();
            index = 0;
        }
        return buffer[current][index];
    }
    string getToken()
    {
        string token = "";
        while (first != index)
        {
            if (first > index)
            {
                token += buffer[other][first];
            }
            else
            {
                token += buffer[current][first];
            }
            if (++first >= BUFFER_SIZE)
            {
                first = 0;
            }
        }
        return token;
    }
private:
    int first, index;
    int current, other;
    char buffer[2][BUFFER_SIZE];
    void read()
    {
        for (int i = 0; i < BUFFER_SIZE; ++i)
        {
            char ch = getchar();
            buffer[current][i++] = ch;
            if (ch == EOF)
            {
                break;
            }
        }
    }
};

class Tokenizer
{
public:
    Tokenizer()
    {
    }
    void parse()
    {
        if (isDigit(stream.getCurrent()))
        {
            //
        }
    }
    void print()
    {
        cout << "<table>" << endl;
        cout << "<tr><th>Token</th><th>Type</th></tr>" << endl;;
        for (auto token : tokens)
        {
            cout << "<tr><td>" << getTokenType(token.type) << "</td>";
            cout << "<td>" << token.token << "</td></tr>";
        }
        cout << "</table>" << endl;
    }
private:
    Stream stream;
    enum TokenType
    {
        TOKEN_KEYWORD, TOKEN_IDENTIFIER, TOKEN_OPERATOR, TOKEN_DELIMITER,
        TOKEN_CHARACTER, TOKEN_STRING, TOKEN_INTEGER, TOKEN_DOUBLE
    };
    struct Token
    {
        string token;
        TokenType type;
    };
    vector<Token> tokens;
    string getTokenType(TokenType type)
    {
        switch (type)
        {
        case TOKEN_KEYWORD: return "Keyword";
        case TOKEN_IDENTIFIER: return "Identifier";
        case TOKEN_OPERATOR: return "Operator";
        case TOKEN_DELIMITER: return "Delimiter";
        case TOKEN_CHARACTER: return "Character";
        case TOKEN_STRING: return "String";
        case TOKEN_INTEGER: return "Integer";
        case TOKEN_DOUBLE: return "Double";
        default: return "Undefined";
        }
    }
    bool isAlpha(char ch)
    {
        return ch >= 'a' && ch <= 'z' && ch >= 'A' && ch <= 'Z';
    }
    bool isDigit(char ch)
    {
        return ch >= '0' && ch <= '9';
    }
};

int main(int argc, char **argv)
{
    Tokenizer tokenizer;
    tokenizer.parse();
    tokenizer.print();
    return 0;
}
