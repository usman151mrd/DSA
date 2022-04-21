#include <fstream>
#include <iostream>
#include <sstream>
#ifdef _WIN32
#include <windows.h> //import if you are running on window os
#else
#include <termios.h> // import if you are running linux mac or unix like os
#include <unistd.h>
#endif

using namespace std;


class Employee {
    int empCode;
    string name;
    int age;
    float salary;
public:
    Employee() {

    }

    Employee(int empCode, const string &name, int age, float salary) : empCode(empCode), name(name), age(age),
                                                                       salary(salary) {

    }

    int getEmpCode() const {
        return empCode;
    }

    void setEmpCode(int empCode){
        Employee::empCode = empCode;
    }

    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        Employee::name = name;
    }

    int getAge() const {
        return age;
    }

    void setAge(int age)  {
        Employee::age = age;
    }

    float getSalary() const {
        return salary;
    }

    void setSalary(float salary) {
        Employee::salary = salary;
    }
};

class Node {
Employee employee;
Node *left;
Node *right;
int height;
public:
    Node(const Employee &employee) : employee(employee) {
        left = NULL;
        right = NULL;
        height = 1;
    }

    Node(Employee &employee, Node *left, Node *right, int height) : employee(employee), left(left), right(right),
                                                                          height(height) {}

    Employee getEmployee() const {
        return employee;
    }

    void setEmployee(Employee &employee) {
        Node::employee = employee;
    }

    Node *getLeft() const {
        return left;
    }

    void setLeft(Node *left) {
        Node::left = left;
    }

    Node *getRight() const {
        return right;
    }

    void setRight(Node *right) {
        Node::right = right;
    }

    int getHeight() const {
        return height;
    }

    void setHeight(int height) {
        Node::height = height;
    }
};

//----------------------------------------------------------------------------

//-------------------------------------------------------------------------








class Tree {
private:
    int Height(Node *node);
    int Max(int a, int b);
    int getBalance(Node *node);
    Node *rightRotate(Node *node);
    Node* leftRotate(Node *node);
    Node* performBalance(int key, Node *node);
public:
    Node* Insert(Employee &employee, Node *node);
    void inOrder(Node *node);
    void preOrder(Node *node);
    void postOrder(Node *node);
    Node* Delete(int key,Node *node);
    Node* Maximum(Node *node);
    Node *Minimum(Node *node);
    void Search(int key,Node *node);
    void Update(int key,Node *node);

};

//------------------------------------------------------------------


int Tree::Height(Node *node) {
    if(node==nullptr)
        return 0;
    return node->getHeight();
}

int Tree::Max(int a, int b) {
    return a>b ? a : b;
}

int Tree::getBalance(Node *node) {
    if(node==nullptr)
        return 0;
    return Height(node->getLeft()) - Height(node->getRight());
}

Node *Tree::rightRotate(Node *node) {
    auto left = node->getLeft();
    auto lRight = left->getRight();
    left->setRight(node);
    node->setLeft(lRight);
    node->setHeight(Max(Height(node->getRight()),Height(node->getLeft()))+1);
    left->setHeight(Max(Height(left->getRight()),Height(left->getLeft()))+1) ;
    return left;
}

Node *Tree::leftRotate(Node *node) {
    auto right = node->getRight();
    auto rLeft = right->getLeft();
    right->setLeft(node);
    node->setRight(rLeft);
    node->setHeight(Max(Height(node->getRight()),Height(node->getLeft()))+1);
    right->setHeight(Max(Height(right->getRight()),Height(right->getLeft()))+1);
    return right;
}

Node *Tree::performBalance(int key, Node *node) {
    auto balance = getBalance(node);

    if(balance > 1 && node->getEmployee().getEmpCode() > key) // left left case
    {
        return rightRotate(node);
    }
    if (balance < -1 && node->getEmployee().getEmpCode() < key) //right right case
    {
        return leftRotate(node);
    }
    if(balance > 1 && node->getEmployee().getEmpCode() < key) // left right case
    {
        node->setLeft(leftRotate(node->getLeft()));
        return rightRotate(node);
    }
    if (balance < -1 && node->getEmployee().getEmpCode() > key) //rotate right left
    {
        node->setRight(rightRotate(node->getRight()));
        return leftRotate(node);
    }
    return node;
}

Node *Tree::Insert(Employee &employee, Node *node) {
    if(node == nullptr)
        return new Node(employee);
    else if(employee.getEmpCode() > node->getEmployee().getEmpCode())
        node->setRight(Insert(employee, node->getRight()));
    else if (employee.getEmpCode() < node->getEmployee().getEmpCode())
        node->setLeft(Insert(employee, node->getLeft()));
    else
        return node;
    node->setHeight(Max(Height(node->getLeft()), Height(node->getRight())) + 1);

    return performBalance(employee.getEmpCode(), node);
}

void Tree::inOrder(Node *node) {
    if(node!=nullptr)
    {
        inOrder(node->getLeft());
        cout<<"\n\n*************Record****************\n\n";
        cout<<"Employee Code : "<<node->getEmployee().getEmpCode()<<endl;
        cout<<"Employee Name : "<<node->getEmployee().getName()<<endl;
        cout<<"Employee Age : "<<node->getEmployee().getAge()<<endl;
        cout<<"Employee Age : "<<node->getEmployee().getSalary()<<endl;
        inOrder(node->getRight());
    }
}

void Tree::preOrder(Node *node) {
    if(node!=nullptr)
    {
        cout<<"\n\n*************Record****************\n\n";
        cout<<"Employee Code : "<<node->getEmployee().getEmpCode()<<endl;
        cout<<"Employee Name : "<<node->getEmployee().getName()<<endl;
        cout<<"Employee Age : "<<node->getEmployee().getAge()<<endl;
        cout<<"Employee Age : "<<node->getEmployee().getSalary()<<endl;
        inOrder(node->getLeft());
        inOrder(node->getRight());
    }
}

void Tree::postOrder(Node *node) {
    if(node!=nullptr)
    {
        inOrder(node->getLeft());
        inOrder(node->getRight());
        cout<<"\n\n*************Record****************\n\n";
        cout<<"Employee Code : "<<node->getEmployee().getEmpCode()<<endl;
        cout<<"Employee Name : "<<node->getEmployee().getName()<<endl;
        cout<<"Employee Age : "<<node->getEmployee().getAge()<<endl;
        cout<<"Employee Age : "<<node->getEmployee().getSalary()<<endl;

    }
}

Node *Tree::Delete(int key, Node *node) {
    if(node==nullptr)
        return nullptr;
    if(key > node->getEmployee().getEmpCode())
        node->setRight(Delete(key, node->getRight()));
    else if (key < node->getEmployee().getEmpCode())
        node->setLeft( Delete(key, node->getLeft()));
    else
    {
        if(node->getRight()==nullptr and node->getLeft()==nullptr)
        {
            delete node;
            return nullptr;
        }
        else if(node->getLeft()==nullptr)
        {
            auto temp = node->getRight();
            delete node;
            return temp;
        }
        else if(node->getRight()==nullptr)
        {
            auto temp = node->getLeft();
            delete node;
            return temp;
        } else
        {
            auto data = Maximum(node->getLeft())->getEmployee().getEmpCode();
            node->getEmployee().setEmpCode(data);
            node->setLeft(Delete(data,node->getLeft()));
        }
    }
    return performBalance(key, node);
}

Node *Tree::Maximum(Node *node) {
    while (node->getRight()!=nullptr)
    {
        node = node->getRight();
    }
    return node;
}

Node *Tree::Minimum(Node *node) {
    while (node->getLeft()!=nullptr)
    {
        node = node->getLeft();
    }
    return node;
}

void Tree::Search(int key, Node *node) {
    while (node!=nullptr and key!=node->getEmployee().getEmpCode())
    {
        if(key > node->getEmployee().getEmpCode())
        {
            node = node->getRight();
        } else
        {
            node = node->getLeft();
        }
    }
    if (node == nullptr) {
        cout << key << " not found\n";
    } else {
		cout<<"\n\n*************Record****************\n\n";
        cout<<"Employee Code : "<<node->getEmployee().getEmpCode()<<endl;
        cout<<"Employee Name : "<<node->getEmployee().getName()<<endl;
        cout<<"Employee Age : "<<node->getEmployee().getAge()<<endl;
        cout<<"Employee Age : "<<node->getEmployee().getSalary()<<endl;
    }
}
void Tree::Update(int key, Node *node) {
    while (node!=nullptr and key!=node->getEmployee().getEmpCode())
    {
        if(key > node->getEmployee().getEmpCode())
        {
            node = node->getRight();
        } else
        {
            node = node->getLeft();
        }
    }
    if (node == nullptr) {
        cout << key << " not found\n";
    } else {
        string name;
        int age;
        float salary;
        cout<<"Enter "<<key<<" name age and salary : "<<endl;
        cin>>name>>age>>salary;
        node->getEmployee().setName(name);
        node->getEmployee().setAge(age);
        node->getEmployee().setSalary(salary);
        cout<<"Record updated successfully"<<endl;
    }

}

//-------------------------------------------------------------------
class Login {
    fstream file;
public:
    Login()
    {

    }
    bool login(string user,string password)
    {
    	file.open("login.csv",ios::in);
        string line,word;
		if(file)
		{

	        while(getline(file,line))
	        {
	            stringstream s(line);
	            bool  p = true;
	            while(getline(s,word,','))
	            {
	                if(word==user and p)
	                {
	                	//cout<<"user : "<<user<<" and word = "<<word<<endl;
	                    p = false;
	                    continue;
	                }
	                else if (word!=user and p)
	                {
	                    break;
	                } else
	                {
	                	//cout<<"else -> password : "<<password<<" and word = -"<<word<<"-"<<endl;
	                	//cout<<"else -> password.length : "<<password.length()<<" and word.length = "<<word.length()<<endl;
	                    if (password==word)
	                    {
	                    //	cout<<"password : "<<password<<" and word = "<<word<<endl;
	                    	file.close();
	                    	return true;
						}

	                    else
	                    {
	                    	file.close();
	                    	 return false;
						}
	                }
	            }
	        }
	    }
        cout<<"Error to file open "<<endl;
        return false;
    }
    void signup(string user="usman",string pass="12345")
    {
    	file.open("login.csv",ios::out|ios::app);
        file<<user<<","<<pass<<endl;
		file.close();
    }
};
//-------------------------------------------------------------------------
class Database {
private:
    fstream file;
public:
    Database();
    Node* read(Node *node);
    void write(Node *node);
    Employee split(string);

    int toInt(string s)
    {
        return atoi(s.c_str());
    }
    void Save(Node *node) {
		if(node!=nullptr)
		{
			write(node);
			Save(node->getLeft());
			Save(node->getRight());
		}
	}
	void close()
	{
		file.close();
	}
	bool open()
	{
		file.open("db.csv",ios::out | ios::trunc);
		if(file)
			return true;
		else
			return false;
	}
};
//----------------------------------------------------------------------

Database::Database() {

}

Node* Database::read(Node *root) {
	file.open("db.csv",ios::in);
    if(file)
    {
        Employee emp;
        string input;
        Tree tree;
        while (getline(file,input))
        {
            emp =  split(input);
            root = tree.Insert(emp,root);
        }
    } else
    {
        return 0;
    }
    file.close();
    return root;

}

void Database::write(Node *node) {
	if(file)
    if(node!=0)
    {
        file<<node->getEmployee().getEmpCode()<<","<<
        node->getEmployee().getName()<<","<<
        node->getEmployee().getAge()<<","<<
        node->getEmployee().getSalary()<<endl;
    }
}
Employee Database::split(string line)
{
	string word;
	Employee emp;
	stringstream s(line);
    getline(s,word,',');
    emp.setEmpCode(toInt(word));
    getline(s,word,',');
    emp.setName(word);
    getline(s,word,',');
    emp.setAge(toInt(word));
    getline(s,word,',');
    emp.setSalary(stof(word.c_str()));
    return emp;
}
//-----------------------------------------------------------------------

class GUI {
    Tree tree;
    Node *root = 0;
    Employee emp;
    Database db;
    bool read = false;
public:
    void start()
    {
		int code;
        while(true)
        {
            switch (menu()) {
                case 1: {
                	if(!read)
                	{
                		root = db.read(root);
                		read = true;
					}
					else
					{
						cout<<"Your are already load data from file. If you load data again. Data will be duplicate. So, this feature is disable"<<endl;
					}

                    break;
                }
                case 2: {

                    int code, age;
                    string name;
                    float salary;
                    cout << "Enter emp code, Name, age and salary " << endl;
                    cin >> code>> name >> age >> salary;
                    Employee emp(code,name,age,salary);
                    root = tree.Insert(emp, root);
                    cout<<"record added successfylly"<<endl;
                    break;
                }
                case 3:
                {
                    cout<<"Enter employee code to delete A reocrd : ";
                    cin>>code;
                    root = tree.Delete(code,root);
                    clrscr();
                    cout<<"record deleted successfylly"<<endl;
                    break;
                }

                case 4:
                {
                    int code;
                    cout<<"Enter employee code to search reocrd : ";
                    cin>>code;
                    clrscr();
                    tree.Search(code,root);
                    break;
                }
                case 5:
                {
					cout<<"Enter employee code to update a record: ";
					cin>>code;
					tree.Update(code,root);
					break;
				}
                case 6:
                {
					cout<<"\n\n*****data are display in ascending order****************\n\n\n"<<endl;
                    tree.inOrder(root);
                    break;
				}
				case 7:
                {
					if(db.open())
					{
						db.Save(root);
						db.close();
						clrscr();
						cout<<"Data saved successfully"<<endl;
					}
					else
					{
						cout<<"error to open file "<<endl;
					}

                    break;
                }
                case 8:
                {
					clrscr();
					break;
				}

                case 9:
                {
                    // in case of exit;
                    char ex;
                    cout<<"are you sure to exit [y/n]";
                    cin>>ex;
                    if(ex=='y' or ex=='Y')
                        exit(0);
                    else
                        continue;
                    break;
                }
                default:
                {
					//clrscr();
					cout<<"********please select a valid choice*********\n\n"<<endl;
                }
            }
        }
    }

private:
    int menu()
    {
        cout<<"\n\n****************** Menu ********************\n\n";
        cout<<"Press 1 to load data"<<endl;
        cout<<"press 2 to Insert Record "<<endl;
        cout<<"press 3 to delete a record"<<endl;
        cout<<"press 4 to search a record"<<endl;
        cout<<"press 5 to update a record"<<endl;
        cout<<"press 6 to display all records"<<endl;
        cout<<"press 7 to save data"<<endl;
        cout<<"press 8 to clear screen "<<endl;
        cout<<"press 9 to exit "<<endl;
        int ch;
        cout<<"enter you choice : ";
        cin>>ch;
        return ch;
    }
    public:
    void clrscr()
    {
		#ifdef  _WIN32
			system("cls"); // if you are running at wnidow os
		#endif
		#ifdef __linux__
			system("clear"); //if your plateform is linux
		#endif
		#ifdef __APPLE__
			system("clear"); // if your plateform is mac
		#endif
		#ifdef _POSIX_VERSION
			system("clear"); // if you are running cygwin compiler on window
		#endif
		#ifdef __unix__
			system("clear"); // if your os is unix
		#endif
	}

};


void SetStdinEcho(bool enable = true)
{
#ifdef _WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);

    if( !enable )
        mode &= ~ENABLE_ECHO_INPUT;
    else
        mode |= ENABLE_ECHO_INPUT;

    SetConsoleMode(hStdin, mode );

#else
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if( !enable )
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
}
string getPassword() //someone cannot see your password at console
{
	string password;

    SetStdinEcho(false);
    cin>>password;
    SetStdinEcho(true);
    return password;
}

int main() {

    Login log;
   // log.signup();// run it first if you run this program first otherwise do comment this statement
    GUI gui;
    string user;
    string pass;
    cout<<"Enter username : ";
    cin>>user;
    cout<<"Enter password : ";
    pass = getPassword();
    for (int i = 0; i < 3; ++i) {
        if(log.login(user,pass))
        {
            gui.start();
        }
        else
        {
			gui.clrscr();
			cout<<"please enter valid username or password"<<endl;
			cout<<"Enter username : ";
			cin>>user;
			cout<<"Enter password : ";
			pass = getPassword();
		}
    }

    return 0;
}


