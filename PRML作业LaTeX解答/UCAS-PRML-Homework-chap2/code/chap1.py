import numpy as np
import sympy as sp

def bayes_discrimination(a, pw1, pw2, X_1, X_2):
    N_1 = (X_1[0].shape)[0]  #获取样本个数
    N_2 = (X_2[0].shape)[0]  #获取样本个数

    m_1 = np.mean(X_1,axis=1)  #计算均值向量m_1
    m_1 = np.matrix(m_1).T
    m_2 = np.mean(X_2,axis=1)  #计算均值向量m_2
    m_2 = np.matrix(m_2).T

    Cov_1 = np.cov(X_1)  #计算协差阵Cov_1
    C_1 = Cov_1*(N_1-1)/(N_1)  #修正协差阵为C_1
    C_1 = np.matrix(C_1)
    Cov_2 = np.cov(X_2)  #计算协差阵Cov_2
    C_2 = Cov_2*(N_2-1)/(N_2)  #修正协差阵为C_2
    C_2 = np.matrix(C_2)

    det_C1 = np.linalg.det(C_1) #计算协差阵的行列式
    det_C2 = np.linalg.det(C_2) #计算协差阵的行列式

    ###求取贝叶斯判别函数d_i(x)###
    if(a == 0):
        x = np.matrix([sp.Symbol('x_1'), sp.Symbol('x_2'), sp.Symbol('x_3')]).T
    elif(a == 1):
        x = np.matrix([sp.Symbol('x_1'), sp.Symbol('x_2')]).T
    D_1 = np.log(pw1) - 0.5 * np.log(det_C1) - 1/2 * (x - m_1).T.dot(C_1.I).dot(x - m_1)  #判别函数d_1(x)
    D_2 = np.log(pw2) - 0.5 * np.log(det_C2) - 1/2 * (x - m_2).T.dot(C_2.I).dot(x - m_2)  #判别函数d_2(x)
    D = np.log(pw1) - np.log(pw2) + (m_1 - m_2).T.dot(C_1.I).dot(x) + \
        1/2 * m_2.T.dot(C_1.I).dot(m_2) - 1/2 * m_1.T.dot(C_1.I).dot(m_1)  #特殊情形下简化后的判别界面方程表达式
    print('d_1(x)=', sp.simplify(D_1), sep = '\n')  #打印判别函数d_1(x)
    print('d_2(x)=',sp.simplify(D_2), sep = '\n')  #打印判别函数d_2(x)
    print('d_1(x)-d_2(x)=',sp.simplify(D_1-D_2), sep = '\n')  #直接相减得到的通用判别界面方程
    print('D=',sp.simplify(D))  #特殊情形下判别界面方程的简化表达式
    return


if __name__ == "__main__":
    a = input('例题请输入0, 作业题请输入1: ')
    a = int(a)
if(a == 0):
    ##### 以下是例题的输入数据 #####
    pw1 = 0.5  ##这里输入先验概率pw1
    pw2 = 0.5  ##这里输入先验概率pw2
    X_1 = np.array([[1, 0, 1, 1], [0, 0, 1, 0], [1, 0, 0, 0]]) #输入样本矩阵X_1
    X_2 = np.array([[0, 0, 0, 1], [0, 1, 1, 1], [1, 1, 0, 1]]) #输入样本矩阵X_2
    ##### 以上是例题的输入数据 #####
    bayes_discrimination(a, pw1, pw2, X_1, X_2) ##输出判别函数和判别界面方程
elif(a == 1):
    ##### 以下是作业题的输入数据 #####
    pw1 = 0.5  #这里输入先验概率pw1
    pw2 = 0.5  #这里输入先验概率pw2
    X_1 = np.array([[0, 2, 2, 0],[0, 0, 2, 2]]) #输入样本矩阵X_1
    X_2 = np.array([[4, 6, 6, 4],[4, 4, 6, 6]]) #输入样本矩阵X_2
    ##### 以上是作业题的输入数据 #####
    bayes_discrimination(a, pw1, pw2, X_1, X_2) ##输出判别函数和判别界面方程