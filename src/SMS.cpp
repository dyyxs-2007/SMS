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
#define MAX_SCORE 150
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

bool judge(void) {
    cout << "确认您做出的操作吗？" << endl;
    cout << "1. 确认   其他. 取消" << endl;
    string answer = cinLineString();
    if (answer == "1") {
        return true;
    } else {
        return false;
    }
}
bool scoreVerify(string score) {
    for (int i = 0; i < score.size(); i++) {
        if (score[i] > '9' || score[i] < '0') {
            return false;
        }
    }
    int num = 0;
    for (int i = 0; i < score.size(); i++) {
        num = num * 10 + (score[i] - '0');
    }
    if (num > MAX_SCORE || num < 0) {
        return false;
    } else {
        return true;
    }
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
//排序
StudentsNode* merge(StudentsNode*s1, StudentsNode* s2, StudentsNode* last) {
    if (NULL == s1 && NULL == s2) {
        return NULL;
    } else if (NULL == s1 && NULL != s2) {
        s2->prev = last;
        return s2;
    } else if (NULL != s1 && NULL == s2) {
        s1->prev = last;
        return s1;
    } else {
        if (stoi(s1->score) < stoi(s2->score)) {
            s2->prev = last;
            s2->next = merge(s1, s2->next, s2);
            return s2;
        } else {
            s1->prev = last;
            s1->next = merge(s1->next, s2, s1);
            return s1;
        }
    }
}
StudentsNode* mergeSort(StudentsNode* ori) {
    if (ori == NULL) {
        return NULL;
    } else if (NULL == ori->next) {
        return ori;
    }
    StudentsNode* left = ori;
    StudentsNode* right = ori;
    while (right->next != NULL && right->next->next != NULL) {
        right = right->next->next;
        left = left->next;
    }
    StudentsNode* temp = left->next;
    temp->prev = NULL;
    left->next = NULL;
    StudentsNode* begin1 = mergeSort(ori);
    StudentsNode* begin2 = mergeSort(temp);
    return merge(begin1, begin2, NULL);
}
//
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
bool existAccountNode(int flag, string ID) {//1学生2老师
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
bool existStudentNode(string number) {
    StudentsNode* temp = studentHead->next;
    while (temp) {
        if (temp->number == number) {
            return true;
        }
        temp = temp->next;
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
void downloadStudent(void) {
    string filename = "\\StudentScore.txt";
    while (1) {
        cleanScreen();
        printf("请输入您要下载的文件夹路径(如: C:\\test\\student.bin)：\n");
        printf("(注: 该操作会清除原文件所有内容, 单击Enter以退出)\n");
        string path = cinLineString();
        if ("" == path) {
            return;
        } else if (path.size() > 250) {
            cout << "路径长度太长！请重新输入" << endl;
            continue;
        }
        path += filename;
        ofstream testFile(path);
        if (!testFile.is_open()) {
            cout << "抱歉，该路径下文件夹不存在或无打开权限" << endl;
            cout << "请先正确创建文件夹再下载" << endl;
            cout << endl;
            system("pause");
            continue;
        }
        testFile.close();
        ofstream ofs(path, ios::trunc);
        StudentsNode* current = studentHead->next;
        while (NULL != current) {
            ofs << current->name << "   " << current->score << "分    "<< current->clss << "班    学号" << current->number << endl;;
            current = current->next;
        }
        ofs.close();
        cout << "已成功下载" << endl;
        sleepClean();
        break;
    }
}

StudentsNode* findStudentIP(void) {
    cleanScreen();
    cout << "请选择根据名字或学号操作" << endl;
    cout << "1. 名字         2. 学号" << endl;
    cout << "3. 返回" << endl;
    string answer = cinLineString();
    cleanScreen();
    if ("1" == answer) {
        cout << "请输入名字" << endl;
        string target = cinLineString();
        StudentsNode* tempNode = studentHead;
        while (NULL != tempNode->next) {
            if (target == tempNode->next->name) {
                return tempNode;
            }
            tempNode = tempNode->next;
        }
        cout << "抱歉，该生信息未查询到，可能是输入错误或者信息尚未录入!" << endl;
        system("pause");
        return NULL;
    } else if ("2" == answer) {
        cout << "请输入学号" << endl;
        string target = cinLineString();
        StudentsNode* tempNode = studentHead;
        while (NULL != tempNode->next) {
            if (target == tempNode->next->number) {
                return tempNode;
            }
            tempNode = tempNode->next;
        }
        cout << "抱歉，该生信息未查询到，可能是输入错误或者信息尚未录入!" << endl;
        system("pause");
        return NULL;
    } else if (answer == "3") {
        return NULL;
    } else {
        cout << "请输入正确的操作序号！" << endl;
        sleepClean();
        return findStudentIP();
    }
}
void showStudent(void) {
    StudentsNode* current = studentHead->next;
    if (NULL == current) {
        cout << "暂时还没有学生信息，请增添" << endl;
    }
    int count = 1;
    while (NULL != current) {
        printf("%d-------------------------------\n", count);
        cout << "姓名：" << current->name << endl;
        cout << "班级：" << current->clss << endl;
        cout << "成绩：" << current->score << endl;
        cout << "学号：" << current->number << endl;
        cout << endl;
        count++;
        current = current->next;
    }
    system("pause");
}
void showScore(string clss) {
    StudentsNode* current = studentHead->next;
    int bad = 0;
    int middle = 0;
    int good = 0;
    int count = 0;
    double sum = 0;
    while (current != NULL) {
        if (clss != "Admin" && current->clss != clss) {
            current = current->next;
            continue;
        }
        count++;
        printf("第%d名  ", count);
        cout << current->name << "    " << current->score << "分" << endl;
        int score = stoi(current->score);
        sum += score;
        if (score < 90) {
            bad++;
        } else if (score >= 90 && score < 120) {
            middle++;
        } else {
            good++;
        }
        current = current->next;
    }
    double even = sum / count;
    cout << endl;
    printf("本次统计共有%d名学生\n", count);
    cout << endl;
    printf("其中，达到优秀(120分及以上)的有%d人\n", good);
    cout << endl;
    printf("达到及格(90分及以上120分以下)的有%d人\n", middle);
    cout << endl;
    printf("不及格(90分以下)的有%d人\n", bad);
    cout << endl;
    printf("平均分为%lf\n",even);
    system("pause");
}
void studentIPOption(void) {
    while (1) {
        cleanScreen();
        printf("            请输入选项序号以进行操作：\n");
        printf("---------------------------------------------------\n");
        printf("1. 新增学生信息             2. 删除学生信息\n");
        printf("3. 修改学生信息             4. 查找学生信息\n");
        printf("5. 学生信息展示             6. 返回上一层\n");
        printf("---------------------------------------------------\n");
        string answer = cinLineString();
        cleanScreen();
        if (answer == "1") {
            cout << "请输入该学生姓名" << endl;
            string name = cinLineString();
            cout << "请输入该学生分数" << endl;
            string score = cinLineString();
            if (!scoreVerify(score)) {
                cleanScreen();
                cout << "抱歉，您输入的分数并不合法，请输入0~150区间内的数字" << endl;
                system("pause");
                continue;
            }
            cout << "请输入该学生学号" << endl;
            string number = cinLineString();
            if (existStudentNode(number)) {
                cleanScreen();
                cout << "抱歉，该学号已存在" <<endl;
                system("pause");
                cleanScreen();
                continue;
            }
            cout << "请输入该学生所在班级" << endl;
            string clss = cinLineString();
            if (!judge()) {
                cleanScreen();
                cout << "好的，您的请求已取消" << endl;
                sleepClean();
                continue;
            }
            StudentsNode* temp = new StudentsNode(name, score, number, clss);
            StudentsNode* seek = studentHead;
            if (NULL == studentHead->next) {
                studentHead->next = temp;
            } else {
                while (NULL != seek->next) {
                    seek = seek->next;
                }
                seek->next = temp;
                temp->prev = seek;
            }
            cleanScreen();
            cout << "添加成功" << endl;
            sleepClean();
        } else if (answer == "2") {
            StudentsNode* target = findStudentIP();
            if (NULL == target) {
                continue;
            }
            if (!judge()) {
                cleanScreen();
                cout << "好的，您的请求已取消" << endl;
                sleepClean();
                continue;
            }
            if (NULL != target) {
                StudentsNode* helpNode = target->next;
                target->next = target->next->next;
                //这里要处理next可能是空的bug
                if (NULL != target->next) {
                    target->next->prev = target;
                }
                delete(helpNode);
                cout << "已成功删除!" << endl;
                sleepClean();
            }
        } else if (answer == "3") {
            StudentsNode* target = findStudentIP();
            if (NULL == target) {
                continue;
            }
            string* ptrTarget;
            while (1) {
                cleanScreen();
                cout << "请问修改什么信息?" <<endl;
                cout << "1. 姓名    2. 班级" << endl;
                cout << "3. 学号    4. 分数" << endl;
                cout << endl;
                string modifyO = cinLineString();
                if (modifyO == "1") {
                    ptrTarget = &(target->next->name);
                    break;
                } else if (modifyO == "2") {
                    ptrTarget = &(target->next->clss);
                    break;
                } else if (modifyO == "3") {
                    ptrTarget = &(target->next->number);
                    break;
                } else if (modifyO == "4") {
                    ptrTarget = &(target->next->score);
                    break;
                } else {
                    cout << "请输入正确的操作序号！" << endl;
                    sleepClean();
                    continue;
                }
            }
            cout << endl;
            cout << "请输入修改后的结果" << endl;
            string modifyA = cinLineString();
            cleanScreen();
            if (!judge()) {
                cleanScreen();
                cout << "好的，您的请求已取消" << endl;
                sleepClean();
                continue;
            }
            *ptrTarget = modifyA;
            cout << "已修改" << endl;
            sleepClean();
        } else if (answer == "4") {
            StudentsNode* target = findStudentIP();
            if (NULL == target) {
                continue;
            }
            StudentsNode* current = target->next;
            cout << "--------------------------------" << endl;
            cout << "姓名：" << current->name << endl;
            cout << "班级：" << current->clss << endl;
            cout << "成绩：" << current->score << endl;
            cout << "学号：" << current->number << endl;
            cout << "--------------------------------" << endl;
            system("pause");
        } else if (answer == "5") {
            showStudent();
        } else if (answer == "6") {
            return;
        } else {
            cout << "请输入正确的操作序号！" << endl;
            sleepClean();
        }
        cleanScreen();
    }
}

void studentOption(void) {
    cout << "开发中" << endl;
    sleepClean();
}
void teacherOption(string clss) {
    while (1) {
        cleanScreen();
        printf("            请输入选项序号以进行操作：\n");
        printf("---------------------------------------------------\n");
        printf("1. 学生信息增删改查     2. 查看班内成绩与成绩分析\n");
        printf("3. 学生信息下载         4. 返回上一层\n");
        printf("---------------------------------------------------\n");
        string answer = cinLineString();
        cleanScreen();
        if (answer == "1") {
            studentIPOption();
        } else if (answer == "2") {
            studentHead->next = mergeSort(studentHead->next);
            showScore(clss);
        } else if (answer == "3") {
            downloadStudent();
        } else if (answer == "4") {
            break;
        } else {
            cout << "请输入正确的操作序号！" << endl;
            sleepClean();
        }
        cleanScreen();
    }
}
void adminOption(void) {
    while (1) {
        cleanScreen();
        printf("            请输入选项序号以进行操作：\n");
        printf("---------------------------------------------------\n");
        printf("1. 账号密码增删改查           2. 增删改查学生信息\n");
        printf("3. 增删改查教师信息           4. 从文件录入所有账号密码\n");
        printf("5. 从文件导出所有账号密码     6. 登陆至教师操作页面\n");
        printf("7. 查看代办                  8. 返回上一层\n");
        printf("---------------------------------------------------\n");
        string answer = cinLineString();
        if (answer == "1") {

        } else if (answer == "2") {
            studentIPOption();
        } else if (answer == "3") {
            
        } else if (answer == "4") {
            
        } else if (answer == "5") {
            
        } else if (answer == "6") {
            teacherOption("Admin");
        } else if (answer == "7") {
            
        } else if (answer == "8") {
            break;
        } else {
        cout << "请输入正确的操作序号！" << endl;
        sleepClean();
        }
        cleanScreen();
    }
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
            teacherOption(tempseek->clss);
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
void dateStorage(int x) {//0管理员1学生2老师
    string path;
    AccountNode* head;
    if (x == 0) {
        path = "C:\\Users\\dyyxs\\Desktop\\SMS\\date\\AdminDate.bin";
        head = AdminAccountHead;
    } else if (x == 1) {
        path = "C:\\Users\\dyyxs\\Desktop\\SMS\\date\\StudentDate.bin";
        head = studentAccountHead;
    } else {
        path = "C:\\Users\\dyyxs\\Desktop\\SMS\\date\\TeacherDate.bin";
        head = teacherAccountHead;
    }
    ofstream ofs(path, ios::trunc | ios::binary);
    if (!ofs) {
        cout << "打开文件失败" << endl;
        exit(1);
    }
    int length = 0;
    AccountNode* count = head->next;
    while (count) {
        length++;
        count = count->next;
    }
    ofs.write((char*)&length, sizeof(int));
    for (int i = 0; i < length; i++) {
        head = head->next;
        string ID = head->ID;
        int size = ID.size();
        ofs.write((char*)&size, sizeof(int));
        ofs.write((char*)&ID[0], ID.size());
        string passWord = head->passWord;
        size = passWord.size();
        ofs.write((char*)&size, sizeof(int));
        ofs.write((char*)&passWord[0], passWord.size());
    }

    ofs.close();
}
void studentIPStorage(void) {
    ofstream ofs("C:\\Users\\dyyxs\\Desktop\\SMS\\date\\StudentIP.bin", ios::trunc | ios::binary);
    if (!ofs) {
        cout << "存储失败" << endl;
        exit(1);
    }
    StudentsNode* count = studentHead->next;
    StudentsNode* current = studentHead;
    int length = 0;
    while (NULL != count) {
        length++;
        count = count->next;
    }
    ofs.write((char*)&length, sizeof(int));
    for (int i = 0; i < length; i++) {
        current = current->next;

        string name = current->name;
        int size = name.size();
        ofs.write((char*)&size, sizeof(int));
        ofs.write((char*)&name[0], size);
        
        string score = current->score;
        size = score.size();
        ofs.write((char*)&size, sizeof(int));
        ofs.write((char*)&score[0], size);

        string number = current->number;
        size = number.size();
        ofs.write((char*)&size, sizeof(int));
        ofs.write((char*)&number[0], size);
        
        string clss = current->clss;
        size = clss.size();
        ofs.write((char*)&size, sizeof(int));
        ofs.write((char*)&clss[0], size);
    }
    ofs.close();
}
void teacherIPStorage(void) {
    ofstream ofs("C:\\Users\\dyyxs\\Desktop\\SMS\\date\\TeacherIP.bin", ios::trunc | ios::binary);
    if (!ofs) {
        cout << "存储失败" << endl;
        exit(1);
    }
    TeachersNode* count = teacherHead->next;
    TeachersNode* current = teacherHead;
    int length = 0;
    while (NULL != count) {
        length++;
        count = count->next;
    }
    ofs.write((char*)&length, sizeof(int));
    for (int i = 0; i < length; i++) {
        current = current->next;
        string name = current->name;
        int size = name.size();
        ofs.write((char*)&size, sizeof(int));
        ofs.write((char*)&name[0], size);
        string number = current->number;
        size = number.size();
        ofs.write((char*)&size, sizeof(int));
        ofs.write((char*)&number[0], size);
        string clss = current->clss;
        size = clss.size();
        ofs.write((char*)&size, sizeof(int));
        ofs.write((char*)&clss[0], size);
    }
    ofs.close();
}
void allStorage(void) {
    dateStorage(0);
    dateStorage(1);
    dateStorage(2);
    teacherIPStorage();
    studentIPStorage();
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
        allStorage();
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
    /*
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
    */
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