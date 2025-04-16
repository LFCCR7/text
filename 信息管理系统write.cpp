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
        printf("\n===== ѧ����Ϣ����ϵͳ =====\n");
        printf("1. ѧ����¼\n");
        printf("2. ��ʦ��¼\n");
        printf("3. ����Ա��¼\n");
        printf("4. �˻�ģ��\n");
        printf("5. �˳�ϵͳ\n");
        printf("��ѡ��: ");
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
            printf("ϵͳ�����ѱ��棬��лʹ��!\n");
            exit(0);
            default:
            printf("��Чѡ������������!\n");
        }
    }
}
void stuMenu(){
    int choice;
    while(1){
        printf("\n===== ѧ���� =====\n");
        printf("1. ��ѯ���˳ɼ�\n");
        printf("2. ��ѯ����ɼ�\n");
        printf("3. �޸�����\n");
        printf("4. ������һ��\n");
        printf("��ѡ��: ");
        choice=getIntInput("");
        switch(choice){
            case 1:{
            Student* student=findstu(studentList,curid);
            if(student){
                printf("\nѧ��: %d\n", student->id);
                printf("����: %s\n", student->name);
                printf("�ɼ�: %d\n", student->score);
            }
            break;
        }
            case 2:{
            sortstu(&studentList);
            int page=1;
            int pageSize=10;
            while(1){
                printstu(studentList,page,pageSize);
                printf("\n1. ��һҳ\n");
                printf("2. ��һҳ\n");
                printf("3. ����\n");
                printf("��ѡ��: ");
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
            printf("��Чѡ������������!\n");
        }
    }
}
void teaMenu(){
    int choice;
    while(1){
        printf("\n===== ��ʦ�� =====\n");
        printf("1. ��ɾ�Ĳ�ѧ����Ϣ\n");
        printf("2. ����/�޸�ѧ���ɼ�\n");
        printf("3. �鿴���ڳɼ�\n");
        printf("4. �޸�����\n");
        printf("5. ������һ��\n");
        printf("��ѡ��: ");
        choice=getIntInput("");
        switch(choice){
            case 1: {
                int studentChoice;
                printf("\n===== ѧ����Ϣ���� =====\n");
                printf("1. �鿴ѧ���б�\n");
                printf("2. ���ѧ��\n");
                printf("3. ɾ��ѧ��\n");
                printf("4. �޸�ѧ����Ϣ\n");
                printf("5. ������һ��\n");
                printf("��ѡ��: ");
                studentChoice=getIntInput("");
                switch(studentChoice){
                    case 1: {
                        sortstu(&studentList);
                        int page=1;
                        int pageSize=10;
                        while (1) {
                            printstu(studentList, page, pageSize);
                            printf("\n1. ��һҳ\n");
                            printf("2. ��һҳ\n");
                            printf("3. ����\n");
                            printf("��ѡ��: ");
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
                        id=getIntInput("������ѧ��: ");
                        getStringInput("����������: ",name,50);
                        while(1){
                            getStringInput("�������Ա�(��/Ů): ",gender,10);
                            if (validateGender(gender)) {
                                break;
                            }
                            printf("�Ա��������ֻ������'��'��'Ů'!\n");
                        }
                        age=getIntInput("����������: ");
                        while(1){
                            getStringInput("������5λ������: ", password,50);
                            if(validatePassword(password)){
                                break;
                            }
                            printf("�������Ϊ5λ����!\n");
                        }
                        Student* newStudent=createStudent(id,name,gender,age,0,password);
                        if(newStudent){
                            addstu(&studentList,newStudent);
                            printf("ѧ����ӳɹ�!\n");
                            savedata();
                        }
                        break;
                    }
                    case 3: {
                        int id=getIntInput("������Ҫɾ����ѧ��ѧ��: ");
                        deletestu(&studentList, id);
                        printf("ѧ��ɾ���ɹ�!\n");
                        savedata();
                        break;
                    }
                    case 4: {
                        int id=getIntInput("������Ҫ�޸���Ϣ��ѧ��ѧ��: ");
                        Student* student=findstu(studentList, id);
                        if (student) {
                            char name[50];
                            char gender[10];
                            int age;
                            char password[50];
                            getStringInput("������������: ", name, 50);
                            while (1) {
                                getStringInput("���������Ա�(��/Ů): ", gender, 10);
                                if (validateGender(gender)) {
                                    break;
                                }
                                printf("�Ա��������ֻ������'��'��'Ů'!\n");
                            }
                            age=getIntInput("������������: ");
                            while (1) {
                                getStringInput("��������5λ������: ", password, 50);
                                if (validatePassword(password)) {
                                    break;
                                }
                                printf("�������Ϊ5λ����!\n");
                            }
                            updatestu(student, name, gender, age, student->score, password);
                            printf("ѧ����Ϣ�޸ĳɹ�!\n");
                            savedata();
                        } else {
                            printf("δ�ҵ���ѧ��!\n");
                        }
                        break;
                    }
                    case 5:
                        break;
                    default:
                        printf("��Чѡ������������!\n");
                }
                break;
    }
    case 2: {
        int id=getIntInput("������ѧ��ѧ��: ");
        Student* student=findstu(studentList,id);
        if(student){
            int score=getIntInput("������ѧ���ɼ�: ");
            student->score=score;
            printf("ѧ���ɼ��Ѹ���!\n");
            savedata();
        }else {
            printf("δ�ҵ���ѧ��!\n");
        }
        break;
    }
    case 3: {
        sortstu(&studentList);
        int page = 1;
        int pageSize = 10;
        while (1) {
            printstu(studentList, page, pageSize);
            printf("\n1. ��һҳ\n");
            printf("2. ��һҳ\n");
            printf("3. ����\n");
            printf("��ѡ��: ");
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
    printf("��Чѡ������������!\n");
}
}
    }
void adminMenu(){
        int choice;
        while (1){
            printf("\n===== ����Ա�� =====\n");
            printf("1. ����ѧ���˺�����\n");
            printf("2. �����ʦ�˺�����\n");
            printf("3. ���������˺�����\n");
            printf("4. ���ļ������˺�����\n");
            printf("5. ע���¹���Ա�˺�\n");
            printf("6. �޸�����\n");
            printf("7. ������һ��\n");
            printf("��ѡ��: ");
            choice=getIntInput("");
            switch (choice){
                case 1: {
                    int id=getIntInput("������Ҫ�޸������ѧ��ѧ��: ");
                    Student* student=findstu(studentList,id);
                    if (student){
                        char password[50];
                        while (1){
                            getStringInput("��������5λ������: ",password,50);
                            if (validatePassword(password)) {
                                break;
                            }
                            printf("�������Ϊ5λ����!\n");
                        }
                        strcpy(student->password,password);
                        printf("ѧ�������޸ĳɹ�!\n");
                        savedata();
                    } else {
                        printf("δ�ҵ���ѧ��!\n");
                    }
                    break;
                }
                case 2: {
                    int id=getIntInput("������Ҫ�޸�����Ľ�ʦ����: ");
                    Teacher* teacher=findtea(teacherList, id);
                    if(teacher){
                        char password[50];
                        while (1) {
                            getStringInput("��������5λ������: ", password, 50);
                            if(validatePassword(password)){
                                break;
                            }
                            printf("�������Ϊ5λ����!\n");
                        }
                        strcpy(teacher->password,password);
                        printf("��ʦ�����޸ĳɹ�!\n");
                        savedata();
                    } else {
                        printf("δ�ҵ��ý�ʦ!\n");
                    }
                    break;
                }
                case 3:
                    exportAllAccounts("accounts.txt");
                    printf("�����˺������ѵ����� accounts.txt\n");
                    break;
                case 4:
                    importAccountsFromFile("accounts_import.txt");
                    printf("�˺������Ѵ��ļ�����\n");
                    savedata();
                    break;
                case 5:
                    adminregister();
                    savedata(); // ע���¹���Ա�󱣴�����
                    break;
                case 6:
                    changePassword();
                    break;
                case 7:
                    logout();
                    return;
                default:
                    printf("��Чѡ������������!\n");
            }
        }
    }
void login(const char *userType){
    int id;
    char password[50];
    printf("\n===== %s��¼ =====\n",userType);
    id=getIntInput("ѧ��/����/ID: ");
    getStringInput("����: ", password, 50);
    if(strcmp(userType,"student")==0){
        Student *student=findstu(studentList,id);
        if(student&&strcmp(student->password,password)==0){
            curid=student->id;
            strcmp(curtype,"student");
            printf("��¼�ɹ�! ��ӭ ѧ��: %d\n", student->id);
            return;
        }
    }else if(strcmp(userType,"teacher")==0){
        Teacher *teacher=findtea(teacherList,id);
        if(teacher&&strcmp(teacher->password,password)==0){
            curid=teacher->id;
            strcmp(curtype,"teacher");
            printf("��¼�ɹ�! ��ӭ ����: %d\n", teacher->id);
            return;
        }
    }else if(strcmp(userType,"admin")==0){
        Admin* admin=findadm(adminList,id);
        if(admin&&strcmp(admin->password,password)==0){
            curid=admin->id;
            strcmp(curtype,"admin");
            printf("��¼�ɹ�! ��ӭ ����ԱID: %d\n", admin->id);
            return;
        }
    }
    printf("ѧ��/����/ID���������!\n");
}
void logout(){
    curid=-1;
    strcpy(curtype,"");
    printf("�ѵǳ�!\n");
}
void accountModule(){
    int choice;
    while (1){
        printf("\n===== �˻�ģ�� =====\n");
        printf("1. ���û�ע��\n");
        printf("2. �޸�����\n");
        printf("3. ������һ��\n");
        printf("��ѡ��: ");
        choice=getIntInput("");
        switch(choice) {
            case 1: {
                int userChoice;
                printf("\n1. ѧ��ע��\n");
                printf("2. ��ʦע��\n");
                printf("��ѡ��: ");
                userChoice=getIntInput("");
                if(userChoice == 1){
                    userRegister("student");
                    savedata();
                } else if(userChoice == 2) {
                    userRegister("teacher");
                    savedata();
                } else {
                    printf("��Чѡ������������!\n");
                }
                break;
            }
            case 2:
                changePassword();
                break;
            case 3:
                return;
            default:
                printf("��Чѡ������������!\n");
        }
    }
}
void changePassword(){
    if(curid==-1){
        printf("���ȵ�¼!\n");
        return;
    }
    char oldPassword[50];
    char newPassword[50];
    char confirmPassword[50];
    getStringInput("�����������: ", oldPassword, 50);
    if(strcmp(curtype,"student")==0){
        Student* student=findstu(studentList,curid);
        if(student&&strcmp(student->password,oldPassword)!=0){
            printf("���������!\n");
            return;
        }
    }else if(strcmp(curtype,"teacher")==0){
        Teacher* teacher=findtea(teacherList,curid);
        if(teacher&&strcmp(teacher->password,oldPassword)!=0){
            printf("���������!\n");
            return;
        }
    }else if(strcmp(curtype,"admin")==0){
        Admin* admin=findadm(adminList,curid);
        if(admin&&strcmp(admin->password,oldPassword)!=0){
            printf("���������!\n");
            return;
        }
    }
    while(1){
        getStringInput("��������5λ������: ", newPassword, 50);
        if(validatePassword(newPassword)){
            break;
        }
        printf("�������Ϊ5λ����!\n");
    }
    getStringInput("���ٴ�����������: ", confirmPassword, 50);
    if (strcmp(newPassword,confirmPassword) != 0) {
        printf("������������벻һ��!\n");
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
    printf("�����޸ĳɹ�!\n");
    savedata();
}
void userRegister(const char* userType) {
    int id;
    char password[50];
    if (strcmp(userType, "student") == 0) {
        char name[50];
        char gender[10];
        int age;
        id=getIntInput("������ѧ��: ");
        getStringInput("����������: ", name, 50);
        while (1){
            getStringInput("�������Ա�(��/Ů): ", gender, 10);
            if (validateGender(gender)) {
                break;
            }
            printf("�Ա��������ֻ������'��'��'Ů'!\n");
        }
        age = getIntInput("����������: ");
        while (1) {
            getStringInput("������5λ������: ", password, 50);
            if (validatePassword(password)) {
                break;
            }
            printf("�������Ϊ5λ����!\n");
        }
        Student* newStudent=createStudent(id, name, gender, age, 0, password);
        if(newStudent){
            addstu(&studentList, newStudent);
            printf("ѧ��ע��ɹ�!\n");
        }
    } else if(strcmp(userType, "teacher") == 0){
        id=getIntInput("�����빤��: ");
        while(1){
            getStringInput("������5λ������: ", password, 50);
            if(validatePassword(password)){
                break;
            }
            printf("�������Ϊ5λ����!\n");
        }
        Teacher* newTeacher=createTeacher(id, password);
        if (newTeacher){
            addtea(&teacherList, newTeacher);
            printf("��ʦע��ɹ�!\n");
        }
    }
}
Student* createStudent(int id,const char *name,const char *gender,int age,int score,const char *password){
    Student* newStudent=(Student*)malloc(sizeof(Student));
    if(newStudent==NULL){
        perror("�ڴ����ʧ��");
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
        perror("�޷�����ѧ�����ݵ��ļ�");
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
        perror("�ڴ����ʧ��");
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
        perror("�޷������ʦ���ݵ��ļ�");
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
        perror("�ڴ����ʧ��");
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
        perror("�޷��������Ա���ݵ��ļ�");
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
        printf("������Ч������������: ");
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
    return (strcmp(gender, "��") == 0 || strcmp(gender, "Ů") == 0);
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
    id=getIntInput("�������¹���ԱID: ");
    while (1) {
        getStringInput("������5λ������: ", password, 50);
        if (validatePassword(password)) {
            break;
        }
        printf("�������Ϊ5λ����!\n");
    }
    Admin* newAdmin=createAdmin(id, password);
    if (newAdmin){
        addadm(&adminList, newAdmin);
        printf("�¹���Աע��ɹ�!\n");
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
    printf("\n===== ѧ���ɼ��б��%dҳ=====\n",page);
    count = 0;
    while (current && count < pageSize) {
        printf("ѧ��: %d\n", current->id);
        printf("����: %s\n", current->name);
        printf("�ɼ�: %d\n", current->score);
        printf("-------------------\n");
        current = current->next;
        count++;
    }
}
void exportAllAccounts(const char* filename) {
    FILE* file=fopen(filename, "w");
    if (!file) {
        perror("�޷������˺����뵽�ļ�");
        return;
    }
    Student* student = studentList;
    while (student) {
        fprintf(file, "ѧ�� ѧ��: %d ����: %s\n", student->id, student->password);
        student=student->next;
    }
    Teacher* teacher = teacherList;
    while (teacher) {
        fprintf(file, "��ʦ ����: %d ����: %s\n", teacher->id, teacher->password);
        teacher=teacher->next;
    }
    Admin* admin = adminList;
    while (admin) {
        fprintf(file, "����Ա ID: %d ����: %s\n", admin->id, admin->password);
        admin=admin->next;
    }
    fclose(file);
}
void importAccountsFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("�޷��򿪵����ļ�");
        return;
    }
}
