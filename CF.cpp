#include<icrsint.h>
#include<iostream>
#include<iomanip>
#include<string>
#include <fstream>

using namespace std;
#import "c:\program files\common files\system\ado\msado15.dll"  no_namespace rename("EOF", "adoEOF")
 
#define MAXVEX 400                       /* ��󶥵���,Ӧ���û����� */
 
typedef string VertexType;               /* ��������Ӧ���û����� */
typedef int EdgeType;                    /* ���ϵ�Ȩֵ����Ӧ���û����� */
 
typedef struct EdgeNode                  /* �߱���  */
{
string adjvex;                       /* �ڽӵ���,�洢�ö����Ӧ���±� */
int weight;                          /* ���ڴ洢Ȩֵ,���ڷ���ͼ���Բ���Ҫ */
struct EdgeNode *next;               /* ����,ָ����һ���ڽӵ� */
} EdgeNode;
 
 
typedef struct VextexNode      /* ������� */
{
string  data;              /* ������,�洢������Ϣ */
EdgeNode *firstedge;      /* �߱�ͷָ�� */
} VextexNode, AdjList[MAXVEX];
 
EdgeNode A[MAXVEX*5];                        //����ʹ��malloc���������(������ȷ�����ж�)̫��ʱ���ˣ���Ϊ��ͳ�Ƶ���MAXVEX����ͬ���û���һ��ʼ�Ҿ���ʶ���ˣ���ʵ*2�ǲ����ģ����Գ�10    
int a=0;                                      //ָʾEdgeNode
 
EdgeNode B[MAXVEX*5];                        //�ڶ�����ʹ��
int b=0;
 
VextexNode songtarget;
 
typedef struct
{
AdjList adjList;
//int numNodes, numEdges;           /* ͼ�е�ǰ�������ͱ��� */
} GraphAdjList;
 
 
//��һ����,�û�_�����ڽӱ��õ��Ĳ���
int i1,i2;
string su;
string suu;
int r;
//�ڶ����֣�����_�����õ����ڽӱ�
int s2=0; //һ�����ݺ���һ���û���һ�����������԰��û�ȡ��10000������Ҳ����10000*5
int c;      //��¼����������λ�ã���ָ�����˼���
int i3;                         //��λ�ظ��Ĺ�������λ��
int countsp,y,u; //y�������Ƿ����صĸ�������ڵ㣬Ĭ��û���ظ��ģ�u�����Һ͸����ڵ��ظ��Ĺ���������Ĭ��û���ظ���
EdgeNode *qe;         //Sp��main�������Ѿ�д��
//�������֣���Ŀ���Ĺ�������
string song;
int g4;
 
 
 
void main()
{   
GraphAdjList Gpp;
GraphAdjList *Gp;                  /*�û�_�����ڽӱ�*/
 
VextexNode Spp[MAXVEX*10];          //ʵ��ȡ�ø������Ǳ��û����
VextexNode *Sp;                  /*����_�����ڽӱ�*/
 
CoInitialize(NULL);
_ConnectionPtr  sqlSp;
HRESULT hr=sqlSp.CreateInstance(_uuidof(Connection));
 
if(FAILED(hr))
{
cout<<"_ConnectionPtr����ָ��ʵ����ʧ�ܣ�����"<<endl;
return ;
}
 
else {
 
try {
_bstr_t strConnect="Driver={sql server};server=202.38.79.135;uid=jinting;pwd=jinting;database=ihou12summer;";
//_bstr_t strConnect="Provider=SQLOLEDB;Server=127.0.0.1,1433;Database=PBMS;uid=sa;pwd=pp471006459;";
//_bstr_t strConnect="Provider=SQLOLEDB.1;Password=pp471006459;Persist Security Info=True;User ID=sa;"
//"Initial Catalog=PBMS;Data Source=127.0.0.1,1433";
//����������strConnect��䶼�����ã������Լ�ϲ��ѡ���ð�
//Ҫע���޸��û���uid������pwd�����ݿ���database�������������������Լ�sql server�����ݿ���Ϣ
sqlSp->Open(strConnect,"","",adModeUnknown);
}
catch(_com_error &e) {
cout<<e.Description()<<endl;
}
 
_RecordsetPtr m_pRecordset; //��¼������ָ�룬����ִ��SQL��䲢��¼��ѯ���
if(FAILED(m_pRecordset.CreateInstance( _uuidof( Recordset ))))
{
cout<<"��¼������ָ��ʵ����ʧ�ܣ�"<<endl;
return;
}
//char strSQL[]="SELECT * FROM  Books";
 
try {
m_pRecordset->Open("SELECT * FROM  Cover",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);//�����ݿ⣬ִ��SQL���
 
}
catch (_com_error &e)
{
cout<<e.Description()<<endl;
}
 
 
try {
m_pRecordset->MoveFirst();
 
for(i1=0;i1<MAXVEX;i1++) 
{
Gp=&Gpp; 
//cout<<(char*)(_bstr_t)(m_pRecordset->Fields->GetItem(_variant_t("UserID"))->Value)<<endl;
string su=(char*)(_bstr_t)(m_pRecordset->Fields->GetItem(_variant_t("UserID"))->Value);
//cout<<su<<endl;
 
if(i1==0){                                                     //��ʱ�û�����GpΪ�գ�����ִֻ��һ��
Gp->adjList[i1].data=su;
//cout<<Gp->adjList[i1].data<<endl;
Gp->adjList[i1].firstedge = NULL;/* ���߱���Ϊ�ձ� */
 
EdgeNode *pe;
pe=&A[a];

//cout<<(char*)(_bstr_t)(m_pRecordset->Fields->GetItem(_variant_t("ResourceID"))->Value)<<endl;
//cout<<"hello"<<endl;
string ss=(char*)(_bstr_t)(m_pRecordset->Fields->GetItem(_variant_t("ResourceID"))->Value);
//cout<<"hello"<<endl;
//cout<<"ss="<<ss<<endl;
 
pe->adjvex=ss;
//pe->adjvex=new string();                                          //���ԭ����malloc
    //pe->adjvex=&ss;
//cout<<pe->adjvex<<endl;
    //cout<<*(pe->adjvex)<<endl;
//cout<<"ss="<<ss<<endl;

pe->next=Gp->adjList[i1].firstedge;
Gp->adjList[i1].firstedge=pe;                                      /* ����ǰ�����ָ��ָ��pe */

//cout<<Gp->adjList[i1].data<<endl;
//cout<<Gp->adjList[i1].firstedge->adjvex<<endl;
a++;                                                                //EdgeNode�õ�һ��
}
 
else{

r=0;
for(i2=0;(i2<=i1)&&(r==0);i2++){
r=(Gp->adjList[i2].data==su);     
}
 
if(r==1){                                                           //�г��ֹ����û�,ֻ�б����п��ܳ���һ���û����ظ��ĸ���
i2=i2-1;
string ss=(char*)(_bstr_t)(m_pRecordset->Fields->GetItem(_variant_t("ResourceID"))->Value);/* �ڽ����Ϊj */
i1=i1-1;                                                        //����ȡ����ʵ�ʵĲ�ͬ��MAXVEX���û����п��ܳ���MAXVEX����¼,������ᵽ�������ִ���
 
EdgeNode *singing; 
int singasong=0;
for(singing=Gp->adjList[i2].firstedge;(singing!=NULL)&&(singasong==0);singing=singing->next)
singasong=(ss==singing->adjvex);

if(singasong==0){
EdgeNode *pe;
pe=&A[a];
/* ��pe��ָ��ָ��ǰ������ָ��Ľ�� */
pe->adjvex=ss;
pe->next=Gp->adjList[i2].firstedge;
Gp->adjList[i2].firstedge = pe;/* ����ǰ�����ָ��ָ��pe */
a++;
}

}
 
else{  //�³��ֵ��û�
Gp->adjList[i1].data=su;
Gp->adjList[i1].firstedge = NULL;/* ���߱���Ϊ�ձ� */
 
EdgeNode *pe;
pe=&A[a];
        string ss= (char*)(_bstr_t)(m_pRecordset->Fields->GetItem(_variant_t("ResourceID"))->Value);/* �ڽ����Ϊj */
/* ��pe��ָ��ָ��ǰ������ָ��Ľ�� */
pe->adjvex=ss; 
pe->next=Gp->adjList[i1].firstedge;
Gp->adjList[i1].firstedge = pe;/* ����ǰ�����ָ��ָ��pe */
//cout<<pe->adjvex<<endl;
a++;
}
 
}
m_pRecordset->MoveNext();
}
 
 
}
catch (_com_error &e)
{
cout << e.Description()<<endl;
}
 
 
}
 
cout<<Gp->adjList[6].data<<endl;
cout<<Gp->adjList[7].data<<endl;
cout<<Gp->adjList[19].data<<endl;                                 //208
cout<<Gp->adjList[0].firstedge->adjvex<<endl;                     //A
cout<<A[0].adjvex<<endl;                                          //B==A���������Ҳ����һ�ᣬ��Ȳ���������Ϊ��ͷ�巨
cout<<Gp->adjList[1].firstedge->adjvex<<endl;  
cout<<A[1].adjvex<<endl;
cout<<A[2].adjvex<<endl;                                          //Gp->adjList[1].firstedge->adjvex�Ǳ�ģ�ͷ�巨��A[i].adjvex�ǲ����
cout<<A[9].adjvex<<endl;
cout<<a<<endl;                                                    //����ʵ�ʲ���������������
cout<<"******************PART ONE END******************"<<endl;
 
 
//�����ǽ��û�_�����ڽӱ� ת���� ����_�����ڽӱ�
//�����µĿ��ǣ�����ڵ㣻���������ڵ�
 
 
for(i1=0;i1<MAXVEX;i1++)              // MAXVEXΪdata��ģ��10000;ʵ�ʾ���10000����ͬ���û�
 
{
EdgeNode *gs2,*gs_cursor2;        //1ָ������ڵ㣬2ָ��߽ڵ�
gs2=Gp->adjList[i1].firstedge;    //Gp,Sp��������ڵ�
gs_cursor2=gs2;                   //��gs_cursor2��ȫ������������������ӣ�gs_cursor2�̶��ڵ�һ���߽ڵ㴦��gs2�����߱���
 
if(gs2->next!=NULL){            //�û����ٳ�����������
 
while(gs2!=NULL){           //gs2Ϊÿһ�׸��������ڽӱ�
 
y=0;
if(s2>0)
for(countsp=0;(countsp<s2)&&(y==0);countsp++){
Sp=&Spp[countsp];
y=(Sp->data==gs2->adjvex);                            //gs2��������ڵ�ģ�gs_cursor2�ҹ�������
}
 
if(y==0){                                                 //�¸�,ָ�½�һ������ڵ�
Sp=&Spp[s2];
Sp->data=gs2->adjvex;
Sp->firstedge=NULL;
s2++;                                                 //��Spp������ڵ㣬�������㣻����������else������û�еģ�ָʾ���µ�����ڵ�Ľ���            
 
while(gs_cursor2!=NULL){
 
if(gs_cursor2!=gs2){                           //ֻ��ifû��else
qe=Sp->firstedge;                             //��ʼ�жϹ��������Ƿ��ǵ�һ�γ���
u=0;
c=0;
 
while((qe!=NULL)&&(u==0)){
u=(qe->adjvex==gs_cursor2->adjvex); 
qe=qe->next;
c++;
}
 
if(u==0){                                    //����������һ�γ��� 
EdgeNode *pe;
pe=&B[b];
pe->adjvex=gs_cursor2->adjvex;
pe->weight=1;
pe->next=Sp->firstedge;
Sp->firstedge = pe;
b++;
}
 
else{
qe=Sp->firstedge;
if(c!=1)
for(i3=1;i3<c;i3++)
qe=qe->next;
 
qe->weight++;
}
 
}//ֻ��ifû��else�Ľ���
 
gs_cursor2=gs_cursor2->next;
 
}
 
}//if�¸� y==0���µ�����ڵ�
 
 
else{                                                     //����ڵ��Ѿ����������
countsp=countsp-1;
Sp=&Spp[countsp];
while(gs_cursor2!=NULL){                              //��ε�һ�£�A��ʼ
 
if(gs_cursor2!=gs2){                           //ֻ��ifû��else
qe=Sp->firstedge;                             //��ʼ�жϹ��������Ƿ��ǵ�һ�γ���
u=0;
c=0;
 
while((qe!=NULL)&&(u==0)){
u=(qe->adjvex==gs_cursor2->adjvex); 
qe=qe->next;
c++;
}
 
if(u==0){                                    //����������һ�γ��� 
EdgeNode *pe;
pe=&B[b];
pe->adjvex=gs_cursor2->adjvex;
pe->weight=1;
pe->next=Sp->firstedge;
Sp->firstedge=pe;
b++;
}
 
else{
qe=Sp->firstedge;
if(c!=1)
for(i3=1;i3<c;i3++)
qe=qe->next;
 
qe->weight++;
}
 
}//ֻ��ifû��else�Ľ���
 
gs_cursor2=gs_cursor2->next;

}                                                                      //��ε�һ��A����
 
 
 
}//else,���������Ѿ����ֹ�                                              
 
 
gs2=gs2->next;                                    //���ûд���򲻱�������ִ�в���
gs_cursor2=Gp->adjList[i1].firstedge;             //�������Ĵ����ˣ����˽���1��Сʱ����ʱ��������¶�λ�����߹�ȥ�� 
}//while(gs2!=NULL)ѭ������
 

 
}//if �û�����2��
 
}//for i1
 
 
cout<<"hello"<<endl;
cout<<Spp[0].data<<endl;
cout<<Spp[0].firstedge->adjvex<<endl;
cout<<Spp[0].firstedge->next->adjvex<<endl;
cout<<Spp[1].data<<endl;
cout<<Spp[1].firstedge->adjvex<<endl;
cout<<Spp[1].firstedge->next->adjvex<<endl;
cout<<Spp[2].data<<endl;
cout<<Spp[2].firstedge->adjvex<<endl;
cout<<Spp[2].firstedge->next->adjvex<<endl;
cout<<Spp[3].data<<endl;
cout<<"hello"<<endl;
cout<<b<<endl;                                                                   //ʵ�ʲ�����������������ȡ20ʱӦ����6
cout<<"******************PART TWO END******************"<<endl;                  //�⼸�������10���������ͨ�����ģ���Ϊ�е�ָ��û����
 
 
 
 
//�������֣��û�����һ�׸裬�ҵ����׸�Ĺ�������
cout<<"������һ�׸�(����)"<<endl;
cin>>song;
 
int st=0;
 
for(g4=0;(g4<s2)&&(st==0);g4++){                                                    //s2�Ǵ�ĸ������鶥����
Sp=&Spp[g4];
st=(Sp->data==song);
}
g4=g4-1;
 
//VextexNode *songs;
//songs=&songtarget;
//songs->data=Sp[g4].firstedge->adjvex;
//songs->firstedge==NULL;

if(st==0)
cout<<"û��ƥ��ĸ���"<<endl;

else{
EdgeNode *lm;
 
if(Spp[g4].firstedge!=NULL){                                                       //Sppд����Sp������ԣ����ǵ�ַ�����Ǿ�������Ǵ��
cout<<"���׸����Ĺ���������:"<<endl;
for(lm=Spp[g4].firstedge;lm!=NULL;lm=lm->next){                                //Sppд����Sp������ԣ����ǵ�ַ�����Ǿ�������Ǵ��
cout<<lm->adjvex<<endl;
//EdgeNode *pe;
//pe=(EdgeNode*)malloc(sizeof(EdgeNode));

//pe->adjvex=lm->adjvex;
//pe->weight=lm->weight;
//pe->next=songs->firstedge;
//songs->firstedge=pe;
}

//for(lm=songs->firstedge;lm!=NULL;lm=lm->next)
// cout<<lm->adjvex<<endl;
 
}//if����
 

else
cout<<"��������׸�û�й�������"<<endl;
 

}//��ƥ������б�else����
 
cout<<"���������б����"<<endl;
cout<<g4<<endl;                                                       //Ŀ�������Spp�����λ�ã����Ĳ���Ҫ�õ��Ĺؼ�����
cout<<"******************PART THREE END******************"<<endl;
 
 
 
//g4�����Ĳ��ֵĽӿڣ�Spp[g4]��Ҫ�ҵĹ�������
//���Ĳ��֣��ҳ��Ƽ����׸��ǰ����û�
 
 
int i5=0;
int tar;
EdgeNode *js;
EdgeNode *tm;
 
int User[MAXVEX]={0};                                     //�����int User[MAXVEX]; ���ݹ�ģ20ʱ�������5��111��
 
for(i5=0;i5<MAXVEX;i5++)
for(js=Gp->adjList[i5].firstedge;js!=NULL;js=js->next)
for(tm=Spp[g4].firstedge;tm!=NULL;tm=tm->next)                                                
if((js->adjvex)==(tm->adjvex))
User[i5]++;



cout<<"�Ƽ���Top5�ͻ��б��ǣ�"<<endl;
for(int c=0;c<5;c++){                                     //���5��Ҫ�Ƽ����û�
tar=0;
//���˳�ֻ���罻��ϵ���û�


for(i5=0;i5<MAXVEX;i5++){
if(User[i5]>User[tar])
tar=i5;
}

  ifstream fin( "C:/Users/Administrator/Desktop/relation12summer.txt" );  // ��ȡ�����ļ�
     if (!fin)  //�����Ƿ�����ļ�
    {
       cout << "cannot open input file." ;  
    }
 
	int social=0;
    string i;
    
	while((fin >> i)&&(social==0)) {
		social=(Gp->adjList[tar].data==i);  
		//cout << i <<endl;  //���������̨
    }
    fin.close(); //�ر�fin��

	if(social==1){
	cout<<Gp->adjList[tar].data<<endl;
	User[tar]=-1;
	}
	else{
	c=c-1;
	User[tar]=-1;
	}

}//for(int c=0;c<5;c++)
 
 
cout<<"******************PART FOUR END******************"<<endl;
 
 
 
 
system("pause");
}
