#include<bits/stdc++.h>
using namespace std;

int main() {
    int d, n1, n2, C;
    cout << "请依次输入样本维数d, w1类的样本数n1, w2类的样本数n2, 迭代步长C" << endl;
    cin >> d >> n1 >> n2 >> C;
    vector<vector<float>> omega_1(n1, vector<float>(d));
    vector<vector<float>> omega_2(n2, vector<float>(d));
    cout << "请依次输入w1类的模式样本" << endl;
    for(int i = 0; i < n1; i++) {
        for(int j = 0; j < d; j++) {
            cout << " omega_1[" << i << "][" << j << "] : ";
            cin >> omega_1[i][j];
        }
    }
    cout << "请依次输入w2类的模式样本" << endl;
    for(int i = 0; i < n2; i++) {
        for(int j = 0; j < d; j++) {
            cout << " omega_2[" << i << "][" << j << "] : ";
            cin >> omega_2[i][j];
        }
    }

    vector<vector<float>> sample_1(n1, vector<float>(d + 1));
    vector<vector<float>> sample_2(n2, vector<float>(d + 1));
    /*增广后的w1类的模式样本*/
    for(int i = 0; i < n1; i++) {
        copy(omega_1[i].begin(), omega_1[i].end(), sample_1[i].begin());
        sample_1[i][d] = 1;
    }
    /*增广后的w2类的模式样本*/
    for(int i = 0; i < n2; i++) {
        copy(omega_2[i].begin(), omega_2[i].end(), sample_2[i].begin());
        sample_2[i][d] = 1;
    }
    for(int i = 0; i < n2; i++) {
        for(int j = 0; j < d + 1; j++) {
            sample_2[i][j] = (-1.0) * sample_2[i][j];  //增广的w2训练样本乘以-1
        }
    }
    int n = n1 + n2;
    vector<vector<float>> sample(n, vector<float>(d + 1));
    copy(sample_1.begin(), sample_1.end(), sample.begin());
    copy(sample_2.begin(), sample_2.end(), sample.begin() + n1);
    vector<float> w(d + 1, 0);
    int cnt = 0;
    while (cnt != n) { //当被正确分类的样本数cnt等于总样本数n时, 结束循环
        cnt = 0; //计数变量清零
        for(int i = 0; i < n; i++) {
            if(inner_product(w.begin(), w.end(), sample[i].begin(), 0.0) > 0) {
                cnt++;  //若被正确分类, 则权向量不变且对应的样本数自增一
            }
            else {
                for(int j = 0; j < d + 1; j++) {  //若x(k)被错误分类,
                    w[j] = w[j] + C * sample[i][j];  //则w(k+1) = w(k) + C * x(k)
                }
            }
        }
    }
    cout << "解向量w的分量分别为" << endl;
    for(int i = 0; i < d + 1; i++) {
        cout << " w[" << i << "]"  << " = " << w[i];
    }
    return 0;
}
