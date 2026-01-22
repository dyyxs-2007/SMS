#include<iostream>
#include<string>
#include<Windows.h>
#include<conio.h>
#include<vector>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<queue>
#include<deque>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<ranges>
#define INPUT_MAX_SIZE 20
using namespace std;

string cinLineString(void);
void printOriginChoice(void);
void originLogin(void);
void registerAccount(void);
void studentLogin(void);
void cleanScreen(void);
void sleepClean(void);
void accountRead(void);

struct AccountNode{
    string ID;
    string passWord;
    AccountNode* next;
    AccountNode(string A, string B) : ID(A), passWord(B), next(NULL) {}
    AccountNode() : ID(""), passWord(""), next(NULL) {}
};
struct StudentsNode{//学生链表节点定义
    StudentsNode* next;
    StudentsNode() : next(NULL) {}
};

////////////
//链表全局头节点
StudentsNode *studentHead = NULL;//学生头节点
AccountNode *AccountHead = NULL;//账号链表头节点
////////////账号链表读取

void accountRead(void) {
    FILE *accountReadPtr = fopen("AccountSave.bin", "rb");
    if (accountReadPtr == NULL) {
        cout << "打开文件失败" << endl;
        exit(1);
    }
    int multiple = -2;
    fread(&multiple, sizeof(int), 1, accountReadPtr);
    if (EOF != multiple) {
        while (multiple--) {
            int accountIDSize;
            size_t check = fread(&accountIDSize, sizeof(int), 1, accountReadPtr);
            string tempAccountID = "";//账号读出
            for (int i = 0; i < accountIDSize; i++) {
                char tempToRead;
                fread(&tempToRead, sizeof(char), 1, accountReadPtr);
                    tempAccountID += tempToRead;
            }

            string tempAccountPassWord = "";//密码读出
            int accountPassWordSize;
            fread(&accountPassWordSize, sizeof(int), 1, accountReadPtr);
            for (int i = 0; i < accountPassWordSize; i++) {
                char tempToRead;
                fread(&tempToRead, sizeof(char), 1, accountReadPtr);
                    tempAccountPassWord += tempToRead;
            }

            AccountNode* storageAccount = new AccountNode(tempAccountID, tempAccountPassWord);
            AccountNode* temp = AccountHead;
            while (NULL != temp->next) {
                temp = temp->next;
            }
            temp->next = storageAccount;
        }
    }
    fclose(accountReadPtr);
}

void sleepClean(void){//延迟清屏函数
    Sleep(700);
    system("cls");
}
string cinLineString(void){//读入整行函数
    string lineAnswer = "";
    getline(cin, lineAnswer);
    return lineAnswer;
}

void cleanScreen(void){//清屏函数
    system("cls");
}

void registerAccount(void){//1
    
}

void studentLogin(void){//2

}

void printOriginChoice(void){//初始界面
    printf("       学生管理系统\n");
    printf("-----------****-----------\n");
    printf("1.注册账号     2.学生登陆\n");
    printf("3.教师登陆     4.管理员登陆\n");
    printf("5.账号修改     6.密码找回\n");
    printf("7.退出系统\n");
    printf("-----------****-----------\n");
    cout << "请输入执行的操作" << endl;
    string firstChoice = cinLineString();
    cleanScreen();
    if ("1" == firstChoice) {
        registerAccount();
    } else if ("2" == firstChoice) {
        studentLogin();
    } else if ("3" == firstChoice) {

    } else if ("4" == firstChoice) {

    } else if ("5" == firstChoice) {

    } else if ("6" == firstChoice) {

    } else if ("7" == firstChoice) {

        cout << "感谢使用学生管理系统" << endl;
        exit(0);
    } else {
        cout << "请输入正确的操作序号！" << endl;
        sleepClean();
    }
}
void originLogin(void){//初始登入界面
    accountRead();
    while (1) {
        printOriginChoice();
    }
}

int main(){
    /*
    FILE *test = fopen("AccountSave.bin", "wb");
    int a = 0;
    fwrite(&a, sizeof(int), 1, test);
    fclose(test);*/

    originLogin();//初始登入
    return 0;
}