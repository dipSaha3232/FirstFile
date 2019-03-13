#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>
#include<fstream>
#include<stack>
#include<queue>
#include<algorithm>
#include<conio.h>

using namespace std;

/*used for reading source code file*/

ifstream iFile;

/*used for writing tokens into another file*/

ofstream oFile;

/*find a separator*/

bool printMethod=false;

bool canCreateSingleWord(char ch)
{
    string seperator[]={"\t","\n"," ",",",";",".","(",")","&","&&","|","||","{","}","+","-","*","/","!","[","]"};

    for(int i=0;i<21;i++)
    {

        if(string(1,ch)==seperator[i])
            return true;
    }
    return false;

}

/*if character is not a separator then concatenate it with substring*/

void concatenate(char ch,string &token)
{
    token+=string(1,ch);
}

/*identify the variable type*/

bool variable_type_identifier(string token)
{
    if(token=="int" || token=="float" || token=="double" || token=="char" || token=="String" || token=="boolean")
        return true;
}

vector <string> method_Signature;

void printMethodSignature()
{
    while(!method_Signature.empty())
    {
        if(method_Signature.front() != "[")
            cout<<method_Signature.front()<<" ";

        else
            cout<<method_Signature.front();

        method_Signature.erase(method_Signature.begin());
    }

    printMethod=false;

    cout<<endl;
}

void store_Component_Of_Method_Signature(string component)
{

    method_Signature.push_back(component);
}

/*to identify a method*/

int method_identifier(string token,int &currentState)
{

    /*check whether the token is a data type or modifier or symbol*/

    if(currentState==3 && token != "[")
    {
        store_Component_Of_Method_Signature(token);
    }

    if(currentState==5)
    {
        store_Component_Of_Method_Signature(token);
    }

    if(currentState==7 && !(token=="public" || token=="private" || token=="protected"
        || token=="int" || token=="float" || token=="double" || token=="char"
         || token=="String" || token=="boolean" || token=="void" || token=="static" ||
          token=="abstract" || token=="(" || token=="[" || token=="]" || token=="{" || token==")"))

    {
        store_Component_Of_Method_Signature(token);
    }

    if(token=="public" || token=="private" || token=="protected"
        || token=="int" || token=="float" || token=="double" || token=="char"
         || token=="String" || token=="boolean" || token=="void" || token=="static" ||
          token=="abstract" || token=="(" || token=="[" || token=="{" || token==")"
          || token=="]")

    {

        if(currentState==7 && token !="{")
        {
            store_Component_Of_Method_Signature(token);

            return currentState;
        }

        if(currentState==0 && (token=="public" || token=="private" || token=="protected"))
        {
            store_Component_Of_Method_Signature(token);
            currentState++;
        }

        else if(currentState==0 && (token=="int" || token=="float" || token=="double" || token=="char" ||
                                    token=="String" || token=="boolean" || token=="void"))
        {
            store_Component_Of_Method_Signature(token);
            currentState=currentState+3;
        }

        else if(currentState==0 && (token=="static" || token=="abstract"))
        {
            store_Component_Of_Method_Signature(token);
            currentState=currentState+2;
        }

        else if(currentState==1 && (token=="int" || token=="float" || token=="double" || token=="char" ||
                                     token=="String" || token=="boolean" || token=="void"))
        {
            store_Component_Of_Method_Signature(token);
            currentState=currentState+2;
        }

        else if(currentState==1 && (token=="static" || token=="abstract"))
        {
            store_Component_Of_Method_Signature(token);
            currentState++;
        }

        else if(currentState==2 && (token=="int" || token=="float" || token=="double" ||
                                    token=="char" || token=="String" || token=="boolean" || token=="void"))
        {
            store_Component_Of_Method_Signature(token);
            currentState++;
        }

        else if(currentState==6 && token=="(")
        {
            store_Component_Of_Method_Signature(token);
            currentState++;
        }

        else if(currentState==3 && token=="[")
        {
            store_Component_Of_Method_Signature(token);
            currentState++;
        }

        else if(currentState==4 && token=="]")
        {
            store_Component_Of_Method_Signature(token);
            currentState++;
        }

        else if(currentState==3)
        {
            //store_Component_Of_Method_Signature(token,currentState);
            currentState=currentState+3;
        }

        else
        {
            currentState=0;
        }

        if(currentState==6)
        {
            currentState++;
        }

    }

    return currentState;

}

int main(void)
{

    /*count total method in a class*/

    int totalMethod=0;

    /*file name of source code*/

    string javaFile;

    cout<<"Enter your file name : ";

    cin>>javaFile;

    /*open the source code file*/

    iFile.open(javaFile.c_str());

    /*a text file "dipOut.txt" is created to write the tokens*/

    oFile.open("dipOut.txt",ofstream::app);

    /*initially token is null*/

    string token=" ";
    token.clear();

    /*if two files are opened*/

    if(iFile.is_open() && oFile.is_open())
    {

        cout<<endl;
        cout<<"your file is reading successfully"<<endl<<endl;

        string sourceCode;
        getline(iFile,sourceCode);

        while(!iFile.eof())
        {

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

                if(sourceCode[i]=='(' || sourceCode[i]==')' || sourceCode[i]=='{' || sourceCode[i]=='}' || sourceCode[i]==';'
                                    || sourceCode[i]==',' || sourceCode[i]=='[' || sourceCode[i]==']')
                    oFile<<sourceCode[i]<<endl;

            }

            getline(iFile,sourceCode);
        }

        iFile.close();
        oFile.close();
    }

    else
    {
        cout<<"There is no such file in this name"<<endl;
    }

    /*used to clear text of a file*/
    fstream ofs;

    //ofs.open("dipOut.txt",ios::out | ios::trunc);

    /*read the token from "dipOut.txt" file*/

    ifstream readFileOfTokens;

    readFileOfTokens.open("dipOut.txt");

    /*store token*/

    string s;

    /*state to check method*/

    int currentState=0;

    if(readFileOfTokens.is_open())
    {

        readFileOfTokens>>s;

        while(!readFileOfTokens.eof())
        {
            currentState=method_identifier(s,currentState);

            /*increment totalMethod if current state is seven and set value of currentState is zero*/

            if(currentState==7 && s==")")
            {
                totalMethod++;
                printMethodSignature();

                currentState=0;
            }

            readFileOfTokens>>s;

        }

        readFileOfTokens.close();
    }

    cout<<endl<<"Total method in the class : "<<totalMethod<<endl;

    return 0;

}
