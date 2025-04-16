#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
typedef struct Student{
    int id;
    char name[20];
    char gender[20];
    int age;
    int score;
    char password[50];
    struct Student* next;
} Student;
typedef struct Teacher{
    int id;
    char password[50];
    struct Teacher* next;
} Teacher;
typedef struct Admin{
    int id;
    char password[50];
    struct Admin* next;
} Admin;
Student* studentList=NULL;
Teacher* teacherList=NULL;
Admin* adminList=NULL;
int curid=-1;
char curtype[20]="";
void initSystem();
void mainMenu();
void stuMenu();
void teaMenu();
void adminMenu();
void login(const char* userType);
void logout();
void accountModule();
void userRegister(const char* userType);
void adminregister();
void savedata();
void changePassword();
Student* createStudent(int id,const char* name,const char* gender,int age,int score,const char* password);
void addstu(Student **head,Student* newStudent);
Student *findstu(Student* head,int id);
int savestu(Student* head,const char* filename);
int loadstu(Student** head,const char* filename);
void deletestu(Student** head,int id);
void updatestu(Student* student,const char* name,const char *gender,int age,int score,const char* password);
void sortstu(Student** head);
void printstu(Student* head,int page,int pageSize);
Teacher* createTeacher(int id,const char* password);
void addtea(Teacher** head,Teacher* newTeacher);
Teacher* findtea(Teacher *head,int id);
int savetea(Teacher* head,const char* filename);
int loadtea(Teacher** head,const char* filename);
void deletea(Teacher** head,int id);
void updatetea(Teacher* teacher,const char* password);
Admin* createAdmin(int id, const char* password);
void addadm(Admin** head, Admin* newAdmin);
Admin* findadm(Admin* head, int id);
int saveadm(Admin* head, const char* filename);
int loadadm(Admin** head, const char* filename);
void exportAllAccounts(const char* filename);
void importAccountsFromFile(const char* filename);
void clearBuffer();
int getIntInput(const char* prompt);
void getStringInput(const char* prompt, char* buffer, int bufferSize);
int validateGender(const char* gender);
int validatePassword(const char* password);
int main() {
    initSystem();
    mainMenu();
    return 0;
}
void initSystem(){
    loadstu(&studentList,"students.txt");
    loadtea(&teacherList,"teachers.txt");
    loadadm(&adminList,"admins.txt");
    if(adminList==NULL){
        Admin* defaultAdmin=createAdmin(1,"admin123");
        if(defaultAdmin){
            addadm(&adminList,defaultAdmin);
            savedata();
        }
    }
}
void mainMenu(){
    int choice;
    while(1){
        printf("\n===== 学生信息管理系统 =====\n");
        printf("1. 学生登录\n");
        printf("2. 教师登录\n");
        printf("3. 管理员登录\n");
        printf("4. 账户模块\n");
        printf("5. 退出系统\n");
        printf("请选择: ");
        choice=getIntInput("");
        switch(choice){
            case 1:
            login("student");
            if(strcmp(curtype,"student")==0){
                stuMenu();
            }
            break;
            case 2:
            login("teacher");
            if(strcmp(curtype,"teacher")==0){
                teaMenu();
            }
            break;
            case 3:
            login("admin");
            if(strcmp(curtype,"admin")==0){
                adminMenu();
            }
            break;
            case 4:
            accountModule();
            break;
            case 5:
            savedata();
            printf("系统数据已保存，感谢使用!\n");
            exit(0);
            default:
            printf("无效选择，请重新输入!\n");
        }
    }
}
void stuMenu(){
    int choice;
    while(1){
        printf("\n===== 学生端 =====\n");
        printf("1. 查询个人成绩\n");
        printf("2. 查询本班成绩\n");
        printf("3. 修改密码\n");
        printf("4. 返回上一级\n");
        printf("请选择: ");
        choice=getIntInput("");
        switch(choice){
            case 1:{
            Student* student=findstu(studentList,curid);
            if(student){
                printf("\n学号: %d\n", student->id);
                printf("姓名: %s\n", student->name);
                printf("成绩: %d\n", student->score);
            }
            break;
        }
            case 2:{
            sortstu(&studentList);
            int page=1;
            int pageSize=10;
            while(1){
                printstu(studentList,page,pageSize);
                printf("\n1. 上一页\n");
                printf("2. 下一页\n");
                printf("3. 返回\n");
                printf("请选择: ");
                int pageChoice=getIntInput("");
                if(pageChoice==1&&page>1){
                    page--;
                }else if(pageChoice==2){
                    page++;
                }else if(pageChoice==3){
                    break;
                }
            }
            break;
        }
            case 3:{
            changePassword();
            break;
            }
            case 4:{
            logout();
            return ;
            }
            default:
            printf("无效选择，请重新输入!\n");
        }
    }
}
void teaMenu(){
    int choice;
    while(1){
        printf("\n===== 教师端 =====\n");
        printf("1. 增删改查学生信息\n");
        printf("2. 输入/修改学生成绩\n");
        printf("3. 查看班内成绩\n");
        printf("4. 修改密码\n");
        printf("5. 返回上一级\n");
        printf("请选择: ");
        choice=getIntInput("");
        switch(choice){
            case 1: {
                int studentChoice;
                printf("\n===== 学生信息管理 =====\n");
                printf("1. 查看学生列表\n");
                printf("2. 添加学生\n");
                printf("3. 删除学生\n");
                printf("4. 修改学生信息\n");
                printf("5. 返回上一级\n");
                printf("请选择: ");
                studentChoice=getIntInput("");
                switch(studentChoice){
                    case 1: {
                        sortstu(&studentList);
                        int page=1;
                        int pageSize=10;
                        while (1) {
                            printstu(studentList, page, pageSize);
                            printf("\n1. 上一页\n");
                            printf("2. 下一页\n");
                            printf("3. 返回\n");
                            printf("请选择: ");
                            int pageChoice=getIntInput("");
                            if(pageChoice==1 && page > 1) {
                                page--;
                            }else if(pageChoice==2) {
                                page++;
                            }else if(pageChoice==3) {
                                break;
                            }
                        }
                        break;
                    }
                    case 2:{
                        int id;
                        char name[50];
                        char gender[10];
                        int age;
                        char password[50];
                        id=getIntInput("请输入学号: ");
                        getStringInput("请输入姓名: ",name,50);
                        while(1){
                            getStringInput("请输入性别(男/女): ",gender,10);
                            if (validateGender(gender)) {
                                break;
                            }
                            printf("性别输入错误，只能输入'男'或'女'!\n");
                        }
                        age=getIntInput("请输入年龄: ");
                        while(1){
                            getStringInput("请输入5位数密码: ", password,50);
                            if(validatePassword(password)){
                                break;
                            }
                            printf("密码必须为5位数字!\n");
                        }
                        Student* newStudent=createStudent(id,name,gender,age,0,password);
                        if(newStudent){
                            addstu(&studentList,newStudent);
                            printf("学生添加成功!\n");
                            savedata();
                        }
                        break;
                    }
                    case 3: {
                        int id=getIntInput("请输入要删除的学生学号: ");
                        deletestu(&studentList, id);
                        printf("学生删除成功!\n");
                        savedata();
                        break;
                    }
                    case 4: {
                        int id=getIntInput("请输入要修改信息的学生学号: ");
                        Student* student=findstu(studentList, id);
                        if (student) {
                            char name[50];
                            char gender[10];
                            int age;
                            char password[50];
                            getStringInput("请输入新姓名: ", name, 50);
                            while (1) {
                                getStringInput("请输入新性别(男/女): ", gender, 10);
                                if (validateGender(gender)) {
                                    break;
                                }
                                printf("性别输入错误，只能输入'男'或'女'!\n");
                            }
                            age=getIntInput("请输入新年龄: ");
                            while (1) {
                                getStringInput("请输入新5位数密码: ", password, 50);
                                if (validatePassword(password)) {
                                    break;
                                }
                                printf("密码必须为5位数字!\n");
                            }
                            updatestu(student, name, gender, age, student->score, password);
                            printf("学生信息修改成功!\n");
                            savedata();
                        } else {
                            printf("未找到该学生!\n");
                        }
                        break;
                    }
                    case 5:
                        break;
                    default:
                        printf("无效选择，请重新输入!\n");
                }
                break;
    }
    case 2: {
        int id=getIntInput("请输入学生学号: ");
        Student* student=findstu(studentList,id);
        if(student){
            int score=getIntInput("请输入学生成绩: ");
            student->score=score;
            printf("学生成绩已更新!\n");
            savedata();
        }else {
            printf("未找到该学生!\n");
        }
        break;
    }
    case 3: {
        sortstu(&studentList);
        int page = 1;
        int pageSize = 10;
        while (1) {
            printstu(studentList, page, pageSize);
            printf("\n1. 上一页\n");
            printf("2. 下一页\n");
            printf("3. 返回\n");
            printf("请选择: ");
            int pageChoice = getIntInput("");
            if (pageChoice == 1 && page > 1) {
                page--;
            } else if (pageChoice == 2) {
                page++;
            } else if (pageChoice == 3) {
                break;
            }
        }
        break;
    }
    case 4: {
        changePassword();
        break;
    }
    case 5: {
        logout();
        return;
    }
    default:
    printf("无效选择，请重新输入!\n");
}
}
    }
void adminMenu(){
        int choice;
        while (1){
            printf("\n===== 管理员端 =====\n");
            printf("1. 管理学生账号密码\n");
            printf("2. 管理教师账号密码\n");
            printf("3. 导出所有账号密码\n");
            printf("4. 从文件导入账号密码\n");
            printf("5. 注册新管理员账号\n");
            printf("6. 修改密码\n");
            printf("7. 返回上一级\n");
            printf("请选择: ");
            choice=getIntInput("");
            switch (choice){
                case 1: {
                    int id=getIntInput("请输入要修改密码的学生学号: ");
                    Student* student=findstu(studentList,id);
                    if (student){
                        char password[50];
                        while (1){
                            getStringInput("请输入新5位数密码: ",password,50);
                            if (validatePassword(password)) {
                                break;
                            }
                            printf("密码必须为5位数字!\n");
                        }
                        strcpy(student->password,password);
                        printf("学生密码修改成功!\n");
                        savedata();
                    } else {
                        printf("未找到该学生!\n");
                    }
                    break;
                }
                case 2: {
                    int id=getIntInput("请输入要修改密码的教师工号: ");
                    Teacher* teacher=findtea(teacherList, id);
                    if(teacher){
                        char password[50];
                        while (1) {
                            getStringInput("请输入新5位数密码: ", password, 50);
                            if(validatePassword(password)){
                                break;
                            }
                            printf("密码必须为5位数字!\n");
                        }
                        strcpy(teacher->password,password);
                        printf("教师密码修改成功!\n");
                        savedata();
                    } else {
                        printf("未找到该教师!\n");
                    }
                    break;
                }
                case 3:
                    exportAllAccounts("accounts.txt");
                    printf("所有账号密码已导出到 accounts.txt\n");
                    break;
                case 4:
                    importAccountsFromFile("accounts_import.txt");
                    printf("账号密码已从文件导入\n");
                    savedata();
                    break;
                case 5:
                    adminregister();
                    savedata(); // 注册新管理员后保存数据
                    break;
                case 6:
                    changePassword();
                    break;
                case 7:
                    logout();
                    return;
                default:
                    printf("无效选择，请重新输入!\n");
            }
        }
    }
void login(const char *userType){
    int id;
    char password[50];
    printf("\n===== %s登录 =====\n",userType);
    id=getIntInput("学号/工号/ID: ");
    getStringInput("密码: ", password, 50);
    if(strcmp(userType,"student")==0){
        Student *student=findstu(studentList,id);
        if(student&&strcmp(student->password,password)==0){
            curid=student->id;
            strcmp(curtype,"student");
            printf("登录成功! 欢迎 学号: %d\n", student->id);
            return;
        }
    }else if(strcmp(userType,"teacher")==0){
        Teacher *teacher=findtea(teacherList,id);
        if(teacher&&strcmp(teacher->password,password)==0){
            curid=teacher->id;
            strcmp(curtype,"teacher");
            printf("登录成功! 欢迎 工号: %d\n", teacher->id);
            return;
        }
    }else if(strcmp(userType,"admin")==0){
        Admin* admin=findadm(adminList,id);
        if(admin&&strcmp(admin->password,password)==0){
            curid=admin->id;
            strcmp(curtype,"admin");
            printf("登录成功! 欢迎 管理员ID: %d\n", admin->id);
            return;
        }
    }
    printf("学号/工号/ID或密码错误!\n");
}
void logout(){
    curid=-1;
    strcpy(curtype,"");
    printf("已登出!\n");
}
void accountModule(){
    int choice;
    while (1){
        printf("\n===== 账户模块 =====\n");
        printf("1. 新用户注册\n");
        printf("2. 修改密码\n");
        printf("3. 返回上一级\n");
        printf("请选择: ");
        choice=getIntInput("");
        switch(choice) {
            case 1: {
                int userChoice;
                printf("\n1. 学生注册\n");
                printf("2. 教师注册\n");
                printf("请选择: ");
                userChoice=getIntInput("");
                if(userChoice == 1){
                    userRegister("student");
                    savedata();
                } else if(userChoice == 2) {
                    userRegister("teacher");
                    savedata();
                } else {
                    printf("无效选择，请重新输入!\n");
                }
                break;
            }
            case 2:
                changePassword();
                break;
            case 3:
                return;
            default:
                printf("无效选择，请重新输入!\n");
        }
    }
}
void changePassword(){
    if(curid==-1){
        printf("请先登录!\n");
        return;
    }
    char oldPassword[50];
    char newPassword[50];
    char confirmPassword[50];
    getStringInput("请输入旧密码: ", oldPassword, 50);
    if(strcmp(curtype,"student")==0){
        Student* student=findstu(studentList,curid);
        if(student&&strcmp(student->password,oldPassword)!=0){
            printf("旧密码错误!\n");
            return;
        }
    }else if(strcmp(curtype,"teacher")==0){
        Teacher* teacher=findtea(teacherList,curid);
        if(teacher&&strcmp(teacher->password,oldPassword)!=0){
            printf("旧密码错误!\n");
            return;
        }
    }else if(strcmp(curtype,"admin")==0){
        Admin* admin=findadm(adminList,curid);
        if(admin&&strcmp(admin->password,oldPassword)!=0){
            printf("旧密码错误!\n");
            return;
        }
    }
    while(1){
        getStringInput("请输入新5位数密码: ", newPassword, 50);
        if(validatePassword(newPassword)){
            break;
        }
        printf("密码必须为5位数字!\n");
    }
    getStringInput("请再次输入新密码: ", confirmPassword, 50);
    if (strcmp(newPassword,confirmPassword) != 0) {
        printf("两次输入的密码不一致!\n");
        return;
    }
    if(strcmp(curtype,"student")==0) {
        Student* student=findstu(studentList,curid);
            if(student){
                strcpy(student->password,newPassword);
            }
        
    }else if(strcmp(curtype,"teacher")==0){
        Teacher* teacher=findtea(teacherList,curid);
            if(teacher){
                strcpy(teacher->password,newPassword);
            }
    }else if(strcmp(curtype,"admin")==0){
        Admin* admin=findadm(adminList,curid);
            if(admin){
                strcpy(admin->password,newPassword);
            }
    }
    printf("密码修改成功!\n");
    savedata();
}
void userRegister(const char* userType) {
    int id;
    char password[50];
    if (strcmp(userType, "student") == 0) {
        char name[50];
        char gender[10];
        int age;
        id=getIntInput("请输入学号: ");
        getStringInput("请输入姓名: ", name, 50);
        while (1){
            getStringInput("请输入性别(男/女): ", gender, 10);
            if (validateGender(gender)) {
                break;
            }
            printf("性别输入错误，只能输入'男'或'女'!\n");
        }
        age = getIntInput("请输入年龄: ");
        while (1) {
            getStringInput("请输入5位数密码: ", password, 50);
            if (validatePassword(password)) {
                break;
            }
            printf("密码必须为5位数字!\n");
        }
        Student* newStudent=createStudent(id, name, gender, age, 0, password);
        if(newStudent){
            addstu(&studentList, newStudent);
            printf("学生注册成功!\n");
        }
    } else if(strcmp(userType, "teacher") == 0){
        id=getIntInput("请输入工号: ");
        while(1){
            getStringInput("请输入5位数密码: ", password, 50);
            if(validatePassword(password)){
                break;
            }
            printf("密码必须为5位数字!\n");
        }
        Teacher* newTeacher=createTeacher(id, password);
        if (newTeacher){
            addtea(&teacherList, newTeacher);
            printf("教师注册成功!\n");
        }
    }
}
Student* createStudent(int id,const char *name,const char *gender,int age,int score,const char *password){
    Student* newStudent=(Student*)malloc(sizeof(Student));
    if(newStudent==NULL){
        perror("内存分配失败");
        return NULL;
    }
    newStudent->id=id;
    strcpy(newStudent->name,name);
    strcpy(newStudent->gender,gender);
    newStudent->age=age;
    newStudent->score=score;
    strcpy(newStudent->password,password);
    newStudent->next=NULL;
    return newStudent;
}
void addstu(Student** head,Student* newStudent){
    if(*head==NULL){
        *head=newStudent;
    }else{
        Student* current=*head;
        while(current->next){
            current=current->next;
        }
        current->next=newStudent;
    }
}
Student* findstu(Student* head,int id){
    Student* current=head;
    while(current){
        if(current->id==id){
            return current;
        }
        current=current->next;
    }
    return NULL;
}
int savestu(Student* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file){
        perror("无法保存学生数据到文件");
        return 0;
    }
    Student* current = head;
    while(current){
        fprintf(file, "%d,%s,%s,%d,%d,%s\n", current->id, current->name, current->gender, current->age, current->score, current->password);
        current = current->next;
    }
    fclose(file);
    return 1;
}
int loadstu(Student** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file){
        return 0;
    }
    int id, age, score;
    char name[50], gender[10], password[50];
    while (fscanf(file, "%d,%[^,],%[^,],%d,%d,%s\n", &id, name, gender, &age, &score, password) == 6) {
        Student* newStudent = createStudent(id, name, gender, age, score, password);
        if (newStudent) {
            addstu(head, newStudent);
        }
    }
    fclose(file);
    return 1;
}
void deletestu(Student** head,int id){
    Student* current=*head;
    Student* pre=NULL;
    while(current!=NULL&&current->id!=id){
        pre=current;
        current=current->next;
    }
    if(current==NULL) return;
    if(pre==NULL){
        *head=current->next;
    }else{
        pre->next=current->next;
    }
    free(current);
}
void updatestu(Student* student, const char* name, const char* gender, int age, int score, const char* password) {
    strcpy(student->name, name);
    strcpy(student->gender, gender);
    student->age = age;
    student->score = score;
    strcpy(student->password, password);
}
Teacher* createTeacher(int id, const char* password) {
    Teacher* newTeacher=(Teacher*)malloc(sizeof(Teacher));
    if (newTeacher==NULL){
        perror("内存分配失败");
        return NULL;
    }
    newTeacher->id=id;
    strcpy(newTeacher->password, password);
    newTeacher->next=NULL;
    return newTeacher;
}
void addtea(Teacher** head, Teacher* newTeacher){
    if (*head==NULL){
        *head = newTeacher;
    } else{
        Teacher* current=*head;
        while(current->next){
            current=current->next;
        }
        current->next=newTeacher;
    }
}
Teacher* findtea(Teacher* head, int id) {
    Teacher* current=head;
    while (current){
        if (current->id==id) {
            return current;
        }
        current=current->next;
    }
    return NULL;
}
int savetea(Teacher* head, const char* filename) {
    FILE* file=fopen(filename, "w");
    if (!file){
        perror("无法保存教师数据到文件");
        return 0;
    }
    Teacher* current=head;
    while (current){
        fprintf(file, "%d,%s\n", current->id, current->password);
        current=current->next;
    }
    fclose(file);
    return 1;
}
int loadtea(Teacher** head, const char* filename) {
    FILE* file=fopen(filename, "r");
    if (!file){
        return 0;
    }
    int id;
    char password[50];
    while(fscanf(file, "%d,%s\n", &id, password) == 2){
        Teacher* newTeacher=createTeacher(id, password);
        if (newTeacher){
            addtea(head, newTeacher);
        }
    }
    fclose(file);
    return 1;
}
void deletea(Teacher** head, int id) {
    Teacher* current=*head;
    Teacher* pre=NULL;
    while(current!=NULL&&current->id!=id) {
        pre=current;
        current=current->next;
    }
    if (current==NULL) return;
    if (pre==NULL) {
        *head=current->next;
    } else{
        pre->next=current->next;
    }
    free(current);
}
void updatetea(Teacher* teacher, const char* password) {
    strcpy(teacher->password, password);
}
Admin* createAdmin(int id, const char* password){
    Admin* newAdmin=(Admin*)malloc(sizeof(Admin));
    if (newAdmin==NULL){
        perror("内存分配失败");
        return NULL;
    }
    newAdmin->id=id;
    strcpy(newAdmin->password, password);
    newAdmin->next=NULL;
    return newAdmin;
}
void addadm(Admin** head,Admin* newAdmin){
    if(*head==NULL){
        *head=newAdmin;
    }else{
        Admin* current=*head;
        while(current->next){
            current=current->next;
        }
        current->next=newAdmin;
    }
}
Admin* findadm(Admin* head, int id) {
    Admin* current=head;
    while(current){
        if (current->id==id) {
            return current;
        }
        current=current->next;
    }
    return NULL;
}
int saveadm(Admin* head, const char* filename) {
    FILE* file=fopen(filename, "w");
    if (!file){
        perror("无法保存管理员数据到文件");
        return 0;
    }
    Admin* current=head;
    while (current){
        fprintf(file,"%d,%s\n", current->id, current->password);
        current=current->next;
    }
    fclose(file);
    return 1;
}
int loadadm(Admin** head, const char* filename) {
    FILE* file=fopen(filename, "r");
    if (!file) {
        return 0;
    }
    int id;
    char password[50];
    while (fscanf(file, "%d,%s\n", &id, password) == 2) {
        Admin* newAdmin = createAdmin(id, password);
        if (newAdmin) {
            addadm(head, newAdmin);
        }
    }
    fclose(file);
    return 1;
}
void clearInputBuffer() {
    while (getchar() != '\n');
}
int getIntInput(const char* prompt) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1) {
        clearInputBuffer();
        printf("输入无效，请重新输入: ");
    }
    clearInputBuffer();
    return value;
}
void getStringInput(const char* prompt, char* buffer, int bufferSize) {
    printf("%s", prompt);
    fgets(buffer, bufferSize, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}
int validateGender(const char* gender) {
    return (strcmp(gender, "男") == 0 || strcmp(gender, "女") == 0);
}
int validatePassword(const char* password){
    if(strlen(password)!=5){
        return 0;
    }
    for(int i=0;i<5;i++){
        if(!isdigit(password[i])){
            return 0;
        }
    }
    return 1;
}
void adminregister() {
    int id;
    char password[50];
    id=getIntInput("请输入新管理员ID: ");
    while (1) {
        getStringInput("请输入5位数密码: ", password, 50);
        if (validatePassword(password)) {
            break;
        }
        printf("密码必须为5位数字!\n");
    }
    Admin* newAdmin=createAdmin(id, password);
    if (newAdmin){
        addadm(&adminList, newAdmin);
        printf("新管理员注册成功!\n");
    }
}
void savedata() {
    savestu(studentList, "students.txt");
    savetea(teacherList, "teachers.txt");
    saveadm(adminList, "admins.txt");
}
void sortstu(Student** head) {
    int swapped;
    Student* ptr1;
    Student* lptr=NULL;
    if (*head==NULL) return;
    do {
        swapped=0;
        ptr1=*head;
        while(ptr1->next!=lptr){
            if (ptr1->score < ptr1->next->score) {
                int tempId=ptr1->id;
                char tempName[50];
                strcpy(tempName, ptr1->name);
                char tempGender[10];
                strcpy(tempGender, ptr1->gender);
                int tempAge=ptr1->age;
                int tempScore=ptr1->score;
                char tempPassword[50];
                strcpy(tempPassword, ptr1->password);
                ptr1->id=ptr1->next->id;
                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->gender, ptr1->next->gender);
                ptr1->age=ptr1->next->age;
                ptr1->score=ptr1->next->score;
                strcpy(ptr1->password, ptr1->next->password);
                ptr1->next->id=tempId;
                strcpy(ptr1->next->name, tempName);
                strcpy(ptr1->next->gender, tempGender);
                ptr1->next->age=tempAge;
                ptr1->next->score=tempScore;
                strcpy(ptr1->next->password, tempPassword);
                swapped=1;
            }
            ptr1=ptr1->next;
        }
        lptr=ptr1;
    } while(swapped);
}
void printstu(Student* head, int page, int pageSize) {
    int count = 0;
    Student* current=head;
    while (current&&count<(page - 1)*pageSize) {
        current=current->next;
        count++;
    }
    printf("\n===== 学生成绩列表第%d页=====\n",page);
    count = 0;
    while (current && count < pageSize) {
        printf("学号: %d\n", current->id);
        printf("姓名: %s\n", current->name);
        printf("成绩: %d\n", current->score);
        printf("-------------------\n");
        current = current->next;
        count++;
    }
}
void exportAllAccounts(const char* filename) {
    FILE* file=fopen(filename, "w");
    if (!file) {
        perror("无法导出账号密码到文件");
        return;
    }
    Student* student = studentList;
    while (student) {
        fprintf(file, "学生 学号: %d 密码: %s\n", student->id, student->password);
        student=student->next;
    }
    Teacher* teacher = teacherList;
    while (teacher) {
        fprintf(file, "教师 工号: %d 密码: %s\n", teacher->id, teacher->password);
        teacher=teacher->next;
    }
    Admin* admin = adminList;
    while (admin) {
        fprintf(file, "管理员 ID: %d 密码: %s\n", admin->id, admin->password);
        admin=admin->next;
    }
    fclose(file);
}
void importAccountsFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("无法打开导入文件");
        return;
    }
}
