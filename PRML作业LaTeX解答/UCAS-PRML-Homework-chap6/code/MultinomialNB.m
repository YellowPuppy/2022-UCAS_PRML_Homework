n=input('请输入训练集的个数:n\n');
k=2; A=zeros(n,3);%存储训练集，用来学习
A(:,1)=input('请输入所有样本的第一个特征(用列向量表示)：\n');
A(:,2)=input('请输入所有样本的第二个特征(用列向量表示)：\n');
A(:,3)=input('请输入所有样本所属的类(用列向量表示)：\n');
x1=input('请输入需要预测的样本的第一个特征：1或2或3 \n');
x2=input('请输入需要预测的样本的第二个特征：S或M或L或N\n','s');
%计算其属于1类的概率
F1=zeros(1,3);
for i=1:n
    if A(i,3)==1
        F1(1,1)=F1(1,1)+1;
        if A(i,1)==x1
            F1(1,2)=F1(1,2)+1;
        end
        if A(i,2)==x2
            F1(1,3)=F1(1,3)+1;
        end
    end
end
C1=(F1(1,1)+1)/(n+k)*(F1(1,2)+1)/(F1(1,1)+3)*(F1(1,3)+1)/(F1(1,1)+4);
%属于2类的概率
F2=zeros(1,3);
for i=1:n
    if A(i,3)==-1
        F2(1,1)=F2(1,1)+1;
        if A(i,1)==x1
            F2(1,2)=F2(1,2)+1;
        end
        if A(i,2)==x2
            F2(1,3)=F2(1,3)+1;
        end
    end
end
C2=(F2(1,1)+1)/(n+k)*(F2(1,2)+1)/(F2(1,1)+3)*(F2(1,3)+1)/(F2(1,1)+4);
if C1>C2
    disp('该样本的类为1');
else if C1==C2
        disp('该样本的类为-1或1')
    else
        disp('该样本的类为-1')
    end
end