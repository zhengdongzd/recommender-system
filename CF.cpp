#include<icrsint.h>
#include<iostream>
#include<iomanip>
#include<string>
#include <fstream>

using namespace std;
#import "c:\program files\common files\system\ado\msado15.dll"  no_namespace rename("EOF", "adoEOF")
 
#define MAXVEX 400                       /* 最大顶点数,应由用户定义 */
 
typedef string VertexType;               /* 顶点类型应由用户定义 */
typedef int EdgeType;                    /* 边上的权值类型应由用户定义 */
 
typedef struct EdgeNode                  /* 边表结点  */
{
string adjvex;                       /* 邻接点域,存储该顶点对应的下标 */
int weight;                          /* 用于存储权值,对于非网图可以不需要 */
struct EdgeNode *next;               /* 链域,指向下一个邻接点 */
} EdgeNode;
 
 
typedef struct VextexNode      /* 顶点表结点 */
{
string  data;              /* 顶点域,存储顶点信息 */
EdgeNode *firstedge;      /* 边表头指针 */
} VextexNode, AdjList[MAXVEX];
 
EdgeNode A[MAXVEX*5];                        //避免使用malloc；这个错误(编译正确，报中断)太费时间了，因为我统计的是MAXVEX个不同的用户，一开始我就意识到了，其实*2是不够的，索性乘10    
int a=0;                                      //指示EdgeNode
 
EdgeNode B[MAXVEX*5];                        //第二部分使用
int b=0;
 
VextexNode songtarget;
 
typedef struct
{
AdjList adjList;
//int numNodes, numEdges;           /* 图中当前顶点数和边数 */
} GraphAdjList;
 
 
//第一部分,用户_歌曲邻接表用到的参数
int i1,i2;
string su;
string suu;
int r;
//第二部分，歌曲_歌曲用到的邻接表
int s2=0; //一条数据含有一条用户和一条歌曲；所以按用户取得10000，歌曲也至多10000*5
int c;      //记录关联歌曲的位置，看指针走了几次
int i3;                         //定位重复的关联歌曲位置
int countsp,y,u; //y用来找是否有重的歌曲数组节点，默认没有重复的；u用来找和歌曲节点重复的关联歌曲，默认没有重复的
EdgeNode *qe;         //Sp在main函数里已经写了
//第三部分，找目标歌的关联歌曲
string song;
int g4;
 
 
 
void main()
{   
GraphAdjList Gpp;
GraphAdjList *Gp;                  /*用户_歌曲邻接表*/
 
VextexNode Spp[MAXVEX*10];          //实际取得歌曲总是比用户多的
VextexNode *Sp;                  /*歌曲_歌曲邻接表*/
 
CoInitialize(NULL);
_ConnectionPtr  sqlSp;
HRESULT hr=sqlSp.CreateInstance(_uuidof(Connection));
 
if(FAILED(hr))
{
cout<<"_ConnectionPtr对象指针实例化失败！！！"<<endl;
return ;
}
 
else {
 
try {
_bstr_t strConnect="Driver={sql server};server=202.38.79.135;uid=jinting;pwd=jinting;database=ihou12summer;";
//_bstr_t strConnect="Provider=SQLOLEDB;Server=127.0.0.1,1433;Database=PBMS;uid=sa;pwd=pp471006459;";
//_bstr_t strConnect="Provider=SQLOLEDB.1;Password=pp471006459;Persist Security Info=True;User ID=sa;"
//"Initial Catalog=PBMS;Data Source=127.0.0.1,1433";
//以上这三条strConnect语句都可以用！！看自己喜好选择用吧
//要注意修改用户名uid、密码pwd、数据库名database，这三个参数均是你自己sql server的数据库信息
sqlSp->Open(strConnect,"","",adModeUnknown);
}
catch(_com_error &e) {
cout<<e.Description()<<endl;
}
 
_RecordsetPtr m_pRecordset; //记录集对象指针，用来执行SQL语句并记录查询结果
if(FAILED(m_pRecordset.CreateInstance( _uuidof( Recordset ))))
{
cout<<"记录集对象指针实例化失败！"<<endl;
return;
}
//char strSQL[]="SELECT * FROM  Books";
 
try {
m_pRecordset->Open("SELECT * FROM  Cover",(IDispatch*)sqlSp,adOpenDynamic,adLockOptimistic, adCmdText);//打开数据库，执行SQL语句
 
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
 
if(i1==0){                                                     //这时用户数组Gp为空，本段只执行一次
Gp->adjList[i1].data=su;
//cout<<Gp->adjList[i1].data<<endl;
Gp->adjList[i1].firstedge = NULL;/* 将边表置为空表 */
 
EdgeNode *pe;
pe=&A[a];

//cout<<(char*)(_bstr_t)(m_pRecordset->Fields->GetItem(_variant_t("ResourceID"))->Value)<<endl;
//cout<<"hello"<<endl;
string ss=(char*)(_bstr_t)(m_pRecordset->Fields->GetItem(_variant_t("ResourceID"))->Value);
//cout<<"hello"<<endl;
//cout<<"ss="<<ss<<endl;
 
pe->adjvex=ss;
//pe->adjvex=new string();                                          //针对原来的malloc
    //pe->adjvex=&ss;
//cout<<pe->adjvex<<endl;
    //cout<<*(pe->adjvex)<<endl;
//cout<<"ss="<<ss<<endl;

pe->next=Gp->adjList[i1].firstedge;
Gp->adjList[i1].firstedge=pe;                                      /* 将当前顶点的指针指向pe */

//cout<<Gp->adjList[i1].data<<endl;
//cout<<Gp->adjList[i1].firstedge->adjvex<<endl;
a++;                                                                //EdgeNode用掉一个
}
 
else{

r=0;
for(i2=0;(i2<=i1)&&(r==0);i2++){
r=(Gp->adjList[i2].data==su);     
}
 
if(r==1){                                                           //有出现过的用户,只有本层有可能出现一个用户唱重复的歌曲
i2=i2-1;
string ss=(char*)(_bstr_t)(m_pRecordset->Fields->GetItem(_variant_t("ResourceID"))->Value);/* 邻接序号为j */
i1=i1-1;                                                        //我们取的是实际的不同的MAXVEX个用户，有可能超过MAXVEX条记录,这个不提到外面来又错了
 
EdgeNode *singing; 
int singasong=0;
for(singing=Gp->adjList[i2].firstedge;(singing!=NULL)&&(singasong==0);singing=singing->next)
singasong=(ss==singing->adjvex);

if(singasong==0){
EdgeNode *pe;
pe=&A[a];
/* 将pe的指针指向当前顶点上指向的结点 */
pe->adjvex=ss;
pe->next=Gp->adjList[i2].firstedge;
Gp->adjList[i2].firstedge = pe;/* 将当前顶点的指针指向pe */
a++;
}

}
 
else{  //新出现的用户
Gp->adjList[i1].data=su;
Gp->adjList[i1].firstedge = NULL;/* 将边表置为空表 */
 
EdgeNode *pe;
pe=&A[a];
        string ss= (char*)(_bstr_t)(m_pRecordset->Fields->GetItem(_variant_t("ResourceID"))->Value);/* 邻接序号为j */
/* 将pe的指针指向当前顶点上指向的结点 */
pe->adjvex=ss; 
pe->next=Gp->adjList[i1].firstedge;
Gp->adjList[i1].firstedge = pe;/* 将当前顶点的指针指向pe */
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
cout<<A[0].adjvex<<endl;                                          //B==A，这个错误也差了一会，相等不成立，因为是头插法
cout<<Gp->adjList[1].firstedge->adjvex<<endl;  
cout<<A[1].adjvex<<endl;
cout<<A[2].adjvex<<endl;                                          //Gp->adjList[1].firstedge->adjvex是变的，头插法；A[i].adjvex是不变的
cout<<A[9].adjvex<<endl;
cout<<a<<endl;                                                    //看看实际产生的下拉歌曲数
cout<<"******************PART ONE END******************"<<endl;
 
 
//下面是将用户_歌曲邻接表 转换成 歌曲_歌曲邻接表
//两层新的考虑：数组节点；关联歌曲节点
 
 
for(i1=0;i1<MAXVEX;i1++)              // MAXVEX为data规模，10000;实际就是10000个不同的用户
 
{
EdgeNode *gs2,*gs_cursor2;        //1指向数组节点，2指向边节点
gs2=Gp->adjList[i1].firstedge;    //Gp,Sp都是数组节点
gs_cursor2=gs2;                   //用gs_cursor2找全与自身相异的所有曲子；gs_cursor2固定在第一个边节点处，gs2往下走遍历
 
if(gs2->next!=NULL){            //用户至少唱过两首曲子
 
while(gs2!=NULL){           //gs2为每一首歌曲建立邻接表
 
y=0;
if(s2>0)
for(countsp=0;(countsp<s2)&&(y==0);countsp++){
Sp=&Spp[countsp];
y=(Sp->data==gs2->adjvex);                            //gs2是找数组节点的，gs_cursor2找关联歌曲
}
 
if(y==0){                                                 //新歌,指新建一个数组节点
Sp=&Spp[s2];
Sp->data=gs2->adjvex;
Sp->firstedge=NULL;
s2++;                                                 //建Spp的数组节点，歌曲顶点；这句在下面的else里面是没有的，指示着新的数组节点的建立            
 
while(gs_cursor2!=NULL){
 
if(gs_cursor2!=gs2){                           //只有if没有else
qe=Sp->firstedge;                             //开始判断关联歌曲是否是第一次出现
u=0;
c=0;
 
while((qe!=NULL)&&(u==0)){
u=(qe->adjvex==gs_cursor2->adjvex); 
qe=qe->next;
c++;
}
 
if(u==0){                                    //关联歌曲第一次出现 
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
 
}//只有if没有else的结束
 
gs_cursor2=gs_cursor2->next;
 
}
 
}//if新歌 y==0，新的数组节点
 
 
else{                                                     //数组节点已经有这个顶点
countsp=countsp-1;
Sp=&Spp[countsp];
while(gs_cursor2!=NULL){                              //大段的一致，A开始
 
if(gs_cursor2!=gs2){                           //只有if没有else
qe=Sp->firstedge;                             //开始判断关联歌曲是否是第一次出现
u=0;
c=0;
 
while((qe!=NULL)&&(u==0)){
u=(qe->adjvex==gs_cursor2->adjvex); 
qe=qe->next;
c++;
}
 
if(u==0){                                    //关联歌曲第一次出现 
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
 
}//只有if没有else的结束
 
gs_cursor2=gs_cursor2->next;

}                                                                      //大段的一致A结束
 
 
 
}//else,关联歌曲已经出现过                                              
 
 
gs2=gs2->next;                                    //这句没写程序不报错，就是执行不完
gs_cursor2=Gp->adjList[i1].firstedge;             //这是最大的错误了，查了将近1个小时，这时如果不重新定位它就走过去了 
}//while(gs2!=NULL)循环结束
 

 
}//if 用户至少2首
 
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
cout<<b<<endl;                                                                   //实际产生的下拉各区属，取20时应该是6
cout<<"******************PART TWO END******************"<<endl;                  //这几句测试在10的情况下是通不过的，因为有的指针没定义
 
 
 
 
//第三部分，用户输入一首歌，找到这首歌的关联歌曲
cout<<"请输入一首歌(数字)"<<endl;
cin>>song;
 
int st=0;
 
for(g4=0;(g4<s2)&&(st==0);g4++){                                                    //s2是存的歌曲数组顶点数
Sp=&Spp[g4];
st=(Sp->data==song);
}
g4=g4-1;
 
//VextexNode *songs;
//songs=&songtarget;
//songs->data=Sp[g4].firstedge->adjvex;
//songs->firstedge==NULL;

if(st==0)
cout<<"没有匹配的歌曲"<<endl;

else{
EdgeNode *lm;
 
if(Spp[g4].firstedge!=NULL){                                                       //Spp写成了Sp，编译对，都是地址，但是具体输出是错的
cout<<"这首歌曲的关联歌曲有:"<<endl;
for(lm=Spp[g4].firstedge;lm!=NULL;lm=lm->next){                                //Spp写成了Sp，编译对，都是地址，但是具体输出是错的
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
 
}//if结束
 

else
cout<<"输入的这首歌没有关联歌曲"<<endl;
 

}//有匹配歌曲列表else结束
 
cout<<"关联歌曲列表结束"<<endl;
cout<<g4<<endl;                                                       //目标歌曲在Spp数组的位置，第四部分要用到的关键参数
cout<<"******************PART THREE END******************"<<endl;
 
 
 
//g4是三四部分的接口，Spp[g4]是要找的关联歌曲
//第四部分，找出推荐这首歌的前五个用户
 
 
int i5=0;
int tar;
EdgeNode *js;
EdgeNode *tm;
 
int User[MAXVEX]={0};                                     //如果是int User[MAXVEX]; 数据规模20时输出的是5个111；
 
for(i5=0;i5<MAXVEX;i5++)
for(js=Gp->adjList[i5].firstedge;js!=NULL;js=js->next)
for(tm=Spp[g4].firstedge;tm!=NULL;tm=tm->next)                                                
if((js->adjvex)==(tm->adjvex))
User[i5]++;



cout<<"推荐的Top5客户列表是："<<endl;
for(int c=0;c<5;c++){                                     //输出5个要推荐的用户
tar=0;
//过滤出只有社交关系的用户


for(i5=0;i5<MAXVEX;i5++){
if(User[i5]>User[tar])
tar=i5;
}

  ifstream fin( "C:/Users/Administrator/Desktop/relation12summer.txt" );  // 读取数据文件
     if (!fin)  //测试是否打开了文件
    {
       cout << "cannot open input file." ;  
    }
 
	int social=0;
    string i;
    
	while((fin >> i)&&(social==0)) {
		social=(Gp->adjList[tar].data==i);  
		//cout << i <<endl;  //输出到控制台
    }
    fin.close(); //关闭fin流

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
