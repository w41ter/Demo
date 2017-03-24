#include <iostream>
#include <algorithm>
using namespace std;

const int oo = 0x7fffffff;

int HM, AM, DM, HY, AY, DY, SH, SA, SD;

int judge(int hy,int ay,int dy, int hm,int am,int dm)//计算特定的攻击与防御之下,需要加多少hp
{
	if(am <= dy)
		return 0;
	int d1 = am - dy;
	int t1 = (hy + d1 - 1) / d1;
	int d2 = ay - dm;
	int t2 = (hm + d2 - 1) / d2;
	if(t1 > t2)
		return 0;
	int t = t2 * d1 - hy + 1;
	return t;
}
int main()
{
	cin >> HY >> AY >> DY >> HM >> AM >> DM >> SH >> SA >> SD;
	long long ans = 0;
	if(DY >= AM) 
	{//y防御高过m攻击时,只要攻击高过防御即可
		if(AY > DM)
			cout << 0 <<endl;
		else
		{
			ans = SA * (DM - AY + 1);
			cout << ans <<endl;
		}
	}
	else 
	{
		long long ans0 = 0;//保证y攻击高过m防御需要的代价
		if(AY <= DM)
		{
			ans0 = SA * (DM - AY + 1);
			AY = DM + 1;
		}
		ans = ans0 + judge(HY, AY, DY, HM, AM, DM) * SH;
		for(int i = 0; i * SA <= ans; i++) //枚举增加攻击防御的值并计算对应需要的hp,找最小值
		{
			for(int j = 0; i * SA + j * SD <= ans; j++)
			{
				long long tmp = ans0 + i * SA + j * SD + judge(HY, AY + i, DY + j, HM, AM, DM) * SH;
				if(tmp < ans)
				{
					ans = tmp;
				}
			}
		}
		cout<< ans <<endl;
	}
	return 0;
}