#include <iostream>
//#include <conio.h>
#include <cstring>
#include <fstream>
#include <list>

#ifdef define(_WIN32)
	#define	CLS		system("cls");
	#define PAUSSE	system("pause>nul");
#else
	#define	CLS		system("reset");
	#define PAUSSE	getchar();getchar();
#endif

using namespace std;


class Employe
{
private:
	int id;
	char name[10];
	char dept[10];
	
public:
	Employe(){};
	Employe(const Employe &e);
	Employe(int no,char* n,char* d);
	int getEmployeId(){return id;};
	string getName();
	void readData();
	void writeData();
	void getInfo();
	void getData();
	
	~Employe(){};
};

Employe::Employe(int no,char* n,char* d)
{
	id=no;
	strcpy(name,n);
	strcpy(dept,d);
}

Employe::Employe(const Employe &e)
{
	id=e.id;
	strcpy(name,e.name);
	strcpy(dept,e.dept);
}

class Dataoperate
{
private:	
	list<Employe> elist;
	int getId();
	void refresh();
public:
	void getListInfo();
	void addToList(Employe e,bool isWrite=false);
	void alterData();
	void delData(); 
	Dataoperate();
	~Dataoperate(){};	
};

Dataoperate::Dataoperate()
{
	ifstream inf("file.txt",ios::in|ios::binary);
	Employe *e=new Employe();
	while(inf.read((char*)e,sizeof(Employe)))
	{
		addToList(*e);
	}
}


void Dataoperate::getListInfo()
{
	list<Employe>::iterator it=elist.begin();
	for(;it!=elist.end();it++)
	{
		(*it).getInfo();
	}
}

void Dataoperate::addToList(Employe ea,bool isWrite)
{
	list<Employe>::iterator it=elist.begin();
	for(;it!=elist.end();it++)
	{
		if((*it).getEmployeId()==ea.getEmployeId()){
			cout <<"信息保存失败:员工id重复";
			PAUSSE
			return;
		}
	}
	Employe *e=new Employe(ea);
	elist.push_back(ea);
	if(isWrite){
		ofstream of("file.txt",ios::out|ios::binary|ios::app);	//写文件
		of.write((char*)e,sizeof(Employe));
		of.close();
	}
}

int Dataoperate::getId()
{
	int id;
	cout<<"\n请输入员工id:";
	cin>>id;
	return id;
} 

void Dataoperate::refresh()
{
	list<Employe>::iterator it=elist.begin();
	ofstream of("file.txt",ios::out|ios::binary);	//更改信息到文件 
	Employe *e;
	for(;it!=elist.end();it++)
	{
		e=new Employe(*it);
		of.write((char*)(e),sizeof(Employe));
		delete e;
		e=NULL;
	}
	of.close();
}


void Dataoperate::alterData()
{
	int id=getId();
	list<Employe>::iterator it=elist.begin();
	bool find=false;
	for(;it!=elist.end();it++)
	{
		if((*it).getEmployeId()==id)
		{
			find=true;
			break;
		}
	}
	if(!find){
		cout <<"查无此人!"<<endl; 
	}else{
		(*it).getInfo();
		(*it).getData();
		refresh();
		cout <<"信息已更新,请按任意键继续";
	}
	PAUSSE
}

void Dataoperate::delData()
{
	cout <<"\n请选择检索方式,id[1],姓名[2]:";
	int choice;
	int id;
	cin>>choice;
	string name;
	if(choice==1){
		id=getId();
	}else if(choice==2){
		cout <<"\n请输入姓名:";
		cin>>name; 
	}else{
		PAUSSE
		return;
	}

	list<Employe>::iterator it=elist.begin();
	bool find=false;
	for(;it!=elist.end();it++)
	{
		if(choice==1){
			if((*it).getEmployeId()==id)
			{
				find=true;
				break;
			}
		}else{
			if((*it).getName()==name)
			{
				find=true;
				break;
			}
		}
		
	}
	if(!find){
		cout <<"查无此人!"<<endl; 
	}else{
		(*it).getInfo();
		cout<<"是否删除?[y/n]";
		char choice;
		cin>>choice;
		if(choice=='y'||choice=='Y'){
			it =elist.erase(it);
			refresh();
			cout <<"信息已更新,请按任意键继续";
		}else{
			return;
		}
		
	}
	PAUSSE
}

string Employe::getName()
{
	string s=name;
	return s;
}

void Employe::getInfo()
{
	cout <<"\n工号:"<<id<<endl;
	cout <<"姓名:"<<name<<endl;
	cout <<"部门:"<<dept<<endl;
}

void Employe::getData()
{
	cout <<"\n请输入工号:";
	cin>>id; 
	cout <<"请输入姓名:";
	cin>>name;
	cout <<"请输入部门:";
	cin>>dept;
}


void menue(Dataoperate* dp)
{
	int choice; 
	CLS
	cout <<"\t员工系统\n"<<endl;
	cout <<"0	退出系统:"<<endl;
	cout <<"1	打印信息:"<<endl;
	cout <<"2	添加信息:"<<endl;
	cout <<"3	修改信息:"<<endl;
	cout <<"4	删除信息:"<<endl;
	cout <<"请选择:";
	choice=getchar()-48;
	switch(choice)
	{
		case 3:
			dp->alterData();
			break;
		case 4:
			dp->delData();
			break;
		case 0:
			cout <<"bye..."<<endl; 
			exit(0);
			break;
		case 1:
			//打印信息 
			dp->getListInfo();
			PAUSSE
			break;
		case 2:
			//添加数据 
			cout<<endl;
			Employe e;
			e.getData(); 
			dp->addToList(e,true);
			break;
	}
	 
}


int main(int argc, char const *argv[])
{
	Dataoperate *dp=new Dataoperate();
	while(1){
		menue(dp);	
	}
	return 0;
}
