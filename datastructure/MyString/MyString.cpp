#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20
//串的存储结构
typedef struct SeqString {
	char list[MAXSIZE];
	int last;
}SeqString;
//串的函数申明
void init_SeqString(SeqString *seqstring);   //初始化
void create_SeqString(SeqString *seqstring, const char *str, int n);   //创建
void set_String(SeqString *S, const char *create, int n);   //一键创建串
void insert_SeqString(SeqString *S, int pos, SeqString T);   //插入
void del_SeqString(SeqString *S, int pos, int len);   //删除
int PMT_SeqString(SeqString st);    //通过求最大前后缀匹配数，返回副串挪动次数
int KMP_SeqString(SeqString S, SeqString T);   //KMP匹配算法

//稀疏矩阵存储结构
typedef struct TupNode{ //每个非零元素点
	int row; 
	int col;  
	int data; 
} TupNode; 
typedef struct THMatrix{  //稀疏矩阵的三元组形式
	int rows;
	int cols;
	int num;
	TupNode list[MAXSIZE];
}THMatrix;
//矩阵函数申明
void init_THMatrix(THMatrix *mat);   //初始化
void create_THMatrix(THMatrix *mat, int *m, int row, int col);   //创建
void turn_THMatrix(THMatrix *mat);   //转置

int main() {
	//原串
	SeqString S;

	//串1  两者和小于MAXSIZE
	set_String(&S, "helloworld", 10);
	SeqString T1;
	set_String(&T1, "56789", 5);
	insert_SeqString(&S, 5, T1);  // hello56789world

	//串2  两者和大于MAXSIZE 且 pos 和 T 长度和小于等于MAXSIZE
	set_String(&S, "helloworld", 10);
	SeqString T2;
	set_String(&T2, "012345678901", 12); // 10 + 12
	insert_SeqString(&S, 5, T2);  // hello012345678901wor

	//串3  两者和大于MAXSIZE 且 pos 和 T 长度和大于MAXSIZE
	set_String(&S, "helloworld", 10);
	SeqString T3;
	set_String(&T3, "01234567890123456789", 20);  // 10 + 20
	insert_SeqString(&S, 5, T3);  // hello012345678901234

	//删除
	set_String(&S, "helloworld", 10);
	del_SeqString(&S, 3, 4);  //helrld

	//KMP匹配
	set_String(&S, "ABCDEABCEABD", 12);
	SeqString test;
	set_String(&test, "EABD", 4);
	int ret_kmp = KMP_SeqString(S, test);  //return 9 

	//稀疏矩阵三元组形式的创建
	THMatrix mat;
	init_THMatrix(&mat);
	// 6*7
	int m[42] = { 0,0,1,0,0,0,0, 0,2,0,0,0,0,0, 3,0,0,0,0,0,0, 0,0,0,5,0,0,0, 0,0,0,0,6,0,0, 0,0,0,0,0,7,4};
	create_THMatrix(&mat, m, 6, 7); // num = 7  rows = 6  cols = 7   021 112 203 335 446 557 564
	//转置
	turn_THMatrix(&mat); // num = 7  rows =7  cols = 6   201 112 023 335 446 557 654
}

void init_SeqString(SeqString *seqstring) {
	seqstring->last = -1;
	for (int i = 0; i < MAXSIZE; i++)
	{
		seqstring->list[i] = '\0';
	}
}

void create_SeqString(SeqString *seqstring, const char *str, int n) {
	for (int i = 0; i < n; i++)
	{
		seqstring->list[i] = str[i];
		seqstring->last++;
	}
}

void set_String(SeqString *S, const char *create, int n) {
	init_SeqString(S);
	create_SeqString(S, create, n);
}

void insert_SeqString(SeqString *S, int pos, SeqString T) {  //pos表示第几个，插在pos之后
	//判断pos是否合法
	if (pos < 1 || pos >(S->last + 1))
		return;
	if ((S->last + 1 + T.last + 1) <= MAXSIZE) {  //S 和 T 长度和小于等于MAXSIZE
		//移动原串 i为移动次数，j为接收点下标
		for (int i = 0, j = S->last; i < S->last + 1 - pos; i++ ,j--)
		{
			S->list[j + T.last + 1] = S->list[j];
		}
		//加入新串 i为移动次数，j为接收点下标
		for (int i = 0, j = pos; i < T.last + 1; i++, j++)
		{
			S->list[j] = T.list[i];
		}
		S->last = S->last + 1 + T.last;
	}
	else {  //S 和 T 长度和大于MAXSIZE
		if (pos + T.last + 1 <= MAXSIZE) {  //pos 和 T 长度和小于等于MAXSIZE 裁剪S 
			//移动原串 i为移动次数，j为接收点下标
			int S_first = MAXSIZE - pos - (T.last + 1);  //S剩下的长度
			for (int i = 0, j = pos + S_first - 1; i < S_first; i++, j--)
			{
				S->list[j + T.last +1] = S->list[j];
			}
			//加入新串 i为移动次数，j为接收点下标
			for (int i = 0, j = pos; i < T.last + 1; i++, j++)
			{
				S->list[j] = T.list[i];
			}
			S->last = MAXSIZE - 1;
		}
		else {  //pos 和 T 长度和大于MAXSIZE S后半段全没 裁剪T
			//移入新串 i为移动次数，j为接收点下标
			for (int i = 0, j = pos; i < MAXSIZE - pos; i++, j++)
			{
				S->list[j] = T.list[i];
			}
			S->last = MAXSIZE - 1;
		}
	}
}

void del_SeqString(SeqString *S, int pos, int len) {  //pos表示第几个，从pos之后开始删
	//判断pos是否合法
	if (pos < 1 || pos > S->last + 1)
		return;
	//判断len是否合法
	if (pos + len > S->last + 1)
		return;     //hel lowo rld 3 4
	//计算各项指标
	int s_begin = pos + len;  //开移的下标
	int s_size = S->last + 1 - (pos + len);   //需要移动的长度/移动次数
	int s_left = S->last - len;   //剩下的长度
	//移动 i为次数，j为开移下标，k为开接下标
	for (int i = 0, j = s_begin, k = pos; i < s_size; i++, j++, k++)
	{
		S->list[k] = S->list[j];
	}
	//清零 i为次数，j为开清下标
	for (int i = 0, j = pos + s_left - 1; i < len; i++, j++)
	{
		S->list[j] = '\0';
	}
	S->last = S->last - len;
}

int KMP_SeqString(SeqString S, SeqString T) {  //成功返回开始是第几个，失败返回-1
	int count;
	int dis;
	SeqString str;  //计算T串挪动量
	init_SeqString(&str);
	for (int i = 0; i <= S.last; i++)
	{
		count = 0;
		dis = -1;
		for (int j = 0; j <= T.last; j++)
		{
			if (S.list[i + j] == T.list[j])
				count++;                    //CCABCDEABCEABD
			else                            //         EABD
				break;                      //0123456789
		}
		if (count == T.last + 1) {  //匹配完成
			return i + 1;
		}
		if (count >= 2) {
			//将匹配到的字符装入串str
			for (int z = 0; z < count; z++)
			{
				str.list[z] = S.list[i + z];
				str.last++;     
			}
			//用str计算T串挪动量
			dis = PMT_SeqString(str);
		}
		if (dis != -1)  //设置T串后移量
			i += dis -1;  //循环一次后i会自加，所以-1
	}
	return -1;
}

int PMT_SeqString(SeqString st) {  //返回T串需要后移的位数，如果没有前后缀匹配就返回-1
	if ((st.last + 1) < 2)
		return -1;
	int temp = 0; 
	int j;
	for (int i = 1, count = 0; i <= (st.last + 1) - 1; i++) //i 比较次数
	{
		j = (st.last + 1);  // j = 4  j比较几个就从倒数第几个开始向后
		for (int q = 0; q < i; q++) //q = 0 1  q每次都从第一个开始向后
		{
			if (st.list[q] == st.list[j - i]) {  //匹配成功1个
				count++;
			}
			j++;
		}
		if (count == i) {  //循环次数内全匹配
			if(i > temp)  //如果全匹配更大则替换
				temp = i;
		}
		count = 0;  //重置匹配因子
	}
	return (st.last + 1) - temp;
}

void init_THMatrix(THMatrix *mat) {
	mat->rows = 0;
	mat->cols = 0;
	mat->num = 0;
	TupNode temp;
	temp.col = 0;
	temp.row = 0;
	temp.data = 0;
	for (int i = 0; i < MAXSIZE; i++)
	{
		mat->list[i] = temp;
	}
}

void create_THMatrix(THMatrix *mat, int *m, int row, int col) {
	TupNode temp;
	int count = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (m[i*col + j] != 0) {
				temp.row = i;
				temp.col = j;
				temp.data = m[i*col + j];
				mat->list[mat->num] = temp;
				mat->num++;
				count++;
			}
		}
	}
	mat->rows = row;
	mat->cols = col;
}

void turn_THMatrix(THMatrix *mat) {
	if (0 == mat->num)
		return;
	int temp;
	for (int i = 0; i < mat->num; i++)
	{
		//内部元素行列转换
		temp = mat->list[i].row;
		mat->list[i].row = mat->list[i].col;
		mat->list[i].col = temp;
	}
	//三元组行列转换
	temp = mat->rows;
	mat->rows = mat->cols;
	mat->cols = temp;
}