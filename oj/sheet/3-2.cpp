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
    SNode *r=c.head, *p=a.head->next, *q=b.head->next;
    //p,q为待合并表头，r为合并的表尾
    r->next=p;
    while(p&&q){
        if(p->data<=q->data){
            r=r->next;
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