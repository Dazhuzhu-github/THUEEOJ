void mergeList(LinkList &HA,LinkList &HB,LinkList &HC){
/*HA和HB为非递减有序线性链表，合并为非递减有序线性链表HC
*HA.head是第一个结点*/
结点数据类型为
struct SNode{
    int data;
    SNode *next;
    SNode():data(0),next(NULL){}
};
void MergeList(LinkList &a, LinkList &b, LinkList &c)
{
    InitList(c);
    SNode *r, *p=a.head, *q=b.head;
    //p,q为待合并表头，r为合并的表尾
    c.head=p;
    if(!q){//b is vacant
        return;
        //不带返回值，类似break;
    }
    if(!p){//a is vacant
        c.head=q.head;
        return;
    }
    if(p->data<=q->data){//小的放前
        r=p;
        p=p->next;
    }else{
        c.head=q;
        r=q;
        q=q->next;
        r->next=p;
    }
    while(p&&q){
        if(p->data<=q->data){
            r=p;
            p=p->next;
        }else{
            r->next=q;
            r=r->next;
            q=q->next;
            r->next=p;
        }
    }
    if(q){r->next=q;}
    a.head=NULL;
    b.head=NULL;
}