#include "SMatrix.h"
#include <iostream>

using namespace std;

// 方阵构造函数：初始化一个 方阵，矩阵中元素全为1
SMatrix::SMatrix(int colNum)
{
    m_Col = colNum;
    m_Row = colNum;
    if (colNum < 0)
        cout << "Error : The colNum can't be negative!" << endl;
    else
    {
        alloc(m_Col, m_Row);
        for (int i = 0; i < colNum; i++)
            for (int j = 0; j < colNum; j++)
                m_pMatrix[i][j] = 0;
    }
}

// 一般矩阵构造函数：初始化一个 一般矩阵，矩阵中元素全为1
SMatrix::SMatrix(int rowNum, int colNum)
{
    m_Col = colNum;
    m_Row = rowNum;
    if (colNum < 0)
        cout << "Error : The colNum can't be negative!" << endl;
    else if (rowNum < 0)
        cout << "Error : The rowNum can't be negative!" << endl;
    else
    {
        alloc(m_Col, m_Row);
        for (int i = 0; i < rowNum; i++)
            for (int j = 0; j < colNum; j++)
                m_pMatrix[i][j] = 1;
    }
}

// 复制构造函数
SMatrix::SMatrix(const SMatrix& other)
{
    m_Col = other.m_Col;
    m_Row = other.m_Row;
    alloc(m_Col, m_Row); //将右边矩阵的行数和列数赋给左边的矩阵，便于进行之后的操作
    for (int i = 0; i < m_Row; i++)
    {
        for (int j = 0; j < m_Col; j++)
        {
            this->m_pMatrix[i][j] = other.m_pMatrix[i][j];
        }
    }
}

//移动复制构造函数
SMatrix::SMatrix(SMatrix&& copy_from_me)
{
    cout << "调用移动复制构造函数" << endl;
    this->m_Col = copy_from_me.m_Col;
    this->m_Row = copy_from_me.m_Row;
    this->m_pMatrix = copy_from_me.m_pMatrix;
    copy_from_me.m_pMatrix = nullptr; //右边矩阵移动复制结束后，将其指针设为空指针
                                      //以防止修改右边矩阵时破坏了左边矩阵
};

SMatrix::SMatrix(int m, int n, initializer_list<double> lst)
{
    m_Row = m;
    m_Col = n;
    alloc(m_Col, m_Row);
    for (int i = 0; i < m_Row; i++)
        for (int j = 0; j < m_Col; j++)
            this->m_pMatrix[i][j] = *(lst.begin() + i * n + j);
}

// 重载加法运算符加实现矩阵整体相加
SMatrix SMatrix::operator + (const SMatrix& rightM)
{
    SMatrix a;			//定义一个临时矩阵a，以存储运算结果后返回
    if (this->m_Col == rightM.m_Col && this->m_Row == rightM.m_Row)
    {
        a.alloc(m_Col, m_Row);
        a.setCol(m_Col);
        a.setRow(m_Row);
        for (int i = 0; i < this->m_Row; i++)
        {
            for (int j = 0; j < this->m_Col; j++)
            {
                a.m_pMatrix[i][j] = this->m_pMatrix[i][j] + rightM.m_pMatrix[i][j];
            }
        }
        return a;
    }
    else
    {
        cout << "两矩阵无法相加！" << endl;
        return 0;
    }
};

// 重载减法运算符加实现矩阵整体相减
SMatrix SMatrix::operator - (const SMatrix& rightM)
{
    SMatrix a;			//定义一个临时矩阵a，以存储运算结果后返回
    if (this->m_Col == rightM.m_Col && this->m_Row == rightM.m_Row)
    {
        a.alloc(m_Col, m_Row);
        a.setCol(m_Col);
        a.setRow(m_Row);
        for (int i = 0; i < this->m_Row; i++)
        {
            for (int j = 0; j < this->m_Col; j++)
            {
                a.m_pMatrix[i][j] = this->m_pMatrix[i][j] - rightM.m_pMatrix[i][j];
            }
        }
        return a;
    }
    else
    {
        cout << "两矩阵无法相减！" << endl;
        return 0;
    }
};

// 重载乘法运算符加实现矩阵数乘
SMatrix SMatrix::operator * (double k)
{
    cout << "调用重载乘法运算符" << endl;
    for (int i = 0; i < this->m_Row; i++)
    {
        for (int j = 0; j < this->m_Col; j++)
        {
            this->m_pMatrix[i][j] = this->m_pMatrix[i][j] * k;
        }
    }
    return *this;
};

// 重载乘法运算符加实现两矩阵相乘
SMatrix SMatrix::operator * (const SMatrix& rightM)
{
    SMatrix a(this->m_Row, rightM.m_Col); //定义一个临时矩阵a，以存储运算结果后返回
    if (this->m_Col == rightM.m_Row)	  //判断两矩阵能否相乘
    {
        for (int i = 0; i < a.m_Row; i++)
        {
            for (int j = 0; j < a.m_Col; j++)
            {
                a.m_pMatrix[i][j] = 0;
            }
        }
        for (int i = 0; i < this->m_Row; i++)
        {
            for (int j = 0; j < rightM.m_Col; j++)
            {
                for (int k = 0; k < rightM.m_Row; k++)
                {
                    a.m_pMatrix[i][j] += this->m_pMatrix[i][k] * rightM.m_pMatrix[k][j];
                }
            }
        } //三重循环实现矩阵相乘
        return a;
    }
    else
    {
        cout << "两矩阵无法相乘！" << endl;
        return 0;
    }
};

// 重载赋值运算符
SMatrix SMatrix::operator = (const SMatrix& rightM)
{
    if (this != &rightM) //判断等号两边矩阵是否相等，以防止自己给自己赋值，造成内存混乱，下同
    {
        delete[] m_pMatrix;
        m_Col = rightM.m_Col;
        m_Row = rightM.m_Row;
        alloc(m_Col, m_Row);  //将右边矩阵的行数和列数赋给左边的矩阵，便于进行之后的操作
        for (int i = 0; i < m_Row; i++)
        {
            for (int j = 0; j < m_Col; j++)
            {
                this->m_pMatrix[i][j] = rightM.m_pMatrix[i][j];
            }
        }
    }
    return *this;
};

// 重载移动赋值运算符
SMatrix SMatrix::operator = (SMatrix&& rightM)
{
    if (this != &rightM)
    {
        this->m_Col = rightM.m_Col;
        this->m_Row = rightM.m_Row;
        this->m_pMatrix = rightM.m_pMatrix;
        rightM.m_pMatrix = nullptr; //右边矩阵移动赋值结束后，将其指针设为空指针
                                    //以防止修改右边矩阵时破坏了左边矩阵
    }
    return *this;
};

//重载插入运算符实现矩阵直接输出
ostream& operator << (ostream& os, const SMatrix& rightM)
{
    for (int i = 0; i < rightM.m_Row; i++)
    {
        for (int j = 0; j < rightM.m_Col; j++)
        {
            if (j == 0)
                cout << " |  "; //为了美观，增加竖线分隔
            cout << rightM.m_pMatrix[i][j] << "  ";
        }
        cout << "|";
        cout << endl;
    }
    return os;
};

double SMatrix::getElement(int m, int n)
{
    return m_pMatrix[m][n];
};

//将矩阵（m, n）位置元素的值设为val，成功返回true, 失败返回错误提示
bool SMatrix::setElement(int m, int n, double val)
{
    if (m_pMatrix[m][n] = val)
        return true;
    else
    {
        cout << "设置失败" << endl;
        return false;
    }
};

//实现动态内存分配，将此部分独立出来，防止代码重复出现过于累赘
inline void SMatrix::alloc(int colNum, int rowNum)
{
    m_pMatrix = (double**)malloc(sizeof(double*) * rowNum);
    for (int i = 0; i < rowNum; i++)
    {
        m_pMatrix[i] = (double*)malloc(sizeof(double) * colNum);
    }
};

// 打印出矩阵的行数、列数及各元素的值
void SMatrix::show()
{
    cout << "矩阵行数为：" << m_Row << endl;
    cout << "矩阵列数为：" << m_Col << endl;
    cout << "矩阵各元素为：" << endl;
    for (int i = 0; i < m_Row; i++)
    {
        for (int j = 0; j < m_Col; j++)
        {
            if (j == 0)
                cout << " |  ";
            cout << m_pMatrix[i][j] << "  ";
        }
        cout << "|";
        cout << endl;
    }
};

void SMatrix::setCol(int colNum)
{
    m_Col = colNum;
}

void SMatrix::setRow(int rowNum)
{
    m_Row = rowNum;
}

SMatrix SMatrix::transpose()
{
    SMatrix a(this->m_Col, this->m_Row);
    for (int i = 0; i < m_Col; ++i)
        for (int j = 0; j < m_Row; ++j)
            a.m_pMatrix[i][j] = this->m_pMatrix[j][i];
    return a;
}

SMatrix inverse(SMatrix& a)
{
    int n = a.m_Col;
    SMatrix b(n, n);
    if (a.m_Col != a.m_Row)
    {
        cout << "矩阵不是方阵！" << endl;
    }
    else
    {

        int i, j, k;
        double max, temp;
        // 定义一个临时矩阵t
        double** t = new double* [n];       //分配一个指针数组，将其首地址保存在b中
        for (i = 0; i < n; i++)             //为指针数组的每个元素分配一个数组
            t[i] = new double[n];
        // 将a矩阵临时存放在矩阵t[n][n]中
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                t[i][j] = a.m_pMatrix[i][j];
            }
        }

        //初始化B为单位矩阵
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                b.m_pMatrix[i][j] = (i == j) ? (double)1 : 0;
            }
        }

        // 进行列主消元，找到每一列的主元
        for (i = 0; i < n; i++)
        {
            max = t[i][i];
            // 用于记录每一列中的第几个元素为主元
            k = i;
            // 寻找每一列中的主元元素
            for (j = i + 1; j < n; j++)
            {
                if (fabs(t[j][i]) > fabs(max))
                {
                    max = t[j][i];
                    k = j;
                }
            }
            //cout<<"the max number is "<<max<<endl;
            // 如果主元所在的行不是第i行，则进行行交换
            if (k != i)
            {
                // 进行行交换
                for (j = 0; j < n; j++)
                {
                    temp = t[i][j];
                    t[i][j] = t[k][j];
                    t[k][j] = temp;
                    // 伴随矩阵B也要进行行交换
                    temp = b.m_pMatrix[i][j];
                    b.m_pMatrix[i][j] = b.m_pMatrix[k][j];
                    b.m_pMatrix[k][j] = temp;
                }
            }
            if (t[i][i] == 0)
            {
                cout << "\nthe matrix does not exist inverse matrix\n";
                break;
            }
            // 获取列主元素
            temp = t[i][i];
            // 将主元所在的行进行单位化处理
            //cout<<"\nthe temp is "<<temp<<endl;
            for (j = 0; j < n; j++)
            {
                t[i][j] = t[i][j] / temp;
                b.m_pMatrix[i][j] = b.m_pMatrix[i][j] / temp;
            }
            for (j = 0; j < n; j++)
            {
                if (j != i)
                {
                    temp = t[j][i];
                    //消去该列的其他元素
                    for (k = 0; k < n; k++)
                    {
                        t[j][k] = t[j][k] - temp * t[i][k];
                        b.m_pMatrix[j][k] = b.m_pMatrix[j][k] - temp * b.m_pMatrix[i][k];
                    }
                }

            }

        }
        for (i = 0; i < n; i++)
        {
            delete[] t[i];
            t[i] = NULL;
        }
        delete[] t;
        t = NULL;
    }
    return b;
}

double* getLine(const SMatrix& a, int line)
{
    if (line < a.m_Row && line >= 0)
        return a.m_pMatrix[line];
    else
        cout << "line越界" << endl;
}
