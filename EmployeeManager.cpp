#include<iostream>
#include<string>
#include<fstream>
#include<map>

using namespace std;
class employee
{
private:
	string m_Id;    //ְ����
	float m_salary;    //����
	string m_name;    //ְ������
	float m_other_income;     //��������
	string m_position;    //ְλ
	float m_tax;     //��������˰
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

/* 2�����빦�ܣ�����ְ����Ϣ�������浽�ļ��У�*/

void AddEmployee()
{
	fstream fs;
	fs.open("employeeinfo.dat", ios::out | ios::app | ios::binary);
	if (!fs)
		cout << "Failed." << endl;
	else {
		int len;
		cout << "��������ӵ�ְ������";
		cin >> len;
		if (len > 0)
		{
			employee* emp = new employee[len];
			cout << "������ְ�������������š�ְλ�����ʡ��������롢��������˰" << endl;
			for (int i = 0; i < len; i++)
			{
				cin >> emp[i];
				fs.write((char*)&emp[i], sizeof(emp[i]));
			}
			cout << "��ӳɹ�" << endl;

		}
	}
	fs.close();
	fs.clear();
}

/* 3����ѯ���ܣ�1���ܹ����ݹ��ž�ȷ��ѯְ����Ϣ��*/

void ReseachByID()
{

	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "�ļ���ʧ��" << endl;
	else
	{
		string id; int i;
		cout << "��������Ҫ��ѯ���˵Ĺ���:";
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
			cout << "�޴�ְ���ţ�" << endl;
		else
		{
			cout << "����       |����       |ְλ           |����               |��������       |��������˰ " << endl;
			cout << "-----------|-----------|---------------|-------------------|---------------|-------------" << endl;
			cout << temp[j];
		}

	}
	fs.close();
	fs.clear();
}

/*3����ѯ���ܣ��ܹ�����������ְλ��ѯְ����Ϣ*/

void ReseachByNameAOffice()
{
	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "�ļ���ʧ��." << endl;
	else
	{
		char name[20];
		char position[20];
		cout << "��������Ҫ��ѯ���˵�����:";
		cin >> name;
		cout << "��������Ҫ��ѯ���˵�ְ��:";
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
			cout << "�޴�ְ����" << endl;
		else
		{
			cout << "����       |����       |ְλ           |����               |��������       |��������˰ " << endl;
			cout << "-----------|-----------|---------------|-------------------|---------------|-------------" << endl;
			cout << temp[j];
		}
	}
	fs.close();
	fs.clear();
}

/*3����ѯ���ܣ�3��ͳ�Ʒ���*/

void AverSalaryByOffice()
{
	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "�ļ���ʧ��." << endl;
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
			cout << "û��ְ����" << endl;

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
				cout << pair.first << "��ƽ������Ϊ:" << average_salary << endl;
			}
			else
				cout << pair.first << "��ƽ������Ϊ:" <<  endl;
		}
		cout << endl;
		cout << endl;
		cout << "��ְ������ͳ������ͼ(����ʾ��ͼ)��" << endl;
		for (const auto& pair : position_num)
		{
			cout << pair.first << ":";
			for (int i = 0; i < 2 * pair.second; i++)
				cout << "��";
			cout << endl;
		}
	}
	fs.close();
	fs.clear();
}

/*4������ְ���Ĺ����������*/

void SortBySalary()
{
	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "�ļ���ʧ��." << endl;
	else
	{
		int i;
		fs.seekg(0, ios::end);
		int file_size = fs.tellg();
		int empoly_num = file_size / sizeof(employee);
		fs.seekg(ios::beg);
		if (empoly_num == 0)
			cout << "ϵͳ����ְ����Ϣ��" << endl;
		else
		{
			employee* e = new employee[empoly_num];
			employee temp;
			for (i = 0; i < empoly_num; i++)
				fs.read((char*)&e[i], sizeof(e[i]));
			for (int j = 0; j < empoly_num - 1; j++)    //ð������
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
			cout << "----------------------------------------����������--------------------------------------------" << endl;
			cout << "����       |����       |ְλ           |����               |��������       |��������˰ " << endl;
			cout << "-----------|-----------|---------------|-------------------|---------------|-------------" << endl;
			for (i = 0; i < empoly_num; i++)
				cout << e[i];

		}
	}
	fs.close();
	fs.clear();
}

/* 5�����ݹ����޸�ְ����Ϣ*/

void ModEmployee()
{

	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::out | ios::binary);
	if (!fs)
		cout << "�ļ���ʧ��." << endl;
	else
	{
		string id; int i;
		cout << "������Ҫ�޸ĵ�ְ����:";
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
			cout << "�޴�ְ����" << endl;
		else
		{
			fs.seekp(sizeof(employee) * j,ios::beg);
			employee t;
			cout << "�������޸�ְ�������������š�ְλ�����ʡ��������롢��������˰" << endl;
			cin >> t;
			fs.write((char*)&t, sizeof(employee));
			cout << "ְ����Ϣ�޸ĳɹ���" << endl;
		}
	}
	fs.close();
	fs.clear();
}

//���������Ա��Ϣ
void Show()
{
	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "�ļ���ʧ�ܣ�������Ϊ�����ļ����뷵�����˵�����1¼����Ϣ�������ļ�." << endl;
	else
	{
		fs.seekg(0, ios::end);
		int s = fs.tellg();
		int n = s / sizeof(employee);
		fs.seekg(ios::beg);
		if (n == 0)
			cout << "ϵͳ����ְ����Ϣ��" << endl;
		else
		{
			employee* e = new employee[n];
			cout << "----------------------------------------����ְ����Ϣ------------------------------------------" << endl;
			cout << "����       |����       |ְλ           |����               |��������       |��������˰ " << endl;
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

/* 6�����ݹ���ɾ��ְ����Ϣ*/

void DelEmployee()
{
	fstream fs;
	fs.open("employeeinfo.dat", ios::in | ios::binary);
	if (!fs)
		cout << "�ļ���ʧ��." << endl;
	else
	{
		fs.seekg(0, ios::end);
		int s = fs.tellg();
		int n = s / sizeof(employee);
		fs.seekg(0, ios::beg);
		if (n == 0)
			cout << "ϵͳ����ְ����Ϣ��" << endl;
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
			cout << "������Ҫɾ����ְ����:";
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
				cout << "�޴�ְ����" << endl;
			else
				cout << "��ְ���ѳɹ�ɾ����" << endl;
			fs.close();
			fs.clear();
		}
	}
}

//�˵�����
void Meun()
{
	cout << "====================================== ְ�����ʹ���ϵͳ =======================================" << endl;
	cout << endl;
	cout << "                        ����������������������������������������������������������������������������������������������" << endl;
	cout << "			1.¼�빤�ʣ�������	";
	cout << "2.ɾ�����ʼ�¼" << endl;
	cout << "			3.��ѯ���ʼ�¼		";
	cout << "4.�޸Ĺ��ʼ�¼" << endl;
	cout << "			5.���빤�ʣ�������	";
	cout << "6.ͳ�Ʒ���" << endl;
	cout << "			7.���ʼ�¼����		";
	cout << "8.��������" << endl;
	cout << "			9.��ʾ���ʼ�¼		";
	cout << "0.�˳�����ϵͳ" << endl;
	cout << "                       ����������������������������������������������������������������������������������������������������			  				    " << endl;
	cout << "																	                    " << endl;
	cout << "===============================================================================================" << endl;
	cout << "������ѡ��(0-9):";
}

//������
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
				cout << "�Ƿ��˳�ϵͳ(y/n):";
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
			cout << "�����������������!" << endl;
		cout << "��������������˵�!" << endl;
		system("pause > nul");
		system("cls");
	}
	return 0;
}