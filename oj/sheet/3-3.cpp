void inverList(SeqList &L){
    if(L.len==0 || L.len==1)return;
    for(j=0;j<L.len/2;j++){
        ElenType temp=L.list[j];
        L.list[j]=L.list[L.len-j-1];
        L.list[L.len-j-i]=L.list[j];
    }
}

void InvertLinkst(LinkList &HL){
    SNode *q, *r, *p=HL.head;
    if(p==NULL) return;
    q=p->next;
    p->next=NULL;
    while(q)
    {
        r=q->next;
        q->next=p;
        p=q;
        q=r;
    }
    HL.head=p;
}

struct NODE{
	ElemType data;
	NODE *next;
	NODE():data(0),next(NULL){}
};
NODE *list_find(NODE *current, ElemType x)
{
    
}
