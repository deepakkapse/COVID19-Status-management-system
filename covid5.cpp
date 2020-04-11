//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class state
{
	int acno;
	char name[50];
	
	int confirm;
	int suspect;
	int death;
	int recover;
	
public:
	void create_state();	//function to get data from user
	void show_state() const;	//function to show data on screen
	void modify();	//function to add new data
	
	void updatecase(int,int,int,int);	//function to accept amount and add to new cases 
	
	void removecase(int);	//function to accept amount and subtract from suspected cases
	void report() const;	//function to show data in tabular format
	int retacno() const;	//function to return account number
	
	int retsuspectcase() const; //functio to return suspected case
	
};         //class ends here

void state::create_state()
{
	cout<<"\nEnter The stateno. : ";
	cin>>acno;
	
	cout<<"\nEnter The State : ";
	cin.ignore();
	cin.getline(name,50);
	
 
    
	
	
	
	
	cout<<"\n\nEnter The Suspected case : ";
	cin>>suspect;
	
	
	cout<<"\n\nEnter The Confirmed case :";
	cin>>confirm;
	
	
	
	cout<<"\n\nEnter The Death case :";
	cin>>death;
	
	
	cout<<"\n\nEnter The Recovered case :";
	cin>>recover;
	
	
	
	
	
	cout<<"\n\n\nState Created..";
}

void state::show_state() const
{
	
	cout<<"\nState. : "<<name;
	
	cout<<"\n\nSuspected case : "<<suspect;
	
	
	cout<<"\n\nConfirmed case : "<<confirm;
	
	
	
	cout<<"\n\nDeath case : "<<death;
	
	
	cout<<"\n\nRecovered case : "<<recover;
	
	
	
	
}


void state::modify()
{
	cout<<"\nState. : "<<name;
	cout<<"\n\nEnter The Suspected case : ";
	cin>>suspect;
	
	cout<<"\n\nModify The Confirmed case : ";
	cin>>confirm;
	
	
	cout<<"\n\nModify The Death case : ";
	cin>>death;
	
	cout<<"\n\nModify The Recovered case : ";
	cin>>recover;
	
	
	
	
	
}

	


void state::updatecase(int susp,int conf,int dth,int rec)
{
	suspect+=susp;
	confirm+=conf;
	death+=dth;
	recover+=rec;
	
}

	


void state::removecase(int neg)
{
	
	suspect-=neg;
}
	
void state::report() const
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<suspect<<setw(10)<<" "<<confirm<<setw(10)<<" "<<death<<setw(10)<<" "<<recover<<endl;
}
	
int state::retacno() const
{
	return acno;
}



int state::retsuspectcase() const
{
	return suspect;
}



//***************************************************************
//    	function declaration
//****************************************************************
void write_state();	//function to write record in binary file
void display_sp(int);	//function to display state details given by user
void modify_state(int);	//function to modify record of file
void delete_state(int);	//function to delete record of file
void display_all();		//function to display all state details
void deposit_withdraw(int, int); // function to add/remove cases for given state
void intro();	//introductory screen function

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************

int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW STATE";
		cout<<"\n\n\t02. ADD CASE";
		cout<<"\n\n\t03. REMOVE CASE";
		cout<<"\n\n\t04. STATE ENQUIRY";
		cout<<"\n\n\t05. ALL STATEWISE CASE LIST";
		cout<<"\n\n\t06. REMOVE STATE";
		cout<<"\n\n\t07. MODIFY STATE DETAILS";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_state();
			break;
		case '2':
			cout<<"\n\n\tEnter The State : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The State : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tEnter The State : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The State : "; cin>>num;
			delete_state(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The State : "; cin>>num;
			modify_state(num);
			break;
		 case '8':
			cout<<"\n\n\tThanks for using COVID19 STATUS MANAGEMENT SYSTEM";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
    }while(ch!='8');
	return 0;
}


//***************************************************************
//    	function to write in file
//****************************************************************

void write_state()
{
	state ac;
	ofstream outFile;
	outFile.open("state.dat",ios::binary|ios::app);
	ac.create_state();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(state));
	outFile.close();
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n)
{
	state ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("state.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nSTATE DETAILS\n";
    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(state)))
	{
		if(ac.retacno()==n)
		{
			ac.show_state();
			flag=true;
		}
	}
    inFile.close();
	if(flag==false)
		cout<<"\n\n state does not exist";
}


//***************************************************************
//    	function to modify record of file
//****************************************************************

void modify_state(int n)
{
	bool found=false;
	state ac;
	fstream File;
    File.open("state.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(state));
		if(ac.retacno()==n)
		{
			ac.show_state();
			cout<<"\n\nEnter The New Details of State"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(state));
			File.seekp(pos,ios::cur);
		    File.write(reinterpret_cast<char *> (&ac), sizeof(state));
		    cout<<"\n\n\t Record Updated";
		    found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_state(int n)
{
	state ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("state.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(state)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(state));
		}
	}
    inFile.close();
	outFile.close();
	remove("state.dat");
	rename("Temp.dat","state.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

//***************************************************************
//    	function to display all states deposit list
//****************************************************************

void display_all()
{
	state ac;
	ifstream inFile;
	inFile.open("state.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tCOVID19 AFFECTED STATE LIST\n\n";
	cout<<"==========================================================================================================\n";
	cout<<"A/c no.      NAME         SUSPECT       CONFIRM       DEATH      RECOVER \n";
	cout<<"===========================================================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(state)))
	{
		ac.report();
	}
	inFile.close();
}

//***************************************************************
//    	function to add and remove cases
//****************************************************************

void deposit_withdraw(int n, int option)
{
	
	int neg;
	int susp;
	int conf;
	int dth;
	int rec;
	bool found=false;
	state ac;
	fstream File;
    File.open("state.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(state));
		if(ac.retacno()==n)
		{
			ac.show_state();
			if(option==1)
			{
				cout<<"\n\n\tTO ADD NEW POSITIVE CASES ";
				
				cout<<"\n\nEnter The new Suspected cases";
				cin>>susp;
				
				cout<<"\n\nEnter The new Confirmed Positive cases";
				cin>>conf;
				
				cout<<"\n\nEnter The new Death cases";
				cin>>dth;
				
				cout<<"\n\nEnter The new Recovered cases";
				cin>>rec;
				
				ac.updatecase(susp,conf,dth,rec); //updating the new cases
			}
		    if(option==2)
			{
				cout<<"\n\n\tTO REMOVE NEGATIVE CASES ";
								
									
				cout<<"\n\nEnter The  Confirmed Negative cases";
				cin>>neg;
				int balance=ac.retsuspectcase()-neg;
				
				if(balance<0 )
				    cout<<"Improper value,Confirmed negative cases are greater than suspected case ";
				else
					ac.removecase(neg);	
		      }
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(state));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
    File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}


//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
	cout<<"\n\n\n\t\t\t\t\t\t\tWELCOME \n\n\n\t\t\t\t\t\t\t   TO";
	cout<<"\n\n\n\t\t\t\t\tCOVID19\tSTATUS\tMANAGEMENT\tSYSTEM";
	cout<<"\n\n\n\nMADE BY : your name";
	cout<<"\n\nSCHOOL : your school name";
	cin.get();
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************
