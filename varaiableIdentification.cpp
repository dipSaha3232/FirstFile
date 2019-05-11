#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<stack>
#include<vector>

using namespace std;

ifstream iFile;
ofstream oFile;

char my_character;

string className;

string superclass="";

string top_for_class="";
vector <string> list_of_interface;

void classIdentifier(string token)
{

    if(token!="/s" && token!="/t" && token!="/n")
    {

        if((token=="public" || token=="private" || token=="protected") && top_for_class=="")
        {
            top_for_class=token;
        }

        else if(token=="abstract" && (top_for_class=="public" || top_for_class=="private"
                                                                || top_for_class=="protected"))
        {
            top_for_class=token;
        }

        else if((token=="class" || token=="interface") && (top_for_class=="public" || top_for_class=="private" || top_for_class=="protected"
                                    || top_for_class=="abstract"))
        {
            top_for_class=token;
        }

        else if(top_for_class=="class" || top_for_class=="interface")
        {
            top_for_class=token;
            className=token;
            top_for_class="classname";
        }

        else if(token=="extends" && top_for_class=="classname")
        {
            top_for_class=token;
        }

        else if(token=="implements" && (top_for_class=="superclass" || top_for_class=="classname"))
        {
            top_for_class=token;
        }

        else if(top_for_class=="implements")
        {
            top_for_class="interfaces";
            list_of_interface.push_back(token);
        }

        else if(top_for_class=="interfaces" && token==",")
        {
            top_for_class="implements";
        }

        else if(top_for_class=="extends")
        {

            top_for_class=token;
            superclass=token;
            top_for_class="superclass";

        }

        else if(token=="{" && top_for_class=="superclass")
        {
            top_for_class=token;
        }

        else if(token=="{" && top_for_class=="interfaces")
        {
            top_for_class=token;
        }

    }
}

string top_for_attribute="";

int total_attribute=0;


string attribute_access_modifier="public";

string attribute_name;

string attribute_data_type;


struct Attribute{

    string access_modifier;

    string data_type;

    string name;
};


bool isParameter=false;


void attributeIdentifier(string token)
{

    if(token!="/s" && token!="/t" && token!="/n")
    {

        if((token=="public" || token=="private" || token=="protected") && top_for_attribute=="")
        {

            top_for_attribute=token;

            attribute_access_modifier=token;
        }

        else if(token=="static" && (top_for_attribute=="public" || top_for_attribute=="private" || top_for_attribute=="protected"
                                         || top_for_attribute==""))
        {

            top_for_attribute=token;
        }

        else if(token=="final" && top_for_attribute=="static")
        {

            top_for_attribute=token;
        }

        else if((token=="int" || token=="float" || token=="double" || token=="char" || token=="String" || token=="void"
                || token=="boolean") && (top_for_attribute=="public" || top_for_attribute=="private" || top_for_attribute=="protected"
                                         || top_for_attribute=="" || top_for_attribute=="static" || top_for_attribute=="final"))
        {

            top_for_attribute=token;

            attribute_data_type=token;

        }

        else if(token=="[" && (top_for_attribute=="int" || top_for_attribute=="float" || top_for_attribute=="double" || top_for_attribute=="char"
                || top_for_attribute=="String" || top_for_attribute=="void" || top_for_attribute=="boolean"))
        {

            top_for_attribute=token;

        }

        else if(top_for_attribute=="int" || top_for_attribute=="float" || top_for_attribute=="double" || top_for_attribute=="char"
                || top_for_attribute=="String" || top_for_attribute=="void" || top_for_attribute=="boolean")
        {

            top_for_attribute=token;

            attribute_name=token;

            top_for_attribute="1attribute";

        }

        else if(token=="[" && top_for_attribute=="1attribute")
        {

            top_for_attribute=token;
        }

        else if(token=="]" && top_for_attribute=="[")
        {
            top_for_attribute=token;
        }

        else if((token=="=" || token==";") && (top_for_attribute=="1attribute" || top_for_attribute=="]"))
        {

            total_attribute++;

            Attribute *attribute=new Attribute;

            attribute->data_type=attribute_data_type;

            attribute->access_modifier=attribute_access_modifier;

            attribute->name=attribute_name;

            top_for_attribute="";

            attribute_access_modifier="public";

        }


        else if(token=="," && top_for_attribute=="1attribute")
        {

            if(!isParameter)
            {
                total_attribute++;
            }

            Attribute *attribute=new Attribute;

            attribute->data_type=attribute_data_type;

            attribute->access_modifier=attribute_access_modifier;

            attribute->name=attribute_name;

            top_for_attribute=token;

        }

        else if(top_for_attribute==",")
        {

            attribute_name=token;

            top_for_attribute="1attribute";

        }

        else if(top_for_attribute=="]")
        {

            top_for_attribute=token;
            attribute_name=token;

            top_for_attribute="1attribute";
        }

        else
        {
            top_for_attribute="";
        }
    }
}


string top_for_method="";

int total_method=0;

string method_access_modifier="public";

string method_return_type;

string method_name;

vector <string> parameter_list;

stack <string> stack_for_method_body;

string method_body="";

int current_state_for_method=0;



struct Method{

    string access_modifier;

    string return_type;

    string name;

    vector <string> list_of_parameter;

    string body;

};

vector <Method> list_of_method;

void method_identifier(string token)
{
        if((token=="public" || token=="private" || token=="protected" || token=="static" || token=="abstract"
            || token=="int" || token=="float" || token=="double" || token=="char" || token=="String"
            || token=="void" || token=="boolean") && top_for_method=="")
        {

            top_for_method=token;

            if(token=="public" || token=="private" || token=="protected")
            {
                method_access_modifier=token;
            }

            else if(token=="int" || token=="float" || token=="double" || token=="char" || token=="String"
            || token=="void" || token=="boolean")

            {
                method_return_type=token;
            }

        }

        else if((token=="static" || token=="abstract"|| token=="int" || token=="float" || token=="double" || token=="char" || token=="String"
            || token=="void" || token=="boolean") && (top_for_method=="public" || top_for_method=="private" ||
            top_for_method=="protected"))

        {
            top_for_method=token;

            if(token=="int" || token=="float" || token=="double" || token=="char" || token=="String"
            || token=="void" || token=="boolean")

            {
                method_return_type=token;
            }
        }

        else if((token=="int" || token=="float" || token=="double" || token=="char" || token=="String"
            || token=="void" || token=="boolean") && (top_for_method=="static" || top_for_method=="abstract"))

        {

            top_for_method=token;

            if(token=="int" || token=="float" || token=="double" || token=="char" || token=="String"
            || token=="void" || token=="boolean")

            {
                method_return_type=token;
            }

        }

        else if(token=="[" && (top_for_method=="int" || top_for_method=="float" || top_for_method=="double" || top_for_method=="char" ||
                top_for_method=="String" || top_for_method=="void" || top_for_method=="boolean"))

        {
            top_for_method=token;
        }

        else if(token=="]" && top_for_method=="[")
        {
            top_for_method=token;
        }

        else if((top_for_method=="int" || top_for_method=="float" || top_for_method=="double" || top_for_method=="char" || top_for_method=="String"
                  || top_for_method=="void" || top_for_method=="boolean" || top_for_method=="]" || top_for_method=="public"))

        {

            if(token!="/s" && token!="/t" && token!="/n")
            {
                top_for_method=token;
            }

            if(token!="/s" && token!="/t" && token!="/n")
            {
                top_for_method="1methodName";
            }

            method_name=token;

        }

        else if(token=="(" && top_for_method=="1methodName")
        {

            total_method++;

            top_for_method=token;

        }

        else if(top_for_method=="(")
        {

            if(token==")")
            {
                top_for_method=token;
            }

            else
            {
                if(token!="/s" && token!="/t" && token!="/n")
                {
                    parameter_list.push_back(token);
                }

                isParameter=true;
            }

        }

        else if(top_for_method==")")
        {

            if(token=="{")
            {
                stack_for_method_body.push(token);

                current_state_for_method=1;
            }

            else if(token=="}")
            {
                stack_for_method_body.pop();
            }

            if(current_state_for_method==1)
            {
                if(token=="/s")
                {
                    method_body+=" ";
                }

                else if(token=="/t")
                {
                    method_body+="\t";
                }

                else if(token=="/n")
                {
                    method_body+="\n";
                }

                else
                {
                    if(token!="{" && token!="}")
                        method_body+=token;
                }
            }

            if(stack_for_method_body.empty() && current_state_for_method==1)
            {

                current_state_for_method=0;


                Method *method=new Method;

                method->access_modifier=method_access_modifier;

                method->name=method_name;

                method->return_type=method_return_type;

                method->list_of_parameter=parameter_list;

                method->body=method_body;

                list_of_method.push_back(*method);


                method_body="";

                parameter_list.clear();

                isParameter=false;

                top_for_method="";
            }

        }

        else
        {
            if(token!="/s" && token!="/t" && token!="/n")
            {
                top_for_method="";
            }
        }

}


bool canCreateSingleWord(char ch)
{
    char seperator[]={'\t','\n',' ',',',';','.','(',')','&','|','{','}','+','-','*','/','!','[',']','>','<','=','^'};

    for(int i=0;i<23;i++)
    {
        if(ch==seperator[i])
        {
            return true;
        }
    }
    return false;

}


void concatenate(char ch,string &token)
{
    token+=string(1,ch);
}

void searchMethod(string methodName)
{
    vector <Method>::iterator itMethod;

    for(itMethod=list_of_method.begin();itMethod!=list_of_method.end();itMethod++)
    {
        if(itMethod->name==methodName)
        {

            int choice;

            cout<<"method is found"<<endl;
            cout<<"see \n1. return type\n2.parameter\n3.body"<<endl;

            cin>>choice;

            if(choice==1)
                cout<<itMethod->return_type<<endl;
            /*else if(choice==2)
                //cout<<itMethod->list_of_parameter<<endl;*/
            else if(choice==3)
                cout<<itMethod->body<<endl;

            return ;
        }
    }

    cout<<"not found"<<endl;
}

int main(void)
{
    string filename;

    cout<<"Enter a file name : ";

    getline(cin,filename);

    iFile.open(filename.c_str());

    oFile.open("dipOut.txt",ofstream::app);

    string token=" ";

    token.clear();

    int commentCheck=0;


    bool tokenization=true;

    bool tokenization2=true;


    bool isPreviousCharacterSlash=false;

    stack <char> multiLineComment;

    stack <char> singleLineComment;

    int state=0;

    int state2=0;

    if(iFile.is_open() && oFile.is_open())
    {
        iFile.get(my_character);

        while(!iFile.eof())
        {
            if(my_character=='*' && multiLineComment.top()=='*')
            {
                state=1;
            }

            else if(my_character=='/' && state==1)
            {

                while(!multiLineComment.empty())
                {
                    multiLineComment.pop();
                }

                tokenization=true;

                state=0;

                state2=1;

                isPreviousCharacterSlash=false;

            }

            else if(my_character!='/' && state==1)
                state=0;


            if(my_character=='*' && isPreviousCharacterSlash)
            {

                multiLineComment.push(my_character);

                tokenization=false;

                isPreviousCharacterSlash=false;

            }
            else if(my_character!='*' && isPreviousCharacterSlash)
            {

                multiLineComment.pop();

                tokenization=true;

                isPreviousCharacterSlash=false;

            }

            if(my_character=='/')
            {

                if(state2==1)
                {
                    state2=0;
                }

                else
                {
                    if(multiLineComment.empty())
                    {
                        multiLineComment.push(my_character);

                        isPreviousCharacterSlash=true;
                    }
                }

                if(commentCheck==0 && singleLineComment.empty())
                {
                    singleLineComment.push(my_character);

                    commentCheck++;
                }

                else if(commentCheck==1 && singleLineComment.top()=='/')
                {
                    singleLineComment.pop();

                    commentCheck++;

                    tokenization2=false;
                }

            }

            if(commentCheck==1 && my_character!='/')
            {
                singleLineComment.pop();

                commentCheck=0;

                tokenization2=true;
            }

            if(commentCheck==2 && my_character=='\n')
            {
                tokenization2=true;

                commentCheck=0;
            }


            if(tokenization && tokenization2)
            {
                bool b=canCreateSingleWord(my_character);

                if(b==false)
                    concatenate(my_character,token);

                else
                {
                    if(!token.empty())
                        oFile<<token<<endl;

                    token.clear();
                }

                char seperator[]={'\t','\n',' ',',',';','.','(',')','&','|','{','}','+','-','*','/','!','[',']','>','<','=','^'};

                for(int i=0;i<23;i++)
                {
                    if(my_character==seperator[i])
                    {

                        if(my_character==' ')
                            oFile<<"/s"<<endl;

                        else if(my_character=='\n')
                            oFile<<"/n"<<endl;

                        else if(my_character=='\t')
                            oFile<<"/t"<<endl;

                        else
                            oFile<<my_character<<endl;

                    }
                }
            }

            iFile.get(my_character);
        }

        iFile.close();

        oFile.close();

    }

    ifstream readFileOfTokens;

    readFileOfTokens.open("dipOut.txt");

    readFileOfTokens>>token;

    while(!readFileOfTokens.eof())
    {

        classIdentifier(token);

        method_identifier(token);

        attributeIdentifier(token);

        readFileOfTokens>>token;

    }

    cout<<"your class name is "<<className<<endl;
    cout<<"see \n1.superClass \n2.interfaces \n3.class information"<<endl;

    int choice;

    cin>>choice;

    if(choice==1)
        cout<<superclass<<endl;

    else if(choice==2)
    {
        vector <string>::iterator itInterface;

        for(itInterface=list_of_interface.begin();itInterface!=list_of_interface.end();itInterface++)
            cout<<*itInterface<<endl;
    }


    cout<<endl<<"total method = "<<total_method<<endl;

    cout<<"total attribute = "<<total_attribute<<endl;

    cout<<"enter a method name : "<<endl;

    string name;

    cin>>name;

    searchMethod(name);

}

