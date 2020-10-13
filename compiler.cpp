#include <iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<cstring>
using namespace std;
string keep[6] = {"BEGIN", "END", "FOR", "IF", "THEN", "ELSE"};

int keepNum[6]={1,2,3,4,5,6};
string symbols[11] = {"+","-","*","/","(",")",",",";",":",":=","="};
int symbolsNum[11]= {7,8,9,10,11,12,13,14,15,16,17};

enum identify
{
    Begin,
    End,
    For,
    If,
    Then,
    Else,
    Ident,    //标识符
    Int,
    Colon,
    Plus,
    //Minus,
    Star,
   // Divi,
    Comma,
    LParenthesis,
    RParenthesis,
    Semi,
    Assign,
    Unknown,
    Note
}symbol;

int num;
char token[106]; 
int length; //length of token

int pointer=0; //a pointer
char reading[1000];//input this
char read;
void readChar(){
    //pointer++;
    read = reading[pointer];            //先读后移动指针
    pointer++;
}
void clearToken(){  //清空token字符数组
    memset(token,'\0',sizeof(token));
}

bool isSpace(char s){            // 1. 是否是string类型 2. “\n” 还是 ‘\n’ 
	if(s == ' ')
		return true;
	else
		return false;
}

bool isNewline(char s){
	if(s == '\n'||s=='\r')
		return true;
	else
		return false;
}

bool isTab(char s){
	if(s == '\t')
		return true;
	else
		return false;
}


bool isLetter(char s){
	if((s >='a' && s <= 'z')||(s >='A' && s <= 'Z'))
		return true;
	else
		return false;
}

bool isDigit(char s){
	if(s >='0' && s <= '9')
		return true;
	else
		return false;
}

bool isColon(char s){ // :
	if(s == ':')
		return true;
	else
		return false;
}

bool isComma(char s){ // ,
	if(s == ',')
		return true;
	else
		return false;
}

bool isSemi(char s){ // ;
	if(s == ';')
		return true;
	else
		return false;
}

bool isEqu(char s){ // =
	if(s == '=')
		return true;
	else
		return false;
}

bool isPlus(char s){ // +
	if(s == '+')
		return true;
	else
		return false;
}

// bool isMinus(char s){ // -
// 	if(s == '-')
// 		return true;
// 	else
// 		return false;
// }

bool isDivi(char s){ // /
	if(s == '/')
		return true;
	else
		return false;
}

bool isStar(char s){ // *
	if(s == '*')
		return true;
	else
		return false;
}

bool isLpar(char s){ // (
	if(s == '(')
		return true;
	else
		return false;
}

bool isRpar(char s){ // )
	if(s == ')')
		return true;
	else
		return false;
}

void catToken(){ // 连接字符串
    strcat(token,&read);
}

void retract(){             //读字符指针后退
    pointer--;
}

int reserver(char* s){            //查找保留字 "BEGIN", "END", "FOR", "IF", "THEN", "ELSE"
    
        if(strcmp(s,"BEGIN")==0)
            return 0;
        else if(strcmp(s,"END")==0)
            return 1;
        else if(strcmp(s,"FOR")==0)
            return 2;
        else if(strcmp(s,"IF")==0)
            return 3;
        else if(strcmp(s,"THEN")==0)
            return 4;
        else if(strcmp(s,"ELSE")==0)
            return 5;
        else
            return -1;
    
}

int transNum(){
    return atoi(token);
}

void error(){
    symbol = Unknown;
}

int getsym(){
    clearToken();

    readChar();
    //char c = read;

    while(isSpace(read) || isNewline(read) || isTab(read))
        readChar();

    if(isLetter(read)){            //是不是字母
        while(isLetter(read) || isDigit(read)){
            catToken();
            readChar();
        }
        retract();

        int resultValue = reserver(token);
        if(resultValue == -1)
            symbol = Ident;
        else
            symbol = (enum identify)resultValue;
    }
    else if(isDigit(read)){
        while(isDigit(read)){
            catToken();
            readChar();
        }
        retract();
        num = transNum();
        symbol = Int;
    }
    else if(isColon(read)){
        readChar();
        if(isEqu(read))
            symbol = Assign;        //赋值符号
        else
            retract();
        symbol = Colon;
    }
    else if(isPlus(read)){
        symbol = Plus;
    }
    // else if(isMinus(read)){
    //     symbol = Minus;
    // }
    else if(isStar(read)){
        symbol = Star;
    }
    else if(isLpar(read)){
        symbol = LParenthesis;
    }
    else if(isRpar(read)){
        symbol = RParenthesis;
    }
    else if(isComma(read))
        symbol = Comma;
    else if(isSemi(read)){
        symbol = Semi;
    }
    else if(isDivi(read)){
        readChar();
        if(isStar(read)){
            do{
                do{
                    readChar();
                } while (!isStar(read));
                do{
                    readChar();
                    if(isDivi(read)){
                        symbol = Note;
                        return 0;
                    }
                        
                } while (isStar(read));
            } while (!isStar(read));
        }
        retract();
        //symbol = Divi;
        symbol = Unknown;
    }
    else
        error();      //程序不继续分析
    return 0;
}

void printsym(){
    switch(symbol){
        case Begin:{
            printf("Begin \n");
            break;
        }
        case End:{
            printf("End \n");
            break;
        }
        case For:{
            printf("For \n");
            break;
        }
        case If:{
            printf("If \n");
            break;
        }
        case Then:{
            printf("Then \n");
            break;
        }
        case Else:{
            printf("Else \n");
            break;
        }
        case Ident:{ //标识符
            printf("Ident(%s)\n", token);
            //cout << "Ident(" << token << ")" << endl;
            break;
        }   
        case Int:{
            printf("Int(%d)\n", num);
            //cout << "Int(" << num << ")" << endl;
            break;
        }
        case Colon:{
            printf("Colon \n");
            break;
        }
        case Plus:{
            printf("Plus \n");
            break;
        }
        // case Minus:{
        //     printf("Minus \n");
        //     break;
        // }
        case Star:{
            printf("Star \n");
            break;
        }
        // case Divi:{
        //     printf("Divi \n");
        //     break;
        // }
        case Comma:{
            printf("Comma \n");
            break;
        }
        case LParenthesis:{
            printf("LParenthesis\n");
            break;
        }
        case RParenthesis:{
            printf("RParenthesis\n");
            break;
        }
        case Semi:{
            printf("Semi \n");
            break;
        }
        case Assign:{
            printf("Assign \n");
            break;
        }
        case Unknown:{
            printf("Unknown \n");
            break;
        }
        case Note:{
            break;
        }
            
        //default:break;
        default:{
            printf("Unknown \n");
            break;
        }
    }
}

void compiler(){
    //for (int i = 0; /*i < length*/ reading[i] != '\0';)//???????????
    while(reading[pointer] != '\0'){
        //read = reading[i++];
        getsym();
        printsym();
        //i = pointer;

        if(symbol == Unknown){
            //printf(" wrong word\n");
            break;
        }
    }
}

int main(int argc,char *argv[]){
    char w;
    //int i, j;
    FILE *input = fopen(argv[1]/*"s.txt"*/, "rb");
    // freopen("s.txt","r",stdin);
    // freopen("result.txt","w",stdout); //从控制台输出，而不是文本输出

    length=0;
    fread(reading, sizeof(char), 10000, input);
    //length = ?
    // w = fgetc(input);
    // while(/*cin.get(w)*/w!=EOF){ 
    //     //if(w!=' '){
    //         reading[length]=w;
    //         length++;
    //         w = fgetc(input);
    //     //}     
    // }
    //g++ -o compiler compiler.cpp
    compiler(); //读文件

    fclose(input);
    // fclose(stdin);//关闭文件 
    // fclose(stdout);//关闭文件 
    return 0;
}