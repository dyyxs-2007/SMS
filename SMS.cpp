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
void allAccountRead(void);
void accountRead(int flag, char* path);
void teacherLogin(void);
void studentOption(void);
bool existPassWordNode(int flag, string passWord);

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
StudentsNode* studentHead = new StudentsNode();//学生头节点
AccountNode* studentAccountHead = new AccountNode();//学生账号链表头节点
AccountNode* teacherAccountHead = new AccountNode();//教师账号链表头节点
////////////账号链表读取
void allAccountRead(void) {
    accountRead(1, "StudentStorage.bin");
    accountRead(0, "TeacherStorage.bin");
}
void accountRead(int flag, char* path) {
    AccountNode* head;
    if (flag == 1) {
        head = studentAccountHead;
    } else {
        head = teacherAccountHead;
    }
    FILE *accountReadPtr = fopen(path, "rb");
    if (accountReadPtr == NULL) {
        cout << "文件读取失败" << endl;
        exit(1);
    }
    int multiple = -2;
    fread(&multiple, sizeof(int), 1, accountReadPtr);
    if (EOF != multiple) {
        while (multiple--) {
            int accountIDSize;
            fread(&accountIDSize, sizeof(int), 1, accountReadPtr);
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
            AccountNode* temp = head;
            while (NULL != temp->next) {
                temp = temp->next;
            }
            temp->next = storageAccount;
        }
    }
    fclose(accountReadPtr);
}

void sleepClean(void) {//延迟清屏函数
    Sleep(700);
    system("cls");
}
string cinLineString(void) {//读入整行函数
    string lineAnswer;
    getline(cin, lineAnswer);
    return lineAnswer;
}

void cleanScreen(void) {//清屏函数
    system("cls");
}
void addAccountNode(int flag, string ID, string passWord) {
    AccountNode* head = NULL;
    if (1 == flag) {
        head = studentAccountHead;
    } else {
        head = teacherAccountHead;
    }
    AccountNode* temp = new AccountNode(ID, passWord);
    while (head->next != NULL) {
        head = head->next;
    }
    head->next = temp;
}
bool existAccountNode(int flag, string ID) {
    AccountNode* head = NULL;
    if (1 == flag) {
        head = studentAccountHead->next;
    } else {
        head = teacherAccountHead->next;
    }
    while (head != NULL) {
        if (head->ID == ID) {
            return true;
        }
        head = head->next;
    }
    return false;
}
bool existPassWordNode(int flag, string passWord) {
    AccountNode* head = NULL;
    if (1 == flag) {
        head = studentAccountHead->next;
    } else {
        head = teacherAccountHead->next;
    }
    while (head != NULL) {
        if (head->passWord == passWord) {
            return true;
        }
        head = head->next;
    }
    return false;
}
void registerAccount(void) {//1
    while (1) {
        cleanScreen();
        printf("请输入注册账号的类型：\n");
        printf("1. 学生账号\n2. 教师账号\n");
        string answer = cinLineString();
        if (answer != "1" && answer != "2") {
            cout << "请输入正确的序号！" << endl;
            sleepClean();
            continue;
        }
        cleanScreen();
        printf("请输入您的账号\n");
        string ID = cinLineString();
        printf("请输入您的密码\n");
        string passWord = cinLineString();
        if (answer == "1") {
            if (existAccountNode(1, ID)) {
                cout << "抱歉，您输入的账户已被注册" << endl;
                sleepClean();
                continue;
            }
            addAccountNode(1, ID, passWord);
            cout << "注册成功！" << endl;
            break;
        } else {
            if (existAccountNode(2, ID)) {
                cout << "抱歉，您输入的账户已被注册" << endl;
                sleepClean();
                continue;
            }
            addAccountNode(2, ID, passWord);
            cout << "注册成功！" << endl;
            break;
        }
    }
    sleepClean();
}

void studentOption(void) {
    cout << "开发中" << endl;
    sleepClean();
}
void studentLogin(void) {//2
    while (1) {
        cleanScreen();
        cout << "请输入您的账号：" << endl;
        string ID = cinLineString();
        cleanScreen();
        if (!existAccountNode(1, ID)) {
            cout << "抱歉，您的账号不存在，请输入序号进行操作:" << endl;
            cout << endl;
            printf("1. 返回主菜单      其他. 重新输入\n");
            cout << endl;
            cout << "（注：“其他”指的是除了“1”以外的其他输入）" << endl;
            string answer = cinLineString();
            cleanScreen();
                if (answer == "1") {
                    return;
                } else {
                    continue;
                }
        }
        cout << "请输入您的密码：" << endl;
        string passWord = cinLineString();
        cleanScreen();
        if (existPassWordNode(1, passWord)) {
            break;
        } else {
            cout << "密码错误，请输入序号进行操作：" << endl;
            cout << endl;
            printf("1. 返回主菜单      其他. 重新输入账号及密码\n");
            cout << endl;
            cout << "（注：“其他”指的是除了“1”以外的其他输入）" << endl;
            string answer = cinLineString();
            if (answer == "1") {
                return;
            } else {
                continue;
            }
        }
    }
    studentOption();
}
void teacherLogin(void) {

}
void printOriginChoice(void) {//初始界面
    printf("       学生管理系统\n");
    printf("-----------****-----------\n");
    printf("1.注册账号     2.学生登陆\n");
    printf("3.教师登陆     4.管理员登陆\n");
    printf("5.账号修改     6.密码找回\n");
    printf("7.保存信息并退出系统\n");
    printf("-----------****-----------\n");
    cout << "请输入执行的操作" << endl;
    string firstChoice = cinLineString();
    cleanScreen();
    if ("1" == firstChoice) {
        registerAccount();
    } else if ("2" == firstChoice) {
        studentLogin();
    } else if ("3" == firstChoice) {
        teacherLogin();
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
void originLogin(void) {//初始登入界面
    allAccountRead();
    while (1) {
        printOriginChoice();
    }
}

int main() {
    /*
    FILE *test = fopen("TeacherStorage.bin", "wb");
    int a = 0;
    fwrite(&a, sizeof(int), 1, test);
    fclose(test);
    */
    originLogin();//初始登入
    return 0;
}