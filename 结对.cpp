//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h> 
#include <time.h>
#include <string>
#include <math.h>
using namespace std;
int gcd(int a, int b)
{
	while (b != 0)
	{
		int c = a % b;
		a = b;
		b = c;
	}
	return a;
}
int lcm(int x, int y) {           //最小公倍数
	return x * y / gcd(x, y);
}

string CharToStr(char* contentChar)
{
	string tempStr;
	for (int i = 0; contentChar[i] != '\0'; i++)
	{
		tempStr += contentChar[i];
	}
	return tempStr;
}
void Spawn(int maxc, int max)//输入生成题目数量，数字最大值
{
	int a, b, c;
	int temp1, result;
	int temp2 = -1;
	char temp3 = '1';
	int flag;
	int i;
	char x;
	char sy[] = { '+','-','*','/' };
	srand(clock());
	ofstream file;
	file.open("L:\\Exercise.txt");//打开文件
	for (b = 1; b <= maxc; b++)
	{
		i = rand() % 4 + 2;
		file << b << "." << "     ";
		for (c = 1; c <= i; c++)
		{
			file << rand() % max + 1;
			if (c == i)
				continue;
			x = sy[rand() % 4];
			file << x;
		}
		file << "=" << endl;

	}
	file.close();
}

void Spawn1(int maxc, int max,int count)//输入生成题目数量，数字最大值
{
	int a, b, c;
	int temp1, result;
	int temp2 = -1;
	char temp3 = '1';
	int flag;
	int i;
	char x;
	char sy[] = { '+','-','*','/' };
	srand(clock());
	ofstream file;
	file.open("L:\\wrong.txt");//打开文件
	for (b = 1; b <= maxc; b++)
	{
		i = rand() % 4 + 2;
		file << count+1 << "." << "     ";
		for (c = 1; c <= i; c++)
		{
			file << rand() % max + 1;
			if (c == i)
				continue;
			x = sy[rand() % 4];
			file << x;
		}
		file << "=" << endl;

	}
	file.close();
}

void ModifyLineData(string fileName, int lineNum, char* lineData)
{
	ifstream in;
	in.open(fileName);

	string strFileData = "";
	int line = 1;
	char tmpLineData[1024] = { 0 };
	while (in.getline(tmpLineData, sizeof(tmpLineData)))
	{
		if (line == lineNum)
		{
			strFileData += CharToStr(lineData);
			strFileData += "\n";
		}
		else
		{
			strFileData += CharToStr(tmpLineData);
			strFileData += "\n";
		}
		line++;
	}
	in.close();

	//写入文件
	ofstream out;
	out.open(fileName);
	out.flush();
	out << strFileData;
	out.close();
}


int calculate(int *num, char *sym, int numc, int symc, int count,int m)
{
	int i=0;
	int newc = 0;
	int j = 0;
	int num1[20][2] = { 0 };//num1[i][0]表示分子,num1[i][1]表示分母
	for (i = 0; i < numc; i++)//把符号中的乘除处理掉，把所有的数变成分数
	{
		if (num1[newc][0] == 0 || num1[newc][1] == 0)
		{
			num1[newc][0] = num[i];
			num1[newc][1] = 1;
		}

		if (sym[j] == '*')
		{
			num1[newc][0] *= num[i + 1];
		}
		else if (sym[j] == '/')
		{
			num1[newc][1] *= num[i + 1];
		}
		/*else if (sym[j] == '\'')
		{
			num1[newc][0] = num1[newc][0] * num[i + 2] + num1[newc][0] * num[i + 1] / num[i];
			num1[newc][1] *= num[i + 2];
			i++;
			j++;
		}*/
		else
		{
			newc++;
		}
		j++;
	}
	num1[newc][1] = 1;
	int gbs = 0;//最小公倍数
	int ans[2] = { num1[0][0],num1[0][1] };
	i = 0;
	for (j = 0; j < symc; j++)
	{
		if (sym[j] == '+')
		{
			/*if (num1[i + 1][1] == 0)
				num1[i + 1][1] = 1;*/
			gbs = lcm(ans[1], num1[i + 1][1]);
			ans[0] = ans[0] * gbs / ans[1] + num1[i + 1][0] * gbs / num1[i + 1][1];
			ans[1] = gbs;
			i++;
		}
		else if (sym[j] == '-')
		{
			gbs = lcm(ans[1], num1[i + 1][1]);
			ans[0] = ans[0] * gbs / ans[1] - num1[i + 1][0] * gbs / num1[i + 1][1];
			ans[1] = gbs;
			i++;
		}
	}
	int gys = gcd(ans[0], ans[1]);
	ans[0] /= gys;//分子
	ans[1] /= gys;//分母
	if (ans[0] <= 0 || ans[1] <= 0)
	{
		Spawn1(1, m, count);
		ifstream file;
		char lineData[30];
		file.open("L:\\wrong.txt", ios::in);
		file.getline(lineData, 255);
		ModifyLineData("L:\\Exercise.txt", count+1, lineData);
		return 1;
	}
	else
	{
		ofstream file;
		file.open("L:\\Answers.txt", ios::app); //以追加模式打开文件
		file << count + 1 << ".";
		if (ans[1] == 1)//分母为1时不必输出分数
			file << ans[0] << endl;
		else
		{
			if (ans[0] / ans[1] != 0)
			file << ans[0] / ans[1] << "'" << ans[0] % ans[1] << "/" << ans[1] << endl;
			else
			file << ans[0] % ans[1] << "/" << ans[1] << endl;
		}
		file.close(); //关闭文件
		return 0;
	}
}


void ReadLineData(string fileName, int lineNum, char* data)
{
	ifstream in;
	in.open(fileName);

	int line = 1;
	while (in.getline(data, 1024))
	{
		if (lineNum == line)
		{
			break;
		}
		line++;
	}

	in.close();
}

void answer(int n,int m)
{
	//ifstream file;
	//file.open("L:\\Exercise.txt", ios::in); //以只读方式打开文件ofstream mf("L:\\Grade.txt");// 创建并打开一个文本文件*************************************************
	int i, j, len, numc, symc;//n记录题目数量,i、j用于for循环,numc表示已记录多少数字,symc表示已记录多少符号
	for (i = 0; i < n; i++)
	{
		char txt[50] = { 0 };
		char sym[20] = { 0 };
		int num[20] = { 0 };
		ReadLineData("L:\\Exercise.txt", i+1, txt);
		numc = symc = 0;
		for (j = 6; j < strlen(txt); j++)
		{
			if (txt[j] <= '9'&&txt[j] >= '0')//将字符型的数据转换为整型并存入num数组中，记录数字
			{
				len = 1;
				while (txt[j + len] <= '9'&&txt[j + len] >= '0')
					len++;
				j += len - 1;
				while (len != 0)
				{
					num[numc] += (txt[j - len + 1] - '0')*pow(10, len - 1);
					len--;
				}
				numc++;
				continue;
			}
			else if (txt[j] == '+' || txt[j] == '-' || txt[j] == '*' || txt[j] == '/' || txt[j] == '\'' || txt[j] == '(' || txt[j] == ')')//记录符号
			{
				sym[symc++] = txt[j];
			}
			else if (txt[j] == ' ' || txt[j] == '=')
				continue;
			else//异常处理
			{
				cout << "第" << i + 1 << "个算式有异常符号" << endl;
				break;
			}
		}
		if (calculate(num, sym, numc, symc, i, m) == 1)
		{
			i--;
		}
	}
	//file.close();
}

void correct(char ans1[][20], char ans2[][20], int n)
{
	int i = 0;
	int r = 0;
	int w = 0;
	int right[20] = { 0 };
	int wrong[20] = { 0 };
	for (i = 0; i < n; i++)
	{
		if (strcmp(ans1[i], ans2[i]) == 0)
			right[r++] = i;
		else
			wrong[w++] = i;
	}
	ofstream mf("L:\\Grade.txt");// 创建并打开一个文本文件
	mf << "Correct:" << r << "(";
	for (i = 0; i < r; i++)
	{
		mf << right[i] + 1;
		if (i != r - 1)
			mf << ",";
	}
	mf << ")" << endl;
	mf << "Wrong:" << w << "(";
	for (i = 0; i < w; i++)
	{
		mf << wrong[i] + 1;
		if (i != w - 1)
			mf << ",";
	}
	mf << ")" << endl;
	mf.close();// 关闭文件
}

void grade(int n)
{
	int i;
	char ans1[10001][20];
	char ans2[10001][20];
	ifstream file;
	file.open("L:\\Answers.txt", ios::in); //以只读方式打开文件
	for (i = 0; i < n; i++)
	{
		file.getline(ans1[i], 255); //读文件
	}
	file.close(); //关闭文件
	file.open("L:\\Stuanswers.txt", ios::in); //以只读方式打开文件
	for (i = 0; i < n; i++)
	{
		file.getline(ans2[i], 255); //读文件
	}
	file.close(); //关闭文件
	correct(ans1, ans2, n);
}

void preanswer(int n)
{
	ofstream file;
	file.open("L:\\Stuanswers.txt");
	int i;
	for (i = 0; i < n; i++)
	{
		file << i + 1 << "." << endl;
	}
	file.close(); //关闭文件
}
int main()
{
	int n;
	cout << "请输入题目数量" << endl;
	cin >> n;
	int m;
	cout << "请输入数值范围" << endl;
	cin >> m;
	Spawn(n, m);
	ofstream file;
	file.open("L:\\Answers.txt");
	file.close();
	answer(n,m);
	preanswer(n);
	cout << "请现在打开Stuanswers.txt文件并输入你的答案" << endl;
	system("pause");
	grade(n);
	return 0;
}



// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
