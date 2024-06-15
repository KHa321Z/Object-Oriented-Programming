// 23L-0700, 23L-0920

#include <iostream>
#include<fstream>
#include<cstdlib>
#include <time.h>
using namespace std;

class super
{

};

class AccType
{
    protected:
    int Withdrawlim;

    public:
    AccType(int lim)
    {
        Withdrawlim=lim;
    }
    int getlimit()
    {
        return Withdrawlim;
    }
    // user to check business client 


};

class Bronze:public AccType
{
    const int TranLimit = 100000;

    public:
    Bronze(): AccType(TranLimit)
    {

    }

};

class Gold:public AccType
{
    const int TranLimit = 500000;

    public:
    Gold(): AccType(TranLimit)
    {

    }

};

class Business:public AccType
{
    const int TranLimit = 20000000;

    public:
    Business(): AccType(TranLimit)
    {

    }

};

class Cards
{
    int cnum[16];
    int pin;
    public:
    Cards(int number[16], int p)
    {
        pin=p;
        for(int i=0;i<16;i++)
        cnum[i]= number[i];
    }

};

class User: public super
{
    protected:
    fstream userfile;
    string name, password, address, username;
    int balance;
    AccType *type= nullptr;    

    public:
    User(string na, string usern, string p,string add,int bal, int wd)
    {
        name= na;
        username= usern;
        password=p;
        balance=bal;
        address=add;
        if(wd<100000)
        type= new Bronze();
        else if (wd<500000)
        type= new Gold();
        else
        type= new Business();

        cout<<"User()\n";      
    }

    virtual void print()
    {
        cout<<"Client Details: "<<endl;
        cout<<"Name: "<<name<<endl<<"Address: "<<address<<endl;
    }

    string getname(){return name;}

    string getaddress(){return address;}

    string getusername(){return username;}
    
    string getpassword(){return password;}

    int getbalance(){return balance;}

    void deposit(int amt){balance+=amt;}

    void withdraw(int amt){balance-=amt;}
   
    int getlim(){return (*type).getlimit();}

    virtual ~User()
    {
        cout<<"~User() called"<<endl;
        
    }

};

class UserClient: public User
{
    
    //int balance; 
    string PhoneNum, CNIC;

    public:
    UserClient(bool create, string na,string add,string cnic, string username, string pass,string phone,int bal=0,int id=0,int wd=0): User(na, username,pass,add, bal, wd)
    {
        PhoneNum= phone;
        if(!create)
        //balance=bal;
        CNIC=cnic;
        cout<<"UserClient()\n";
        if(create)
        {
            balance=0;
        fstream userfile;
        userfile.open("users.txt", ios::app);
        if(userfile.is_open())
        userfile<<id<<", "<<name<<", "<<add<<", "<<cnic<<", "<<username<<", "<<pass<<", "<<PhoneNum<<", "<<balance<<endl;
        userfile.close();
        }

    }

    string getcnic(){return CNIC;}

    string getphone(){return PhoneNum;}
    
    void print()
    {
        User::print();
        cout<<"CNIC: "<<CNIC<<endl<<"Phone Number: "<<PhoneNum<<endl<<"Balance: "<<balance<<endl<<endl;
        //<<name<<CNIC<<endl;
    }

    virtual ~UserClient()
    {
        cout<<"~UserClient() called"<<endl;
    }
};

class CompanyClient: public User
{
    int taxnum, ID ;
    UserClient **compemp;

    public:
    CompanyClient(bool create, string na,string add, string username,string pass, int wd, int taxn, int id=0, int bal=0): User(na, username, pass, add,bal, wd)
    {
        taxnum=taxn;
        ID=id;
        cout<<"CompanyClient()\n";
        fstream company;
        if(create)
        {            
        company.open("CompanyDetails.txt",ios::app);
        company<<id<<", "<<name<<", "<<address<<", "<<taxnum<<", "<<username<<", "<<pass<<", "<<balance<<endl;
        company.close();
        }


    }

    UserClient** getemparray()
    {
        return compemp;
    }
    int gettax(){return taxnum;}

    void print()
    {
        User::print();
        cout<<"Username."<<username<<" pass."<<password<<endl;
        cout<<"Comapny ID: "<<ID<<endl<<"Tax Number: "<<taxnum<<endl<<"Balance: "<<balance<<endl<<endl;
    }
    
    void applyloan(int amt)
    {
        fstream loanfile;

        loanfile.open("Loan.txt", ios::app);

        loanfile<<ID<<","<<amt<<endl;

        loanfile.close();

    }

    int getid(){return ID ;}


};


class BankEmp: public super
{
    UserClient** allusers;//this array would be created and the data will be loaded once th e employee logs in
    CompanyClient **allcompany;
    string username, pass;
    int useracc, companyacc;
    void readline(fstream &userfile,string &userid, string &name,string &address,string &cnic, string &username, string &password,string &phonenum,int &bal)
    {
            getline(userfile, userid, ',');  userfile.ignore();        
            getline(userfile, name, ',');userfile.ignore();
            getline(userfile, address, ',');  userfile.ignore();        
            getline(userfile, cnic, ',');userfile.ignore();
            getline(userfile, username, ','); userfile.ignore();         
            getline(userfile, password, ',');userfile.ignore();
            getline(userfile, phonenum, ',');userfile.ignore();
            userfile>>bal;userfile.ignore();

    }

    void loadclients()
    {
        fstream userfile;
        userfile.open("users.txt", ios::in);
        useracc=0;
        string line;

        while( getline(userfile, line))
            useracc++;
        
        userfile.close();
        
        userfile.open("users.txt", ios::in);
        allusers= new UserClient*[useracc+1];
           for(int i=0;i<useracc;i++)
        {
            string userid, name, address, cnic, username, password, phonemnum;
            int bankbalance;
            readline(userfile, userid, name, address, cnic, username, password, phonemnum, bankbalance);


            *(allusers+i)= new UserClient(false, name, address, cnic, username, password,phonemnum, bankbalance, i+1);
    

        }
        userfile.close();
    }

    
    void loadcompany()
    {
        fstream userfile;
        userfile.open("CompanyDetails.txt", ios::in);
        companyacc=0;
        string line;
        while(getline(userfile, line))
            companyacc++;

        userfile.close();
        
        userfile.open("CompanyDetails.txt", ios::in);
        allcompany= new CompanyClient*[companyacc+1];
           for(int i=0;i<companyacc;i++)
        {
            string name, address, username, password;
            int companyid, balance, taxnum, withdrawlim;
            userfile>> companyid;  
            userfile.ignore();
            userfile.ignore();         
            getline(userfile, name, ',');userfile.ignore();
            getline(userfile, address, ',');  userfile.ignore(); 
            userfile>> taxnum;  
            userfile.ignore();userfile.ignore();  
            getline(userfile, username, ','); userfile.ignore();         
            getline(userfile, password, ',');userfile.ignore();
            userfile>>balance;userfile.ignore();
            //readline(userfile, userid, name, address, cnic, username, password, phonemnum, bankbalance);
            *(allcompany+i)= new CompanyClient(false, name, address, username, password, withdrawlim, taxnum,i+1, balance);   
            (*(allcompany+i))->print();
            cout<<endl;

        }
        userfile.close();


    }

    public:
    BankEmp(bool create, string u, string p)
    {
        if(create)
        {
        fstream empfile;
        empfile.open("admin.txt", ios::app);
        empfile<<u<<","<<p<<endl;
        empfile.close();
        }
        username= u, pass=p;
        loadclients();
        loadcompany();
    
    }

    UserClient* getclient(int index){return allusers[index];}

    CompanyClient*getcompany(int index){return allcompany[index];}

    void ViewAllUser()
    {
        cout<<"Total users: "<<useracc<<endl;
        for(int i=0;i<useracc;i++)
            allusers[i]->print();
        
    }

    void ViewAllComapnies()
    {
        cout<<"Total companies: "<<companyacc<<endl;
        for(int i=0;i<companyacc;i++)
            allcompany[i]->print();

    }

    // void ViewLoanRequests()
    // {
    //     fstream file;
    //     file.open("LoanApprovals.txt", ios::in);
    //     while(!file.eof())
    //     {
    //         int companyid, amount;
    //         string name;

    //         file>> companyid;
    //         file.ignore();
    //         getline(file, name, ',');
    //         file>>amount;
    //         file.ignore();           

            
    //         cout<<companyid<<", "<< name<<","<<amount <<endl;
    //         char approve;
    //         cout<<"Press 1 to approve and any other key to reject: ";
    //         cin>>approve;

    //     }
    //     file.close();
    // }


    void deposit(bool user, int amt, int clientindex)
    {
        if(user)
        {
        if((*allusers[clientindex]).getlim()<=amt)
        (*allusers[clientindex]).deposit(amt);
        else
        cout<<"Your account type does not allow this kind of transaction\n";  
        }

        else
        {
            if((*allcompany[clientindex]).getlim()<=amt)
                (*allcompany[clientindex]).deposit(amt);
            else  cout<<"Your account type does not allow this kind of transaction\n";

        }        
    }
    
    void withdraw(bool user, int amt, int clientindex)
    {
        if(user)
        {
            if(amt<=(*allusers[clientindex]).getbalance()&&(*allusers[clientindex]).getlim()<=amt)
                (*allusers[clientindex]).withdraw(amt);
            else cout<<"Your account type does not allow this kind of transaction\n";     
        }     
        else
        {
            if(amt<=(*allcompany[clientindex]).getbalance()&&(*allcompany[clientindex]).getlim()<=amt)
                (*allcompany[clientindex]).withdraw(amt);
            else cout<<"Your account type does not allow this kind of transaction\n"; 
        }
    }

    bool transfer(bool user, int amt,int clientindex, int recipientindex)
    {
        if(user)
        {
        if(amt<=(*allusers[clientindex]).getbalance()&&recipientindex<=useracc&&(*allusers[clientindex]).getlim()<=amt)//checking if the recipient exists and suffiecient balance
        {
            (*allusers[clientindex]).withdraw(amt);
            (*allusers[recipientindex]).deposit(amt);
            return true;
        }
        else {cout<<"Transfer failed\n";
        return false;}
        }     
        else{
        if(amt<=(*allcompany[clientindex]).getbalance()&&recipientindex<=useracc&&(*allcompany[clientindex]).getlim()<=amt)//checking if the recipient exists and suffiecient balance
        {
            (*allcompany[clientindex]).withdraw(amt);
            (*allusers[recipientindex]).deposit(amt);
            cout<<(*allusers[recipientindex]).getbalance();
            return true;
        }
        else {cout<<"Transfer failed\n";
        return false;}
        }
    }


    void cardallotment(bool user, int id)
    {
        srand(time(0));
        fstream file;
        int start;
        file.open("cards.txt", ios::app);
        if(user)
        start=1;
        else start= 2;
        file<<id<<", "<<start;

        for(int i=1;i<16;i++)
        {
            file<< rand()%10;
        }
        file<<endl;
 
        file.close();


    }


    void approveloans()
    {
        fstream file;
        file.open("Loan.txt", ios::in);
        int id, amt;

        while(file>>id)
        {
            file.ignore();
            file>>amt;
            file.ignore();
            cout<<"Company ID: "<<id<<" Amount: "<<amt<<endl;
            cout<<"Press 1 to approve loan or any other key to reject\n";
            char choice;
            cin>>choice;
            if(choice=='1')
            {
                
                allcompany[id-1]->deposit(amt);
                for(int i=0;i<companyacc;i++)
                cout<<(*allcompany[i]).getbalance()<<endl;
                cout<<"Loan approved\n";
            }
        }

        file.close();
        file.open("Loan.txt", ios::out);
        file.close();

    }
    void userPendingApp()
    {
        fstream file;
        file.open("UserApplications.txt", ios::in);
        while(!file.eof())
        {
            string userid, name, address, cnic, username, password, phonenum;
            int withdrawlim;
            readline(file, userid, name, address, cnic, username, password, phonenum, withdrawlim);
            cout<<userid<<", "<< name<<","<<address<<","<<cnic<<","<<username<<","<<password<<", "<<withdrawlim<<", "<<phonenum<<endl;
            char approve;
            cout<<endl<<endl<<"Press 1 to approve and any other key to reject: ";
            cin>>approve;
            if(approve=='1')
            {
                UserClient**newarray= new UserClient*[useracc+2];//Because we have the last pointer as null
                for(int i=0;i<useracc;i++)
                {
                    *(newarray+i)= *(allusers+i);

                }
                allusers=newarray;
                
                *(allusers+useracc)= new UserClient(true, name, address, cnic, username, password,phonenum, 0, useracc+1);
                useracc++;
                *(allusers+useracc)=nullptr;
                cardallotment(true, useracc);
            }

        }
        file.close();  
        file.open("UserApplications.txt", ios::out);
        file.close();

    }

    void CompanyPendingApp()
    {
        fstream file;
        file.open("CompanyApplications.txt", ios::in);
        int companyid;
        while(file>> companyid )
        {
            // if(!file.eof())
            // {

            string name, address, username, password;
            int balance, taxnum, withdrawlim;

             
            file.ignore();file.ignore();        
            getline(file, name, ',');file.ignore();
            getline(file, address, ',');file.ignore(); 
            file>> taxnum;  
            file.ignore();
            file.ignore();  
            getline(file, username, ',');file.ignore();         
            getline(file, password, ',');file.ignore();
            file>>withdrawlim;file.ignore();
            char approve;
            cout<<"\nCompany Name: "<<name<<"\nAddress: "<<address<<"\nTax Number: "<<taxnum<<endl;
            cout<<"Press 1 to approve and any other key to reject: ";
            cin>>approve;
            if(approve=='1')
            {
                CompanyClient**newarray= new CompanyClient*[companyacc+2];//Because we have the last pointer as null
                for(int i=0;i<companyacc;i++)
                {
                    *(newarray+i)= *(allcompany+i);

                }
                allcompany=newarray;
                *(allcompany+ companyacc)= new CompanyClient(true, name, address, username, password, withdrawlim, taxnum, companyacc+1, 0);
                ( *(allcompany+ companyacc))->print();
                companyacc++;
                *(allcompany+ companyacc)=nullptr;
                cardallotment(false, companyacc);
            }
            }

        //}
        file.close();  

        file.open("CompanyApplications.txt", ios::out);
        file.close();
        

    }

    int checkIDPass(string u, string pass, bool user)
    {
       if(user)
       {
        for(int i=0;i<useracc;i++)
        {
            if(u==(*allusers[i]).getusername()&&pass==(*allusers[i]).getpassword())
            return i;
        }
            return -1;
       }
       else
       {
        for(int i=0;i<companyacc;i++)
            if(u==(*allcompany[i]).getusername()&&pass==(*allcompany[i]).getpassword())
            return i;
            return -1;
       }
    }
    
    void addemployee(CompanyClient&c1)
    {
        int employeeNum, id;
        
        cout<<"Enter the number of employee account you wish to link with your company:";cin>>employeeNum;

         UserClient ** array =c1.getemparray();

        array= new UserClient*[employeeNum];

        for(int i=0;i<employeeNum;i++)
        {
            cout<<"Enter ID of Employee "<<i+1;
            cin>>id;
            *(array+ i)= *(allusers+id-1);

        }
        fstream file;
        file.open("companies_employees.txt",ios::app);
        file<<c1.getid()<<", "<<id<<endl;

        file.close();
    }

    ~BankEmp()
    {
        fstream userfile;

        userfile.open("users.txt", ios::out);

        for(int i=0;i<useracc;i++)
        {
            userfile<<i+1<<", "<<(*allusers[i]).getname()<<", "<<(*allusers[i]).getaddress()<<", "<<(*allusers[i]).getcnic()<<", "<<(*allusers[i]).getusername()<<", "<<(*allusers[i]).getpassword()<<", "<<(*allusers[i]).getphone()<<", "<<(*allusers[i]).getbalance()<<endl;
        }
        userfile.close();

        fstream companyfile;

        companyfile.open("CompanyDetails.txt", ios::out);

        for(int i=0;i<companyacc;i++)
        {
            companyfile<<i+1<<", "<<(*allcompany[i]).getname()<<", "<<(*allcompany[i]).getaddress()<<", "<<(*allcompany[i]).gettax()<<", "<<(*allusers[i]).getusername()<<", "<<(*allusers[i]).getpassword()<<", "<<(*allusers[i]).getbalance()<<endl;
        }
        companyfile.close();
        
    } 
// 1, Maryam Salman, Dha phase 1, 3520987654332, m1, m2, 03498888888, 90
// 2, hammad zaeem, dha phase 2, 3520988888888, h1, h2, 03000000000, 0
// 3, Maryam Salman, Dha phase 1, 3520987654332, m1, m2, 03498888888, 0
};

bool EmployeeExists(string username, string password)
{
        fstream empfile;
        empfile.open("admin.txt", ios::in);
        
        string user, pass;

        while(!empfile.eof())
        {
            getline(empfile,user, ',');
            getline(empfile, pass, '\n');
            
            if(user==username&&pass==password)
            {
                empfile.close();
                return true;
            }
            
        }

        empfile.close();
        return false;


}

void EmployeeOperations(BankEmp &emp)
{
    char choice;
    do
    {
        cout<<endl<<endl<<"Press\n1. To view all Client Details\n2. To view User account applications\n3. To view Company account applications\n4. To view Company Loans\n5. View Transaction history of an Account\n6. To freeze an account\nAny other key to exit";
        cin>>choice;

        if(choice=='1')
        {
            emp.ViewAllUser();
            emp.ViewAllComapnies();
        }

        else if(choice=='2')
        {
            emp.userPendingApp();//need to erase the file
        }

        else if(choice=='3')
        {
            emp.CompanyPendingApp();
        }

        else if(choice=='4')
        {
            emp.approveloans();


        }

        else if(choice=='5')
        {

        }
    } 

    while(choice>='1'&&choice<='5');

}

void ClientOperations(BankEmp&emp, int client)
{
    UserClient* user= emp.getclient(client);
    char choice;
    do
    {
        cout<<endl<<endl<<"Press\n1. To view Balance\n2. To Deposit Funds\n3. To Withdraw Funds\n4. To Transfer Funds\n5. View Transaction history\nAny other key to exit";
        cin>>choice;

        if(choice=='1')
        {
            cout<<"Your Balance is: "<< user->getbalance();
        }

        else if(choice=='2')
        {
            int amt;
            cout<<"Enter amount to deposit: ";
            cin>>amt;
            emp.deposit(true, amt, client);
            
        }

        else if(choice=='3')
        {
            int amt;
            cout<<"Enter amout to withdraw: ";
            cin>>amt;
            emp.withdraw(true,amt, client);
        }

        else if(choice=='4')
        {
            int amt, ID;
            cout<<"Enter amout to Transfer: ";
            cin>>amt;
            cout<<"Enter the ID of the recipient User Account: ";
            cin>>ID;
            emp.transfer(true,amt, client, ID-1);//Index of Recipient = ID-1
            //client.transfer(amt, ID-1);ye kaise krna hai that is a v good question
        }

        else if(choice=='5')
        {

        }
    } 

    while(choice>='1'&&choice<='5');

}

void EmpAccess()
{
    string user, pass;

    cout<<"Enter username: ";
    getline(cin, user);

    cout<<"Enter password: ";
    getline(cin, pass);

    if(EmployeeExists(user, pass))
    {
        cout<<"Access Granted";
        BankEmp obj(false, user, pass);
        EmployeeOperations(obj);
    }
    else    cout<<"Access Denied";

    cout<<endl;
}

void CreateEmp()
{     //Format of admin.txt: Username,password;
    string user, pass;
    cout<<"Enter username: ";
    getline(cin, user);
    cout<<"Enter password: ";
    getline(cin, pass);
    BankEmp bemployee1(true, user, pass);
    cout<<"Congratulations, welcome to the firm!"<<endl;
    

}

void ClientAccess()
{
    BankEmp b1(false, "rr", "ii");//making a temporary object to make changes in the class
    string u, p;

    cout<<"Enter Username: ";
    getline(cin, u);

    cout<<"Enter Password: ";
    getline(cin, p);

    int clientindex =b1.checkIDPass(u, p, true);

    if(clientindex!=-1)
    ClientOperations(b1, clientindex);
    else cout<<"Invalid Username or Password!";




}

void CreateClient()
{
    string name, address, password,cnic, phone, username;
    int withdrawlimit;

    cout<<"Enter your name: ";
    getline(cin, name);

    cout<<"Enter your address: ";
    getline(cin, address);

    cout<<"Enter your CNIC: ";
    getline(cin, cnic);

    cout<<"Enter your Phone Number: ";
    getline(cin, phone);

    cout<<"Enter withdraw limit: ";
    cin>>withdrawlimit;
    cin.ignore();

    cout<<"Enter Username: ";
    getline(cin, username);

    cout<<"Enter your password: ";
    getline(cin, password);

    fstream file;

    file.open("UserApplications.txt", ios::app);
    file<<1<<", "<<name<<", "<<address<<", "<<cnic<<", "<<username<<", "<<password<<", "<<phone<<", "<<withdrawlimit<<endl;
    file.close();

    cout<<"Your request for creating an account has been submitted"<<endl;
    

}

void CreateCompany()
{
    string name, address, password, tax, username;
    int withdrawlimit;

    cout<<"Enter your Company Name: ";
    getline(cin, name);

    cout<<"Enter your address: ";
    getline(cin, address);

    cout<<"Enter withdraw limit: ";
    cin>>withdrawlimit;
    cin.ignore();

    cout<<"Enter Username: ";
    getline(cin, username);

    cout<<"Enter your password: ";
    getline(cin, password);

    cout<<"Enter your Tax Number: ";
    getline(cin, tax);

    fstream file;

    file.open("CompanyApplications.txt", ios::app);
    file<<1<<", "<<name<<", "<<address<<", "<<tax<<", "<<username<<", "<<password<<", "<<withdrawlimit<<endl;
    file.close();

    cout<<"Your request for creating a Company Account has been submitted"<<endl;
    //CompanyClient newcompany(true, name, address, username, password, withdrawlimit, tax, 0 , 0);
    // CompanyClient company(true, name, address, username, password, withdrawlimit, tax, 0, 0);
    // CompanyClient c( false,  name, address, username, password, tax);

}

void CompanyOperations(BankEmp&emp, int client)
{
    CompanyClient*user=emp.getcompany(client);

    char choice;
    do
    {
        cout<<endl<<endl<<"Press\n1. To view Balance\n2. To Deposit Funds\n3. To Withdraw Funds\n4. To Transfer Funds To a User Account\n5. To Request Loan\n6. View Transaction history\nAny other key to exit";
        cin>>choice;

        if(choice=='1')
        {
            cout<<"Your balance is: "<< user->getbalance();
        }

        else if(choice=='2')
        {
            int amt;

            cout<<"Enter amount to deposit: ";
            cin>>amt;

            emp.deposit(false, amt, client);
            
        }

        else if(choice=='3')
        {
            int amt;

            cout<<"Enter amount to withdraw: ";
            cin>>amt;

            emp.withdraw(false,amt, client);
        }

        else if(choice=='4')
        {
            int amt, ID;

            cout<<"Enter amount to Transfer: ";
            cin>>amt;

            cout<<"Enter the ID of the recipient User Account: ";
            cin>>ID;

            emp.transfer(false, amt, client, ID-1);//Index of Recipient = ID-1
            //client.transfer(amt, ID-1);ye kaise krna hai that is a v good question
        }

        else if(choice=='5')
        {
            int amt;
            cout<<"Enter the value for loan: ";
            cin>>amt;
            user->applyloan(amt);

        }
        else if(choice=='6')
        {

        }
    } 

    while(choice>='1'&&choice<='6');
}

void CompanyAccess()
{
    BankEmp b1(false, "rr", "ii");//making a temporary object to make changes in the class
    string u, p;

    cout<<"Enter Username: ";
    getline(cin, u);

    cout<<"Enter Password: ";
    getline(cin, p);

    int companyid =b1.checkIDPass(u, p, false);

    if(companyid!=-1)
    CompanyOperations(b1, companyid);
    else cout<<"Invalid Username or Password!";

}

void main_menu()
{
    char choice;
    do
    {
        cout<<endl<<endl<<"Press\n1. If you are an employee\n2. If you are a Client\nAny other key to exit";
        cin>>choice;
        cin.ignore();

        if(choice=='1')
        {
           cout<<"Press\n1. To create an employee account\n2. To Login as an employee\n";
           cin>>choice;
           cin.ignore();

           if(choice=='1')
           CreateEmp();

           else if (choice=='2')
           EmpAccess();

           else cout<<"Invalid Option!";
        }
        else 
        {
           cout<<endl<<endl<<"Press\n1. To create a User Account\n2. To create a Company Account\n3. To Login as a User\n4.To Login as a Company";
           cin>>choice;
           cin.ignore();

           if(choice=='1')
           CreateClient();

           else if (choice=='2')
           CreateCompany();

           else if (choice=='3')
           ClientAccess();
           
           else if(choice=='4')
           CompanyAccess();

           else cout<<"Invalid Option!";
        }
    }    
    while(choice=='1'||choice=='2');

}
int main()
{   
    main_menu();
    BankEmp b1(false, "rr", "ii");
    // b1.ViewAllUser();
    // b1.ViewAllComapnies();
    // // b1.pendingapplications();
    // // b1.ViewAllUser();
    
}