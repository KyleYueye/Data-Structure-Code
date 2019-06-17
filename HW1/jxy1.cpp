/*
# 马尔科夫链
# MCM2018 C++代码模板 SJTU
# By: Mingran Peng
*/

//-------------------------------------------------------
/*
输入数据的说明及注意事项：
# 1. 由于马尔科夫链中状态数和长度不定，本程序采用vector进行存储
# 2. 简单来讲，vector就是一个可变长度的数组，其提供的方法可参阅具体文档
# 3. C++可视化异常麻烦，如需可视化可使用python或者matlab的代码
*/

//--------------------------------------------------------
#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>
using namespace std;
//输出0-1之间的随机数
double Rand()
{
	return double(rand())/double(RAND_MAX);
}
//Markov 函数以a和m作为输入参数，m表示过程总状态数
//a为任意长vector，每项的数字代表状态
//为效率起见函数无异常检查，请保证a中每一项取值为 [0,m-1]
//返回一个m×m矩阵，就是转移矩阵
vector< std::vector<double> > Markov(vector<int> a,int m)
{
	vector< std::vector<double> >res;
	int n =a.size();
	for (int i=0;i<m;i++)
		res.push_back(vector<double> (m,0));
	for(int i=0;i<n-1;i++)
		res[a[i]][a[i+1]]+=1;
	int sum=0;
	for(int i=0;i<m;i++)
	{
		sum=0;
		for(int j=0;j<m;j++)
			sum+=res[i][j];
		if(sum==0)
			for(int j=0;j<m;j++)
				res[i][j]=1/m;
		else
			for(int j=0;j<m;j++)
				res[i][j]/=sum;
	}
	return res;
}
//Generate 函数以trans，n，start作为输入参数，
//n表示希望生成的马尔科夫过程长度
//start为初始状态
//trans为转移矩阵
//为效率起见函数无异常检查，请保证转移矩阵行和为1，start是合法状态，n为正
//返回生成的马尔科夫过程
vector<int> Generate(vector< std::vector<double> >trans,int n,int start)
{
	vector<int> ans;
	int m=trans.size();
	int prev=start;
	int next=m-1;
	double pos;
	for(int i=0;i<n;i++)
	{
		next=m-1;
		pos=Rand();
		for(int j=0;j<m-1;j++)
		{
			if(pos<trans[prev][j])
			{
				next=j;
				break;
			}
			else
			{
				pos-=trans[prev][j];
			}
		}
		ans.push_back(next);
		prev=next;
	}
	return ans;
}
//main函数是为了测试所用，为了方便写了一些C++11的语法
//如果不会编译C++11,直接去掉即可，不影响前面两个函数的使用
int main()
{
	//a是一个马尔科夫链，t是a的转移矩阵，g是根据t生成的马尔科夫链，res是g的转移矩阵
	//比较res与g发现两者相差无几，证明了程序的正确性
	int a[24]={0,0,1,0,1,1,0,0,0,1,0,1,0,0,1,1,0,0,1,0,1,0,0,0};
	vector<int> b;
	for(const auto &i:a)
		b.push_back(i);
	auto t=Markov(b,2);
	auto g=Generate(t,100000,0);
	auto res=Markov(g,2);
	for(const auto &i:res)
	{
		for(const auto &j:i)
			cout<<j<<" ";
		cout<<endl;
	}
}