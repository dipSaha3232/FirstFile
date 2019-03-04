#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

ifstream iFile;
ofstream oFile;


bool canCreateSingleWord(char ch)
{
    string seperator[]={"\t","\n"," ",",",";",".","(",")","&","&&","|","||","{","}","+","-","*","/"};

    for(int i=0;i<18;i++)
    {
        if(string(1,ch)==seperator[i])
            return true;
    }
    return false;

}

void concatenate(char ch,string &token)
{
    token+=string(1,ch);
}

bool variable_type_identifier(string token)
{
    if(token=="int" || token=="float" || token=="double" || token=="char" || token=="String" || token=="boolean")
        return true;
}

int method_identifier(string token,int &currentState)
{
    if(token=="public" || token=="private" || token=="protected" || token=="int" || token=="float" || token=="double" || token=="char" || token=="String" || token=="boolean" || token=="void" || token=="static" || token=="abstract" || token=="(")
    {
        if(currentState==0 && (token=="public" || token=="private" || token=="protected"))
            currentState++;
        else if(currentState==0 && (token=="int" || token=="float" || token=="double" || token=="char" || token=="String" || token=="boolean" || token=="void"))
            currentState=currentState+3;
        else if(currentState==0 && (token=="static" || token=="abstract"))
            currentState=currentState+2;
        else if(currentState==1 && (token=="int" || token=="float" || token=="double" || token=="char" || token=="String" || token=="boolean" || token=="void"))
            currentState=currentState+2;
        else if(currentState==1 && (token=="static" || token=="abstract"))
            currentState++;
        else if(currentState==2 && (token=="int" || token=="float" || token=="double" || token=="char" || token=="String" || token=="boolean" || token=="void"))
            currentState++;
        else if(currentState==4 && token=="(")
            currentState++;
        else
            currentState=0;
        if(currentState==3)
            currentState++;
    }
    return currentState;

}

int main(void)
{
    int totalMethod=0;

    string javaFile;

    cout<<"Enter your file name : ";
    cin>>javaFile;

    iFile.open(javaFile.c_str());

    oFile.open("dipOut.txt",ofstream::app);

    string token=" ";
    token.clear();

    if(iFile.is_open() && oFile.is_open())
    {
        string sourceCode;
        getline(iFile,sourceCode);

        for(long long int i=0;i<sourceCode.length();i++)
        {
            bool b=canCreateSingleWord(sourceCode[i]);

            if(b==false)
                concatenate(sourceCode[i],token);

            else
            {
                if(!token.empty())
                    oFile<<token<<endl;
                token.clear();
            }
            if(sourceCode[i]=='(' || sourceCode[i]==')' || sourceCode[i]=='{' || sourceCode[i]=='}' || sourceCode[i]==';')
                oFile<<sourceCode[i]<<endl;
        }

        iFile.close();
        oFile.close();
    }

    else
        cout<<"No such file exists."<<endl;

}

/*

#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

vector <string> streamOfTokens;

bool canCreateSingleWord(char ch)
{
    string seperator[]={"\t","\n"," ",",",";",".","(",")","&","&&","|","||","{","}","+","-","*","/"};

    for(int i=0;i<18;i++)
    {
        if(string(1,ch)==seperator[i])
            return true;
    }
    return false;

}

void concatenate(char ch,string &token)
{
    token+=string(1,ch);
}

bool variable_type_identifier(string token)
{
    if(token=="int" || token=="float" || token=="double" || token=="char" || token=="String" || token=="boolean")
        return true;
}

int method_identifier(string token,int &currentState)
{
    if(token=="public" || token=="private" || token=="protected" || token=="int" || token=="float" || token=="double" || token=="char" || token=="String" || token=="boolean" || token=="void" || token=="static" || token=="abstract" || token=="(")
    {
        if(currentState==0 && (token=="public" || token=="private" || token=="protected"))
            currentState++;
        else if(currentState==0 && (token=="int" || token=="float" || token=="double" || token=="char" || token=="String" || token=="boolean" || token=="void"))
            currentState=currentState+3;
        else if(currentState==0 && (token=="static" || token=="abstract"))
            currentState=currentState+2;
        else if(currentState==1 && (token=="int" || token=="float" || token=="double" || token=="char" || token=="String" || token=="boolean" || token=="void"))
            currentState=currentState+2;
        else if(currentState==1 && (token=="static" || token=="abstract"))
            currentState++;
        else if(currentState==2 && (token=="int" || token=="float" || token=="double" || token=="char" || token=="String" || token=="boolean" || token=="void"))
            currentState++;
        else if(currentState==4 && token=="(")
            currentState++;
        else
            currentState=0;
        if(currentState==3)
            currentState++;
    }
    return currentState;

}

int main(void)
{
    int totalMethod=0;
    string sourceCode;
    getline(cin,sourceCode);

    string token=" ";
    token.clear();

    for(long long int i=0;i<sourceCode.length();i++)
    {
        bool b=canCreateSingleWord(sourceCode[i]);

        if(b==false)
           concatenate(sourceCode[i],token);

        else
        {
            if(!token.empty())
                streamOfTokens.push_back(token);
            token.clear();
        }
        if(sourceCode[i]=='(' || sourceCode[i]==')' || sourceCode[i]=='{' || sourceCode[i]=='}' || sourceCode[i]==';')
            streamOfTokens.push_back(string(1,sourceCode[i]));
    }

    vector <string>::iterator tokenPtr;

    int currentState=0;

    for(tokenPtr=streamOfTokens.begin(); tokenPtr != streamOfTokens.end();tokenPtr++ )
    {
        token=*tokenPtr;
        currentState=method_identifier(token,currentState);
        if(currentState==5)
        {
            totalMethod++;
            currentState=0;
        }
    }
    cout<<totalMethod;
}
*/
