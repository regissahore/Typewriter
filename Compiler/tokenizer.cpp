#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
const int BUFFER_SIZE = 1024;

const int KEYWORD_NUM = 32;
const string KEYWORD_LIST[] = {
    "auto", "break", "case", "char", "const",
    "continue", "default", "do", "double", "else",
    "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return",
    "short", "signed", "sizeof", "static", "struct",
    "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};

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
    char next()
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
    char prev()
    {
        --index;
        if (index < 0)
        {
            swap(current, other);
            index = BUFFER_SIZE - 1;
        }
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
    void ignoreToken()
    {
        first = index;
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
            buffer[current][i] = ch;
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
        while (true)
        {
            char ch = stream.getCurrent();
            if (isDigit(ch))
            {
                parseNumber();
            }
            else if (isAlpha(ch) or ch == '_')
            {
                parseIdentifier();
            }
            else if (isDelimiter(ch))
            {
                parseDelimiter();
            }
            else if (isOperator(ch))
            {
                parseOperator();
            }
            else if (ch == '\'')
            {
                parseChar();
            }
            else if (ch == '"')
            {
                parseString();
            }
            else if (ch == '#')
            {
                parseMarco();
            }
            else if (isWhitespace(ch))
            {
                stream.next();
                stream.ignoreToken();
            }
            else if (ch == EOF)
            {
                return;
            }
            else
            {
                fprintf(stderr, "Invalid character: %c\n", stream.getCurrent());
                stream.next();
                stream.ignoreToken();
            }
        }
    }
    void print()
    {
        for (auto token : tokens)
        {
            cout << getTokenType(token.type) << "\t" << token.token << endl;
        }
    }
    void printHTML()
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
        TOKEN_CHARACTER, TOKEN_STRING, TOKEN_INTEGER, TOKEN_DOUBLE, TOKEN_MARCO
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
        case TOKEN_MARCO: return "Marco";
        default: return "Undefined";
        }
    }
    bool isAlpha(char ch)
    {
        return (ch >= 'a' and ch <= 'z') or (ch >= 'A' and ch <= 'Z');
    }
    bool isDigit(char ch)
    {
        return ch >= '0' and ch <= '9';
    }
    bool isDelimiter(char ch)
    {
        return ch == '(' or ch == ')' or
               ch == '{' or ch == '}' or
               ch == ',' or ch == ';';
    }
    bool isOperator(char ch)
    {
        return ch == '+' or ch == '-' or ch == '*' or ch == '/' or ch == '%' or
               ch == '<' or ch == '=' or ch == '>' or
               ch == '&' or ch == '|' or ch == '!' or
               ch == '^' or ch == '~' or
               ch == '[' or ch == ']' or
               ch == '?' or ch == ':' or ch == '.';
    }
    bool isWhitespace(char ch)
    {
        return ch == ' ' or ch == '\t' or ch == '\n' or
               ch == '\v' or ch == '\f' or ch == '\r';
    }
    bool isKeyword(string &word)
    {
        for (auto keyword : KEYWORD_LIST)
        {
            if (keyword == word)
            {
                return true;
            }
        }
        return false;
    }
    void parseNumber()
    {
        int state = 0;
        stream.next();
        while (true)
        {
            char ch = stream.getCurrent();
            switch (state)
            {
            case 0:
                if (isDigit(ch)) state = 0;
                else if (ch == '.') state = 1;
                else if (ch == 'e' or ch == 'E') state = 2;
                else
                {
                    tokens.push_back({stream.getToken(), TOKEN_INTEGER});
                    return;
                }
                break;
            case 1:
                if (isDigit(ch)) state = 1;
                else if (ch == 'e' or ch == 'E') state = 2;
                else
                {
                    tokens.push_back({stream.getToken(), TOKEN_DOUBLE});
                    return;
                }
                break;
            case 2:
                if (isDigit(ch)) state = 3;
                else
                {
                    stream.next();
                    fprintf(stderr, "The format of number is invalid: ");
                    fprintf(stderr, stream.getToken().c_str());
                    fprintf(stderr, "\n");
                    return;
                }
                break;
            case 3:
                if (isDigit(ch)) state = 3;
                else
                {
                    tokens.push_back({stream.getToken(), TOKEN_DOUBLE});
                    return;
                }
                break;
            }
            stream.next();
        }
    }
    void parseIdentifier()
    {
        stream.next();
        while (true)
        {
            char ch = stream.getCurrent();
            if (isDigit(ch) or isAlpha(ch) or ch == '_')
            {
                stream.next();
            }
            else
            {
                break;
            }
        }
        string token = stream.getToken();
        if (isKeyword(token))
        {
            tokens.push_back({token, TOKEN_KEYWORD});
        }
        else
        {
            tokens.push_back({token, TOKEN_IDENTIFIER});
        }
    }
    void parseDelimiter()
    {
        stream.next();
        tokens.push_back({stream.getToken(), TOKEN_DELIMITER});
    }
    void parseOperator()
    {
        char ch1 = stream.getCurrent();
        stream.next();
        char ch2 = stream.getCurrent();
        switch (ch1)
        {
        case '=':
            if (ch2 == '=')
            {
                stream.next();
            }
            break;
        case '+':
            if (ch2 == '+' or ch2 == '=')
            {
                stream.next();
            }
            break;
        case '-':
            if (ch2 == '-' or ch2 == '=' or ch2 == '>')
            {
                stream.next();
            }
            break;
        case '*':
        case '%':
        case '!':
        case '~':
        case '^':
            if (ch2 == '=')
            {
                stream.next();
            }
            break;
        case '/':
            if (ch2 == '=')
            {
                stream.next();
            }
            else if (ch2 == '*')
            {
                parseComment();
                return;
            }
            break;
        case '&':
            if (ch2 == '&' or ch2 == '=')
            {
                stream.next();
            }
            break;
        case '|':
            if (ch2 == '|' or ch2 == '=')
            {
                stream.next();
            }
            break;
        case '>':
            if (ch2 == '>')
            {
                stream.next();
                if (stream.getCurrent() == '=')
                {
                    stream.next();
                }
            }
            else if (ch2 == '=')
            {
                stream.next();
            }
            break;
        case '<':
            if (ch2 == '<')
            {
                stream.next();
                if (stream.getCurrent() == '=')
                {
                    stream.next();
                }
            }
            else if (ch2 == '=')
            {
                stream.next();
            }
            break;
        }
        tokens.push_back({stream.getToken(), TOKEN_OPERATOR});
    }
    void parseComment()
    {
        while (true)
        {
            if (stream.getCurrent() == '*')
            {
                stream.next();
                if (stream.getCurrent() == '/')
                {
                    stream.next();
                    break;
                }
                stream.next();
            }
            else
            {
                stream.next();
            }
        }
        stream.ignoreToken();
    }
    void parseChar()
    {
        bool valid = true;
        stream.next();
        if (stream.getCurrent() == '\\')
        {
            stream.next();
            stream.next();
            if (stream.getCurrent() == '\'')
            {
                stream.next();
            }
            else
            {
                valid = false;
            }
        }
        else
        {
            if (stream.getCurrent() == '\'')
            {
                valid = false;
            }
            stream.next();
            if (stream.getCurrent() == '\'')
            {
                stream.next();
            }
            else
            {
                valid = false;
            }
        }
        if (valid)
        {
            tokens.push_back({stream.getToken(), TOKEN_CHARACTER});
        }
        else
        {
            stream.next();
            fprintf(stderr, "The format of char is invalid: ");
            fprintf(stderr, stream.getToken().c_str());
            fprintf(stderr, "\n");
        }
    }
    void parseString()
    {
        stream.next();
        while (true)
        {
            if (stream.getCurrent() == '"')
            {
                stream.next();
                tokens.push_back({stream.getToken(), TOKEN_STRING});
                return;
            }
            else if (stream.getCurrent() == '\\')
            {
                stream.next();
            }
            stream.next();
        }
        stream.next();
        fprintf(stderr, "The format of string is invalid: ");
        fprintf(stderr, stream.getToken().c_str());
        fprintf(stderr, "\n");
    }
    void parseMarco()
    {
        stream.next();
        while (stream.getCurrent() != '\n' and stream.getCurrent() != EOF)
        {
            stream.next();
            if (stream.getCurrent() == '/')
            {
                stream.next();
                if (stream.getCurrent() == '*')
                {
                    stream.prev();
                    tokens.push_back({stream.getToken(), TOKEN_MARCO});
                    parseComment();
                    return;
                }
            }
        }
        tokens.push_back({stream.getToken(), TOKEN_MARCO});
    }
};

int main(int argc, char **argv)
{
    Tokenizer tokenizer;
    tokenizer.parse();
    tokenizer.printHTML();
    return 0;
}
