#include<iostream>
#include <fstream>
#include<stdlib.h>
#define MAX 100
using namespace std;
class person  //定义一个类实现共有的基础信息
{
public:
	int num;
	char name[20];
	char sex[4];
	int age;
};
//Teacher class
/*公开访问性：任何代码都可以直接调用。
虚拟性质：允许并鼓励派生类进行重写，以实现多态性，确保通过基类引用来调用时，能根据实际对象类型调用相应的实现。
*/
class Teacher : virtual public person
{
public:
	char dept[20];
	char special[20];
	char title[20];
	void Input()  //录入信息，编辑功能需要 
	{
		cout << "输入编号:"; cin >> num;
		cout << "输入姓名:"; cin >> name;
		cout << "输入性别:"; cin >> sex;
		cout << "输入年龄:"; cin >> age;
		cout << "输入所在系:"; cin >> dept;
		cout << "输入专业:"; cin >> special;
		cout << "输入职称:"; cin >> title;
	}
	void Output()  //输出信息，显示功能需要 
	{
		cout << "编号: " << num << endl << "姓名: " << name << endl<< "性别: " << sex <<endl << "年龄: " << age <<
		endl<< "所在系: " << dept << endl << "专业: " << special << endl << "职称: " << title << endl;
	}
};
Teacher Tea[MAX];  //定义一个教师的对象数组
static int Teatop;  //定义一个静态常量，显示当前录入人数 


class TeaManager  //教师的管理类
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
int TeaManager::Add()  //添加功能
{
	system("cls");  //清屏
	Teacher t;
	int i, nu;
	if (Teatop == MAX)
	{
		cout << "人数已满" << endl;
		return 0;
	}
	cout << "请输入编号(判断该编号是否存在)："; 
	cin >> nu;
	for (i = 0; i < Teatop; i++)
	{
		if (nu == Tea[i].num)
		{
			cout << "已有该编号" << endl;
			return 0;
		}
	}
	t.Input(); Tea[Teatop] = t; Teatop++;
	cout << "添加成功！" << endl;
	return 1;
}

int TeaManager::Search()  //查询功能
{
	system("cls");
	int j, n;
	cout << "请输入编号："; cin >> n;
	for (j = 0; j < Teatop; j++)
	{
		if (n == Tea[j].num) break;
	}
	if (j == Teatop)
		cout << "没有此人！" << endl;
	else
		Tea[j].Output();
	return 1;
}
void TeaManager::Show()  //显示功能
{
	system("cls");
	int i;
	if (Teatop == 0)
	{
		cout << "记录为空！" << endl; return;
	}
	for (i = 0; i < Teatop; i++)
		Tea[i].Output();
}
void TeaManager::Edit()  //编辑功能
{
	system("cls");  //清屏
	Teacher t1;
	int j, n;
	cout << "请输入要编辑的人的编号："; cin >> n;
	for (j = 0; j < Teatop; j++)
	{
		if (n == Tea[j].num) break;
	}
	if (j == Teatop)
	{
		cout << "没有此人！" << endl; return;
	};
	cout << "输入修改后的信息，编号不能改:" << endl;
	t1.Input();
	Tea[j] = t1;
	cout << "编辑成功！" << endl;
}
int TeaManager::Delete()  //删除功能
{
	system("cls");  //清屏
	int j, n;
	cout << "请输入要删除的人的编号："; cin >> n;
	for (j = 0; j < Teatop; j++)
	{
		if (n == Tea[j].num) break;//要删除人的编号已找到 
	}
	if (j == Teatop)
	{
		cout << "没有此人！" << endl; return 0;
	};
	for (j; j < Teatop; j++)
	{
		Tea[j] = Tea[j + 1];// 删除编号为n的人 
	}
	Teatop--;//删除之后，总人数人数减一 
	cout << "删除成功！" << endl;
	return 1;
}

void TeaManager::Save()  //保存功能
{
	system("cls");  //清屏
	int i;
	ofstream outfile, outfile1;//生成两个对象 

	outfile1.open("教师人数.dat", ios::out);//打开teatop文件，写入当前信息 
	outfile1 << Teatop;
	
	outfile.open("教师人员数据.dat", ios::binary);//打开teadate文件， （以二进制形式） 
	if (!outfile)
	{
		cerr << "open error!" << endl; return;
	}
	for (i = 0; i < Teatop; i++)
		outfile.write((char*)&Tea[i], sizeof(Tea[i]));//以二进制格式写入文件 ，实现保存 
	outfile.close();//关闭文件 
	cout << "保存成功！" << endl;
}
void TeaManager::Read()  //读取功能
{
	system("cls");
	int i;
	ifstream infile, infile1;//生成两个对象 
	infile1.open("教师人数.dat", ios::in);//打开teatop文件，写入当前信息
	infile1 >> Teatop;
	infile.open("教师人员数据.dat", ios::binary);//打开teadate文件，（以二进制形式） 
	if (!infile)
	{
		cerr << "open error!" << endl; return;
	}
	for (i = 0; i < Teatop; i++)
		infile.read((char*)&Tea[i], sizeof(Tea[i]));//以二进制格式读入文件 ，即读取 
	infile.close();//关闭文件 
	cout << "读取成功！" << endl;
}
void Tea_mune(TeaManager TM)  //用一个管理教师的类来实现结果的显示 //mune -> menu 
{
	system("cls");
	int b;
	char c;
	do {

		cout << endl; cout << endl;
		cout << "//教师管理" << endl;
		cout << "1.添加    "<<endl;
		cout << "2.查询    "<<endl;
		cout << "3.显示    "<<endl;
		cout << "4.编辑    "<<endl;
		cout << "5.删除    "<<endl;
		cout << "6.统计    "<<endl;
		cout << "7.保存    "<<endl;
		cout << "8.读取    "<<endl;
		cout << "0.退出 " << endl;
		cout << "//请选择："; cin >> b;
		switch (b)
		{
		case 1:TM.Add(); break;
		case 2:TM.Search(); break;
		case 3:TM.Show(); break;
		case 4:TM.Edit(); break;
		case 5:TM.Delete(); break;
		case 6:cout << "共有教师人数：" << Teatop << endl; break;  //统计功能
		case 7:TM.Save(); break;
		case 8:TM.Read(); break;
		default:cout << "\n error" << endl; break;
		case 0:break;
		}


	} while (b != 0);
}

class Tester :virtual public person  //实验员
{
public:
	char testroom[10];
	char post[10];
	void Input()
	{
		cout << "请输入编号:"; cin >> num;
		cout << "请输入姓名:"; cin >> name;
		cout << "请输入性别:"; cin >> sex;
		cout << "请输入年龄:"; cin >> age;
		cout << "请输入实验室名称:"; cin >> testroom;
		cout << "请输入职称:"; cin >> post;
	}
	void Output()
	{
		cout << "编号: " << num << endl << "姓名: " << name << endl << "性别: " << sex << endl<< "年龄: " << age <<
			endl<< "所在实验室: " << testroom << endl<< "职务: " << post << endl;
	}

};
Tester Test[MAX];
static int Testop;
class TestManager  //管理实验员的类
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
		cout << "人数已满" << endl;
		return 0;
	}
	cout << "请输入编号(判断该编号是否存在)："; cin >> nu;
	for (i = 0; i < Testop; i++)
	{
		if (nu == Test[i].num)
		{
			cout << "已有该编号" << endl;
			return 0;
		}
	}
	t.Input();
	Test[Testop] = t;
	Testop++;
	cout << "添加成功！" << endl;
	return 1;
}
int TestManager::Search()
{
	system("cls");
	int j, n;
	cout << "请输入编号："; cin >> n;
	for (j = 0; j < Testop; j++)
	{
		if (n == Test[j].num) break;
	}
	if (j == Testop)
		cout << "没有此人！" << endl;
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
		cout << "记录为空！" << endl; return;
	}
	for (i = 0; i < Testop; i++)
		Test[i].Output();
}
void TestManager::Edit()
{
	system("cls");
	Tester t1;
	int j, n;
	cout << "请输入要编辑的人的编号："; cin >> n;
	for (j = 0; j < Testop; j++)
	{
		if (n == Test[j].num) break;
	}
	if (j == Testop)
	{
		cout << "没有此人！" << endl; return;
	};
	cout << "输入修改后的信息，编号不能改:" << endl;
	t1.Input();
	Test[j] = t1;
	cout << "编辑成功！" << endl;
}
int TestManager::Delete()
{
	system("cls");
	int j, n;
	cout << "请输入要删除的人的编号："; cin >> n;
	for (j = 0; j < Testop; j++)
	{
		if (n == Test[j].num) break;
	}
	if (j == Testop)
	{
		cout << "没有此人！" << endl; return 0;
	};
	for (j; j < Testop; j++)
	{
		Test[j] = Test[j + 1];
	}
	Testop--;
	cout << "删除成功！" << endl;
	return 1;
}
void TestManager::Save()
{
	system("cls");
	int i;
	ofstream outfile, outfile1;
	outfile1.open("实验人员人数.dat", ios::out);
	outfile1 << Testop;
	outfile.open("实验人员数据.dat", ios::binary);
	if (!outfile)
	{
		cerr << "open error!" << endl; return;
	}
	for (i = 0; i < Testop; i++)
		outfile.write((char*)&Test[i], sizeof(Test[i]));
	outfile.close();
	cout << "保存成功！" << endl;
}
void TestManager::Read()
{
	system("cls");
	int i;
	ifstream infile, infile1;
	infile1.open("实验人员人数.dat", ios::in);
	infile1 >> Testop;
	infile.open("实验人员数据.dat", ios::binary);
	if (!infile)
	{
		cerr << "open error!" << endl; return;
	}
	for (i = 0; i < Testop; i++)
		infile.read((char*)&Test[i], sizeof(Test[i]));
	infile.close();
	cout << "读取成功！" << endl;
}
void Test_mune(TestManager TM)
{
	system("cls");
	int b;
	char c;
	do {
		cout << endl; cout << endl;
		cout << "//实验人员管理" << endl;
		cout << "1.添加    "<< endl;
		cout << "2.查询    "<< endl;
		cout << "3.显示    "<< endl;
		cout << "4.编辑    "<< endl;
		cout << "5.删除    "<< endl;
		cout << "6.统计    "<< endl;
		cout << "7.保存    "<< endl;
		cout << "8.读取    "<< endl;
		cout << "0.退出" << endl;
		cout << "//请选择："; cin >> b;
		switch (b)
		{
		case 1:TM.Add(); break;
		case 2:TM.Search(); break;
		case 3:TM.Show(); break;
		case 4:TM.Edit(); break;
		case 5:TM.Delete(); break;
		case 6:cout << "共有实验员人数：" << Testop << endl; break;
		case 7:TM.Save(); break;
		case 8:TM.Read(); break;
		default:cout << "\n error" << endl; break;
		case 0:break;
		}

	} while (b != 0);
}

class Policer : virtual public person  //行政人员
{
public:
	char polices[10];
	char post1[10];
	void Input()
	{
		cout << "请输入编号:"; cin >> num;
		cout << "请输入姓名:"; cin >> name;
		cout << "请输入性别"; cin >> sex;
		cout << "请输入年龄:"; cin >> age;
		cout << "请输入政治面貌:"; cin >> polices;
		cout << "请输入职称:"; cin >> post1;
	}
	void Output()
	{
		cout << "编号: " << num << endl << "姓名: " << name << endl << "性别: " << sex << endl << "年龄: " << age <<
			endl<< "政治面貌: " << polices << endl << "职称: " << post1 << endl;
	}

};
Policer Policers[MAX];
static int Policersop;
class PolicerManager  //管理行政人员的类
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
		cout << "人数已满" << endl;
		return 0;
	}
	cout << "请输入编号(判断该编号是否存在)："; cin >> nu;
	for (i = 0; i < Policersop; i++)
	{
		if (nu == Policers[i].num)
		{
			cout << "已有该编号" << endl;
			return 0;
		}
	}
	t.Input();
	Policers[Policersop] = t;
	Policersop++;
	cout << "添加成功！" << endl;
	return 1;
}
int PolicerManager::Search()
{
	system("cls");
	int j, n;
	cout << "请输入编号："; cin >> n;
	for (j = 0; j < Policersop; j++)
	{
		if (n == Policers[j].num) break;
	}
	if (j == Policersop)
		cout << "没有此人！" << endl;
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
		cout << "记录为空！" << endl; return;
	}
	for (i = 0; i < Policersop; i++)
		Policers[i].Output();
}
void PolicerManager::Edit()
{
	system("cls");
	Policer t1;
	int j, n;
	cout << "请输入要编辑的人的编号："; cin >> n;
	for (j = 0; j < Policersop; j++)
	{
		if (n == Policers[j].num) break;
	}
	if (j == Policersop)
	{
		cout << "没有此人！" << endl; return;
	};
	cout << "输入修改后的信息，编号不能改:" << endl;
	t1.Input();
	Policers[j] = t1;
	cout << "编辑成功！" << endl;
}
int PolicerManager::Delete()
{
	system("cls");
	int j, n;
	cout << "请输入要删除的人的编号："; cin >> n;
	for (j = 0; j < Policersop; j++)
	{
		if (n == Policers[j].num) break;
	}
	if (j == Policersop)
	{
		cout << "没有此人！" << endl; return 0;
	};
	for (j; j < Policersop; j++)
	{
		Policers[j] = Policers[j + 1];
	}
	Policersop--;
	cout << "删除成功！" << endl;
	return 1;
}
void PolicerManager::Save()
{
	system("cls");
	int i;
	ofstream outfile, outfile1;
	outfile1.open("行政人员人数.dat", ios::out);
	outfile1 << Policersop;
	outfile.open("行政人员数据.dat", ios::binary);
	if (!outfile)
	{
		cerr << "open error!" << endl; return;
	}
	for (i = 0; i < Policersop; i++)
		outfile.write((char*)&Policers[i], sizeof(Policers[i]));
	outfile.close();
	cout << "保存成功！" << endl;
}
void PolicerManager::Read()
{
	system("cls");
	int i;
	ifstream infile, infile1;
	infile1.open("行政人员人数.dat", ios::in);
	infile1 >> Policersop;
	infile.open("行政人员数据.dat", ios::binary);
	if (!infile)
	{
		cerr << "open error!" << endl; return;
	}
	for (i = 0; i < Policersop; i++)
		infile.read((char*)&Policers[i], sizeof(Policers[i]));
	infile.close();
	cout << "读取成功！" << endl;
}
void Policers_mune(PolicerManager TM)
{
	system("cls");
	int b;
	char c;
	do {
		cout << endl; cout << endl;
		cout << "//行政人员管理" << endl;
		cout << "1.添加    "<< endl;
		cout << "2.查询    "<< endl;
		cout << "3.显示    "<< endl;
		cout << "4.编辑    "<< endl;
		cout << "5.删除    "<< endl;
		cout << "6.统计    "<< endl;
		cout << "7.保存    "<< endl;
		cout << "8.读取    "<< endl;
		cout << "0.退出" << endl;
		cout << "//请选择："; cin >> b;
		switch (b)
		{
		case 1:TM.Add(); break;  //TM去调用add类
		case 2:TM.Search(); break;
		case 3:TM.Show(); break;
		case 4:TM.Edit(); break;
		case 5:TM.Delete(); break;
		case 6:cout << "共有行政员人数：" << Policersop << endl; break;
		case 7:TM.Save(); break;
		case 8:TM.Read(); break;
		default:cout << "\n error" << endl; break;
		case 0:break;
		}

	} while (b != 0);
}
class Teapoli : virtual public person  //教师兼行政
{

public:
	void Input()  //录入信息
	{
		cout << "请输入编号:"; cin >> num;
		cout << "请输入姓名:"; cin >> name;
		cout << "请输入性别："; cin >> sex;
		cout << "请输入年龄:"; cin >> age;
	}
	void Output()  //输出信息
	{
		cout << "编号: " << num <<endl << "姓名: " << name <<endl<< "性别: " << sex << "  " << "年龄: " << age << endl;
	}
};
Teapoli Teap[MAX];
static int Teapolitop;

class TeapoliManager  //教师兼行政管理类
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
int TeapoliManager::Add()  //添加功能
{
	system("cls");  //清屏
	Teapoli t;
	int i, nu;
	if (Teapolitop == MAX)
	{
		cout << "人数已满" << endl;
		return 0;
	}
	cout << "请输入编号（判断该编号是否存在）："; cin >> nu;
	for (i = 0; i < Teapolitop; i++)
	{
		if (nu == Teap[i].num)
		{
			cout << "已有该编号" << endl;
			return 0;
		}
	}
	t.Input(); Teap[Teapolitop] = t; Teapolitop++;
	cout << "添加成功！" << endl;
	return 1;
}

int TeapoliManager::Search()  //查询功能
{
	system("cls");
	int j, n;
	cout << "请输入编号："; cin >> n;
	for (j = 0; j < Teapolitop; j++)
	{
		if (n == Teap[j].num) break;
	}
	if (j == Teapolitop)
		cout << "没有此人！" << endl;
	else
		Teap[j].Output();
	return 1;
}
void TeapoliManager::Show()  //显示功能
{
	
	system("cls");
	int i;
	if (Teapolitop == 0)
	{
		cout << "记录为空！" << endl; return;
	}
	for (i = 0; i < Teapolitop; i++)
		Teap[i].Output();
}
void TeapoliManager::Edit()  //编辑功能
{
	system("cls");  //清屏
	Teapoli t1;
	int j, n;
	cout << "请输入要编辑的人的编号："; cin >> n;
	for (j = 0; j < Teapolitop; j++)
	{
		if (n == Teap[j].num) break;
	}
	if (j == Teapolitop)
	{
		cout << "没有此人！" << endl; return;
	};
	cout << "输入修改后的信息，编号不能改:" << endl;
	t1.Input();
	Teap[j] = t1;
	cout << "编辑成功！" << endl;
}
int TeapoliManager::Delete()  //删除功能
{
	
	system("cls");  //清屏
	int j, n;
	cout << "请输入要删除的人的编号："; cin >> n;
	for (j = 0; j < Teapolitop; j++)
	{
		if (n == Teap[j].num) break;
	}
	if (j == Teapolitop)
	{
		cout << "没有此人！" << endl; return 0;
	};
	for (j; j < Teapolitop; j++)
	{
		Teap[j] = Teap[j + 1];
	}
	Teapolitop--;
	cout << "删除成功！" << endl;
	return 1;
}
void TeapoliManager::Save()  //保存功能
{
	system("cls");  //清屏
	int i;
	ofstream outfile, outfile1;
	outfile1.open("教师行政人员人数.dat", ios::out);
	outfile1 << Teapolitop;
	outfile.open("教师行政人员数据.dat", ios::binary);
	if (!outfile)
	{
		cerr << "open error!" << endl; return;
	}
	for (i = 0; i < Teapolitop; i++)
		outfile.write((char*)&Tea[i], sizeof(Tea[i]));
	outfile.close();
	cout << "保存成功！" << endl;
}

void TeapoliManager::Read()  //读取功能
{
	system("cls");
	int i;
	ifstream infile, infile1;
	infile1.open("教师行政人员人数.dat", ios::in);
	infile1 >> Teapolitop;
	infile.open("教师行政人员数据.dat", ios::binary);
	if (!infile)
	{
		cerr << "open error!" << endl; return;
	}
	for (i = 0; i < Teapolitop; i++)
		infile.read((char*)&Teap[i], sizeof(Teapoli[i]));
	infile.close();
	cout << "读取成功！" << endl;
}

void Teapoli_mune(TeapoliManager TM)
{
	system("cls");
	int b;
	char c;
	do {

		cout << endl; cout << endl;
		cout << "//教师兼行政管理" << endl;
		cout << "1.添加   "<<endl;
		cout << "2.查询    "<<endl;
		cout << "3.显示    "<<endl;
		cout << "4.编辑    "<<endl;
		cout << "5.删除    "<<endl;
		cout << "6.统计    "<<endl;
		cout << "7.保存    "<<endl;
		cout << "8.读取    "<<endl;
		cout << "0.退出" << endl;
		cout << "//请选择："; cin >> b;
		switch (b)
		{
		case 1:TM.Add(); break;
		case 2:TM.Search(); break;
		case 3:TM.Show(); break;
		case 4:TM.Edit(); break;
		case 5:TM.Delete(); break;
		case 6:cout << "共有教师兼行政人数：" << Teapolitop << endl; break;  //统计功能
		case 7:TM.Save(); break;
		case 8:TM.Read(); break;
		default:cout << "\n error" << endl; break;
		case 0:break;
		}


	} while (b != 0);
}

int main()   //主函数
{
	//创建各个管理类的对想 
	TeaManager Tmer1;
	TestManager Tetmer;
	PolicerManager Polimer;
	TeapoliManager Tp;
	int a=2,m = 0;
	char c;
	cout<<"    *************************************";
	cout<<endl<<"    *     欢迎使用高校人员管理系统      *"<<endl;
	cout<<"    *************************************";
	cout<<endl<<"请输入密码：";
	cin>>m;

	if(m!=000000)
	{
		cout<<"密码错误！"<<endl;
		c=getchar();
		return 0;
	}

	while (a)
	{
		system("cls");

		cout << endl;
		cout << "             // 欢迎使用高校人员信息管理系统" << endl; 
		cout << "                1.教师管理                    " << endl<< endl;
		cout << "                2.实验员管理                  " << endl<< endl;
		cout << "                3.行政员管理                  " << endl<< endl;
		cout << "                4.教师兼行政管理              " << endl<< endl;
		cout << "                0.退出                        " << endl<< endl;
		cout << "              // 请选择您要管理的人员:"; \
		cin >> a;

		switch (a)  //用switch语句来判断输入的数字
		{
		case 1:Tea_mune(Tmer1); break;
		case 2:Test_mune(Tetmer); break;
		case 3:Policers_mune(Polimer); break;
		case 4:Teapoli_mune(Tp); break;
		case 0:break;
		default:cout << "\n error" << endl;
			cout << "按回车键继续" << endl;
			c = getchar();//输入错误，继续输入 
			break;
		}
	}
	system("cls");
	cout << endl << "谢谢使用" << endl;
	c = getchar();//使用完成，继续选择 
	return 0;
}






