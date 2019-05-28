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

bool is_Interface=false;

bool isAbstract=false;

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

            isAbstract=true;
        }

        else if((token=="class" || token=="interface") && (top_for_class=="public" || top_for_class=="private" || top_for_class=="protected"
                                    || top_for_class=="abstract"))
        {
            top_for_class=token;

            if(token=="interface")
            {
                is_Interface=true;
            }
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

vector <Attribute> list_of_attribute;

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

        else if((token=="List" || token=="ArrayList" || token=="LinkedList" || token=="Set" || token=="HashSet"
                 || token=="LinkedHashSet" || token=="TreeSet" || token=="Map" || token=="HashMap"
                  || token=="LinkedHashMap" || token=="TreeMap" || token=="Vector" || token=="Stack"
                  || token=="Queue" || token=="Deque" || token=="PriorityQueue") && (top_for_attribute==""
                    || top_for_attribute=="public" || top_for_attribute=="private" || top_for_attribute=="protected"
                    || top_for_attribute=="static" || top_for_attribute=="final"))

        {
            top_for_attribute=token;

            attribute_data_type=token;
        }

        else if((top_for_attribute=="List" || top_for_attribute=="ArrayList" || top_for_attribute=="LinkedList"
                  || top_for_attribute=="Set" || top_for_attribute=="HashSet"
                 || top_for_attribute=="LinkedHashSet" || top_for_attribute=="TreeSet" || top_for_attribute=="Map"
                  || top_for_attribute=="HashMap" || top_for_attribute=="LinkedHashMap" || top_for_attribute=="TreeMap"
                || top_for_attribute=="Vector" || top_for_attribute=="Stack" || top_for_attribute=="Queue" ||
                 top_for_attribute=="Deque" || top_for_attribute=="PriorityQueue") && token=="<")

        {
            top_for_attribute=token;
        }

        else if((token=="Integer" || token=="String" || token=="Double" || token=="Character" || token=="Char"
                 || token=="Float" || token=="Object" || token=="") && top_for_attribute=="<")

        {
            top_for_attribute=token;
        }

        else if((top_for_attribute=="Integer" || top_for_attribute=="String" || top_for_attribute=="Double" ||
                  top_for_attribute=="Character" || top_for_attribute=="Char" || top_for_attribute=="Float" ||
                   top_for_attribute=="Object" || top_for_attribute=="") && token==">")

        {
            top_for_attribute=token;
        }

        else if((token=="int" || token=="float" || token=="double" || token=="char" || token=="String" || token=="void"
                || token=="boolean" || token=="Tread" || token=="BigInteger" || (token[0]>=65 && token[0]<=90)) && (top_for_attribute=="public" || top_for_attribute=="private" ||
                top_for_attribute=="protected"|| top_for_attribute=="" || top_for_attribute=="static" || top_for_attribute=="final"))
        {

            top_for_attribute=token;

            attribute_data_type=token;

            if(token[0]>=65 && token[0]<=90 && token !="String" && token!="Tread" && token!="BigInteger")
            {
                top_for_attribute="1class";
            }

        }

        else if(token=="[" && (top_for_attribute=="int" || top_for_attribute=="float" || top_for_attribute=="double" || top_for_attribute=="char"
                || top_for_attribute=="String" || top_for_attribute=="void" || top_for_attribute=="boolean"
                || top_for_attribute=="Tread"|| top_for_attribute=="BigInteger" || top_for_attribute=="1class"))

        {

            top_for_attribute=token;

        }

        else if(top_for_attribute=="int" || top_for_attribute=="float" || top_for_attribute=="double" || top_for_attribute=="char"
                || top_for_attribute=="String" || top_for_attribute=="void" || top_for_attribute=="boolean" ||
                top_for_attribute=="Tread" || top_for_attribute=="BigInteger" || top_for_attribute==">" || top_for_attribute=="1class")

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

        else if(token=="new" && top_for_attribute=="=")
        {
            total_attribute++;

            Attribute *attribute=new Attribute;

            attribute->data_type=attribute_data_type;

            attribute->access_modifier=attribute_access_modifier;

            attribute->name=attribute_name;

            list_of_attribute.push_back(*attribute);

            top_for_attribute="";

            attribute_access_modifier="public";
        }

        else if((token=="=" || token==";") && (top_for_attribute=="1attribute" || top_for_attribute=="]"))
        {

            total_attribute++;

            Attribute *attribute=new Attribute;

            attribute->data_type=attribute_data_type;

            attribute->access_modifier=attribute_access_modifier;

            attribute->name=attribute_name;

            list_of_attribute.push_back(*attribute);

            top_for_attribute="";

            attribute_access_modifier="public";

        }


        else if(token=="," && top_for_attribute=="1attribute")
        {

            if(!isParameter)
            {
                total_attribute++;

                Attribute *attribute=new Attribute;

                attribute->data_type=attribute_data_type;

                attribute->access_modifier=attribute_access_modifier;

                attribute->name=attribute_name;

                list_of_attribute.push_back(*attribute);

                top_for_attribute=token;
            }

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

string parameter_list="";

stack <string> stack_for_method_body;

string method_body="";

int current_state_for_method=0;

int method_line_number;

bool isStaticMethod=false;

bool isAbstractMethod=false;


struct Method{

    string access_modifier;

    string return_type;

    string name;

    string list_of_parameter;

    string body;

    bool isStaticMethod;

    bool isAbstractMethod;

    int line;

};

vector <Method> list_of_method;

void method_identifier(string token , int lineNumber)
{

    attributeIdentifier(token);

        if((token=="public" || token=="private" || token=="protected" || token=="static" || token=="abstract"
            || token=="int" || token=="float" || token=="double" || token=="char" || token=="String"
            || token=="void" || token=="boolean") && top_for_method=="")
        {

            method_line_number=lineNumber;

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
            method_line_number=lineNumber;

            top_for_method=token;

            if(token=="static")
            {
                isStaticMethod=true;
            }

            if(token=="abstract")
            {
                isAbstractMethod=true;
            }

            if(token=="int" || token=="float" || token=="double" || token=="char" || token=="String"
            || token=="void" || token=="boolean")

            {
                method_return_type=token;
            }
        }

        else if((token=="List" || token=="ArrayList" || token=="LinkedList" || token=="Set" || token=="HashSet"
                 || token=="LinkedHashSet" || token=="TreeSet" || token=="Map" || token=="HashMap"
                  || token=="LinkedHashMap" || token=="TreeMap" || token=="Vector" || token=="Stack"
                  || token=="Queue" || token=="Deque" || token=="PriorityQueue") && (top_for_method==""
                    || top_for_method=="public" || top_for_method=="private" || top_for_method=="protected"
                    || top_for_method=="static" || top_for_method=="final"))

        {
            top_for_method=token;

            method_return_type=token;
        }

        else if((top_for_method=="List" || top_for_method=="ArrayList" || top_for_method=="LinkedList"
                  || top_for_method=="Set" || top_for_method=="HashSet"
                 || top_for_method=="LinkedHashSet" || top_for_method=="TreeSet" || top_for_method=="Map"
                  || top_for_method=="HashMap" || top_for_method=="LinkedHashMap" || top_for_method=="TreeMap"
                || top_for_method=="Vector" || top_for_method=="Stack" || top_for_method=="Queue" ||
                 top_for_method=="Deque" || top_for_method=="PriorityQueue") && token=="<")

        {
            top_for_method=token;
        }

        else if((token=="Integer" || token=="String" || token=="Double" || token=="Character" || token=="Char"
                 || token=="Float" || token=="Object" || token=="") && top_for_method=="<")

        {
            top_for_method=token;
        }

        else if((top_for_method=="Integer" || top_for_method=="String" || top_for_method=="Double" ||
                  top_for_method=="Character" || top_for_method=="Char" || top_for_method=="Float" ||
                   top_for_method=="Object" || top_for_method=="") && token==">")

        {
            top_for_method=token;
        }

        else if((token=="int" || token=="float" || token=="double" || token=="char" || token=="String"
            || token=="void" || token=="boolean") && (top_for_method=="static" || top_for_method=="abstract"))

        {
            method_line_number=lineNumber;

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
                  || top_for_method=="void" || top_for_method=="boolean" || top_for_method=="]" || top_for_method=="public"
                  || top_for_method==">"))

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

            isParameter=true;

        }

        else if(top_for_method=="(")
        {

            if(token==")")
            {
                top_for_method=token;
                isParameter=false;
            }

            else
            {
                if(token=="/s")
                {
                    parameter_list+=" ";
                }

                else if(token=="/t")
                {
                    parameter_list+="\t";
                }

                else if(token=="/n")
                {
                    parameter_list+="\n";
                }

                if(token!="/s" && token!="/t" && token!="/n")
                {
                    parameter_list+=token;
                }

                isParameter=true;
            }

        }

        else if(top_for_method==")")
        {

            isParameter=false;

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

                method->isAbstractMethod=isAbstractMethod;

                method->isStaticMethod=isStaticMethod;

                method->line=method_line_number;

                list_of_method.push_back(*method);


                method_body="";

                parameter_list.clear();

                isParameter=false;

                top_for_method="";

                isStaticMethod=false;

                isAbstractMethod=false;
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

bool methodFound=false;

void printAllMethodInfo()
{
    vector <Method>::iterator itMethod;

    string token;
    int lineNumber;


    for(itMethod=list_of_method.begin();itMethod!=list_of_method.end();itMethod++)
    {
        cout<<"method name : "<<itMethod->name<<endl;

        cout<<"return type : "<<itMethod->return_type<<endl;

        cout<<"access modifier : "<<itMethod->access_modifier<<endl;

        cout<<"parameter list : ";

        if((itMethod->list_of_parameter)!="")
        {
            cout<<itMethod->list_of_parameter<<endl;
        }
        else
        {
            cout<<"no parameter contains"<<endl;
        }

        cout<<"declared in line : "<<itMethod->line<<endl;

        cout<<"called in lines : ";

        ifstream readFileOfTokens;

        readFileOfTokens.open("dipOut.txt");

        readFileOfTokens>>token;
        readFileOfTokens>>lineNumber;

        while(!readFileOfTokens.eof())
        {
            if(token==itMethod->name)
            {
                if(lineNumber!=itMethod->line)
                    cout<<lineNumber<<"  ";
            }

            readFileOfTokens>>token;
            readFileOfTokens>>lineNumber;
        }

        cout<<endl<<endl;

        methodFound=true;

        cout<<endl;
    }
}

bool abstractMethodFound=false;

bool staticMethodFound=false;

void searchAbstractMethod()
{
    vector <Method>::iterator itMethod;

    for(itMethod=list_of_method.begin();itMethod!=list_of_method.end();itMethod++)
    {
        if(itMethod->isAbstractMethod)
        {
            abstractMethodFound=true;

            cout<<"method name : "<<itMethod->name<<endl;
            cout<<"return type : "<<itMethod->return_type<<endl;
            cout<<"access modifier : "<<itMethod->access_modifier<<endl;
            cout<<"parameter list : ";

            if((itMethod->list_of_parameter)!="")
            {
                cout<<itMethod->list_of_parameter<<endl;
            }
            else
            {
                cout<<"no parameter contains"<<endl;
            }

            cout<<"declared in line : "<<itMethod->line<<endl<<endl;
        }
    }
}

void searchStaticMethod()
{
    vector <Method>::iterator itMethod;

    for(itMethod=list_of_method.begin();itMethod!=list_of_method.end();itMethod++)
    {
        if(itMethod->isStaticMethod)
        {
            staticMethodFound=true;

            cout<<"method name : "<<itMethod->name<<endl;
            cout<<"return type : "<<itMethod->return_type<<endl;
            cout<<"access modifier : "<<itMethod->access_modifier<<endl;
            cout<<"parameter list : ";

            if((itMethod->list_of_parameter)!="")
            {
                cout<<itMethod->list_of_parameter<<endl;
            }
            else
            {
                cout<<"no parameter contains"<<endl;
            }

            cout<<"declared in line : "<<itMethod->line<<endl;
        }
    }
}

int main(void)
{
    //remove("dipOut.txt");

    string filename;

    cout<<"Enter a file name : ";

    getline(cin,filename);

    iFile.open(filename.c_str());

    oFile.open("dipOut.txt");

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

    int lineNumber=1;

    if(iFile.is_open() && oFile.is_open())
    {
        iFile.get(my_character);

        while(!iFile.eof())
        {
            if(my_character=='\n')
            {
                lineNumber++;
            }

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
                        oFile<<token<<" "<<lineNumber<<endl;

                    token.clear();
                }

                char seperator[]={'\t','\n',' ',',',';','.','(',')','&','|','{','}','+','-','*','/','!','[',']','>','<','=','^'};

                for(int i=0;i<23;i++)
                {
                    if(my_character==seperator[i])
                    {

                        if(my_character==' ')
                            oFile<<"/s"<<" "<<lineNumber<<endl;

                        else if(my_character=='\n')
                            oFile<<"/n"<<" "<<lineNumber<<endl;

                        else if(my_character=='\t')
                            oFile<<"/t"<<" "<<lineNumber<<endl;

                        else
                            oFile<<my_character<<" "<<lineNumber<<endl;

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
    readFileOfTokens>>lineNumber;

    while(!readFileOfTokens.eof())
    {

        classIdentifier(token);

        method_identifier(token,lineNumber);

        readFileOfTokens>>token;

        readFileOfTokens>>lineNumber;

    }

    //Full class description

    cout<<endl<<"Class Name : "<<className<<endl;

    cout<<"Is it Interface? : ";

    if(is_Interface)
    {
        cout<<"Yes"<<endl;
    }

    else
        cout<<"No"<<endl;

    cout<<"Is it abstract? : ";

    if(isAbstract)
    {
        cout<<"Yes"<<endl;
    }

    else
        cout<<"No"<<endl;

    cout<<"SuperClass : ";

    if(superclass=="")
    {
        cout<<"Does not extend any super class"<<endl;
    }

    else
        cout<<superclass<<endl;

    cout<<"Implements : ";

    if(list_of_interface.empty())
    {
        cout<<"Does not implement any class"<<endl;
    }

    else
    {
        vector <string>::iterator itInterface;

        for(itInterface=list_of_interface.begin();itInterface!=list_of_interface.end();itInterface++)
            cout<<*itInterface<<"  ";

        cout<<endl;
    }

    //all method information
    cout<<endl<<"all methods"<<endl<<endl;
    printAllMethodInfo();

    if(!methodFound)
    {
        cout<<"no method found"<<endl;
    }

    cout<<endl<<"total method : "<<total_method<<endl<<endl;

    //search abstract method in the code
    cout<<"abstract methods"<<endl<<endl;
    searchAbstractMethod();
    cout<<endl;

    //search static method in the code
    cout<<"static methods"<<endl<<endl;
    searchStaticMethod();

    if(!abstractMethodFound)
    {
        cout<<"no abstract method found"<<endl;
    }

    if(!staticMethodFound)
    {
        cout<<"no static method found"<<endl;
    }

    cout<<endl<<"attribute name\tdata type\taccess modifier"<<endl;
    cout<<"--------------\t---------\t---------------"<<endl;

    vector <Attribute>::iterator itAttribute;

    for(itAttribute=list_of_attribute.begin();itAttribute!=list_of_attribute.end();itAttribute++)
    {
        cout<<itAttribute->name<<"\t\t"<<itAttribute->data_type<<"\t\t"<<itAttribute->access_modifier<<endl;
    }

    cout<<endl<<"total attribute : "<<total_attribute<<endl;

    return 0;

}

