#include<iostream>
#include <fstream>
#include<stdlib.h>
#define MAX 100
using namespace std;
class person  //����һ����ʵ�ֹ��еĻ�����Ϣ
{
public:
	int num;
	char name[20];
	char sex[4];
	int age;
};
//Teacher class
/*���������ԣ��κδ��붼����ֱ�ӵ��á�
�������ʣ��������������������д����ʵ�ֶ�̬�ԣ�ȷ��ͨ����������������ʱ���ܸ���ʵ�ʶ������͵�����Ӧ��ʵ�֡�
*/
class Teacher : virtual public person
{
public:
	char dept[20];
	char special[20];
	char title[20];
	void Input()  //¼����Ϣ���༭������Ҫ 
	{
		cout << "������:"; cin >> num;
		cout << "��������:"; cin >> name;
		cout << "�����Ա�:"; cin >> sex;
		cout << "��������:"; cin >> age;
		cout << "��������ϵ:"; cin >> dept;
		cout << "����רҵ:"; cin >> special;
		cout << "����ְ��:"; cin >> title;
	}
	void Output()  //�����Ϣ����ʾ������Ҫ 
	{
		cout << "���: " << num << endl << "����: " << name << endl<< "�Ա�: " << sex <<endl << "����: " << age <<
		endl<< "����ϵ: " << dept << endl << "רҵ: " << special << endl << "ְ��: " << title << endl;
	}
};
Teacher Tea[MAX];  //����һ����ʦ�Ķ�������
static int Teatop;  //����һ����̬��������ʾ��ǰ¼������ 


class TeaManager  //��ʦ�Ĺ�����
{
public:
	int Add();
	int Search();
	void Show();
	void Edit();
	int Delete();
	void Save();
	void Read();
};
int TeaManager::Add()  //��ӹ���
{
	system("cls");  //����
	Teacher t;
	int i, nu;
	if (Teatop == MAX)
	{
		cout << "��������" << endl;
		return 0;
	}
	cout << "��������(�жϸñ���Ƿ����)��"; 
	cin >> nu;
	for (i = 0; i < Teatop; i++)
	{
		if (nu == Tea[i].num)
		{
			cout << "���иñ��" << endl;
			return 0;
		}
	}
	t.Input(); Tea[Teatop] = t; Teatop++;
	cout << "��ӳɹ���" << endl;
	return 1;
}

int TeaManager::Search()  //��ѯ����
{
	system("cls");
	int j, n;
	cout << "�������ţ�"; cin >> n;
	for (j = 0; j < Teatop; j++)
	{
		if (n == Tea[j].num) break;
	}
	if (j == Teatop)
		cout << "û�д��ˣ�" << endl;
	else
		Tea[j].Output();
	return 1;
}
void TeaManager::Show()  //��ʾ����
{
	system("cls");
	int i;
	if (Teatop == 0)
	{
		cout << "��¼Ϊ�գ�" << endl; return;
	}
	for (i = 0; i < Teatop; i++)
		Tea[i].Output();
}
void TeaManager::Edit()  //�༭����
{
	system("cls");  //����
	Teacher t1;
	int j, n;
	cout << "������Ҫ�༭���˵ı�ţ�"; cin >> n;
	for (j = 0; j < Teatop; j++)
	{
		if (n == Tea[j].num) break;
	}
	if (j == Teatop)
	{
		cout << "û�д��ˣ�" << endl; return;
	};
	cout << "�����޸ĺ����Ϣ����Ų��ܸ�:" << endl;
	t1.Input();
	Tea[j] = t1;
	cout << "�༭�ɹ���" << endl;
}
int TeaManager::Delete()  //ɾ������
{
	system("cls");  //����
	int j, n;
	cout << "������Ҫɾ�����˵ı�ţ�"; cin >> n;
	for (j = 0; j < Teatop; j++)
	{
		if (n == Tea[j].num) break;//Ҫɾ���˵ı�����ҵ� 
	}
	if (j == Teatop)
	{
		cout << "û�д��ˣ�" << endl; return 0;
	};
	for (j; j < Teatop; j++)
	{
		Tea[j] = Tea[j + 1];// ɾ�����Ϊn���� 
	}
	Teatop--;//ɾ��֮��������������һ 
	cout << "ɾ���ɹ���" << endl;
	return 1;
}

void TeaManager::Save()  //���湦��
{
	system("cls");  //����
	int i;
	ofstream outfile, outfile1;//������������ 

	outfile1.open("��ʦ����.dat", ios::out);//��teatop�ļ���д�뵱ǰ��Ϣ 
	outfile1 << Teatop;
	
	outfile.open("��ʦ��Ա����.dat", ios::binary);//��teadate�ļ��� ���Զ�������ʽ�� 
	if (!outfile)
	{
		cerr << "open error!" << endl; return;
	}
	for (i = 0; i < Teatop; i++)
		outfile.write((char*)&Tea[i], sizeof(Tea[i]));//�Զ����Ƹ�ʽд���ļ� ��ʵ�ֱ��� 
	outfile.close();//�ر��ļ� 
	cout << "����ɹ���" << endl;
}
void TeaManager::Read()  //��ȡ����
{
	system("cls");
	int i;
	ifstream infile, infile1;//������������ 
	infile1.open("��ʦ����.dat", ios::in);//��teatop�ļ���д�뵱ǰ��Ϣ
	infile1 >> Teatop;
	infile.open("��ʦ��Ա����.dat", ios::binary);//��teadate�ļ������Զ�������ʽ�� 
	if (!infile)
	{
		cerr << "open error!" << endl; return;
	}
	for (i = 0; i < Teatop; i++)
		infile.read((char*)&Tea[i], sizeof(Tea[i]));//�Զ����Ƹ�ʽ�����ļ� ������ȡ 
	infile.close();//�ر��ļ� 
	cout << "��ȡ�ɹ���" << endl;
}
void Tea_mune(TeaManager TM)  //��һ�������ʦ������ʵ�ֽ������ʾ //mune -> menu 
{
	system("cls");
	int b;
	char c;
	do {

		cout << endl; cout << endl;
		cout << "//��ʦ����" << endl;
		cout << "1.���    "<<endl;
		cout << "2.��ѯ    "<<endl;
		cout << "3.��ʾ    "<<endl;
		cout << "4.�༭    "<<endl;
		cout << "5.ɾ��    "<<endl;
		cout << "6.ͳ��    "<<endl;
		cout << "7.����    "<<endl;
		cout << "8.��ȡ    "<<endl;
		cout << "0.�˳� " << endl;
		cout << "//��ѡ��"; cin >> b;
		switch (b)
		{
		case 1:TM.Add(); break;
		case 2:TM.Search(); break;
		case 3:TM.Show(); break;
		case 4:TM.Edit(); break;
		case 5:TM.Delete(); break;
		case 6:cout << "���н�ʦ������" << Teatop << endl; break;  //ͳ�ƹ���
		case 7:TM.Save(); break;
		case 8:TM.Read(); break;
		default:cout << "\n error" << endl; break;
		case 0:break;
		}


	} while (b != 0);
}

class Tester :virtual public person  //ʵ��Ա
{
public:
	char testroom[10];
	char post[10];
	void Input()
	{
		cout << "��������:"; cin >> num;
		cout << "����������:"; cin >> name;
		cout << "�������Ա�:"; cin >> sex;
		cout << "����������:"; cin >> age;
		cout << "������ʵ��������:"; cin >> testroom;
		cout << "������ְ��:"; cin >> post;
	}
	void Output()
	{
		cout << "���: " << num << endl << "����: " << name << endl << "�Ա�: " << sex << endl<< "����: " << age <<
			endl<< "����ʵ����: " << testroom << endl<< "ְ��: " << post << endl;
	}

};
Tester Test[MAX];
static int Testop;
class TestManager  //����ʵ��Ա����
{
public:
	int Add();
	int Search();
	void Show();
	void Edit();
	int Delete();
	void Save();
	void Read();
};
int TestManager::Add()
{
	system("cls");
	Tester t;
	int i, nu;
	if (Testop == MAX)
	{
		cout << "��������" << endl;
		return 0;
	}
	cout << "��������(�жϸñ���Ƿ����)��"; cin >> nu;
	for (i = 0; i < Testop; i++)
	{
		if (nu == Test[i].num)
		{
			cout << "���иñ��" << endl;
			return 0;
		}
	}
	t.Input();
	Test[Testop] = t;
	Testop++;
	cout << "��ӳɹ���" << endl;
	return 1;
}
int TestManager::Search()
{
	system("cls");
	int j, n;
	cout << "�������ţ�"; cin >> n;
	for (j = 0; j < Testop; j++)
	{
		if (n == Test[j].num) break;
	}
	if (j == Testop)
		cout << "û�д��ˣ�" << endl;
	else
		Test[j].Output();
	return 1;
}
void TestManager::Show()
{
	system("cls");
	int i;
	if (Testop == 0)
	{
		cout << "��¼Ϊ�գ�" << endl; return;
	}
	for (i = 0; i < Testop; i++)
		Test[i].Output();
}
void TestManager::Edit()
{
	system("cls");
	Tester t1;
	int j, n;
	cout << "������Ҫ�༭���˵ı�ţ�"; cin >> n;
	for (j = 0; j < Testop; j++)
	{
		if (n == Test[j].num) break;
	}
	if (j == Testop)
	{
		cout << "û�д��ˣ�" << endl; return;
	};
	cout << "�����޸ĺ����Ϣ����Ų��ܸ�:" << endl;
	t1.Input();
	Test[j] = t1;
	cout << "�༭�ɹ���" << endl;
}
int TestManager::Delete()
{
	system("cls");
	int j, n;
	cout << "������Ҫɾ�����˵ı�ţ�"; cin >> n;
	for (j = 0; j < Testop; j++)
	{
		if (n == Test[j].num) break;
	}
	if (j == Testop)
	{
		cout << "û�д��ˣ�" << endl; return 0;
	};
	for (j; j < Testop; j++)
	{
		Test[j] = Test[j + 1];
	}
	Testop--;
	cout << "ɾ���ɹ���" << endl;
	return 1;
}
void TestManager::Save()
{
	system("cls");
	int i;
	ofstream outfile, outfile1;
	outfile1.open("ʵ����Ա����.dat", ios::out);
	outfile1 << Testop;
	outfile.open("ʵ����Ա����.dat", ios::binary);
	if (!outfile)
	{
		cerr << "open error!" << endl; return;
	}
	for (i = 0; i < Testop; i++)
		outfile.write((char*)&Test[i], sizeof(Test[i]));
	outfile.close();
	cout << "����ɹ���" << endl;
}
void TestManager::Read()
{
	system("cls");
	int i;
	ifstream infile, infile1;
	infile1.open("ʵ����Ա����.dat", ios::in);
	infile1 >> Testop;
	infile.open("ʵ����Ա����.dat", ios::binary);
	if (!infile)
	{
		cerr << "open error!" << endl; return;
	}
	for (i = 0; i < Testop; i++)
		infile.read((char*)&Test[i], sizeof(Test[i]));
	infile.close();
	cout << "��ȡ�ɹ���" << endl;
}
void Test_mune(TestManager TM)
{
	system("cls");
	int b;
	char c;
	do {
		cout << endl; cout << endl;
		cout << "//ʵ����Ա����" << endl;
		cout << "1.���    "<< endl;
		cout << "2.��ѯ    "<< endl;
		cout << "3.��ʾ    "<< endl;
		cout << "4.�༭    "<< endl;
		cout << "5.ɾ��    "<< endl;
		cout << "6.ͳ��    "<< endl;
		cout << "7.����    "<< endl;
		cout << "8.��ȡ    "<< endl;
		cout << "0.�˳�" << endl;
		cout << "//��ѡ��"; cin >> b;
		switch (b)
		{
		case 1:TM.Add(); break;
		case 2:TM.Search(); break;
		case 3:TM.Show(); break;
		case 4:TM.Edit(); break;
		case 5:TM.Delete(); break;
		case 6:cout << "����ʵ��Ա������" << Testop << endl; break;
		case 7:TM.Save(); break;
		case 8:TM.Read(); break;
		default:cout << "\n error" << endl; break;
		case 0:break;
		}

	} while (b != 0);
}

class Policer : virtual public person  //������Ա
{
public:
	char polices[10];
	char post1[10];
	void Input()
	{
		cout << "��������:"; cin >> num;
		cout << "����������:"; cin >> name;
		cout << "�������Ա�"; cin >> sex;
		cout << "����������:"; cin >> age;
		cout << "������������ò:"; cin >> polices;
		cout << "������ְ��:"; cin >> post1;
	}
	void Output()
	{
		cout << "���: " << num << endl << "����: " << name << endl << "�Ա�: " << sex << endl << "����: " << age <<
			endl<< "������ò: " << polices << endl << "ְ��: " << post1 << endl;
	}

};
Policer Policers[MAX];
static int Policersop;
class PolicerManager  //����������Ա����
{
public:
	int Add();
	int Search();
	void Show();
	void Edit();
	int Delete();
	void Save();
	void Read();
};
int PolicerManager::Add()
{
	system("cls");
	Policer t;
	int i, nu;
	if (Policersop == MAX)
	{
		cout << "��������" << endl;
		return 0;
	}
	cout << "��������(�жϸñ���Ƿ����)��"; cin >> nu;
	for (i = 0; i < Policersop; i++)
	{
		if (nu == Policers[i].num)
		{
			cout << "���иñ��" << endl;
			return 0;
		}
	}
	t.Input();
	Policers[Policersop] = t;
	Policersop++;
	cout << "��ӳɹ���" << endl;
	return 1;
}
int PolicerManager::Search()
{
	system("cls");
	int j, n;
	cout << "�������ţ�"; cin >> n;
	for (j = 0; j < Policersop; j++)
	{
		if (n == Policers[j].num) break;
	}
	if (j == Policersop)
		cout << "û�д��ˣ�" << endl;
	else
		Policers[j].Output();
	return 1;
}
void PolicerManager::Show()
{
	system("cls");
	int i;
	if (Policersop == 0)
	{
		cout << "��¼Ϊ�գ�" << endl; return;
	}
	for (i = 0; i < Policersop; i++)
		Policers[i].Output();
}
void PolicerManager::Edit()
{
	system("cls");
	Policer t1;
	int j, n;
	cout << "������Ҫ�༭���˵ı�ţ�"; cin >> n;
	for (j = 0; j < Policersop; j++)
	{
		if (n == Policers[j].num) break;
	}
	if (j == Policersop)
	{
		cout << "û�д��ˣ�" << endl; return;
	};
	cout << "�����޸ĺ����Ϣ����Ų��ܸ�:" << endl;
	t1.Input();
	Policers[j] = t1;
	cout << "�༭�ɹ���" << endl;
}
int PolicerManager::Delete()
{
	system("cls");
	int j, n;
	cout << "������Ҫɾ�����˵ı�ţ�"; cin >> n;
	for (j = 0; j < Policersop; j++)
	{
		if (n == Policers[j].num) break;
	}
	if (j == Policersop)
	{
		cout << "û�д��ˣ�" << endl; return 0;
	};
	for (j; j < Policersop; j++)
	{
		Policers[j] = Policers[j + 1];
	}
	Policersop--;
	cout << "ɾ���ɹ���" << endl;
	return 1;
}
void PolicerManager::Save()
{
	system("cls");
	int i;
	ofstream outfile, outfile1;
	outfile1.open("������Ա����.dat", ios::out);
	outfile1 << Policersop;
	outfile.open("������Ա����.dat", ios::binary);
	if (!outfile)
	{
		cerr << "open error!" << endl; return;
	}
	for (i = 0; i < Policersop; i++)
		outfile.write((char*)&Policers[i], sizeof(Policers[i]));
	outfile.close();
	cout << "����ɹ���" << endl;
}
void PolicerManager::Read()
{
	system("cls");
	int i;
	ifstream infile, infile1;
	infile1.open("������Ա����.dat", ios::in);
	infile1 >> Policersop;
	infile.open("������Ա����.dat", ios::binary);
	if (!infile)
	{
		cerr << "open error!" << endl; return;
	}
	for (i = 0; i < Policersop; i++)
		infile.read((char*)&Policers[i], sizeof(Policers[i]));
	infile.close();
	cout << "��ȡ�ɹ���" << endl;
}
void Policers_mune(PolicerManager TM)
{
	system("cls");
	int b;
	char c;
	do {
		cout << endl; cout << endl;
		cout << "//������Ա����" << endl;
		cout << "1.���    "<< endl;
		cout << "2.��ѯ    "<< endl;
		cout << "3.��ʾ    "<< endl;
		cout << "4.�༭    "<< endl;
		cout << "5.ɾ��    "<< endl;
		cout << "6.ͳ��    "<< endl;
		cout << "7.����    "<< endl;
		cout << "8.��ȡ    "<< endl;
		cout << "0.�˳�" << endl;
		cout << "//��ѡ��"; cin >> b;
		switch (b)
		{
		case 1:TM.Add(); break;  //TMȥ����add��
		case 2:TM.Search(); break;
		case 3:TM.Show(); break;
		case 4:TM.Edit(); break;
		case 5:TM.Delete(); break;
		case 6:cout << "��������Ա������" << Policersop << endl; break;
		case 7:TM.Save(); break;
		case 8:TM.Read(); break;
		default:cout << "\n error" << endl; break;
		case 0:break;
		}

	} while (b != 0);
}
class Teapoli : virtual public person  //��ʦ������
{

public:
	void Input()  //¼����Ϣ
	{
		cout << "��������:"; cin >> num;
		cout << "����������:"; cin >> name;
		cout << "�������Ա�"; cin >> sex;
		cout << "����������:"; cin >> age;
	}
	void Output()  //�����Ϣ
	{
		cout << "���: " << num <<endl << "����: " << name <<endl<< "�Ա�: " << sex << "  " << "����: " << age << endl;
	}
};
Teapoli Teap[MAX];
static int Teapolitop;

class TeapoliManager  //��ʦ������������
{
public:
	int Add();
	int Search();
	void Show();
	void Edit();
	int Delete();
	void Save();
	void Read();
};
int TeapoliManager::Add()  //��ӹ���
{
	system("cls");  //����
	Teapoli t;
	int i, nu;
	if (Teapolitop == MAX)
	{
		cout << "��������" << endl;
		return 0;
	}
	cout << "�������ţ��жϸñ���Ƿ���ڣ���"; cin >> nu;
	for (i = 0; i < Teapolitop; i++)
	{
		if (nu == Teap[i].num)
		{
			cout << "���иñ��" << endl;
			return 0;
		}
	}
	t.Input(); Teap[Teapolitop] = t; Teapolitop++;
	cout << "��ӳɹ���" << endl;
	return 1;
}

int TeapoliManager::Search()  //��ѯ����
{
	system("cls");
	int j, n;
	cout << "�������ţ�"; cin >> n;
	for (j = 0; j < Teapolitop; j++)
	{
		if (n == Teap[j].num) break;
	}
	if (j == Teapolitop)
		cout << "û�д��ˣ�" << endl;
	else
		Teap[j].Output();
	return 1;
}
void TeapoliManager::Show()  //��ʾ����
{
	
	system("cls");
	int i;
	if (Teapolitop == 0)
	{
		cout << "��¼Ϊ�գ�" << endl; return;
	}
	for (i = 0; i < Teapolitop; i++)
		Teap[i].Output();
}
void TeapoliManager::Edit()  //�༭����
{
	system("cls");  //����
	Teapoli t1;
	int j, n;
	cout << "������Ҫ�༭���˵ı�ţ�"; cin >> n;
	for (j = 0; j < Teapolitop; j++)
	{
		if (n == Teap[j].num) break;
	}
	if (j == Teapolitop)
	{
		cout << "û�д��ˣ�" << endl; return;
	};
	cout << "�����޸ĺ����Ϣ����Ų��ܸ�:" << endl;
	t1.Input();
	Teap[j] = t1;
	cout << "�༭�ɹ���" << endl;
}
int TeapoliManager::Delete()  //ɾ������
{
	
	system("cls");  //����
	int j, n;
	cout << "������Ҫɾ�����˵ı�ţ�"; cin >> n;
	for (j = 0; j < Teapolitop; j++)
	{
		if (n == Teap[j].num) break;
	}
	if (j == Teapolitop)
	{
		cout << "û�д��ˣ�" << endl; return 0;
	};
	for (j; j < Teapolitop; j++)
	{
		Teap[j] = Teap[j + 1];
	}
	Teapolitop--;
	cout << "ɾ���ɹ���" << endl;
	return 1;
}
void TeapoliManager::Save()  //���湦��
{
	system("cls");  //����
	int i;
	ofstream outfile, outfile1;
	outfile1.open("��ʦ������Ա����.dat", ios::out);
	outfile1 << Teapolitop;
	outfile.open("��ʦ������Ա����.dat", ios::binary);
	if (!outfile)
	{
		cerr << "open error!" << endl; return;
	}
	for (i = 0; i < Teapolitop; i++)
		outfile.write((char*)&Tea[i], sizeof(Tea[i]));
	outfile.close();
	cout << "����ɹ���" << endl;
}

void TeapoliManager::Read()  //��ȡ����
{
	system("cls");
	int i;
	ifstream infile, infile1;
	infile1.open("��ʦ������Ա����.dat", ios::in);
	infile1 >> Teapolitop;
	infile.open("��ʦ������Ա����.dat", ios::binary);
	if (!infile)
	{
		cerr << "open error!" << endl; return;
	}
	for (i = 0; i < Teapolitop; i++)
		infile.read((char*)&Teap[i], sizeof(Teapoli[i]));
	infile.close();
	cout << "��ȡ�ɹ���" << endl;
}

void Teapoli_mune(TeapoliManager TM)
{
	system("cls");
	int b;
	char c;
	do {

		cout << endl; cout << endl;
		cout << "//��ʦ����������" << endl;
		cout << "1.���   "<<endl;
		cout << "2.��ѯ    "<<endl;
		cout << "3.��ʾ    "<<endl;
		cout << "4.�༭    "<<endl;
		cout << "5.ɾ��    "<<endl;
		cout << "6.ͳ��    "<<endl;
		cout << "7.����    "<<endl;
		cout << "8.��ȡ    "<<endl;
		cout << "0.�˳�" << endl;
		cout << "//��ѡ��"; cin >> b;
		switch (b)
		{
		case 1:TM.Add(); break;
		case 2:TM.Search(); break;
		case 3:TM.Show(); break;
		case 4:TM.Edit(); break;
		case 5:TM.Delete(); break;
		case 6:cout << "���н�ʦ������������" << Teapolitop << endl; break;  //ͳ�ƹ���
		case 7:TM.Save(); break;
		case 8:TM.Read(); break;
		default:cout << "\n error" << endl; break;
		case 0:break;
		}


	} while (b != 0);
}

int main()   //������
{
	//��������������Ķ��� 
	TeaManager Tmer1;
	TestManager Tetmer;
	PolicerManager Polimer;
	TeapoliManager Tp;
	int a=2,m = 0;
	char c;
	cout<<"    *************************************";
	cout<<endl<<"    *     ��ӭʹ�ø�У��Ա����ϵͳ      *"<<endl;
	cout<<"    *************************************";
	cout<<endl<<"���������룺";
	cin>>m;

	if(m!=000000)
	{
		cout<<"�������"<<endl;
		c=getchar();
		return 0;
	}

	while (a)
	{
		system("cls");

		cout << endl;
		cout << "             // ��ӭʹ�ø�У��Ա��Ϣ����ϵͳ" << endl; 
		cout << "                1.��ʦ����                    " << endl<< endl;
		cout << "                2.ʵ��Ա����                  " << endl<< endl;
		cout << "                3.����Ա����                  " << endl<< endl;
		cout << "                4.��ʦ����������              " << endl<< endl;
		cout << "                0.�˳�                        " << endl<< endl;
		cout << "              // ��ѡ����Ҫ�������Ա:"; \
		cin >> a;

		switch (a)  //��switch������ж����������
		{
		case 1:Tea_mune(Tmer1); break;
		case 2:Test_mune(Tetmer); break;
		case 3:Policers_mune(Polimer); break;
		case 4:Teapoli_mune(Tp); break;
		case 0:break;
		default:cout << "\n error" << endl;
			cout << "���س�������" << endl;
			c = getchar();//������󣬼������� 
			break;
		}
	}
	system("cls");
	cout << endl << "ллʹ��" << endl;
	c = getchar();//ʹ����ɣ�����ѡ�� 
	return 0;
}






