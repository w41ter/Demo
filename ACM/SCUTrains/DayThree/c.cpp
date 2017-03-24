#include <iostream>
#include <cstring>

using namespace std;
int T;
char c[20];
int num[] = {12,6,4,3,2,1};
int _flag[6];
int count;

int main()
{
    cin >> T;
    while(T--)
    {
        count = 0;
        memset(_flag,0,sizeof(_flag));
        cin >> c;
        for(int i = 0;i < 6;i++)
        {
            for(int j = 0;j < num[i];j++)
            {
                bool flag = true;
                for(int k = j, kk = 0;kk < (12 / num[i]);k += num[i],kk++)
                {
                    if(c[k] == 'O')
                    {
                        flag = false;
                        break;
                    }
                }
                if(flag)
                {
                    _flag[i] = 1;
                    count++;
                    break;
                }
            }
        }
        cout << count;
        for(int i = 0;i < 6;i++)
        {
            if(_flag[i])
                cout << " " << 12 / num[i] << "x" << num[i];
        }
        cout << endl;

    }
    return 0;
}