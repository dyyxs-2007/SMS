#include<iostream>
#include<string>
#include<Windows.h>
#include<conio.h>
#include<vector>
#include<map>
#include<queue>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<ranges>
#include<fstream>
using namespace std;

string cinLineString(void);
void printOriginChoice(void);
void originLogin(void);
void registerAccount(void);
void studentLogin(void);
void cleanScreen(void);
void sleepClean(void);
void teacherLogin(void);
void studentOption(void);
bool existPassWordNode(int flag, string passWord);

struct AccountNode{//账号密码节点定义
    string ID;
    string passWord;
    AccountNode* next;
    AccountNode(string A, string B) : ID(A), passWord(B), next(NULL) {}
    AccountNode() : ID(""), passWord(""), next(NULL) {}
};
struct StudentsNode{//学生信息节点定义
    StudentsNode* next;
    StudentsNode* prev;
    string name;
    string score;
    string number;
    string clss;
    StudentsNode() : next(NULL), prev(NULL) {}
    StudentsNode(string s1, string s2, string s3, string s4) : next(NULL), prev(NULL), name(s1), score(s2), number(s3), clss(s4) {}
};

struct TeachersNode{//老师信息节点定义
    TeachersNode* next;
    string name;
    string number;
    string clss;
    TeachersNode() : next(NULL) {}
    TeachersNode(string s1, string s2, string s3) : next(NULL), name(s1), number(s2), clss(s3) {}
};

////////////
//链表全局头节点
StudentsNode* studentHead = new StudentsNode();//学生细节信息头节点
TeachersNode* teacherHead = new TeachersNode();//教师细节信息头节点
AccountNode* studentAccountHead = new AccountNode();//学生账号链表头节点
AccountNode* teacherAccountHead = new AccountNode();//教师账号链表头节点
AccountNode* AdminAccountHead = new AccountNode();//管理员账号链表头节点
////////////账号链表读取
void teacherNodeRead(void) {//老师细节信息节点读取
    ifstream ifs("C:\\Users\\dyyxs\\Desktop\\SMS\\date\\TeacherIP.bin",  ios::binary);
    if (!ifs) {
        cout << "打开文件失败" << endl;
        exit(1);
    }
    int multiple = 0;
    ifs.read((char *)&multiple, sizeof(int));
    if (multiple > 0) {
        for (int i = 0; i < multiple; i++) {
            int length;
            ifs.read((char*)&length, sizeof(int));
            string name(length, '\0');
            ifs.read((char*)&name[0], length);
            ifs.read((char*)&length, sizeof(int));
            string number(length, '\0');
            ifs.read((char*)&number[0], length);
            ifs.read((char*)&length, sizeof(int));
            string clss(length, '\0');
            ifs.read((char*)&clss[0], length);
            TeachersNode* temp = new TeachersNode(name, number, clss);
            TeachersNode* help = teacherHead;
            while (NULL != help->next) {
                help = help->next;
            }
            help->next = temp;
            if(!ifs) {
                cout << "读取文件失败" << endl;
                exit(1);
            }
        }
    }
    ifs.close();
}
void accountRead(int flag) {//所有账号节点读取
    string path;
    AccountNode* head = NULL;
    if (flag == 1) {//学生
        head = studentAccountHead;
        path = "C:\\Users\\dyyxs\\Desktop\\SMS\\date\\StudentDate.bin";
    } else if (flag == 0) {//老师
        head = teacherAccountHead;
        path = "C:\\Users\\dyyxs\\Desktop\\SMS\\date\\TeacherDate.bin";
    } else {//管理员
        head = AdminAccountHead;
        path = "C:\\Users\\dyyxs\\Desktop\\SMS\\date\\AdminDate.bin";
    }

    ifstream ifs(path, ios::binary);
    if (!ifs) {
        cout << "打开文件失败" << endl;
        exit(1);
    }
    int multiple;
    ifs.read((char*)&multiple, sizeof(int));
    if (multiple > 0) {
        for (int i = 0; i < multiple; i++) {
            int length;
            ifs.read((char*)&length, sizeof(int));
            string ID(length, '\0');
            ifs.read((char*)&ID[0], length);
            ifs.read((char*)&length, sizeof(int));
            string passWord(length, '\0');
            ifs.read((char*)&passWord[0], length);
            AccountNode* temp = new AccountNode(ID, passWord);
            AccountNode* seek = head;
            if (!ifs) {
                cout << "文件读取失败" << endl;
            }
            while (NULL != seek->next) {
                seek = seek->next;
            }
            seek->next = temp;
        }
    }
    ifs.close();
}
void studentNodeRead(void) {//学生细节信息节点读取
    ifstream ifs("C:\\Users\\dyyxs\\Desktop\\SMS\\date\\StudentIP.bin", ios::binary);
    if (!ifs) {
        cout << "打开文件失败" << endl;
        exit(1);
    }
    int multiple;
    StudentsNode* head = studentHead;
    StudentsNode* last = NULL;//防止访问到哨兵节点
    ifs.read((char*)&multiple, sizeof(int));
    if (multiple > 0) {
        for (int i = 0; i < multiple; i++) {
            int length;
            ifs.read((char*)&length, sizeof(int));
            string name(length, '\0');
            ifs.read((char*)&name[0], length);
            ifs.read((char*)&length, sizeof(int));
            string score(length, '\0');
            ifs.read((char*)&score[0], length);
            ifs.read((char*)&length, sizeof(int));
            string number(length, '\0');
            ifs.read((char*)&number[0], length);
            ifs.read((char*)&length, sizeof(int));
            string clss(length, '\0');
            ifs.read((char*)&clss[0], length);
            StudentsNode* temp = new StudentsNode(name, score, number, clss);
            temp->prev = last;
            if (NULL == last) {
                studentHead->next = temp;
            } else {
                last->next = temp;
            }
            last = temp;
            if (!ifs) {
                cout << "读取文件失败"  << endl;
            }
        }
    }
    ifs.close();
}
void allRead(void) {
    teacherNodeRead();//老师细节信息读取
    studentNodeRead();//学生细节信息读取
    accountRead(1);//1代表学生，0代表老师,2代表管理员
    accountRead(0);
    accountRead(2);
}

void sleepClean(void) {//延迟清屏函数
    Sleep(600);
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
        printf("3. 返回菜单界面\n");
        string answer = cinLineString();
        if (answer != "1" && answer != "2" && answer != "3") {
            cout << "请输入正确的序号！" << endl;
            sleepClean();
            continue;
        }
        if (answer == "3") {
            return;
        }
        cleanScreen();
        printf("请输入您的账号\n");
        string ID = cinLineString();
        printf("请输入您的密码\n");
        string passWord = cinLineString();
        if (ID == "" || passWord == "") {
            cout << "账号或密码不能为空，请重新输入" << endl;
            sleepClean();
            continue;
        }
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
void teacherOption(void) {
    printf("请输入选项序号以进行操作：\n");
    printf("1. 学生信息增删改查     2. 查看班内成绩\n");
    printf("3. 学生信息下载         4. 成绩分析\n");
    printf("5. 返回上一层\n");
}
void studentConfirm(void) {
    while (1) {
        printf("请输入您的学号:\n");
        string number = cinLineString();
        cleanScreen();
        bool flag = 0;
        StudentsNode* tempseek = studentHead->next;
        while (tempseek != NULL) {
            if (tempseek->number == number) {
                flag = 1;
                break;
            }
            tempseek = tempseek->next;
        }
        if (flag == 1) {
            studentOption();
            break;
        } else {
            printf("抱歉，您的学号未查询到，重新输入或退出？");
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
    }
}
void teacherConfirm(void) {
    while (1) {
        printf("请输入您的教师工号:\n");
        string number = cinLineString();
        cleanScreen();
        bool flag = 0;
        TeachersNode* tempseek = teacherHead->next;
        while (tempseek != NULL) {
            if (tempseek->number == number) {
                flag = 1;
                break;
            }
            tempseek = tempseek->next;
        }
        if (flag == 1) {
            teacherOption();
            break;
        } else {
            printf("抱歉，您的工号未查询到，重新输入或退出？");
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
    }
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
    cleanScreen();
    studentConfirm();
}
void teacherLogin(void) {
    while (1) {
        cleanScreen();
        cout << "请输入您的账号：" << endl;
        string ID = cinLineString();
        cleanScreen();
        if (!existAccountNode(2, ID)) {
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
        if (existPassWordNode(2, passWord)) {
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
    cleanScreen();
    teacherConfirm();
}
void adminOption(void) {
    cout << "成功登录，开发中" << endl;
    system("pause");
}
void adminLogin(void) {
    while (1) {
        printf("请输入您的管理员账号\n");
        string ID = cinLineString();
        printf("请输入您的管理员密码\n");
        string passWord = cinLineString();
        cleanScreen();
        AccountNode* temp = AdminAccountHead->next;
        int flag = 0;
        while (NULL != temp) {
            if (temp->ID == ID && temp->passWord == passWord) {
                flag = 1;
                break;
            }
            temp = temp->next;
        }
        if (0 == flag) {
            cout << "抱歉，您的账号或密码不正确，请输入序号进行操作:" << endl;
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
        } else {
            adminOption();
            break;
        }
    }
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
        adminLogin();
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
    allRead();
    while (1) {
        cleanScreen();
        printOriginChoice();
    }
}

int main() {
    
    string filename = "C:\\Users\\dyyxs\\Desktop\\SMS\\date\\AdminDate.bin";
    ofstream fls(filename, ios::trunc | ios::binary);
    int te1 = 1;
    fls.write((char *)&te1, sizeof(int));
    int length;
    string ID = "dyyxs";
    length = ID.size();
    fls.write((char*)&length, sizeof(int));
    fls.write((char*)&ID[0], ID.size());
    string passWord = "20070806";
    length = passWord.size();
    fls.write((char*)&length, sizeof(int));
    fls.write((char*)&passWord[0], passWord.size());
    fls.close();
    
    /*
    ifstream fls1(filename, ios::binary);
    int out;
    fls1.read((char *)&out, sizeof(int));
    cout << out << endl;
    fls1.close();
    */
    originLogin();//初始登入
    return 0;
}