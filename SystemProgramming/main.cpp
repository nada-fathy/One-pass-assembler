#include <iostream>
#include <fstream>
#include <iterator>
#include <map>
#include "operations.h"
#include <vector>
using namespace std;

struct preobj
{
     string Label;
     string Operator;
     string Operand;
     string Opcode;
     int Format;

};


class pass1{
    private:
    map<string, int> format;
    map<string, string> opcode;
    public:
    pass1(){
        format = getformat();
        opcode = getopcode();
    }
    void handleLine(string line){
        vector<string> data = noSpace(line);
        struct preobj info = extract(data);
        cout<<info.Format<<"\n";
        cout<<info.Label<<"\n";
        cout<<info.Operand<<"\n";
        cout<<info.Operator<<"\n";
        cout<<info.Opcode<<"\n";
    }
    void readFile(string filename){
        ifstream myfile;
        myfile.open (filename.c_str());
        string line;
        while (getline(myfile, line))
            handleLine(line);
        myfile.close();
    }

    struct preobj extract (vector<string> data){
        struct preobj info;
        string Label, Operator, Operand, Opcode;
        int Format;
        if(data.size()==3){
            Label = data.at(0);
            Operator = data.at(1);
            Operand = data.at(2);
        }
        else if(data.size()==2){
            Label = "";
            Operator = data.at(0);
            Operand = data.at(2);
        }
        string Operator2 = Operator;
        if(Operator2[0] == '+')
            Operator2.erase(0,1);
        if(format.find(Operator2) == format.end())//Wrong Operator
            Operator = "";
        else{
            Format = format.at(Operator2);
            if(Format == 3){
                if(Operator[0]=='+')
                    Format = 4;
            }
            Opcode = opcode.at(Operator2);
        }
        info.Format = Format;
        info.Label = Label;
        info.Opcode = Opcode;
        info.Operand = Operand;
        info.Operator = Operator;
        return info;
    }
};


int main()
{
    pass1 e;
    e.readFile("assembler.txt");
    return 0;
}





