/*
   Objective: Banking System Management Project Assignment
   Author: Husain Dhariwala
   Created On: 09/10/21
   Modified On: 11/10/21
   Dependencies:None
   Reference: GeeksForGeeks, cplusplus.com, code-projects.org, programiz.com 
*/

#include <iostream>
#include <fstream>
#include<iomanip>
#include<ctime>

using namespace std;

class Bank{
   public:
      int accNo, balance;
      char name[30],accType;
      time_t start;
      void newAccount(){
         cout<<"\nEnter Account No. : ";
         cin>>accNo;
         cout<<"Enter Name of the Account holder : ";
         cin.ignore();
         cin.getline(name,50);
         //LOOP UNTIL CORRECT ACCOUNT TYPE ENTERED
         do{
            cout<<"Enter Account Type (C/S) : ";
            cin>>accType;
            accType=toupper(accType);
            if(!(accType=='S' || accType=='C')){
               cout<<"Wrong Input\n";
            }
         }while(!(accType=='S' || accType=='C'));
         cout<<"Enter The Initial amount : ";
         cin>>balance;
         //SAVING TIME OF ACCOUNT OPENING
         time(&start);
         cout<<"\n<---Account Created--->";
      }
};

void writeAccount(){
   Bank b;
   ofstream out;
   out.open("account.txt",ios::app);
   b.newAccount();
   out.write(reinterpret_cast<char *> (&b), sizeof(Bank));
	out.close();

}

void displayAll()
{
	Bank b;
	ifstream in;
	in.open("account.txt");
	if(!in)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"        ACCOUNT HOLDER LIST\n\n";

   cout<<"-------------------------------------"<<endl;
	cout<<"A/c No.        NAME           Balance"<<endl;
   cout<<"-------------------------------------"<<endl;
   //EXTRACTING ALL ACCOUNT DETAILS PRESENT 
	while(in.read(reinterpret_cast<char *> (&b), sizeof(Bank)))
	{
      cout<<setw(7)<<b.accNo<<setw(15)<<b.name<<setw(15)<<b.balance<<"\n";
	}
	in.close();
}

void deleteAccount(int n){
   bool flag=0;
   Bank b;
   ofstream out;
   ifstream in;
	in.open("account.txt");
   if(!in){
      cout<<"File not found";
   }else{
      //CREATING A TEMP FILE TO COPY ACCOUNTS EXCEPT THE ONE TO BE DELETED
      out.open("Temp.txt");
      while(in.read(reinterpret_cast<char *> (&b), sizeof(Bank)))
	{
      //CHECKING TO REJECT DELETED ACCOUNT
		if(b.accNo!=n)
		{
			out.write(reinterpret_cast<char *> (&b), sizeof(Bank));
		}else{
         flag=1;
      }
	}
   in.close();
	out.close();
   //SAVING TEMP FILE AS NEW ACCOUNT.TXT WITH DELETED ACCOUNT
	remove("account.txt");
	rename("Temp.txt","account.txt");
   if(flag){
      cout<<"\n\n<----Account Deleted---->\n";
   }else{
      cout<<"X---Account not there---X\n\n";
   }

   }
}

void withdraw(int n){
   int amt;
   bool flag=1;
   Bank b;
   fstream inout;
   inout.open("account.txt",ios::in|ios::out);
   if(!inout){
      cout<<"File Not Found";
   }else{
      while(inout.read(reinterpret_cast<char *> (&b), sizeof(Bank))){
         if(b.accNo==n){
            flag=0;
            cout<<"\nEnter the amount to withdraw: ";
            cin>>amt;
            //CHECKING IF ENTERED AMOUNT IS SUFFICIENT
            if(amt>b.balance){
               cout<<"<----Not enough amount in your account---->";
            }else{
               //UPDATING AMOUNT AFTER TRANSACTION
               b.balance-=amt;
               //UPDATING IN TXT FILE
               int pos=(-1)*static_cast<int>(sizeof(b));
               inout.seekp(pos,ios::cur);
               inout.write(reinterpret_cast<char *> (&b), sizeof(Bank));
               cout<<"\n<-- Amount Successfully Withdrawn -->\n\n";
            }
		   }
      }
   }
   //CHECKING IF ENTERED ACCOUNT NUMBER IS PRESENT
   if(flag){
      cout<<"X---Account not there---X\n\n";
   }
}

void deposit(int n){
   int amt;
   bool flag=1;
   Bank b;
   fstream inout;
   inout.open("account.txt",ios::in|ios::out);
   if(!inout){
      cout<<"File Not Found";
   }else{
      while(inout.read(reinterpret_cast<char *> (&b), sizeof(Bank))){
         if(b.accNo==n){
            cout<<"\nEnter the amount to deposit: ";
            cin>>amt;
            //UPDATING AMOUNT AFTER TRANSACTION
            b.balance+=amt;
            //UPDATING IN TXT FILE
            int pos=(-1)*static_cast<int>(sizeof(b));
			   inout.seekp(pos,ios::cur);
			   inout.write(reinterpret_cast<char *> (&b), sizeof(Bank));
            cout<<"\n<-- Amount Successfully Deposited -->\n\n";
            flag=0;
		   }
      }
   }
   //CHECKING IF ENTERED ACCOUNT NUMBER IS PRESENT
   if(flag){
      cout<<"X---Account not there---X\n\n";
   }
}

void checkAccount(int n){
   bool flag=1;
   Bank b;
   ifstream in;
	in.open("account.txt");
   if(!in){
      cout<<"File not found";
   }else{
      while(in.read(reinterpret_cast<char *> (&b), sizeof(Bank)))
	   {
		   if(b.accNo==n){
			   flag = 0;
		   }
	   }
      in.close();
      if(flag){
         cout<<"Account not there in bank....";
      }else{
         cout<<"Account present in bank....";
      }
   }
}

void retrieveDetails(int n){
   bool flag=1;
   Bank b;
   ifstream in;
	in.open("account.txt");
   if(!in){
      cout<<"File not found";
   }else{
      while(in.read(reinterpret_cast<char *> (&b), sizeof(Bank)))
	   {
		   if(b.accNo==n){
            cout<<"\n\nName: "<<b.name<<"\nBalance: "<<b.balance<<"\nType :";
            if(b.accType=='S'){
               cout<<"Savings Account\n";
            }else{
               cout<<"Current Account\n";
            }
			   flag = 0;
		   }
	   }
      in.close();
      if(flag){
         cout<<"Account not there in bank....";
      }
   }
}

void calcInterest(int n){
   bool flag=1;
   Bank b;
   ifstream in;
	in.open("account.txt");
   if(!in){
      cout<<"File not found";
   }else{
      while(in.read(reinterpret_cast<char *> (&b), sizeof(Bank)))
	   {
		   if(b.accNo==n){
            time_t finish;
            //TAKING CURRENT TIME
            time(&finish);
            //difftime TO FIND TIME PASSED AFTER CREATING ACCOUNT
            double timee = difftime(finish, b.start);
            //S.I = P*R*T/100
            //TIME IN INSECONDS SO CONVERTING IT INTO DAY [1Day = 86400Seconds]
            double interst = (b.balance*0.1*timee)/(100*86400);
            cout<<"\nName: "<<b.name<<"\nBalance: "<<b.balance;
            cout<<"\nAccout present since: "<<timee<<"seconds";
            cout<<"\n\n(*Taking seconds as reference and interest calculated 0.1% per day.)\n";
            cout<<"\n--------------------------------------------";
            cout<<"\nInterest amount until now: "<<interst <<"Rs";
            cout<<"\n--------------------------------------------\n";
			   flag = 0;
		   }
	   }
      in.close();
      if(flag){
         cout<<"Account not there in bank....";
      }
   }
}

int main() {
   int choice,acNum;
   //Do While Loop for doing transactions until required
   do{
      system("CLS");
      cout<<"\n-------------------------------\n";
      cout<<"---Banking System Management---\n";
      cout<<"-------------------------------\n";
      cout<<"\nSelect what you want to do:\n1.Add New Account\n2.Display All Accounts\n3.Delete Account\n4.Withdraw\n5.Deposit\n6.Check if account exist\n7.Retrieve Details\n8.Calculate Interest\n9.Exit\n";
      cin>>choice;
      switch (choice)
      {
         case 1:
            writeAccount();
            cout<<"\n\nPress Enter to Continue...";
            break;
         case 2:
            displayAll();
            cout<<"\nPress Enter to Continue...";
            break;
         case 3:
            cout<<"\nWrite account number to delete: ";
            cin>>acNum;
            deleteAccount(acNum);
            cout<<"\nPress Enter to Continue...";
            break;
         case 4:
            cout<<"\nWrite account number to withdraw: ";
            cin>>acNum;
            withdraw(acNum);
            cout<<"\nPress Enter to Continue...";
            break;
         case 5:
            cout<<"\nWrite account number to deposit: ";
            cin>>acNum;
            deposit(acNum);
            cout<<"\nPress Enter to Continue...";
            break;
         case 6:
            cout<<"\nWrite account number to check: ";
            cin>>acNum;
            checkAccount(acNum);
            cout<<"\nPress Enter to Continue...";
            break;
         case 7:
            cout<<"\nWrite account number to retrieve details: ";
            cin>>acNum;
            retrieveDetails(acNum);
            cout<<"\nPress Enter to Continue...";
            break;
         case 8:
            cout<<"\nWrite account number to calculate interest until now: ";
            cin>>acNum;
            calcInterest(acNum);
            cout<<"\nPress Enter to Continue...";
            break;
         case 9:
            cout<<"\n}-----Thank You for Banking-----{";
            cout<<"\nPress Enter to Exit";
            break;
         default:
            cout<<"X--Wrong Choice--X";
            cout<<"\nPress Enter to Continue...";
            break;
      }
      //TO HOLD SCREEN TILL ENTER IS PRESSED
      cin.ignore();
      cin.get();
   }while(choice!=9);
   return 0;
}