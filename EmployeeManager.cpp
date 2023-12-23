#include<iostream>
#include<string>
#include<fstream>
#include<map>

using namespace std;
class employee
{
private:
	string m_Id;    //职工号
	float m_salary;    //工资
	string m_name;    //职工姓名
	float m_other_income;     //其他收入
	string m_position;    //职位
	float m_tax;     //个人所得税
public:
	employee() {}
	employee& operator =(employee& re)
	{
		m_Id = re.m_Id;
		m_salary = re.m_salary;
		m_name = re.m_name;
		m_other_income = re.m_other_income;
		m_position = re.m_position;
		m_tax = re.m_tax;
		return *this;
	}
	string get_name()
	{
		return m_name;
	}
	string get_position()
	{
		return m_position;
	}
	float get_salary()
	{
		return m_salary;
	}
	string get_ID()
	{
		return m_Id;
	}
	float get_other_income()
	{
		return m_other_income;
	}
	float out_tax()
	{
		return m_tax;
	}
	friend ostream& operator <<(ostream& os, const employee& re)
	{
		os << re.m_name << "\t\t" << re.m_Id << "\t\t" << re.m_position << "\t\t" << re.m_salary << "\t\t" << re.m_other_income << "\t\t" << re.m_tax << endl;
		return os;
	}
	friend istream& operator >>(istream& is, employee& re)
	{
		is >> re.m_name >> re.m_Id >> re.m_position >> re.m_salary >> re.m_other_income >> re.m_tax;
		return is;
	}
	~employee() {}
};

/* 2、输入功能：输入职工信息，并保存到文件中；*/

void AddEmployee()
{
	fstream fs;
	fs.open("employeeinfo.dat", ios::out | ios::app | ios::binary);
	if (!fs)
		cout << "Failed." << endl;
	else {
		int len;
		cout << "请输入添加的职工数：";
		cin >> len;
		if (len > 0)
		{
			employee* emp = new employee[len];
			cout << "请输入职工的姓名、工号、职位、工资、其他收入、个人所得税" << endl;
			for (int i = 0; i < len; i++)
			{
				cin >> emp[i];
				fs.write((char*)&emp[i], sizeof(emp[i]));
			}
			cout << "添加成功" << endl;

		}
	}
	fs.close();
	fs.clear();
}

/* 3、查询功能：1）能够根据工号精确查询职工信息；*/

void ReseachByID()
{

	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "文件打开失败" << endl;
	else
	{
		string id; int i;
		cout << "请输入你要查询的人的工号:";
		cin >> id;
		fs.seekg(0, ios::end);
		int file_size = fs.tellg();
		int empolyee_num = file_size / sizeof(employee);
		fs.seekg(ios::beg);
		employee* temp = new employee[empolyee_num];

		for (i = 0; i < empolyee_num; i++)
			fs.read((char*)&temp[i], sizeof(temp[i]));

		int j = -1;
		for (i = 0; i < empolyee_num; i++)
			if (id == temp[i].get_ID())
				j = i;
		if (j == -1)
			cout << "无此职工号！" << endl;
		else
		{
			cout << "姓名       |工号       |职位           |工资               |其他收入       |个人所得税 " << endl;
			cout << "-----------|-----------|---------------|-------------------|---------------|-------------" << endl;
			cout << temp[j];
		}

	}
	fs.close();
	fs.clear();
}

/*3、查询功能：能够根据姓名、职位查询职工信息*/

void ReseachByNameAOffice()
{
	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "文件打开失败." << endl;
	else
	{
		char name[20];
		char position[20];
		cout << "请输入你要查询的人的姓名:";
		cin >> name;
		cout << "请输入你要查询的人的职务:";
		cin >> position;
		fs.seekg(0, ios::end);
		int file_size = fs.tellg();
		int empolyee_num = file_size / sizeof(employee);
		fs.seekg(ios::beg);
		employee* temp = new employee[empolyee_num];

		int i, j;
		for (i = 0; i < empolyee_num; i++)
			fs.read((char*)&temp[i], sizeof(temp[i]));
		j = -1;
		for (i = 0; i < empolyee_num; i++)
			if ((name == temp[i].get_name()) && (position == temp[i].get_position()))
				j = i;
		if (j == -1)
			cout << "无此职工！" << endl;
		else
		{
			cout << "姓名       |工号       |职位           |工资               |其他收入       |个人所得税 " << endl;
			cout << "-----------|-----------|---------------|-------------------|---------------|-------------" << endl;
			cout << temp[j];
		}
	}
	fs.close();
	fs.clear();
}

/*3、查询功能：3）统计分析*/

void AverSalaryByOffice()
{
	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "文件打开失败." << endl;
	else
	{
		int check = -1;
		double sum_salary = 0.0;
		double average_salary = 0.0;
		map <string, int> position_num;

		fs.seekg(0, ios::end);
		int file_size = fs.tellg();
		int employee_num = file_size / sizeof(employee);
		fs.seekg(ios::beg);
		string* position_arry = new string[employee_num];
		employee* temp = new employee[employee_num];
		
		for (int i = 0; i < employee_num; i++)
		{
			check = i;
			fs.read((char*)&temp[i], sizeof(employee));
			position_arry[i] = temp[i].get_position();
		}
		if (check == -1)
			cout << "没有职工！" << endl;

		for (int i = 0; i < employee_num; i++)
				position_num[position_arry[i]]++;

		for (const auto& pair : position_num)
		{
			sum_salary = 0.0;
			for (int i = 0; i < employee_num; i++)
			{
				if (temp[i].get_position() == pair.first)
				{
					sum_salary += temp[i].get_salary() + temp[i].get_other_income() - temp[i].out_tax();
				}
			}
			if (pair.second != 0)
			{
				average_salary = sum_salary / pair.second;
				cout << pair.first << "的平均工资为:" << average_salary << endl;
			}
			else
				cout << pair.first << "的平均工资为:" <<  endl;
		}
		cout << endl;
		cout << endl;
		cout << "各职工人数统计条形图(比例示意图)：" << endl;
		for (const auto& pair : position_num)
		{
			cout << pair.first << ":";
			for (int i = 0; i < 2 * pair.second; i++)
				cout << "■";
			cout << endl;
		}
	}
	fs.close();
	fs.clear();
}

/*4、根据职工的工资排序输出*/

void SortBySalary()
{
	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "文件打开失败." << endl;
	else
	{
		int i;
		fs.seekg(0, ios::end);
		int file_size = fs.tellg();
		int empoly_num = file_size / sizeof(employee);
		fs.seekg(ios::beg);
		if (empoly_num == 0)
			cout << "系统中无职工信息！" << endl;
		else
		{
			employee* e = new employee[empoly_num];
			employee temp;
			for (i = 0; i < empoly_num; i++)
				fs.read((char*)&e[i], sizeof(e[i]));
			for (int j = 0; j < empoly_num - 1; j++)    //冒泡排序
			{
				for (int k = 0; k < empoly_num - 1 - j; k++)
				{
					if (e[k].get_salary() > e[k + 1].get_salary())
					{
						temp = e[k];
						e[k] = e[k + 1];
						e[k + 1] = temp;
					}
				}
			}
			cout << "----------------------------------------按工资排序--------------------------------------------" << endl;
			cout << "姓名       |工号       |职位           |工资               |其他收入       |个人所得税 " << endl;
			cout << "-----------|-----------|---------------|-------------------|---------------|-------------" << endl;
			for (i = 0; i < empoly_num; i++)
				cout << e[i];

		}
	}
	fs.close();
	fs.clear();
}

/* 5、根据工号修改职工信息*/

void ModEmployee()
{

	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::out | ios::binary);
	if (!fs)
		cout << "文件打开失败." << endl;
	else
	{
		string id; int i;
		cout << "输入你要修改的职工号:";
		cin >> id;
		fs.seekg(0, ios::end);
		int s = fs.tellg();
		int n = s / sizeof(employee);
		fs.seekg(ios::beg);
		int j = -1;
		employee* e = new employee[n];
		for (i = 0; i < n; i++)
			fs.read((char*)&e[i], sizeof(e[i]));
		for (i = 0; i < n; i++)
		{
			if (id == e[i].get_ID()) {
				j = i;
				break;
			}
		}
		if (j == -1)
			cout << "无此职工！" << endl;
		else
		{
			fs.seekp(sizeof(employee) * j,ios::beg);
			employee t;
			cout << "请输入修改职工的姓名、工号、职位、工资、其他收入、个人所得税" << endl;
			cin >> t;
			fs.write((char*)&t, sizeof(employee));
			cout << "职工信息修改成功！" << endl;
		}
	}
	fs.close();
	fs.clear();
}

//浏览所有人员信息
void Show()
{
	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "文件打开失败，您可能为创建文件，请返回主菜单，按1录入信息并创建文件." << endl;
	else
	{
		fs.seekg(0, ios::end);
		int s = fs.tellg();
		int n = s / sizeof(employee);
		fs.seekg(ios::beg);
		if (n == 0)
			cout << "系统中无职工信息！" << endl;
		else
		{
			employee* e = new employee[n];
			cout << "----------------------------------------所有职工信息------------------------------------------" << endl;
			cout << "姓名       |工号       |职位           |工资               |其他收入       |个人所得税 " << endl;
			cout << "-----------|-----------|---------------|-------------------|---------------|-------------" << endl;
			for (int i = 0; i < n; i++)
			{
				fs.read((char*)&e[i], sizeof(e[i]));
				cout << e[i];
			}

		}

	}
	fs.close();
	fs.clear();
}

/* 6、根据工号删除职工信息*/

void DelEmployee()
{
	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "文件打开失败." << endl;
	else
	{
		fs.seekg(0, ios::end);
		int s = fs.tellg();
		int n = s / sizeof(employee);
		fs.seekg(0, ios::beg);
		if (n == 0)
			cout << "系统中无职工信息！" << endl;
		else
		{
			employee* e = new employee[n];
			string id; int i, j;
			for (i = 0; i < n; i++)
			{
				fs.read((char*)&e[i], sizeof(e[i]));
			}
			fs.close();
			fs.clear();
			cout << "请输入要删除的职工号:";
			cin >> id;
			for (i = 0; i < n; i++)
			{
				j = -1;
				if (id == e[i].get_ID())
				{
					j = i;
					break;
				}
			}
			fs.open("employeeinfo.dat", ios::out | ios::trunc | ios::binary);
			for (i = 0; i < n; i++)
			{
				if (i == j)
					continue;
				else
				{
					fs.write((char*)&e[i], sizeof(e[i]));
				}
			}
			if (j == -1)
				cout << "无此职工！" << endl;
			else
				cout << "该职工已成功删除！" << endl;
			fs.close();
			fs.clear();
		}
	}
}

//菜单函数
void Meun()
{
	cout << "====================================== 职工工资管理系统 =======================================" << endl;
	cout << endl;
	cout << "                        ———————————————————————————————————————————————" << endl;
	cout << "			1.录入工资（批量）	";
	cout << "2.删除工资记录" << endl;
	cout << "			3.查询工资记录		";
	cout << "4.修改工资记录" << endl;
	cout << "			5.插入工资（单条）	";
	cout << "6.统计分析" << endl;
	cout << "			7.工资记录排序		";
	cout << "8.调整工资" << endl;
	cout << "			9.显示工资记录		";
	cout << "0.退出管理系统" << endl;
	cout << "                       ——————————————————————————————————————————————————			  				    " << endl;
	cout << "																	                    " << endl;
	cout << "===============================================================================================" << endl;
	cout << "请输入选择(0-9):";
}

//主函数
int main()
{

	char flag = 'n';
	while (flag == 'n' || flag == 'N')
	{
		Meun();
		int judge;
		cin >> judge;
		if (judge >= 0 && judge <= 9)
		{
			switch (judge)
			{
			case 0:
				cout << "是否退出系统(y/n):";
				cin >> flag;
				break;
			case 1:
				AddEmployee();
				break;
			case 2:
				DelEmployee();
				break;
			case 3:
				ReseachByID();
				break;
			case 4:
				ModEmployee();
				break;
			case 5:
				AddEmployee();
				break;
			case 6:
				AverSalaryByOffice();
				break;
			case 7:
				SortBySalary();
				break;
			case 8:
				ModEmployee();
				break;
			case 9:
				Show();
				break;
			}
		}
		else
			cout << "输入错误，请重新输入!" << endl;
		cout << "按任意键返回主菜单!" << endl;
		system("pause > nul");
		system("cls");
	}
	return 0;
}