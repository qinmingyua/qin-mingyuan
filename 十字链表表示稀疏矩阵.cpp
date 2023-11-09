#include<stdio.h>
#include<stdlib.h>

typedef struct OLNode 
{//定义十字链表结点
    int i, j;
    int val;
    struct OLNode* right, * down;
}OLNode, * OLink;

typedef struct CrossList
{//定义十字链表
    OLink* rhead, * chead;//定义行和列的头指针地址组（注意是指向指针的指针）
    int mu, nu, tu;
}CrossList;

void CreatMatrix_OL(CrossList* M, int m, int n, int t) 
{
    //创建一个m行n列容量为t的十字链表
    M->rhead = M->chead = NULL;
    M->mu = m;
    M->nu = n;
    M->tu = t;
    M->rhead = (OLink*)malloc(sizeof(OLink) * (m + 1));
    M->chead = (OLink*)malloc(sizeof(OLink) * (n + 1));
    //初始化行列链表头节点
    for (int k = 1; k <= m; k++) 
    {
        M->rhead[k] = NULL;
    }
    for (int k = 1; k <= n; k++) 
    {
        M->chead[k] = NULL;
    }
    //存储接收的数据
    int i, j, v;
    printf("请按照行号/列号/元素值输入元素\n");
    for (int k = 0; k < t; k++) 
    {
        int i, j, v;
        OLink p, q;
        printf("您现在正在输入第%d个元素\n", k + 1);
        scanf_s("%d %d %d", &i, &j, &v);
        p = (OLink)malloc(sizeof(OLNode));
        p->i = i;
        p->j = j;
        p->val = v;
        //如果数据所在行的头指针为空，或头指针的列大于数据的列，则数据位置即为头指针
        if (M->rhead[i] == NULL || M->rhead[i]->j > j) 
        {
            M->rhead[i] = p;
        }
        else 
        {//否则依次查找该元素插入位置
            for (q = M->rhead[i]; (q->right) && (q->right->j < j); q = q->right);
            p->right = q->right;
            q->right = p;
        }
        p->down = NULL;
        //列的操作同行的类似
        if (M->chead[j] == NULL || M->chead[j]->i > i) 
        {
            M->chead[j] = p;
        }
        else 
        {
            for (q = M->chead[j]; (q->down) && (q->down->i < i); q = q->down);
            p->down = q->down;
            q->down = p;
        }
        p->right = NULL;
    }
}
void show(CrossList M)
{ // 按矩阵形式输出M
    int i, j;
    OLink p;
    for (i = 1; i <= M.mu; i++)
    { // 从第1行到最后1行
        p = M.rhead[i]; // p指向该行的第1个非零元素
        for (j = 1; j <= M.nu; j++) // 从第1列到最后1列
            if (!p || p->j != j) // 已到该行表尾或当前结点的列值不等于当前列值
                printf("%d\t", 0); // 输出0
            else
            {
                printf("%d\t", p->val);
                p = p->right;
            }
        printf("\n");
    }
}
void add(CrossList M1, CrossList M2)
{
    int i;
    OLink p,temp1,temp2;
    for (i = 1; i <= M1.mu; i++)//一行一行处理
    {
        if (M2.rhead[i] == NULL)continue;//和M1的行对应的M2的行中没有元素则换M1的下一行
        else
        {
            if (M1.rhead[i] == NULL)//若M1的行中没有元素则把对应M2行第一个元素复制到M1中
            {
                p = (OLink)malloc(sizeof(OLink));
                p->j = M2.rhead[i]->j;
                p->i = M2.rhead[i]->i;
                p->val = M2.rhead[i]->val;
                M1.rhead[i] = p;
                p->right = NULL;
                M2.rhead[i] = M2.rhead[i]->right;//头节点位置前进
            }
            if (M2.rhead == NULL) continue;//和M1的行对应的M2的行中没有元素则换M1的下一行
            for (temp1 = M2.rhead[i];; temp1 = temp1->right)//遍历M2中某个行的元素
            {
                for (temp2 = M1.rhead[i];; temp2 = temp2->right)//遍历M1中某个行的元素
                {
                    if (temp2->j == temp1->j)//两数位置一样则相加并退出换下一个M2的元素判断
                    {
                        temp2->val += temp1->val;
                        break;
                    }
                    else if (temp2 == M1.rhead[i] && temp1->j < temp2->j)//头节点位置而且M2位置靠前，把M2元素插入进M1
                    {
                        p = (OLNode*)malloc(sizeof(OLNode));
                        p->i = temp1->i;
                        p->j = temp1->j;
                        p->val = temp1->val;
                        p->right = temp2->right;
                        p->right = temp2;
                        M1.rhead[i] = p;//头节点位置前进
                        break;
                    }
                    else if ((temp2->right == NULL || temp2->right->j > temp1->j) && temp1->j > temp2->j)
                    {
                        p = (OLNode*)malloc(sizeof(OLNode));//把M2的结点链接在M1后面
                        p->j = temp1->j;
                        p->i = temp1->i;
                        p->val = temp1->val;
                        p->right = temp2->right;
                        temp2->right = p;
                        break;
                    }

                }

                if (temp1->right == NULL) break;
            }
        }
    }
    printf("相加结果如下\n");
    show(M1);

}
void substract(CrossList M1, CrossList M2)
{
    int i;
    OLink p, temp1, temp2;
    for (i = 1; i <= M1.mu; i++)//一行一行处理
    {
        if (M2.rhead[i] == NULL)continue;//和M1的行对应的M2的行中没有元素则换M1的下一行
        else
        {
            if (M1.rhead[i] == NULL)//若M1的行中没有元素则把对应M2行第一个元素复制到M1中
            {
                p = (OLink)malloc(sizeof(OLink));
                p->j = M2.rhead[i]->j;
                p->i = M2.rhead[i]->i;
                p->val = M2.rhead[i]->val;
                M1.rhead[i] = p;
                p->right = NULL;
                M2.rhead[i] = M2.rhead[i]->right;//头节点位置前进
            }
            if (M2.rhead == NULL) continue;//和M1的行对应的M2的行中没有元素则换M1的下一行
            for (temp1 = M2.rhead[i];; temp1 = temp1->right)//遍历M2中某个行的元素
            {
                for (temp2 = M1.rhead[i];; temp2 = temp2->right)//遍历M1中某个行的元素
                {
                    if (temp2->j == temp1->j)//两数位置一样则相减并退出换下一个M2的元素判断
                    {
                        temp2->val -= temp1->val;
                        break;
                    }
                    else if (temp2 == M1.rhead[i] && temp1->j < temp2->j)//头节点位置而且M2位置靠前，把M2元素插入进M1
                    {
                        p = (OLNode*)malloc(sizeof(OLNode));
                        p->i = temp1->i;
                        p->j = temp1->j;
                        p->val = temp1->val-2* temp1->val;
                        p->right = temp2->right;
                        p->right = temp2;
                        M1.rhead[i] = p;//头节点位置前进
                        break;
                    }
                    else if ((temp2->right == NULL || temp2->right->j > temp1->j) && temp1->j > temp2->j)
                    {
                        p = (OLNode*)malloc(sizeof(OLNode));//把M2的结点链接在M1后面
                        p->j = temp1->j;
                        p->i = temp1->i;
                        p->val = temp1->val-2*temp1->val;
                        p->right = temp2->right;
                        temp2->right = p;
                        break;
                    }

                }

                if (temp1->right == NULL) break;
            }
        }
    }
    printf("相减结果如下\n");
    show(M1);
}
int main()
{
    CrossList M1;
    int rows1 = 0, cols1 = 0, nums1 = 0;
    printf("请输入矩阵1的行数\n");
    scanf_s("%d", &rows1);
    printf("请输入矩阵1的列数\n");
    scanf_s("%d", &cols1);
    printf("请输入矩阵1元素的个数\n");
    scanf_s("%d", &nums1);
    CreatMatrix_OL(&M1, rows1, cols1, nums1);
    printf("矩阵1如下\n");
    show(M1);
    /******************************************/
    CrossList M2;
    int rows2 = 0, cols2 = 0, nums2 = 0;
    printf("请输入矩阵2的行数\n");
    scanf_s("%d", &rows2);
    printf("请输入矩阵2的列数\n");
    scanf_s("%d", &cols2);
    printf("请输入矩阵2元素的个数\n");
    scanf_s("%d", &nums2);
    CreatMatrix_OL(&M2, rows2, cols2, nums2);
    printf("矩阵2如下\n");
    show(M2);
    /*************************/
    printf("请选择要进行的操作\n");
    printf("1:相加\n2:相减\n3:相乘\n");
    int flag = 0;
    scanf_s("%d", &flag);
    switch (flag)
    {
    case 1:add(M1, M2); break;
    case 2:substract(M1, M2); break;
   // case 3:mult(M1, M2); break;
    }
    return 0;

}

