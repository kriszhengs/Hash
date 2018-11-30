#include <iostream>
#include <string>
#include <cmath>
#include <windows.h>
#include <iomanip>
using namespace std;

typedef unsigned int uint;

void RadnCreat()
{
	string str;
	cout<<"请输入要创建的文件名"<<endl;
	getline(cin,str);
	string comd="RandCreat.exe ";
	cout << "正在创建中，请稍等\n";
	system(comd.append(str).c_str());
	cout<<"创建成功"<<endl;
}
void PrintInf()
{
	cout << "*************************" << endl;
	cout << "请选择测试模式" << endl;
	cout << "*************************" << endl;
	cout << "1:\t通过文件" << endl;
	cout << "2:\t键盘输入" << endl;
	cout << "3:\t随机创建数据" << endl;
	cout << "4:\t退出程序" << endl;
	cout << "*************************" << endl;
}

class Hash
{
private:
	string * base;
	int Amount = 100000;
	double rate = 0.6233;
	uint M; //开放地址的数量
	uint P; //离M最近的素数

	int NextPrime();
	bool Isprime(int n);
public:
	Hash(double rate);
	Hash();
	uint HashCode(string str);
	bool Find(string e, int &times);
	void CreatBaseFile(string address);
	void FileTest(void);
	void KeyBoardTest();
};

int main(void)
{
	double rate;
	cout << "请输入填充因子:";
	cin >> rate;
	Hash hash(rate);
	hash.CreatBaseFile("input.txt");
	
	while (true)
	{
		cin.clear();
		PrintInf();
		char n;
		cin >> n;
		cin.get();
		switch (n)
		{
		case '1': hash.FileTest();
			break;
		case '2': hash.KeyBoardTest();
			break;
		case '3':	RadnCreat();
			break;	
		case '4': return 0;
			break;
		default: cout << "输入非法请重新输入" << endl;
			break;
		}

		//system("cls");
		cout << endl;
	}
	return 0;
}

Hash::Hash(double rate)
{
	this->rate = rate;
	M = (int)(Amount / rate);
	base = new string[M];
	P = NextPrime();
}

Hash::Hash()
{
	M = (int)(Amount / rate);
	base = new string[M];
	P = NextPrime();
}

bool Hash::Find(string e, int &times)
{
	bool flag = false;
	uint n = HashCode(e);
	times = 1;
	while (base[n] != "")
	{
		
		if (e == base[n])
		{
			flag = true;
			break;
		}
		n = (n + 1) % M;
		times++;
	}

	return flag;
}

int Hash::NextPrime()
{
	for (int i = M; i >= 1; i--)
	{
		if (Isprime(i))
			return i;
	}
	return 1;
}

uint Hash::HashCode(string str)
{

	uint h = 0;
	for (uint i = 0; i < str.size(); i++) {
		h = (h << 4) + str[i];
		uint g = h & 0Xf0000000L;
		if (g)  h ^= g >> 24;
		h &= ~g;
	}
	return h % P;

}

bool Hash::Isprime(int num)
{    
     if(num ==2|| num==3 )
        return true ;
        
     if(num %6!= 1&&num %6!= 5)
        return false ;
        
     int tmp =sqrt( num);
     for(int i= 5;i <=tmp; i+=6 )
        if(num %i== 0||num %(i+ 2)==0 )
            return false ;
    
     return true ;
}

void Hash::CreatBaseFile(string address)
{
	cout << "正在构造哈希表，请稍等......" << endl << endl;
	cout << "填充因子为 " << this->rate << endl << endl;

	freopen(address.c_str(),"r",stdin);
	string str;
	uint cnt = 0;
	while (!cin.eof())
	{
		getline(cin, str);
		if (str == "0")
			break;
		uint location = HashCode(str);
		int time = 0;
		Find(str, time);
		cnt += time;
		base[location + time - 1] = str;
	}

	freopen("con","r",stdin);
	cout << "哈希表构造完毕!" << endl << endl;;
	cout << "平均成功查找长度 " << 1.0*cnt / Amount << endl << endl;
}


void Hash::FileTest(void)
{
	string address;
	cout << endl<<"请输入要测试文件的地址 非绝对路径请用\\\\代替\\,并且确保地址无误"<<endl;
	cin >> address;
	cout << "正在处理中请稍等" << endl;	
	freopen(address.c_str(),"r",stdin);
	freopen("out.txt","w",stdout);
	
	this->KeyBoardTest();	
	
	freopen("con","w",stdout);
	freopen("con","r",stdin);
}

void Hash::KeyBoardTest()
{
	string name;
	uint amount = 0, cnt = 0;
	while (!cin.eof())
	{
		getline(cin, name);
		if (name == "0") break;
		cnt++;
		cout << cnt << ": ";
		int times;
		if (Find(name, times))
		{
			cout << "Pos " << HashCode(name) + times;
		}
		else
		{
			cout << "Sorry! ";
		}
		amount += times;
		cout << " ; cur: " << times << ", Avg: ";
		cout << fixed << setprecision(6) << 1.0*amount / cnt << endl;

	}
	freopen("con","w",stdout);
	cout << "平均查找长度为" << fixed << setprecision(6) << 1.0*amount / cnt << endl;
}

