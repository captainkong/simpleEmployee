#include <iostream>
#include <conio.h>
#include <cstring>
#include <fstream>
#include <list>

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
			cout <<"��Ϣ����ʧ��:Ա��id�ظ�";
			system("pause>nul");
			return;
		}
	}
	Employe *e=new Employe(ea);
	elist.push_back(ea);
	if(isWrite){
		ofstream of("file.txt",ios::out|ios::binary|ios::app);	//д�ļ�
		of.write((char*)e,sizeof(Employe));
		of.close();
	}
}

int Dataoperate::getId()
{
	int id;
	cout<<"\n������Ա��id:";
	cin>>id;
	return id;
} 

void Dataoperate::refresh()
{
	list<Employe>::iterator it=elist.begin();
	ofstream of("file.txt",ios::out|ios::binary);	//������Ϣ���ļ� 
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
		cout <<"���޴���!"<<endl; 
	}else{
		(*it).getInfo();
		(*it).getData();
		refresh();
		cout <<"��Ϣ�Ѹ���,�밴���������";
	}
	system("pause>nul");
}

void Dataoperate::delData()
{
	cout <<"\n��ѡ�������ʽ,id[1],����[2]:";
	int choice=getch()-48;
	int id;
	string name;
	if(choice==1){
		id=getId();
	}else if(choice==2){
		cout <<"\n����������:";
		cin>>name; 
	}else{
		system("pause");
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
		cout <<"���޴���!"<<endl; 
	}else{
		(*it).getInfo();
		cout<<"�Ƿ�ɾ��?[y/n]";
		char choice;
		cin>>choice;
		if(choice=='y'||choice=='Y'){
			it =elist.erase(it);
			refresh();
			cout <<"��Ϣ�Ѹ���,�밴���������";
		}else{
			return;
		}
		
	}
	system("pause>nul");
}

string Employe::getName()
{
	string s=name;
	return s;
}

void Employe::getInfo()
{
	cout <<"\n����:"<<id<<endl;
	cout <<"����:"<<name<<endl;
	cout <<"����:"<<dept<<endl;
}

void Employe::getData()
{
	cout <<"\n�����빤��:";
	cin>>id; 
	cout <<"����������:";
	cin>>name;
	cout <<"�����벿��:";
	cin>>dept;
}


void menue(Dataoperate* dp)
{
	int choice; 
	system("cls");
	cout <<"\tԱ��ϵͳ\n"<<endl;
	cout <<"0	�˳�ϵͳ:"<<endl;
	cout <<"1	��ӡ��Ϣ:"<<endl;
	cout <<"2	�����Ϣ:"<<endl;
	cout <<"3	�޸���Ϣ:"<<endl;
	cout <<"4	ɾ����Ϣ:"<<endl;
	cout <<"��ѡ��:";
	choice=getch()-48;
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
			//��ӡ��Ϣ 
			dp->getListInfo();
			system("pause");
			break;
		case 2:
			//������� 
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
