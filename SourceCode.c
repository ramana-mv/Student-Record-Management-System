//including required header files
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<ctype.h>
//structure for login
typedef struct
{
	char username[30];
	char password[30];
}log;
//structure for date format
typedef struct
{
	int day;
	int month;
	int year;
}Date;
//structure for student details
typedef struct 
{
	char rollno[20];
	char name[30];
	char gender[7];
	char father_name[30];
	char mother_name[30];
	char address[30];
	char mobile_no[10];
	Date date_of_birth;
	Date date_of_joining;
	char branch[6];
	char section[10];
	int academic_year;
}student;
//structure for storing student marks
typedef struct
{
	char rollno[20];
	char sub[20][20];
	int no_of_subjects,max_score[20],score[20];
}marks;
int choice;// variable for choosing between administrator and user
//defining methods
char iname[30];//variable to store institution name
void SetColor(int BacC,int ForgC);
void move(int x,int y);
void start();
void draw_rect(int extra_length);
void draw_rect2();
void draw_line();
void draw_box(int x,int y,int no_of_rows,int no_of_columns);
int option(int val,int y);
void head();
void institute();
void menu1();
void menu2();
void menu3();
void register_user();
int ask_type();
void login();
void menu4(char *username);
void menu5(char *username);
int validate_name(char *name);
student details();
int validate_date(Date *date_given);
void add_student(char *username);
void view_student(char *username,char *id);
void modify_student(char *username);
void delete_student(char *username);
void change_password(char *username);
void add_modify_marks(char *username);
void delete_marks(char *username);
//main methods
int main()
{
	start();//calling start function
	return 0;
}
//function to set color to text and background
void SetColor(int BacC,int ForgC)
{
     WORD wColor;
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (BacC << 4) + (ForgC);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}
//Function to move cursor position on screen
void move(int x,int y)
{
	COORD coord={0,0};
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
//start() function which shows the opening screen and for adding institution name
void start()
{
	SetColor(15,0);
	system("cls");
	draw_rect2(0);
	move(70,20);printf("WELCOME TO STUDENT RECORD MANAGEMENT SYSTEM");
	move(70,25); printf("Starting");
	Sleep(1000);
	move(78,25);printf(".");
	Sleep(1000);
	move(79,25);printf(".");
	Sleep(1000);
	move(80,25);printf(".");
	system("cls");
	FILE *fp;
	fp=fopen("institute.txt","r");
    //after opening the file if it is empty then institute function is called which asks user to enter institute name
	if(fp==NULL)
	{
		institute();
		Sleep(1000);
	}
    //if file is not empty then the name present on it is displayed on screen
	else
	{
		fread(&iname,sizeof(iname),1,fp);
		puts(iname);
	}
	fclose(fp);
	fflush(stdin);
	menu1();//calling menu function to display home page
}
//Function to draw outer border
void draw_rect(int extra_length)
{
	int i,j;
	move(20,3);
	printf("%c",178);
	for(i=20;i<180;i++)
	{
		move(i,3);
		printf("%c",178);
	}
	move(20,4);
	for(j=4;j<49+extra_length;j++)
	{
		printf("%c",178);
		move(20,j);
	}
	move(20,48+extra_length);
	printf("%c",178);
	for(i=20;i<180;i++)
	{
		move(i,48+extra_length);
		printf("%c",178);
	}
	move(180,3);
	printf("%c",178);
	for(j=4;j<49+extra_length;j++)
	{
		move(180,j);
		printf("%c",178);
	}
}
//Function to draw inner border
void draw_rect2()
{
	move(50,13);
	int i,j;
	for(i=50;i<150;i++)
	{
		move(i,13);
		printf("%c",178);
	}
	move(50,14);
	for(j=13;j<30;j++)
	{
		move(50,j);
		printf("%c",178);
	}
	move(50,29);
	for(i=50;i<150;i++)
	{
		move(i,29);
		printf("%c",178);
	}
	move(150,13);
	for(j=13;j<30;j++)
	{
		move(150,j);
		printf("%c",178);
	}
}
//Function to draw single line
void draw_line()
{
	for(int i=21;i<180;i++)
	{
		printf("%c",196);
	}
}
//function to draw double line
void draw_line2()
{
	for(int i=21;i<180;i++)
	{
		printf("%c",205);
	}
}
//Function to draw a box with x,y coordinates and no of rows and columns as parameters
void draw_box(int x,int y,int no_of_rows,int no_of_columns)
{
	int i,j=0,k;
	move(x,y);
	//drawing horizontal lines
	for(k=1;k<=no_of_rows+2;k++)
	{
		for(i=x;i<=180;i++)
		{
			printf("%c",196);
			move(i,y+j);
		}
		j=j+2;
	}
	x=x+8;
	j=5;
    //drawing vertical lines
	for(k=1;k<=no_of_columns;k++)
	{
		move(x+j,y);
		printf("%c",194);
		for(i=y+1;i<=(y+1)+no_of_rows*2;i++)
		{
			move(x+j,i);
			printf("%c",179);
		}
		move(x+j,i);
		printf("%c",193);
		j=j+15;
	}
	
}
//Function to move the arrow key up and down to choose an option
int option(int val,int y)
{
	int a,count=0;
	move(68,y);printf(">>>");
	while(1)
	{
		move(70,48);
		a=getch();
		if(a==72)//up arrow
		{
			if(count==0)
			{
				move(68,y);printf("   ");
				count=val-1;
				move(68,y+2*count);printf(">>>");
			}
			else
			{
				move(68,y+2*count);printf("   ");
				count--;
				move(68,y+2*count);printf(">>>");
			}
		}
		else if(a==80)//down arrow
		{
			if(count==val-1)
			{
				move(68,y+2*count);printf("   ");
				count=0;
				move(68,y+2*count);printf(">>>");
			}
			else
			{
				move(68,y+2*count);printf("   ");
				count++;
				move(68,y+2*count);printf(">>>");
			}
		}
		else if(a==13)
		{
			return count;
		}
	}
}
//Function to display institution name on top of every page
void head()
{
	move(85,7);
	puts(iname);
	move(30,9);
	for(int i=30;i<170;i++)
	{
		move(i,9);
		printf("%c",205);
	}
}
//Function to read and save institution name
void institute()
{
	draw_rect2();
	move(80,17);
	printf("Enter institute name : ");
	scanf("%[^\n]",iname);
	FILE *fp;
	fp=fopen("institute.txt","w");
	fwrite(&iname,sizeof(iname),1,fp);
	fclose(fp);
	move(60,19);
	printf("Note :This will be default username and password for logging in to register");
	move(60,21);
	printf("Press any key to continue");
	getch();
	fflush(stdin);
}
//Function to provide protection while registering an user
void default_passcheck()
{
	system("cls");
	Sleep(100);
	draw_rect(0);
	draw_rect2();
	head();
	move(70,17);
	printf("DEFAULT PASSCHECK");
	move(70,19);
	printf("Enter username : ");
	log a;
	move(70,21);
	printf("Enter password : ");
	fflush(stdin);
	move(87,19);
	scanf(" %[^\n]",a.username);
	move(87,21);
	int i=0,x;
	char c;
	while(1)
	{
		x=87+i;
		move(x,21);
		c=getch();
		if(c==13)
		{
			break;
		}
		else if(c==8)
		{
			i--;
			a.password[i]='\0';
			x=x-1;
			move(x,21);printf(" ");
			continue;
		}
		a.password[i]=c;
		printf("*");
		i++;
	}
	if(!strcmp(iname,a.username)&&!strcmp(a.password,iname))
	{
		Sleep(100);
		register_user();
	}
	else
	{
		move(70,23);
		printf("Wrong username or password press 1 to re-enter or 2 to go back");
		int ch;
		move(70,25);
		printf("Enter : ");
		move(78,25);
		fflush(stdin);
		scanf("%d",&ch);
		Sleep(100);
		if(ch==1)
		{
			default_passcheck();
		}
		else
		{
			menu2();
		}	
	}
}
//Function to display home page
void menu1()
{
	system("cls");
	draw_rect(0);
	draw_rect2();
	head();
	move(70,15);
	printf("HOME");
	move(70,17);
	printf("CHOOSE AN OPTION");
	move(72,19);
	printf("%c%c%c Administrator",176,176,176);
	move(72,21);
	printf("%c%c%c Student",176,176,176);
	move(72,23);
	printf("%c%c%c Exit",176,176,176);
	choice=option(3,19)+1;
	switch(choice)
	{
		case 1:menu2();
			break;
		case 2:menu3();			
			break;
		case 3:system("cls");
			exit(0);
	}
	
}
//Function to display page with register,login options
void menu2()
{
	system("cls");
	draw_rect(0);
	draw_rect2();
	head();
	move(70,15);
	printf("CHOOSE AN OPTION");
	move(72,17);
	printf("%c%c%c Register_user",177,177,177);
	move(72,19);
	printf("%c%c%c Login",177,177,177);
	move(72,21);
	printf("%c%c%c go back",177,177,177);
	int ch=option(3,17)+1;
	switch(ch)
	{
		case 1:default_passcheck();
			break;
		case 2:login();			
			break;
		case 3:menu1();
			break;
	}
}
//Function to display page with login option for stundet
void menu3()
{
	system("cls");
	draw_rect(0);
	draw_rect2();
	head();
	move(70,15);
	printf("CHOOSE AN OPTION");
	move(72,17);
	printf("%c%c%c Login",177,177,177);
	move(72,19);
	printf("%c%c%c go back",177,177,177);
	int ch=option(2,17)+1;
	switch(ch)
	{
		case 1:login();			
			break;
		case 2:menu1();
			break;
	}
}
//Function to register a new user
void register_user()
{
	system("cls");
	draw_rect(0);
	draw_rect2();
	head();
	int value,found=0;
	value=ask_type();//calling function to ask user for type of user to be registered
	if(value==3)
	{
		menu2();//returning to previous page
	}
	log a,b;
	move(70,15);
	printf("USER REGISTER");
	move(70,17);
	printf("Enter User_Id : ");
	move(70,19);
	printf("Enter Password : ");
	move(86,17);
	fflush(stdin);
	scanf("%[^\n]",a.username);//reading username form user
	fflush(stdin);
	move(87,19);
	scanf("%[^\n]",a.password);//reading password from user
	fflush(stdin);
	FILE *fp,*fpw;
	//opening files
	if(value==1)
	{
		fp=fopen("Admin_Login.bin","rb");
		fpw=fopen("Admin_Login.bin","ab");
	}
	else if(value==2)
	{
		fp=fopen("Student_Login.bin","rb");
		fpw=fopen("Student_Login.bin","ab");
	}
	while(fread(&b,sizeof(b),1,fp))
	{
		if(!strcmp(a.username,b.username))
		{
			found=1;
		}
	}
	if(found==1)
	{
		move(70,20);
		printf("User already registered");
	}
	else
	{
		fwrite(&a,sizeof(a),1,fpw);//writing user login credentials into file
		move(70,20);
		printf("USER REGISTERED SUCCESSFULLY");
	}
	fclose(fp);
	fclose(fpw);
	move(70,23);
	printf("Press 1 to register another user or 2 to exit");
	int n;
	move(120,23);
	fflush(stdin);
	scanf("%d",&n);
	if(n==1)
	{
		register_user();
	}
	else if(n==2)
	{
		menu2();
	}
}
//Function to ask type of user: admin or student
int ask_type()
{
	system("cls");
	draw_rect(0);
	draw_rect2();
	head();
	move(70,17);
	printf("CHOOSE AN OPTION");
	move(72,19);
	printf(" Register Administrator");
	move(72,21);
	printf(" Register Student");
	move(72,23);
	printf(" Go Back");
	int ch=option(3,19)+1;
	system("cls");
	draw_rect(0);
	draw_rect2();
	head();
	return ch;
}
//Function to login user
void login()
{
	system("cls");
	draw_rect(0);
	draw_rect2();
	head();
	move(70,15);
	printf("USER LOG_IN");
	log a;
	move(70,17);
	printf("Enter User_Id : ");
	move(70,19);
	printf("Enter Password : ");
	move(86,17);
	fflush(stdin);
	scanf("%[^\n]",a.username);//reading username from user
	move(87,19);
	char ch;
	int i=0,x;
	//reading password from user
	while(1)
	{
		x=87+i;
		move(x,19);
		ch=getch();
		if(ch==13)
		{
			break;
		}
		else if(ch==8)
		{
			i--;
			a.password[i]='\0';
			x=x-1;
			move(x,19);printf(" ");
			continue;
		}
		a.password[i]=ch;
		printf("*");
		i++;
	}
	FILE *fp;
	log b;
	int k=0;
	if(choice==1)
	{
		fp=fopen("Admin_Login.bin","rb");
	}
	else if(choice==2)
	{
		fp=fopen("Student_Login.bin","rb");
	}
	while(fread(&b,sizeof(log),1,fp))//reading credentials from the data file
	{
		if(!(strcmp(a.username,b.username))&&!(strcmp(a.password,b.password)))//comparing credentials entered with that in file
		{
			move(70,21);
			printf("User identified");
			fclose(fp);
			fflush(stdin);
			Sleep(1000);
			if(choice==1)
			{
				menu4(a.username);//redirecting to admin menu page if user is admin and entered correct login credentials
				return;
			}
			else if(choice==2)
			{
				menu5(a.username);////redirecting to student menu page if user is student and entered correct login credentials
				return;
			}
		}
		
	}
	fclose(fp);
	move(70,21);
	//if no details found
	printf("User unidentified");
	move(70,23);
	printf("Enter1 to re-try or 2 to goback");
	int ch1;
	move(70,25);
	printf("Enter : ");
	move(78,25);
	fflush(stdin);
	scanf("%d",&ch1);
	fflush(stdin);
	if(ch1==1)
	{
		login();
	}
	else
	{
		if(choice==1)
		{
			menu2();
		}
		else if(choice==2)
		{
			menu3();
		}
	}
}
//Function to display menu with various record management facilities for admin
void menu4(char *username)
{
	system("cls");
	draw_rect(0);
	head();
	int ch;
	move(70,15);
	printf("MAIN MENU ");
	move(72,17);
	printf("CHOOSE AN OPTION");
	move(72,19);
	printf("%c%c%c Add Student",178,178,178);
	move(72,21);
	printf("%c%c%c View Student",178,178,178);
	move(72,23);
	printf("%c%c%c Modify Student",178,178,178);
	move(72,25);
	printf("%c%c%c Delete Student",178,178,178);
	move(72,27);
	printf("%c%c%c Add/Modify Marks",178,178,178);
	move(72,29);
	printf("%c%c%c Delete Marks",178,178,178);
	move(72,31);
	printf("%c%c%c Change Password",178,178,178);
	move(72,33);
	printf("%c%c%c GO to back",178,178,178);
	ch=option(8,19)+1;
	//calling function based on the choice selected
	switch(ch)
	{
		case 1:add_student(username);
			break;
		case 2:fflush(stdin);
			char id[20];
			system("cls");
			draw_rect2();
			move(70,19);printf("Enter roll no : ");
			move(100,19);
			scanf("%[^\n]",id);
			view_student(username,id);
			break;
		case 3:modify_student(username);
			break;
		case 4:delete_student(username);
			break;
		case 5:add_modify_marks(username);
			break;
		case 6:delete_marks(username);
			break;
		case 7:change_password(username);
			break;
		case 8:menu2();
			break;
	}
}
//Function to display menu for student with options to view details or change password
void menu5(char *username)
{
	system("cls");
	draw_rect(0);
	head();
	int ch;
	move(70,15);
	printf("MAIN MENU");
	move(70,17);
	printf("===============================================================================");
	move(72,20);
	printf("CHOOSE AN OPTION");
	move(72,22);
	printf("%c%c%c View Records",178,178,178);
	move(72,24);
	printf("%c%c%c Change Password",178,178,178);
	move(72,26);
	printf("%c%c%c Go Back",178,178,178);
	move(70,29);
	printf("===============================================================================");
	ch=option(3,22)+1;
	//calling required function based on choice selected
	switch(ch)
	{
		case 1 :view_student(username,username);
			break;
		case 2 :change_password(username);
			break;
		case 3 :menu3();
			break;
	}
	
}
//Function to validate name
int validate_name(char *name)
{
	int validate = 1;
    	int length = 0;
    	int index;
    	length = strlen(name);
    	for(index = 0; index <length ; index++)
    	{
        	if(!(isalpha(name[index])) && (name[index] != '\n') && (name[index] != ' '))
        	{
        	    validate = 0;
        	    break;
        	}
    	}
    	return validate;
}
//Function to check whether date entered is in correct format
int validate_date(Date *date_given)
{
	if(date_given->month>12 || date_given->month<=0)
	{
		return 0;
	}
	if(date_given->year<=0 || date_given->year>9999)
	{
		return 0;
	}
	if(date_given->day>31 || date_given->day<=0)
	{
		return 0;
	}
	if(date_given->month==2)
	{
		if((date_given->year%400==0) || ((date_given->year%4==0) && (date_given->year%100!=0)))
		{
			if(date_given->day>28)
			{
				return 0;
			}
		}
		else
		{
			if(date_given->day>29)
			{
				return 0;
			}
		}
	}
	if(date_given->month==4 || date_given->month==6 || date_given->month==9 || date_given->month==11)
	{
		if(date_given->day>30)
		{
			return 0;
		}
	}
	return 1;
}
//Function to read student details from user
student details()
{
	student s;
	move(70,13); 
	printf("Enter Roll no : ");
	move(70,15);
	printf("Enter Student name : ");
	move(70,17);
	printf("Enter Gender : ");
	move(70,19);
	printf("Enter Father name : ");
	move(70,21);
	printf("Enter mother name : ");
	move(70,23);
	printf("Enter Address : ");
	move(70,25);
	printf("Enter mobile number : ");
	move(70,27);
	printf("Enter Date of Birth(dd/mm/yyyy) : ");
	move(70,29);
	printf("Enter Date of Joininh(dd/mm/yyyy) : ");
	move(70,31);
	printf("Branch : ");
	move(70,33);
	printf("Section : ");
	move(70,35);
	printf("Academic Year : ");
	move(86,13);
	fflush(stdin);
	scanf("%[^\n]",s.rollno);//reading roll number
	fflush(stdin);
	move(91,15);
	//reading name
	scanf("%[^\n]",s.name);
	while(!validate_name(s.name))
	{
		move(91,15);
		printf("Invalid name please re-enter");
		Sleep(1000);
		move(91,15);
		printf("                            ");
		move(91,15);
		fflush(stdin);
		scanf("%[^\n]",s.name);
	}
	move(91,17);
	fflush(stdin);
	scanf("%[^\n]",s.gender);//reading gender from user
	fflush(stdin);
	move(91,19);
	fflush(stdin);
	//reading father name and validating
	scanf("%[^\n]",s.father_name);
	while(!validate_name(s.father_name))
	{
		move(91,19);
		printf("Invalid name please re-enter");
		Sleep(1000);
		move(91,19);
		printf("                            ");
		move(91,19);
		fflush(stdin);
		scanf("%[^\n]",s.father_name);
	}
	move(91,21);
	fflush(stdin);
	//reading mother name and validating
	scanf("%[^\n]",s.mother_name);
	while(!validate_name(s.mother_name))
	{
		move(91,21);
		printf("Invalid name please re enter");
		Sleep(1000);
		move(91,21);
		printf("                            ");
		move(91,21);
		fflush(stdin);
		scanf("%[^\n]",s.mother_name);
	}
	move(87,23);
	fflush(stdin);
	scanf("%[^\n]",s.address);//reading address
	move(92,25);
	fflush(stdin);
	scanf("%[^\n]",s.mobile_no);//reading mobile number
	move(106,27);
	fflush(stdin);
	//reading date of birth
	scanf("%d/%d/%d",&s.date_of_birth.day,&s.date_of_birth.month,&s.date_of_birth.year);
	while(!validate_date(&s.date_of_birth))
	{
		move(106,27);
		printf("Enter valid date of birth");
		Sleep(1000);
		move(106,27);
		printf("                            ");
		move(106,27);
		fflush(stdin);
		scanf("%d/%d/%d",&s.date_of_birth.day,&s.date_of_birth.month,&s.date_of_birth.year);
	}
	move(106,29);
	fflush(stdin);
	//reading date of joining
	scanf("%d/%d/%d",&s.date_of_joining.day,&s.date_of_joining.month,&s.date_of_joining.year);
	while(!validate_date(&s.date_of_joining))
	{
		move(106,29);
		printf("Enter valid date of joining");
		Sleep(1000);
		move(106,29);
		printf("                            ");
		move(106,29);
		fflush(stdin);
		scanf("%d/%d/%d",&s.date_of_joining.day,&s.date_of_joining.month,&s.date_of_joining.year);
	}
	move(79,31);
	fflush(stdin);
	scanf("%[^\n]",s.branch);//reading branch
	move(82,33);
	fflush(stdin);
	scanf("%[^\n]",s.section);//reading section
	move(90,35);
	fflush(stdin);
	scanf("%d",&s.academic_year);//reading academic year
	fflush(stdin);
	return s;
}
//Function to add student details read into the data file
void add_student(char *username)
{
	system("cls");
	draw_rect(0);
	head();
	move(21,38);draw_line();
	int status;
	student s,t;
	move(70,11);
	printf("ADD STUDENT RECORDS ");
	s=details();
	int found=0;
	FILE *fp;
	char file_name[30];
	fp=fopen("Student.bin","rb");
	while(fread(&t,sizeof(t),1,fp))
	{
		if(!strcmp(t.rollno,s.rollno))//checking if student details are already present or not
		{
			found=1;
		}
	}
	fclose(fp);
	if(found==1)//if records already present
	{
		move(70,40);
		printf("Records already present");
	}
	else
	{
		fp=fopen("Student.bin","ab+");//writing records into file
		fwrite(&s,sizeof(s),1,fp);
		move(70,40);
		printf("details added successfully");
	}
	fflush(stdin);
	fclose(fp);
	move(70,43);
	printf("Press any key to go back");
	move(96,43);
	getch();
	menu4(username);
}
//Function to view student details
void view_student(char *username,char *roll_no)

{
	system("cls");
	head();
	char branch[6];
	int found=0,extra_length=0;
	student s;
	move(70,11);
	printf("STUDENT DETAILS");
	fflush(stdin);
	FILE *fp;
	fp=fopen("Student.bin","rb");
	while(fread(&s,sizeof(s),1,fp))
	{
		if(!strcmp(s.rollno,roll_no))//checking whether student roll number entered is present in database or not
		{
			move(80,13);
			printf("Record found");
			move(40,15);
			//printing student details on screen
			printf("-----------------------------------------------------------------------------------------------------------------");
			move(30,17);printf("Roll no : %s",s.rollno);
			move(70,17);printf("Student Name : %s",s.name);
			move(110,17);printf("Gender : %s",s.gender);
			move(21,18);draw_line();
			move(30,19);printf("Father name : %s",s.father_name);
			move(70,19);printf("Mother name : %s",s.mother_name);
			move(110,19);printf("Phone no. : %s",s.mobile_no);
			move(21,20);draw_line();
			move(30,21);printf("Address : %s",s.address);
			move(70,21);printf("Date of birth : %d/%d/%d",s.date_of_birth.day,s.date_of_birth.month,s.date_of_birth.year);
			move(110,21);printf("Date of joining : %d/%d/%d",s.date_of_joining.day,s.date_of_joining.month,s.date_of_joining.year);
			move(21,22);draw_line();
			move(30,23);printf("Branch  : %s",s.branch);
			move(70,23);printf("Section : %s",s.section);
			move(110,23);printf("Academic Year : %d",s.academic_year);
			FILE *fpm;
			marks m;
			fpm=fopen("Marks.bin","rb");
			int ca;
			while((ca=fread(&m,sizeof(m),1,fpm))!=0)
			{
				if(!strcmp(m.rollno,roll_no))//checking whether marks of students are added
				{
					move(21,25);draw_line2();
					move(22,27);printf("MARKS SHEET :");
					move(24,29);printf("SUB");
					move(38,29);printf("MAX MARKS");
					move(52,29);printf("MARKS SCORED");
					move(100,29);printf("%c",196);
					for(int i=0;i<m.no_of_subjects;i++)
					{
						move(24,31+2*i);
						printf("%s",m.sub[i]);
						move(38,31+2*i);
						printf("%d",m.max_score[i]);
						move(54,31+2*i);
						printf("%d",m.score[i]);
						move(100,31+2*i);
						printf("%c",196);
					}
					extra_length=m.no_of_subjects;
					draw_box(21,28,extra_length,3);
					found++;
					break;
				}
			}
			fclose(fpm);
			found++;
			break;
		}
	}
	draw_rect(extra_length);
	fclose(fp);
	if(found==0)
	{
		move(70,17);
		printf("No records found");
	}
	else if(found==1)
	{
		move(70,31);
		printf("No marks found");
	}
	move(21,45+extra_length);
	draw_line();
	move(70,46.5+extra_length);
	printf("Press any key to go back");
	getch();
	fflush(stdin);
	if(choice==1)
	{
		menu4(username);
	}
	else if(choice==2)
	{
		menu5(roll_no);
	}
}
//Function to change password of user with parameter as username of respective user
void change_password(char *username)
{
	system("cls");
	draw_rect(0);
	draw_rect2();
	head();
	log a,b;
	char filename[20]="";
	move(70,15);
	printf("PASSWORD RESET");
	strcpy(b.username,username);
	move(70,17);
	printf("Enter New password : ");
	fflush(stdin);
	move(92,17);
	fflush(stdin);
	scanf("%[^\n]",b.password);//reading password from user
	fflush(stdin);
	FILE *fp,*fp2;
	//opening file based on user type
	if(choice==1)
	{
		strcat(filename,"Admin_Login.bin");
	}
	else if(choice==2)
	{
		strcat(filename,"Student_Login.bin");
	}
	fp=fopen(filename,"ab+");
	fp2=fopen("tempp.bin","ab+");
	while(fread(&a,sizeof(a),1,fp))
	{
		if(strcmp(a.username,b.username)!=0)//checking whether user is registered or not and if user is not found
		{
			fwrite(&a,sizeof(a),1,fp2);
		}
		else
		{
			fwrite(&b,sizeof(b),1,fp2);//writing new credentials if user is found
		}
	}
	fclose(fp);
	fclose(fp2);
	move(70,19);
	printf("Password updated successfully");
	fflush(stdin);
	//removing old file and renaming new file created with old file name
	remove(filename);
	rename("tempp.bin",filename);
	move(70,21);
	printf("Press any key to go back");
	getch();
	fflush(stdin);
	if(choice==1)
	{
		fflush(stdin);
		menu4(username);
	}
	else if(choice==2)
	{
		fflush(stdin);
		menu5(username);
	}
}
//Function to delete student records
void delete_student(char *username)
{
	system("cls");
	draw_rect(0);
	draw_rect2();
	head();
	fflush(stdin);
	char id[20];
	move(70,15);
	printf("STUDENT RECORD DELETION");
	move(70,17);
	printf("Enter roll number of student : ");
	move(100,17);
	fflush(stdin);
	scanf("%[^\n]",id);//reading roll number of the student from user
	fflush(stdin);
	student s;
	int found=0;
	FILE *fp,*fptemp;
	//opening temporary and original files
	fp=fopen("Student.bin","rb");
	fptemp=fopen("temp.bin","ab");
	while(fread(&s,sizeof(s),1,fp))
	{
		if(strcmp(id,s.rollno)!=0)//comparing with data in file based on roll no
		{
			fwrite(&s,sizeof(s),1,fptemp);
		}
		else
		{
			found=1;
		}
	}
	fclose(fp);
	fclose(fptemp);
	fflush(stdin);
	remove("Student.bin");
	rename("temp.bin","Student.bin");
	//deleting records of marks
	marks m;
	FILE *fpm,*fmtemp;
	fpm=fopen("Marks.bin","rb");
	fmtemp=fopen("tempm.bin","ab");
	while(fread(&m,sizeof(m),1,fpm))
	{
		if(strcmp(m.rollno,id)!=0)
		{
			fwrite(&m,sizeof(m),1,fmtemp);
		}
		else
		{
			found=1;
		}
	}
	fclose(fpm);
	fclose(fmtemp);
	remove("Marks.bin");
	rename("tempm.bin","Marks.bin");
	log a;
	FILE *fpl,*fltemp;
	fpl=fopen("Student_Login.bin","rb");
	fltemp=fopen("templ.bin","ab");
	while(fread(&a,sizeof(a),1,fpl))
	{
		if(strcmp(a.username,id)!=0)
		{
			fwrite(&a,sizeof(a),1,fltemp);
		}
		else
		{
			found=1;
		}
	}
	fclose(fpl);
	fclose(fltemp);
	//deleting login credential records
	remove("Student_Login.bin");
	rename("templ.bin","Student_Login.bin");
	if(found==1)
	{
		move(70,19);
		printf("Records deleted successfully");
	}
	else
	{
		move(70,19);
		printf("No records found/problem in deleting records");
	}
	fflush(stdin);
	move(70,22);
	printf("Press any key to go back");
	getch();
	fflush(stdin);
	menu4(username);
}
//Function to modify student records
void modify_student(char *username)
{
	system("cls");
	draw_rect(0);
	head();
	fflush(stdin);
	char id[20];
	move(70,13);
	printf("STUDENT DETAILS MODIFICATION");
	move(70,15);
	printf("Enter Student roll number : ");
	move(100,15);
	fflush(stdin);
	scanf("%[^\n]",id);//reading student roll number whose records are to be modified from user
	fflush(stdin);
	student s,curr;
	int found=0;
	FILE *fp,*fptemp;
	fp=fopen("Student.bin","rb");
	fptemp=fopen("temp.bin","ab");
	while(fread(&s,sizeof(s),1,fp))
	{
		if(strcmp(s.rollno,id)!=0)//checking whether student is added or not
		{
			fwrite(&s,sizeof(s),1,fptemp);//if stdeunt not found copying details into temporary file
		}
		else//when student found then asking to enter new details
		{
			move(50,16);printf("------------------------------------------------------------------------------------------");
			move(70,17);
			printf("Enter details and same details if no modification");
			strcpy(curr.rollno,s.rollno);
			move(50,19);
			printf("Name : %s",s.name);
			move(80,19);
			printf("Enter Name : ");
			move(105,19);
			fflush(stdin);
			scanf("%[^\n]",curr.name);
			fflush(stdin);
			move(50,21);
			fflush(stdin);
			printf("Father Name : %s",s.father_name);
			move(80,21);
			printf("Enter Father Name : ");
			move(105,21);
			scanf("%[^\n]",curr.father_name);
			fflush(stdin);
			move(50,23);
			printf("Mother Name : %s",s.mother_name);
			move(80,23);
			printf("Enter Mother Name : ");
			move(105,23);
			fflush(stdin);
			scanf("%[^\n]",curr.mother_name);
			fflush(stdin);
			move(50,25);
			printf("Address : %s",s.address);
			move(80,25);
			printf("Enter Address");
			move(105,25);
			fflush(stdin);
			scanf("%[^\n]",curr.address);
			fflush(stdin);
			move(50,27);
			printf("Phone no. : %s",s.mobile_no);
			move(80,27);
			printf("Enter phone no : ");
			move(105,27);
			scanf("%[^\n]",curr.mobile_no);
			fflush(stdin);
			move(50,29);
			printf("Date Of Birth : %d/%d/%d",s.date_of_birth.day,s.date_of_birth.month,s.date_of_birth.year);
			move(80,29);
			printf("Enter date of birth : ");
			move(105,29);
			fflush(stdin);
			scanf("%d/%d/%d",&curr.date_of_birth.day,&curr.date_of_birth.month,&curr.date_of_birth.year);
			fflush(stdin);
			move(50,31);
			printf("Date Of Joining : %d/%d/%d",s.date_of_joining.day,s.date_of_joining.month,s.date_of_joining.year);
			move(80,31);
			printf("Enter date of joining : ");
			move(105,31);
			fflush(stdin);
			scanf("%d/%d/%d",&curr.date_of_joining.day,&curr.date_of_joining.month,&curr.date_of_joining.year);
			fflush(stdin);
			move(50,33);
			printf("Branch : %s",s.branch);
			move(80,33);
			printf("Enter Branch : ");
			move(105,33);
			fflush(stdin);
			scanf("%[^\n]",curr.branch);
			fflush(stdin);
			move(50,35);
			printf("Section : %s",s.section);
			move(80,35);
			printf("Enter section : ");
			move(105,35);
			scanf("%[^\n]",curr.section);
			fflush(stdin);
			move(50,37);
			printf("Academic year : %d",s.academic_year);
			move(80,37);
			printf("Enter Academic year : ");
			move(105,37);
			fflush(stdin);
			scanf("%d",&curr.academic_year);
			fflush(stdin);
			fwrite(&curr,sizeof(curr),1,fptemp);//writing new details into file
			fflush(stdin);
			found++;

		}
	}
	fclose(fp);
	fclose(fptemp);
	//removing and renaming files
	remove("Student.bin");
	rename("temp.bin","Student.bin");
	if(found==0)
	{
		move(70,20);
		printf("No records found to modify");
	}
	else
	{
		move(50,38);printf("-----------------------------------------------------------------------------------------------------");
		move(70,40);printf("Records modified successfully");
	}
	move(70,42);
	printf("Press any key to go back");
	getch();
	fflush(stdin);
	menu4(username);
}
//Function to add and modify marks of student
void add_modify_marks(char *username)
{
	system("cls");
	draw_rect(0);
	head();
	fflush(stdin);
	char id[20];
	move(70,13);
	printf("STUDENT MARKS ADDITION/MODIFICATION");
	move(70,15);
	printf("Enter Student roll number : ");
	move(100,15);
	fflush(stdin);
	scanf("%[^\n]",id);//reading roll number of student from user
	fflush(stdin);
	marks m,curr;
	student s;
	int found=0;
	FILE *fpm,*fptemp,*fp;
	//opening files
	fp=fopen("Student.bin","rb");
	fpm=fopen("Marks.bin","ab+");
	while(fread(&s,sizeof(s),1,fp))
	{
		if(!strcmp(s.rollno,id))
		{
			while(fread(&m,sizeof(m),1,fpm))//checking whether student is registered
			{
				if(strcmp(id,m.rollno)==0)//if student  not found
				{
					found=1;
					
				}
				else
				{
					found=0;
				}
			}
			if(found==0)//if student  not found
			{
				strcpy(m.rollno,id);
				m.no_of_subjects=0;
				fwrite(&m,sizeof(m),1,fpm);//writing details into file
			}
			found=1;
		}
	}
	fclose(fp);
	fclose(fpm);
	if(found==0)
	{
		move(70,20);
		printf("No records found");
	}
	else//if student found
	{
	    //opening files
		fpm=fopen("Marks.bin","rb");
		fptemp=fopen("tempm.bin","ab");
		while(fread(&m,sizeof(m),1,fpm))
		{
			if(strcmp(id,m.rollno)!=0)//comparing stdeunt roll no with those in file
			{
				fwrite(&m,sizeof(m),1,fptemp);//writing into file if no student found
			}
			else
			{
			    //if student found then asking user to choose an option to modify a specific subject's marks or add a subject
				move(50,16);printf("-------------------------------------------------------------------------------");
				move(70,17);printf("Choose a subject");
				strcpy(curr.rollno,m.rollno);
				curr.no_of_subjects=m.no_of_subjects;
				int i;
				while(1)
				{
					for(i=0;i<curr.no_of_subjects;i++)
					{
						move(50,19+i);
						printf("%d.%s",i+1,m.sub[i]);
					} 
					move(50,19+i);
					printf("%d.Add a subject",i+1);
					int option,sub_marks,max_marks;
					char sub_name[20];
					move(50,19+i+2);
					printf("Enter : ");
					fflush(stdin);
					scanf("%d",&option);
					while(option>i+1)//if option chosen is not present
					{
						move(58,19+i+2);printf("!!!Inavlid option please try again");
						Sleep(1000);
						move(58,19+i+2);printf("                                  ");
						move(58,19+i+2);
						fflush(stdin);
						scanf("%d",&option);
					}
					if(option==i+1)//add subject marks
					{
						move(100,19);printf("Enter subject name : ");
						move(125,19);
						fflush(stdin);
						scanf("%[^\n]",sub_name);
						fflush(stdin);
						move(100,21);printf("Enter maximum marks : ");
						move(125,21);
						scanf("%d",&max_marks);
						while(1)
						{
							move(100,23);printf("Enter marks scored : ");
							move(125,23);
							scanf("%d",&sub_marks);
							if(max_marks<sub_marks)
							{
								move(125,23);printf("Enter marks less than maximum marks");
								Sleep(1000);
								move(125,23);printf("                                   ");
							}
							else
							{
								break;
							}
						}
						m.no_of_subjects++;
						strcpy(m.sub[m.no_of_subjects-1],sub_name);
						m.max_score[m.no_of_subjects-1]=max_marks;
						m.score[m.no_of_subjects-1]=sub_marks;
						
					}
					else if(option<i+1)//modify subject marks
					{
						for(int j=1;j<=m.no_of_subjects;j++)
						{
							if(j==option)
							{
								move(100,19);printf("%s    : %d",m.sub[j-1],m.score[j-1]);
								move(100,21);printf("Enter new marks : ");
								move(120,21);
								fflush(stdin);
								int mark;
								scanf("%d",&mark);
								m.score[j-1]=mark;
							}
						}
					}
					for(int k=0;k<m.no_of_subjects;k++)
					{
						strcpy(curr.sub[k],m.sub[k]);
						curr.max_score[k]=m.max_score[k];
						curr.score[k]=m.score[k];
					}
					if(m.no_of_subjects>curr.no_of_subjects)
					{
						curr.no_of_subjects=m.no_of_subjects;
						strcpy(curr.sub[curr.no_of_subjects-1],m.sub[m.no_of_subjects-1]);
						curr.max_score[curr.no_of_subjects-1]=m.max_score[m.no_of_subjects-1];
						curr.score[curr.no_of_subjects-1]=m.score[m.no_of_subjects-1];
					}
					move(100,26);
					printf("Press 1 to modify or add marks and 2 to exit");
					move(100,28);printf("Enter choice : ");
					move(120,28);
					int chi;
					fflush(stdin);
					scanf("%d",&chi);
					fflush(stdin);
					if(chi==1)
					{
						move(50,19+i+2);printf("                                 ");
						for(int x=50;x<150;x++)
						{
							for(int y=19;y<30;y++)
							{
								move(x,y);printf(" ");
							}
						}
						continue;
					}
					else if(chi==2)
					{
						break;
					}
				}
				fwrite(&curr,sizeof(curr),1,fptemp);
				found++;
				break;
			}
		}
		fclose(fpm);
		fclose(fptemp);
		remove("Marks.bin");
		rename("tempm.bin","Marks.bin");
		move(50,38);printf("-----------------------------------------------------------------------------------------------------");
		move(70,40);printf("Records modified successfully");
	}
	move(70,42);
	printf("Press any key to go back");
	getch();
	fflush(stdin);
	menu4(username);
}
//Function to delete records of student marks
void delete_marks(char *username)
{
	system("cls");
	draw_rect(0);
	draw_rect2();
	head();
	fflush(stdin);
	char id[20];
	move(70,15);
	printf("STUDENT MARKS DELETION");
	move(70,17);
	printf("Enter roll number of student : ");
	move(100,17);
	fflush(stdin);
	scanf("%[^\n]",id);//reading student roll no. from user
	fflush(stdin);
	student s;
	int found=0;
	marks m;
	FILE *fpm,*fmtemp;
	//opening files
	fpm=fopen("Marks.bin","rb");
	fmtemp=fopen("tempm.bin","ab");
	while(fread(&m,sizeof(m),1,fpm))
	{
		if(strcmp(m.rollno,id)!=0)//checking whether student required is matching with the student in file and if no writing the student into file
		{
			fwrite(&m,sizeof(m),1,fmtemp);
		}
		else
		{
			found=1;
		}
	}
	fclose(fpm);
	fclose(fmtemp);
	//removing and renaming files
	remove("Marks.bin");
	rename("tempm.bin","Marks.bin");
	if(found==1)
	{
		move(70,19);
		printf("Records deleted successfully");
	}
	else
	{
		move(70,19);
		printf("No records found/problem in deleting records");
	}
	fflush(stdin);
	move(70,22);
	printf("Press any key to go back");
	getch();
	fflush(stdin);
	menu4(username);
}
//end of code