#include<iostream>
#include<fstream>
#include<iomanip>

using namespace std;



class student
{
	int idnum;
	char name[50];
	int classBehaviour,teacherBehaviour , adminstrationBehaviour;
	double per;
	char grade;
	void calculate();
public:
	void getdata();
	void showdata() const;
	void show_tabular() const;
	int getIDNum() const;
};


void student::calculate()
{
	per=(classBehaviour+teacherBehaviour+adminstrationBehaviour)/3.0;
	if(per>=9)
		grade='A+';
	else if(per<9 && per>=7.0)
		grade='A';
	else if(per<7.0 && per>=5.0)
		grade='B';
	else
		grade='C';
}

 void student::getdata()
{
	cout<<"\nEnter The Roll number of the Student ";
	cin>>idnum;
	cout<<"\n\nEnter Student's Name: ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nRate student's behaviour with classmates out of 10: ";
	cin>>classBehaviour;
	cout<<"\nRate student's behaviour with teachers out of 10: ";
	cin>>teacherBehaviour;
	cout<<"\nRate student's behaviour with adminstrators out of 10: ";
	cin>>adminstrationBehaviour;
	calculate();
}
void student::showdata() const
{
	cout<<"\Roll Number: "<<idnum;
	cout<<"\nName: "<<name;
	cout<<"\nStudent's behaviour with classmates: "<<classBehaviour;
	cout<<"\nStudent's behaviour with teachers: "<<teacherBehaviour;
	cout<<"\nStudent's behaviour with adminstrators: "<<adminstrationBehaviour;
	cout<<"\nOverall Behaviour: "<<per;
	cout<<"\nGrade: "<<grade;
	if(per>=7.5 && per<10.0){
	cout<<"\nStudent has a good character and is well behaved";}
   else if(per<7.5 && per>=5){
    cout<<"\nBetter attitude and behaviour expected...";}
    else{
        cout<<"\nStrict disciplinary actions are required.";}
    }

void student::show_tabular() const
{
	cout<<idnum<<setw(6)<<" "<<name<<setw(8)<<classBehaviour<<setw(10)<<teacherBehaviour<<setw(10)
	<<adminstrationBehaviour<<setw(20)<<per<<setw(10)<<grade<<endl;
}

int  student::getIDNum() const
{
	return idnum;
}

void SaveStudent();
void displayAll();
void Searchdisplay(int);
void modifyStudent(int);
void deleteStudent(int);
void DisplayClassResult();
void DisplayResult();




void write_student()
{
	student st;
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	st.getdata();
	outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
	outFile.close();
    	cout<<"\n\nStudent record Has Been Created ";
	cin.ignore();
	cin.get();
}


void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n========================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}


void display_sp(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.getIDNum()==n)
		{
	  		 st.showdata();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nrecord not exist";
	cin.ignore();
	cin.get();
}


void modify_student(int n)
{
	bool found=false;
	student st;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof() && found==false)
	{

		File.read(reinterpret_cast<char *> (&st), sizeof(student));
		if(st.getIDNum()==n)
		{
			st.showdata();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			st.getdata();
		    	int pos=(-1)*static_cast<int>(sizeof(st));
		    	File.seekp(pos,ios::cur);
		    	File.write(reinterpret_cast<char *> (&st), sizeof(student));
		    	cout<<"\n\n\t Record Updated";
		    	found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
	cin.ignore();
	cin.get();
}


void delete_student(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.getIDNum()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
}


void class_result()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
	cout<<"=============================================================================================\n";
	cout<<"R.No       Name      classBeh   teacherBeh   AdminBeh      overallBeh   Grade"<<endl;
	cout<<"=============================================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}


int main()
{
	char ch;
	int num;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2);
	do
	{
	system("cls");
	cout<<"\t\t\t\t\t\tSTUDENT BEHAVIOUR ANALYSIS";
	cout<<"\n\n\n\n\t################################################";
	cout<<"\n\n\t1.RECORD STUDENT BEHAVIOUR";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS BEHAVIOUR";
	cout<<"\n\n\t3.SEARCH STUDENT BEHAVIOUR ";
	cout<<"\n\n\t4.MODIFY STUDENT BEHAVIOUR";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
	cout<<"\n\n\t6. DISPLAY CLASS BEHAVIOUR";
	cout<<"\n\n\t7. EXIT";
	cout<<"\n\n\t############################################";
	cout<<"\n\n\tPlease Enter Your Choice (1-7): ";
	cout<<"\n\n\n\n\n\n\n\Developed by:-Coding Mates(Asha pun & Snehil)";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1':	write_student(); break;
	case '2':	display_all(); break;
	case '3':	cout<<"\n\n\tPlease Enter Student's Roll number: "; cin>>num;
				display_sp(num); break;
	case '4':	cout<<"\n\n\tPlease Enter Student's Roll number: "; cin>>num;
			modify_student(num);break;
	case '5':	cout<<"\n\n\tPlease Enter Student's Roll number: "; cin>>num;
			delete_student(num);break;
	case '6' :	class_result(); break;
	case '7':	exit(0);;
	default:	cout<<"\a";

    }
	}while(ch!='7');

	return 0;
}
