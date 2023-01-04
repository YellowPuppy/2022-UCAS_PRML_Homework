#include<bits/stdc++.h>
using namespace std;

int main() {
    int d, M, C;
    cout << "请依次输入样本维数d, 样本类别数M, 迭代步长C" << endl;
    cin >> d >> M >> C;
    vector<int> N(M);

    cout << "请依次输入各类别的样本个数" << endl;
    for(int i = 0; i < M; i++) {
        cin >> N[i];
    }

    int n = accumulate(N.begin(), N.end(), 0);
    vector<vector<float>> sample_init(n, vector<float>(d));
    cout << "请按照w1,w2,...,wM的类别顺序依次输入各类的模式样本" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < d; j++) {
            cout << " sample[" << i << "][" << j << "] = ";
            cin >> sample_init[i][j];
        }
    }
    
    vector<vector<float>> sample(n, vector<float>(d + 1));
    for(int i = 0; i < n; i++) {
        copy(sample_init[i].begin(), sample_init[i].end(), sample[i].begin());
        sample[i][d] = 1;
    }
    
    vector<vector<float>> w(M, vector<float>(d + 1, 0));
    vector<float> D(M);
    int cnt = 0;
    while (cnt != n) { //当被正确分类的样本数cnt等于总样本数n时, 结束循环
        cnt = 0; //每一轮迭代都需要把计数变量cnt清零
        for(int i = 0; i < n; i++) {
            for(int m = 0; m < M; m++) {
                D[m] = inner_product(w[m].begin(), w[m].end(), sample[i].begin(), 0.0);
            }
            int index = max_element(D.begin(), D.end()) - D.begin();
            int flag = count(D.begin(), D.end(), D[index]);
            if(i <= N[0] - 1 && i >= 0) { //第1类需要单独判断, 否则会越界
                if(index + 1 == 1 && flag == 1) {
                    cnt++;  //若当前样本被正确分类, 则权向量不变且对应的样本数自增一
                }
                else {  //若当前样本没被正确分类, 则按算法规则调整权向量
                    for(int m = 0; m < M; m++) {
                        if(D[m] >= D[0] && m != 0) {
                            for(int j = 0; j < d + 1; j++) {
                                w[m][j] = w[m][j] - C * sample[i][j];
                            }
                        }
                        else if(D[m] < D[0]) {
                            ;
                        }
                        else if(m == 0) {
                            for(int j = 0; j < d + 1; j++) {
                                w[m][j] = w[m][j] + C * sample[i][j];
                            }
                        }
                    }
                }
            }
            else {
                int Class = 2;
                for(int k = 2; k <= M; k++) {
                    int left = accumulate(N.begin(), N.begin() + k - 1, 0);
                    int right = accumulate(N.begin(), N.begin() + k, 0) - 1;
                    if(i >= left && i <= right) {
                        Class = k;  //求出当前样本所在的真实类别(即第k类)
                        break;
                    }
                }

                if(index + 1 == Class && flag == 1) { 
                    cnt++;  //若当前样本被正确分类, 则权向量不变且对应的样本数自增一
                }

                else {  //若当前样本没被正确分类, 则按规则调整权向量
                    for(int m = 0; m < M; m++) {
                        if(D[m] >= D[Class - 1] && m != Class - 1) {
                            for(int j = 0; j < d + 1; j++) {
                                w[m][j] = w[m][j] - C * sample[i][j];
                            }
                        }
                        else if(D[m] < D[Class - 1]) {
                            ;
                        }
                        else if(m == Class - 1) {
                            for(int j = 0; j < d + 1; j++) {
                                w[m][j] = w[m][j] + C * sample[i][j];
                            }
                        }
                    }
                }
            }
        }
    }

    for(int i = 0; i < M; i++) {
        cout << "解向量w[" << i + 1 << "]的分量分别为: " << endl;
        for(int j = 0; j < d + 1; j++) {
            cout << " w[" << i + 1 << "][" << j + 1 << "] = " << w[i][j] << "," << endl;
        }
    }

    return 0;
}
