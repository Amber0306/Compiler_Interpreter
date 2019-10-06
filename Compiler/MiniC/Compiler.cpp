#include "Compiler.h"
#include "Label.h"
#include "Action.h"
#include "Goto.h"






Compiler::Compiler(string CmdLine)
{




      isTokenClose = true;
      isFtClose = true;
      isStkClose = true;
      isAsmClose = true;
      isLogClose = true;
 isClrIn = false;
 isLexErrId  = false;
 lexErrChar = ' ';
 nextquad = 0;
 line=1;
 hasError=0;
 needOutSuppose=0;
 hasFile=0;
 fileName=CmdLine;
 //log.open((fileName + "_Log.txt").c_str(),ios::out);
 keywordstr[0] = "int";
 keywordstr[1] = "char";
 keywordstr[2] = "float";
 keywordstr[3] = "if";
 keywordstr[4] = "else";
 keywordstr[5] = "while";
 //code = "";
 code1 = "";
 tNum = 0;
 stk = "";
 initMaincode();
 //char c; //����nextChar()
 //do{c=nextChar();log<<c;}while(c!='#');log<<endl;
}

Compiler::Compiler()
{
      isTokenClose = true;
      isFtClose = true;
      isStkClose = true;
      isAsmClose = true;
      isLogClose = true;



 isClrIn = false;
 isLexErrId  = false;
 lexErrChar = ' ';
 nextquad = 0;
 line=1;
 hasError=0;
 needOutSuppose=0;
 hasFile=false;
 //fileName=CmdLine;
 //log.open((fileName + "_Log.txt").c_str(),ios::out);
 keywordstr[0] = "int";
 keywordstr[1] = "char";
 keywordstr[2] = "float";
 keywordstr[3] = "if";
 keywordstr[4] = "else";
 keywordstr[5] = "while";
 code = "";
 code1 = "";
 tNum = 0;
 stk = "";
 ss.empty();
 sos.empty();
 initMaincode();

 isClose = false;

}

Compiler::~Compiler()
{
 //log.close();
}

Token *Compiler::lexer()
{
 char c;
 int s=1;
 //Symbol *r;
 Token   *r;
 TokenGroup tg;
 r = new Token();
 //r=new Symbol();
 isLexErrId = false; //�����޷�ʶ��ID
 c=currentChar;  //֮ǰ�Ѿ���ʼ��
 //log.open((fileName + "_Log.txt").c_str(),ios::out);
 while(s){
  switch(s){
  case 1:
   if(c=='\x0A')line++;
   else if(isspace(c))
    s=1;
   else if(isalpha(c)||c=='_'){
    s=2;
    r->word=c;
   }
   else if(isdigit(c)){
    s=3;
    r->word=c;
   }
   else{
    switch(c){
    case '+':
    case '-':
     s=0;
     r->word=c;
     r->group='+';
     r->line=line;
     break;
    case '*':
    case '%':
     s=0;
     r->word=c;
     r->group='*';
     r->line=line;
     break;
    case '&':
    case '|':
     r->word=c;
     s=4;
     break;
    case '>':
    case '<':
     r->word=c;
     s=5;
     break;
    case '!':
     r->word=c;
     s=6;
     break;
    case '=':
     r->word=c;
     s=7;
     break;
    case ',':
    case ';':
    case '{':
    case '}':
    case '(':
    case ')':
    case '$':
     s=0;
     r->word=c;
     r->group=c;
     r->line=line;
     break;
    case '/':
     r->word=c;
     s=8;
     break;
    case '#':
     s=11;
     break;
    default:
     s=1;
     lexErrChar = currentChar;
     err(1,line);    //�޷�ʶ����ַ�
    }
   }
   c=nextChar();
   break;
  case 2:
   if(isalnum(c)||c=='_'){
    s=2;
    r->word+=c;
    c=nextChar();
   }
   else{
    s=0;
    r->line=line;
    r->group = 'r';
    if(!isLexErrId)
    {
         tg = IsKeyword(r->word,KEYNUM);


        /*if(r->word=="int")
                r->group='z';
         else if(r->word=="if")
                r->group='i';
         else if(r->word=="else")
                r->group='e';
         else if(r->word=="do")
                r->group='d';
         else if(r->word=="while")
                r->group='w';
        else if(r->word=="return")
                r->group='r';
        else
	*/

	switch(tg)
	{
	case _INT:
	case _CHAR:
	case _FLOAT:
		r->group = 'z';break;
          case _IF:
		r->group = 'i';break;
	case _ELSE:
		r->group = 'e';break;
	case _WHILE:
		r->group = 'w';break;
	default:
		r->group='@';break;
	}
    }

    else
    {
        cmes<<r->word<<endl;
    }
   }
   break;
  case 3:
   if(isdigit(c)){
    s=3;
    r->word+=c;
    c=nextChar();
   }
   else if(isalpha(c)||c=='_'){
    s=2;
    r->word+=c;
    err(2,line);     //���ֲ���ȷ�ı�ʶ��
    isLexErrId = true;
    c=nextChar();
   }
   else{
    s=0;
    r->line=line;
    r->group='n';
   }
   break;
  case 4:
   if((r->word.c_str())[0]==c){
    s=0;
    r->word+=c;
    r->group='&';
    r->line=line;
    c=nextChar();
   }
   else {
    s=1;
    err(3,line);       //�����ϣ�Ӧ�����﷨����ʱ���ֵĴ���
   }
   break;
  case 5:
   if(c=='='){
    r->word+=c;
    c=nextChar();
   }
   s=0;
   r->line=line;
   r->group='>';
   break;
  case 6:
   if(c=='='){
    r->word+=c;
    r->group='>';
    c=nextChar();
   }
   else{
    r->group='!';
   }
   s=0;
   r->line=line;
   break;
  case 7:
   if(c=='='){
    r->word+=c;
    r->group='>';
    c=nextChar();
   }
   else{
    r->group='=';
   }
   s=0;
   r->line=line;
   break;
  case 8:
   if(c=='*'){
    s=9;
    r->word="";
    c=nextChar();
   }
   else if( c == '/')
   {
		while(nextChar() != '/n');
		s = 0;
		break;
   }
   else
   {					///////////???????????
    r->line=line;
    r->group='*';
    s=0;
   }

   break;
  case 9:
   if(c=='*')
    s=10;
   else
    s=9;
   c=nextChar();
   break;
  case 10:
   if(c=='/')
    s=1;
   else if(c=='*')
    s=10;
   else
    s=9;
   c=nextChar();
   break;
  case 11:
   if(c=='\n'){
    s=1;
    line++;
   }
   else
    s=11;
   c=nextChar();
   break;
  default:
   s=1;
   err(0,line);            //����������ᷢ��
   c=nextChar();
  }
 }
 currentChar=c;
 log<<"�ʷ�����:"<<r->word<<endl;
 //log.close();
 return r;
}

Compiler::parser(bool islex)
{
 //log.open((fileName + "_Log.txt").c_str(),ios::app);
 log<<endl;
 log<<"*******************************************"<<endl;
 log<<"�﷨������ʼ..."<<endl;
 if(! islex)
 {
        preProcess();
        if(hasFile)
                in.open((fileName+".crr").c_str(),ios::in);
        currentChar=nextChar();//�ʷ���������ʼ��
 }
// Symbol *s=NULL; //����lexer()
// do{
//  if(s!=NULL)
//   delete s;
//  s=lexer();
//  log<<s->word;
//  log<<"    ";
//  log<<s->group;
//  log<<'\t';
//  log<<s->line;
//  log<<endl;
// }while(s->group!='#');
// delete s;

 int i = 0;
 int r,s=1,t=1;
 Token *ip ,*it=NULL;
 Symbol *s1,*s2,*s3,*s4,*s5,*s6,*s7,*m,*sip,*iq;    //������1����
 //Label *l1,*l2;
 TokenGroup tg;
 int quad,quad1;
 CTemp*  ct;
 ip = new Token;
 Id *id;
 ss.push(s);
 saveStack("����");
 if(!islex)
 {
        ip=lexer();
 }

 else
 {
        ip->word = cct[i].word;
        cout<<ip->word<<endl;
        ip->group = cct[i].group;
        ip->line = cct[i].line;
        i++;
 }
 while(t){
  s=ss.top();
  t=Action::lookUp(ip->group,s);
  if(t>0){						//�ƽ�
	if(ip->group == 'w'||ip->group == '&')	//�ƽ�ʱ���ı���״̬��
	{
		bk.push(nextquad);
		log<< "��ջ" << intTostr(nextquad) << endl;
	}
	if(ip->group == 'e')
	{
		nlist = nextquad;
		ft[nextquad].op = "j";
		ft[nextquad].p1 = "-";
		ft[nextquad].p2 = "-";
		ft[nextquad].res = "-1";
		ft[nextquad].next = -1;
		nextquad ++;

		bk.push(nextquad);
		log<< "��ջ" << intTostr(nextquad) << endl;
	}

   sip = new Symbol;
   sip->line = ip->line;
   sip->group = ip->group;
   sip->word  = ip->word;
   if(ip->group == 'z'||ip->group == 'n')
        sip->type = _INT;
   sos.push(sip);
   ss.push(t);
   saveStack("�ƽ�");
   if(it==NULL)			//???????
    if(!islex)
    {
        ip=lexer();
    }

     else
        {
               ip->word = cct[i].word;
                ip->group = cct[i].group;
                ip->line = cct[i].line;
                i++;
        }
   else
    ip=it;
   it=NULL;
  }

  else if(t<0)
  {
   switch(-t)
   {
   case 1://OK
    //D->@()S
    log<<"�﷨����:D->@()S"<<endl;
    ss.pop();
    ss.pop();
    ss.pop();
    ss.pop();
    s4=sos.top();
    sos.pop();
    s3=sos.top();
    sos.pop();
    s2=sos.top();
    sos.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='D';
    m->line=s1->line;
    sos.push(m);
	saveStack("��ԼD->@()S");
    //����
    if(s1->word!="main")
     err(5,s1->line);

	if(s4->nextlist != -1)						//�������
		backPath(s4->nextlist,nextquad);
   // code=s4->code;

	if(bk.size() != 0)
	{
		log<<"�����д���!"<<bk.size()<<endl;
	}
	//saveQuad(ip);

    delete s1;
    delete s2;
    delete s3;
    delete s4;
    break;
   case 2://OK
    //S->@=E;
    log<<"�﷨����:S->@=E;"<<endl;
    ss.pop();
    ss.pop();
    ss.pop();
    ss.pop();
    s4=sos.top();
    sos.pop();
    s3=sos.top();
    sos.pop();
    s2=sos.top();
    sos.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='S';
    m->line=s1->line;
    sos.push(m);
	saveStack("��ԼS->@=E");
    //����
    tg = lookup(s1->word);
    if(tg != _NKEY)									//û������
		if(tg == s3->type)
		{
			log<<"���ͼ��:S->@=E;"<<endl;			//������Ԫʽ
			ft[nextquad].op = "=";
			ft[nextquad].p1 = s3->word;
			ft[nextquad].p2 = "-";
			ft[nextquad].res = s1->word;
			nextquad ++;

			//if(IsBackpath(sos))
			//{
			//	bk.push(nextquad);					//���ڻ���
			//}

		       //	m->code=s3->code+"\tpop ax\n\tmov "+s1->word+",ax\n";
		}
		else
		{
			log<<"���ͼ��:S->@=E; �д���." <<endl;
			err(12,m->line);
		}

    else
     err(10,s1->line);
    delete s1;
    delete s2;
    delete s3;
    delete s4;

	//saveQuad(ip);

    break;
   case 3://OK
    //S->{W}
    log<<"�﷨����:S->{W}"<<endl;
    ss.pop();
    ss.pop();
    ss.pop();
    s3=sos.top();
    sos.pop();
    s2=sos.top();
    sos.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='S';
    m->line=s1->line;
    sos.push(m);
	saveStack("��ԼS->{W}");
    //����

	m->nextlist = s2->nextlist;

   // m->code=s2->code;
    delete s1;
    delete s2;
    delete s3;
    break;
   case 4://OK
    //S->i(G)S
    ss.pop();
    ss.pop();
    ss.pop();
    ss.pop();
    ss.pop();
    s5=sos.top();
    sos.pop();
    s4=sos.top();
    sos.pop();
    s3=sos.top();
    sos.pop();
    s2=sos.top();
    sos.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='S';
    m->line=s1->line;
    sos.push(m);
	saveStack("��ԼS->i(G)S");
    //����
    if(s1->word=="if"){//////???????????
    // l1=new Label;
    // m->code=s3->code+"\tpop ax\n\tcmp ax,1\n\tjne "+l1->text+"\n"+s5->code+l1->text+":\n";
    // delete l1;
     log<<"�﷨����:S->i(G)S"<<endl;

	 if(bk.size() != 0)
	 {
		 quad = bk.top();

		 //if(backPath(s3->truelist,quad))
		 backPath(s3->truelist,quad);
		 bk.pop();
		 log<<"��ջ"<<intTostr(quad)<<endl;
	 }
	m->nextlist = Merge(s3->falselist,s5->nextlist);
    }
    if(s1->word=="while"){
  //   l1=new Label;
  //   l2=new Label;
  //   m->code=l1->text+":\n"+s3->code+"\tpop ax\n\tcmp ax,1\n\tjne "+l2->text+"\n"+s5->code+"\tjmp "+l1->text+"\n"+l2->text+":\n";
  //   delete l1;
  //   delete l2;
     log<<"�﷨����:S->w(G)S"<<endl;

	 if(bk.size() != 0)
	 {
		 quad1 = bk.top();
		 //if(backPath(s3->truelist,quad1))
		 backPath(s3->truelist,quad1);
		 bk.pop();
		 log<<"��ջ"<<intTostr(quad1)<<endl;
	 }
	 else
		 err(13,m->line);

	 if(bk.size() != 0)
	 {
		 quad = bk.top();
		 //if(backPath(s5->nextlist,quad))
		 backPath(s5->nextlist,quad);
		 bk.pop();
		 log<<"��ջ"<<intTostr(quad)<<endl;
	 }
	 else
		 err(13,m->line);

	 m->nextlist = s3->falselist;

	 ft[nextquad].op = "j";
	 ft[nextquad].p1 = "-";
	 ft[nextquad].p2 = "-";
	 ft[nextquad].res = intTostr(quad);				//int ->string

	nextquad ++;
    }

    delete s1;
    delete s2;
    delete s3;
    delete s4;
    delete s5;

	//saveQuad(ip);
    break;
   case 5://OK
    //S->i(G)SeS
    ss.pop();
    ss.pop();
    ss.pop();
    ss.pop();
    ss.pop();
    ss.pop();
    ss.pop();
    s7=sos.top();
    sos.pop();
    s6=sos.top();
    sos.pop();
    s5=sos.top();
    sos.pop();
    s4=sos.top();
    sos.pop();
    s3=sos.top();
    sos.pop();
    s2=sos.top();
    sos.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='S';
    m->line=s1->line;
    sos.push(m);
	saveStack("��ԼS->i(G)SeS");
    //����
//    l1=new Label;
//    l2=new Label;
    if(s1->word=="if"){
      //		m->code=s3->code+"\tpop ax\n\tcmp ax,1\n\tjnz "+l1->text+"\n"+s5->code+"\tjmp "+l2->text+"\n"+l1->text+":\n"+s7->code+l2->text+":\n";
		log<<"�﷨����:S->i(G)SeS"<<endl;

		if(bk.size() != 0)
		{
			quad = bk.top();
			//if(backPath(s3->falselist,quad))				//ע��˳��
			backPath(s3->falselist,quad);
			bk.pop();
			log<<"��ջ"<<intTostr(quad)<<endl;
		}
		else
			err(13,m->line);
		 if(bk.size() != 0)
		{
			quad = bk.top();
			//if(backPath(s3->truelist,quad))
			backPath(s3->truelist,quad);
			bk.pop();

			log<<"��ջ"<<intTostr(quad)<<endl;

			m->nextlist = Merge(s7->nextlist,nlist);
			m->nextlist = Merge(m->nextlist,s5->nextlist);
		}
		 else
			 err(13,m->line);
	}
    else
     err(8,s6->line);
  //  delete l1;
  //  delete l2;
    delete s1;
    delete s2;
    delete s3;
    delete s4;
    delete s5;
    delete s6;
    delete s7;

	//saveQuad(ip);

    break;
   case 6://ok
    //S->w(G)S
    log<<"�﷨����:S->w(G)S"<<endl;
    ss.pop();
    ss.pop();
    ss.pop();
    ss.pop();
    ss.pop();
    s5=sos.top();
    sos.pop();
    s4=sos.top();
    sos.pop();
    s3=sos.top();
    sos.pop();
    s2=sos.top();
    sos.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='S';
    m->line=s1->line;
    sos.push(m);
	saveStack("��ԼS->w(G)S");
    //����

	if(bk.size() != 0)
	{
		quad1 = bk.top();
		//if(backPath(s3->truelist,quad1))
		backPath(s3->truelist,quad1);
			bk.pop();
		log<<"��ջ"<<intTostr(quad1)<<endl;
	}
	else
		err(13,m->line);

	if(bk.size() != 0)
	{
		quad = bk.top();
		//if(backPath(s5->nextlist,quad))
		backPath(s5->nextlist,quad);
			bk.pop();
		log<<"��ջ"<<intTostr(quad)<<endl;
	}
	else
		err(13,m->line);

	m->nextlist = s3->falselist;

	ft[nextquad].op = "j";
	ft[nextquad].p1 = "-";
	ft[nextquad].p2 = "-";
	ft[nextquad].res = intTostr(quad);				//int ->string

	nextquad ++;

	//saveQuad(ip);
    delete s1;
    delete s2;
    delete s3;
    delete s4;
    delete s5;
    break;
   case 7://OK
    //S->zL;
    log<<"�﷨����:S->zL;"<<endl;
    ss.pop();
    ss.pop();
    ss.pop();
    s3=sos.top();
    sos.pop();
    s2=sos.top();
    sos.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='S';
    m->line=s1->line;
    sos.push(m);
    //����
	saveStack("��ԼS->zL;");
	loadSymbol(s1->type);


    delete s1;
    delete s2;
    delete s3;

	//saveQuad(ip);
    break;
   case 8://OK
    //S->@(E);
    log<<"�﷨����:S->@(E);"<<endl;
    ss.pop();
    ss.pop();
    ss.pop();
    ss.pop();
    ss.pop();
    s5=sos.top();
    sos.pop();
    s4=sos.top();
    sos.pop();
    s3=sos.top();
    sos.pop();
    s2=sos.top();
    sos.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='S';
    m->line=s1->line;
    sos.push(m);
	saveStack("��ԼS->@(E)");
    //����
    if(s1->word=="cout"&&needOutSuppose)
	{
		m->code=s3->code+"\tpop ax\n\tcall outint\n";
		ft[nextquad].op = "cal";
		ft[nextquad].p1 = "outint";
		ft[nextquad].p2 = s3->word;
		ft[nextquad].res = "-";
		nextquad ++;

	}
    else
     err(6,s1->line);
    delete s1;
    delete s2;
    delete s3;
    delete s4;
    delete s5;

	//saveQuad(ip);
    break;
   case 9://OK
    //W->WS
    log<<"�﷨����:W->WS"<<endl;
    ss.pop();
    ss.pop();
    s2=sos.top();
    sos.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='W';
    m->line=s1->line;
    sos.push(m);
    //����
	saveStack("��ԼW->WS");
	if(bk.size() != 0)
	{
		quad = bk.top();
		//if(backPath(s1->nextlist,quad))
		backPath(s1->nextlist,quad);
			bk.pop();
		log<<"��ջ"<<intTostr(quad)<<endl;
	}

	m->nextlist = s2->nextlist;

	if(ip->word != "}")
	{
		bk.push(nextquad);
		log<<"��ջ"<<intTostr(nextquad)<<endl;
	}

   // m->code=s1->code+s2->code;
    delete s1;
    delete s2;
	//saveQuad(ip);
    break;
   case 10://OK
    //W->S
    log<<"�﷨����:W->S"<<endl;
    ss.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='W';
    m->line=s1->line;
    sos.push(m);
	saveStack("��ԼW->S");
    //����
	if(ip->word != "}")
	{
		bk.push(nextquad);
		log<<"��ջ"<<intTostr(nextquad)<<endl;
	}

	m->nextlist = s1->nextlist;
    //m->code=s1->code;
    delete s1;

	//saveQuad(ip);
    break;
   case 11://OK
    //L->@
    log<<"�﷨����:L->@"<<endl;
    ss.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='L';
    m->line=s1->line;
    sos.push(m);
	saveStack("��ԼL->@");
    //����
	Id* id ;
    if(lookup(s1->word) == _NKEY)							//������û���������϶��Ǳ�������
	{
		id = new Id;
		id->word = s1->word;
		id->type = _NKEY;
		symbolList.insert(symbolList.end(),*id);
	}
    else
     err(11,s1->line);

    delete s1;

	//saveQuad(ip);
    break;
   case 12://OK
    //L->L,@
    log<<"�﷨����:L->L,@"<<endl;
    ss.pop();
    ss.pop();
    ss.pop();
    s3=sos.top();
    sos.pop();
    s2=sos.top();
    sos.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='L';
    m->line=s1->line;
    sos.push(m);
	saveStack("��ԼL->L,@");
	//����
    if(lookup(s3->word) == _NKEY)
	{
		id = new Id;
		id->word = s3->word;
		id->type = _NKEY;
		symbolList.insert(symbolList.end(),*id);
	}
    else
     err(11,s3->line);
    delete s1;
    delete s2;
    delete s3;

	//saveQuad(ip);
    break;
   case 13://OK
    //G->G&M
    log<<"�﷨����:G->G&M"<<endl;
    ss.pop();
    ss.pop();
    ss.pop();
    s3=sos.top();
    sos.pop();
    s2=sos.top();
    sos.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='G';
    m->line=s1->line;
    sos.push(m);
	saveStack("��ԼG->G&M");
    //����

	if(IsBackpath(sos))
	{
		bk.push(nextquad);
		log<<"��ջ"<<intTostr(nextquad)<<endl;
	}

    if(s2->word=="&&")
	{
	       //	 m->code=s3->code+s1->code+"\tpop ax\n\tpop bx\n\tand ax,bx\n\tpush ax\n";
		 if(bk.size() != 0)
		 {
			 quad = bk.top();
			 //if(backPath(s1->truelist,quad))
			 backPath(s1->truelist,quad);
				 bk.pop();
			 log<<"��ջ"<<intTostr(quad)<<endl;
		 }
		 else
			 err(13,m->line);
		 m->truelist = Merge(s1->truelist,s3->truelist);
		 m->falselist = s3->falselist;
	}
    if(s2->word=="||")
	{
	     //	m->code=s3->code+s1->code+"\tpop ax\n\tpop bx\n\tor ax,bx\n\tpush ax\n";
		if(bk.size() != 0)
		{
			quad = bk.top();
			//if(backPath(s1->truelist,quad))
			backPath(s1->truelist,quad);
				bk.pop();
			log<<"��ջ"<<intTostr(quad)<<endl;
		}
		else
			err(13,m->line);

		m->falselist = Merge(s1->falselist,s3->falselist);
		m->truelist = s3->truelist;

	}
    delete s1;
    delete s2;
    delete s3;

	//saveQuad(ip);
    break;
   case 14://OK
    //G->M
    log<<"�﷨����:G->M"<<endl;
    ss.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='G';
    m->line=s1->line;
    sos.push(m);
	saveStack("��ԼG->M");
    //����
	if(IsBackpath(sos))
	{
		bk.push(nextquad);
		log<<"��ջ"<<intTostr(nextquad)<<endl;
	}

  //  m->code=s1->code;

	m->truelist = s1->truelist;
	m->falselist = s1->falselist;

    delete s1;

	//saveQuad(ip);
    break;
   case 15:
    //M->E>E
    log<<"�﷨����:M->E>E"<<endl;
    ss.pop();
    ss.pop();
    ss.pop();
    s3=sos.top();
    sos.pop();
    s2=sos.top();
    sos.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='M';
    m->line=s1->line;
    sos.push(m);
	saveStack("��ԼM->E>E");
    //����
  //  l1=new Label;
  //  l2=new Label;
  /*  m->code=s3->code+s1->code+"\tpop ax\n\tpop bx\n\tcmp ax,bx\n";
    if(s2->word==">")
     m->code+="\tjg "+l1->text+"\n";
    if(s2->word=="<")
     m->code+="\tjl "+l1->text+"\n";
    if(s2->word=="==")
     m->code+="\tje "+l1->text+"\n";
    if(s2->word=="!=")
     m->code+="\tjne "+l1->text+"\n";
    if(s2->word==">=")
     m->code+="\tjge "+l1->text+"\n";
    if(s2->word=="<=")
     m->code+="\tjle "+l1->text+"\n";
    m->code+="\tmov ax,0\n\tjmp "+l2->text+"\n"+l1->text+":\tmov ax,1\n"+l2->text+":\tpush ax\n";
     */
	m->truelist = nextquad;
	m->falselist = nextquad + 1;

	ft[nextquad].op = "j"+s2->word;
	ft[nextquad].p1 = s1->word;
	ft[nextquad].p2 = s3->word;
	ft[nextquad].res = "-1";
	ft[nextquad].next = -1;

	nextquad ++;

	ft[nextquad].op = "j";
	ft[nextquad].p1 = "-";
	ft[nextquad].p2 = "-";
	ft[nextquad].next = -1;
	ft[nextquad].res = "-1";
	nextquad++;

      //	delete l1;
   // delete l2;
    delete s1;
    delete s2;
    delete s3;

	//saveQuad(ip);
    break;
   case 16://OK
    //M->!M
    log<<"�﷨����:M->!M"<<endl;
    ss.pop();
    ss.pop();
    s2=sos.top();
    sos.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='M';
    m->line=s1->line;
    sos.push(m);
	saveStack("��ԼM->!M");
    //����
    m->code="\tpop ax\n\txor ax,ax\n\tpush ax\n";

	m->truelist = s1->falselist;
	m->falselist = s1->truelist;

    delete s1;
    delete s2;

	//saveQuad(ip);
    break;
   case 17://OK
    //M->(G)
    log<<"�﷨����:M->(G)"<<endl;
    ss.pop();
    ss.pop();
    ss.pop();
    s3=sos.top();
    sos.pop();
    s2=sos.top();
    sos.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='M';
    m->line=s1->line;
    sos.push(m);
	saveStack("��ԼM->(G)");
    //����
    m->code=s2->code;

	m->truelist = s2->falselist;
	m->falselist = s2->truelist;

    delete s1;
    delete s2;
    delete s3;

	//saveQuad(ip);
    break;
   case 18://OK
    //E->E+T
    log<<"�﷨����:E->E+T"<<endl;
    ss.pop();
    ss.pop();
    ss.pop();
    s3=sos.top();
    sos.pop();
    s2=sos.top();
    sos.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->line=s1->line;
    m->group='E';
    sos.push(m);
	saveStack("��ԼE->E+T");
    //����
	if(s3->type == s1->type)
	{
		if(s2->word=="+")
		{
			m->code=s3->code+s1->code+"\tpop ax\n\tpop bx\n\tadd ax,bx\n\tpush ax\n";

			ct = new CTemp;
			ft[nextquad].op = "+";
			ft[nextquad].p1 = s1->word;
			ft[nextquad].p2 = s3->word;
			ft[nextquad].res = ct->text;
			nextquad ++;
			m->type = s1->type;
			m->word = ct->text;

		}
		if(s2->word=="-")
		{
			m->code=s3->code+s1->code+"\tpop ax\n\tpop bx\n\tsub ax,bx\n\tpush ax\n";
			ct = new CTemp;
			ft[nextquad].op = "-";
			ft[nextquad].p1 = s1->word;
			ft[nextquad].p2 = s3->word;
			ft[nextquad].res = ct->text;
			nextquad ++;
			m->type = s1->type;
			m->word = ct->text;
		}
	}

	else
	{
		err(12,s3->line);
	}

    delete s1;
    delete s2;
    delete s3;

	//saveQuad(ip);
    break;
   case 19://OK
    //E->T
    log<<"�﷨����:E->T"<<endl;
    ss.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='E';
    m->line=s1->line;
    sos.push(m);
	saveStack("��ԼE->T");
    //����

	m->word = s1->word;
	m->type = s1->type;
    m->code=s1->code;

    delete s1;

	//saveQuad(ip);
    break;
   case 20://OK
    //T->T*F
    log<<"�﷨����:T->T*F"<<endl;
    ss.pop();
    ss.pop();
    ss.pop();
    s3=sos.top();
    sos.pop();
    s2=sos.top();
    sos.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='T';
    m->line=s1->line;
    sos.push(m);
	saveStack("��ԼT->T*F");
    //����
	if(s3->type == s1->type)
	{
		ct = new CTemp;
		ft[nextquad].p1 = s1->word;
		ft[nextquad].p2 = s3->word;
		ft[nextquad].res = ct->text;


		if(s2->word=="*")
		{
			m->code=s3->code+s1->code+"\tpop ax\n\tpop bx\n\tmov dx,0\n\tmul bx\n\tpush ax\n";
			ft[nextquad].op = "*";
		}
		if(s2->word=="/")
		{
			m->code=s3->code+s1->code+"\tpop ax\n\tpop bx\n\tmov dx,0\n\tdiv bx\n\tpush ax\n";
			ft[nextquad].op = "/";
		}
		if(s2->word=="%")
		{
			m->code=s3->code+s1->code+"\tpop ax\n\tpop bx\n\tmov dx,0\n\tdiv bx\n\tpush dx\n";
			ft[nextquad].op = "%";
		}

		nextquad ++;
		m->type = s1->type;
		m->word = ct->text;
	}
	else
	{
		err(12,s3->line);
	}
	delete s1;
    delete s2;
    delete s3;

	//saveQuad(ip);
    break;
   case 21://OK
    //T->F
    log<<"�﷨����:T->F"<<endl;
    ss.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='T';
    m->line=s1->line;
    sos.push(m);
    saveStack("��ԼT->F");
    //����

	m->type = s1->type;
	m->word = s1->word;

    m->code=s1->code;

    delete s1;

	//saveQuad(ip);
    break;
   case 22://OK
    //F->(E)
    log<<"�﷨����:F->(E)"<<endl;
    ss.pop();
    ss.pop();
    ss.pop();
    s3=sos.top();
    sos.pop();
    s2=sos.top();
    sos.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='F';
    m->line=s1->line;
    sos.push(m);
	saveStack("��ԼF->(E)");
    //����

	m->type = s2->type;
	m->word = s2->word;

    m->code=s2->code;
    delete s1;
    delete s2;
    delete s3;
	//saveQuad(ip);
    break;
   case 23://OK
    //F->@
    log<<"�﷨����:F->@"<<endl;
    ss.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='F';
    m->line=s1->line;
    sos.push(m);
	saveStack("��ԼF->@");
    //����
	tg = lookup(s1->word);
    if(tg != _NKEY)
	{
		m->code="\tmov ax,"+s1->word+"\n\tpush ax\n";

		m->word = s1->word;
		//m->type = s1->type;
                m->type = tg;
	}
    else
     err(10,s1->line);
    delete s1;

	//saveQuad(ip);
    break;
   case 24://OK
    //F->n
    log<<"�﷨����:F->n"<<endl;
    ss.pop();
    s1=sos.top();
    sos.pop();
    m=new Symbol;
    m->group='F';
    m->line=s1->line;
    sos.push(m);
	saveStack("��ԼF->n");
    //����

	m->word = s1->word;
	m->type = s1->type;

    m->code="\tmov ax,"+s1->word+"\n\tpush ax\n";
    delete s1;

	//saveQuad(ip);
    break;
   case 30:
    //else
    err(8,ip->line);
    ss.push(0);
    ss.push(0);
    ss.push(0);
    ss.push(0);
    ss.push(45);
    s1=new Symbol;
    s1->group='i';
    s1->line=line;
    sos.push(s1);
    s1=new Symbol;
    s1->group='(';
    s1->line=line;
    sos.push(s1);
    s1=new Symbol;
    s1->group='G';
    s1->line=line;
    sos.push(s1);
    s1=new Symbol;
    s1->group=')';
    s1->line=line;
    sos.push(s1);
    s1=new Symbol;
    s1->group='S';
    s1->line=line;
    sos.push(s1);
	saveStack("���ִ��� elseû����֮ƥ���if");
    continue;
   case 31:
    err(7,ip->line);
    it=ip;
    ip=new Token;
    ip->group=';';
    ip->line=line;
    continue;
   case 32:
    err(9,ip->line);
    s1=new Symbol;
    s1->line=line;
    s1->group='S';
    sos.push(s1);
	saveStack("���ִ��� ȱ�����.");
    break;
   default:
    err(4,ip->line);
    goto label1;
   }//switch

   r=ss.top();
   iq=sos.top();
   r=Goto::lookUp(iq->group,r);
   if(r)
   {
	   ss.push(r);
	   saveStack("��Լ����ƽ�");
   }
   else
   {
    err(4,iq->line);                         //�޷��ָ�
    goto label1;
    }
  }//else


  else if(t==0&&!hasError){
   log<<endl;
   log<<"����ͨ���﷨���,δ�����﷨����."<<endl;
  }

 }//while

label1:

  if(!islex)
  {
        in.close();
        in.clear(ios::goodbit);    //û�дʷ���������������û���
  }
 log<<"�﷨�Ƶ��������..."<<endl;
 log<<"*******************************************"<<endl;

 tNum = CTemp::_temp;
 //log.close();
}


Compiler::preProcess()
{
 string tmpstr;
 ifstream ins((fileName+".crr").c_str(),ios::in);
 //log.open((fileName + "_Log.txt").c_str(),ios::app);
 log<<"*******************************************"<<endl;
 log<<"����Ԥ������ʼ"<<endl;
 if(ins.is_open()){
  hasFile=1;
  log<<"���ļ� \'"<<fileName<<".crr\' �ɹ�!"<<endl;
 }
 else{
  hasFile=0;
  log<<"���ļ�ʧ��!"<<endl;
 }
 while(getline(ins,tmpstr)){     //����������
  if(tmpstr.substr(0,19)=="#include <stdio.h>"){
   needOutSuppose=1;
   break;
  }
 }
 if(needOutSuppose)
  log<<"��Ҫ����ϵͳ�⺯��\'stdio\'."<<endl;
 else
  log<<"����Ҫ����ϵͳ�⺯��\'stdio\'."<<endl;
 log<<"����Ԥ�������!"<<endl;
 log<<"*******************************************"<<endl;
 ins.close();
// log.close();
}

char Compiler::nextChar()
{
 char ch;
 if(in.get(ch)){
  currentChar=ch;
  return ch;
 }
 else{
  currentChar=ch;
  return '$';
 }
}

void Compiler::emitter()
{
 if(hasError){
  log<<endl;
  log<<"*******************************************"<<endl;
  log<<"Դ�������д���,��������Ŀ�����!"<<endl;
  log<<"*******************************************"<<endl;
  return;
 }
 log<<endl;
 log<<"*******************************************"<<endl;
 log<<"��ʼ����Ŀ�����..."<<endl;
 out.open((fileName + ".asm").c_str(),ios::out);

 //mout.open(("my"+fileName + ".asm").c_str(),ios::out);
 genMaincode();
 creatAsm();
 wriStk();
 if(out.is_open()){
 log<<"�����ļ�"<<(fileName + ".asm").c_str()<<"�ɹ�!"<<endl;
 out<<"\t.model small"<<endl;
 out<<"\t.stack"<<endl;
 out<<"\t.data"<<endl;
 while(!symbolList.empty())
 {
  out<<symbolList.front().word.c_str()<<"\tdw ?"<<endl;
  symbolList.pop_front();
 }
 out<<"__end\tdb 13,10,\'Press Any Key To Continue...\',\'$\'"<<endl;
 out<<"\t.code"<<endl;
 out<<endl;
 if(needOutSuppose){
  log<<"д�뱻����ϵͳ��������."<<endl;
  out<<"outint proc near"<<endl;
  out<<"\tmov cx,0"<<endl;
  out<<"\tmov bx,10"<<endl;
  out<<"again:\tmov dx,0"<<endl;
  out<<"\tdiv bx"<<endl;
  out<<"\tpush dx"<<endl;
  out<<"\tinc cx"<<endl;
  out<<"\tcmp ax,0"<<endl;
  out<<"\tjne again"<<endl;
  out<<"print:\tpop dx"<<endl;
  out<<"\tadd dl,30h"<<endl;
  out<<"\tmov ah,02h"<<endl;
  out<<"\tint 21h"<<endl;
  out<<"\tloop print"<<endl;
  out<<"\tmov dl,20h"<<endl;
  out<<"\tmov ah,02h"<<endl;
  out<<"\tint 21h"<<endl;
  out<<"\tret"<<endl;
  out<<"outint\tendp"<<endl;
  out<<endl;
 }
 out<<"main\tproc near"<<endl;
 out<<"\t;***CODE START***"<<endl;
 log<<"��ʼ�Ż�����."<<endl;
 optimize();
 log<<"�Ż��������."<<endl;
 out<<code;
 log<<"д��Ŀ�����."<<endl;
 out<<"\t;***CODE END***"<<endl;
 out<<"\tret"<<endl;
 out<<"main endp"<<endl;
 out<<endl;
 out<<"start:"<<endl;
 out<<"\tmov ax,@data"<<endl;
 out<<"\tmov ds,ax"<<endl;
 out<<"\tcall main"<<endl;
 out<<"\tlea dx,__end"<<endl;
 out<<"\tmov ah,09h"<<endl;
 out<<"\tint 21h"<<endl;
 out<<"\tmov ah,08h"<<endl;
 out<<"\tint 21h"<<endl;
 out<<"\tmov ah,4ch"<<endl;
 out<<"\tint 21h"<<endl;
 out<<"\tend start"<<endl;
 out.close();
 log<<endl;
 log<<"�����������!"<<endl;
 log<<"*******************************************"<<endl;
 }

 else
 {
  log<<endl;
  log<<"�޷������ļ�!"<<endl;
  log<<"*******************************************"<<endl;

 }
// Label *q;//����Label
// for(int i=0;i<10;i++){
//   q=new Label;
//   log<<q->text.c_str()<<endl;
//  delete q;
// }
 return;
}

Compiler::err(int no,int line)
{
 string errText;
 hasError=1;
 switch(no){
 case 1:
  errText="�����޷�ʶ��ķ���.";
  cmes<<"��"<<line<<"��"<<"����:"<<"\t�����޷�ʶ����ַ�."<<"'"<<lexErrChar<<"'"<<"\n";
  break;
 case 2:
  errText="����ı�ʶ��.";
  cmes<<"��"<<line<<"��"<<"����:"<<"\t���ֲ���ȷ�ı�ʾ��.";
  break;
 case 3:
  errText="�����\'&&\'(\'||\')д��\'&\'(\'|\')��.";
  cmes<<"��"<<line<<"��"<<"����:"<<"\t���\'&&\'(\'||\')д��\'&\'(\'|\')��\n";
  break;
 case 4:
  errText="�﷨����,����ֹͣ!";
  cmes<<"��"<<line<<"��"<<"����:"<<"\t�﷨���󣬱���ֹͣ."<<endl;
  break;
 case 5:
  errText="�Ҳ���main()����.";
  cmes<<"��"<<line<<"��"<<"����:"<<"\t�Ҳ���main()����." <<endl;
  break;
 case 6:
  errText="��ʹ�õĺ���δ����";
  cmes<<"��"<<line<<"��"<<"����:"<<"\t��ʹ�õĺ���δ����"<<endl;
  break;
 case 7:
  errText="����ȱ��\';\'.";
  cmes<<"��"<<line<<"��"<<"����:"<<"\t����ȱ��\';\'."<<endl;
  break;
 case 8:
  errText="elseû����֮ƥ���if.";
  cmes<<"��"<<line<<"��"<<"����:"<<"\telseû����֮ƥ���if."<<endl;
  break;
 case 9:
  errText="ȱ�����.";
  cmes<<"��"<<line<<"��"<<"����:"<<"\tȱ�����."<<endl;
  break;
 case 10:
  errText="����δ����.";
  cmes<<"��"<<line<<"��"<<"����:"<<"\t����δ����."<<endl;
  break;
 case 11:
  errText="�����Զ����,�������¶���.";
  cmes<<"��"<<line<<"��"<<"����:"<<"\t�����Զ����,�������¶���."<<endl;
  break;
 case 12:
	errText="����ƥ�����.";
        cmes<<"��"<<line<<"��"<<"����:"<<"\t����ƥ�����."<<endl;
  break;
 default:
  errText="δ֪����!";
  cmes<<"��"<<line<<"��"<<"����:"<<"\t����δ֪����.\n";

 }
 log<<"��������:�ļ�"<<fileName<<".crr��"<<line<<"��:"<<errText<<endl;
}


TokenGroup Compiler::lookup(string m)
{
 list<Id>::iterator i;
 for (i =  symbolList.begin(); i != symbolList.end(); ++i)
  if((*i).word==m)
   return (*i).type;
 return _NKEY;

}


Compiler::optimize()
{
	int i,j,f;
	string t="\tpush ax\n\tpop ax\n";
	do{
		f=0;
		j=code.length()-17;
		for(i=0;i<j;i++){
			if(code.substr(i,17)==t){
				f=1;
				code.replace(i,17,"");
				break;
			}
		}
	}while(f);
}



TokenGroup Compiler::IsKeyword(string m,int num)
{
	int i = 0;
	TokenGroup kt;
	for(i=0;i<num;i++)
		if(keywordstr[i] == m)
			break;
	switch(i)
	{
	case 0:
		return _INT;
	case 1:
		return _CHAR;
	case 2:
		return _FLOAT;
	case 3:
		return _IF;
	case 4:
		return _ELSE;
	case 5:
		return _WHILE;
	}
	
	return _NKEY;
}



bool Compiler::IsBackpath(stack<Symbol *> sos)
{
	Symbol* s1,*s2,*s3;
	s3 = sos.top();
	sos.pop();
	s1 = sos.top();
	sos.pop();
	if(s1->word == "(")
	{
		s2 = sos.top();
		sos.push(s2);
		sos.push(s3);
		if(s2->word == "if"||s2->word == "while")
			return true;
		else 
			return false;
	}
	
	else 
		return false;
		
}



int Compiler::Merge(int line1,int line2)  //int Merge(int line1,int line2);
{
	int hl;
	int pre;
	if(line1 == -1)
		return line2;
	if(line2 == -1)
		return line1;

	 hl = line1;
	while(line1 != -1)
	{
		pre = line1;
		line1 = ft[line1].next;
	}
////////////////////////////////////////////////////???
	ft[pre].next = line2;

	return hl;
}


void Compiler::loadSymbol(TokenGroup tg)
{
	list<Id>::iterator i;
	for(i = symbolList.begin();i!= symbolList.end();i++)
		if((*i).type == _NKEY)
			(*i).type = tg;

	//i = symbolList.begin();
	//if((*i).type == _NKEY)
	//	(*i).type = tg;
	return;
}


bool   Compiler::backPath(int head,int line)
{
	if(head == -1)
		return false;
	while(head != -1)
	{
		//itoa(line,ft[head].res,10);
		ft[head].res = intTostr(line);
		head = ft[head].next;
	}

	return true;
}


string Compiler::intTostr(int num)
 {
     if (num==0) return "0";
     string str="";
    int num_=num>0?num:-1*num;
     while (num_)
   {
       //  cout<<(char)(num_%10+48);
        str=(char)(num_%10+48)+str;
        num_=num_/10;
    }
     if (num<0)
		 str='-'+str;
     return str;
 }


void Compiler::showFterm(void)
{
	int i = 0;
	ofstream f;
	FourTerm * ff = NULL;
      //	f.open((fileName+".ft").c_str(),ios::out);

	for(;i<nextquad;i++)
	{
		ff = ft+i;
                fft<<intTostr(i)+" "+"("+ff->op+","+ff->p1+","+ff->p2+","+ff->res+")"<<endl;
	}

	fft<<intTostr(nextquad)<<endl;
        log<<"��Ԫʽд��"+fileName+"_fourTerm.txt"<<endl;
	fft.close();
        isFtClose = true;
	return;
}


void Compiler::reverseStk(stack<int> sss,stack<int> *tsss)
{
	while(sss.size() != 0)
	{
		tsss->push(sss.top());
		sss.pop();
	}

	return;
}


void Compiler::reverseStk(stack<Symbol*> soss,stack<Symbol*>* tsoss)
{
	while(soss.size() != 0)
	{
		tsoss->push(soss.top());
		soss.pop();
	}
	
	return;
	
}


void Compiler::saveStack(const string str)
{
	int i;
	Symbol *s;
	stack<int>  tss;
	stack<Symbol*> tsos;
	reverseStk(ss,&tss);
        int n = 0;
	while(tss.size() != 0)
	{
		i = tss.top();
		stk += intTostr(i);
		tss.pop();
                n++;
	}
        addBlank(&stk,30-n);
	reverseStk(sos,&tsos);
	//stk  +=  "\t\t";
        n = 0;
	while(tsos.size() != 0)
	{
		s = tsos.top();
		tsos.pop();
		stk += s->group;
                n++ ;
	}
	
	addBlank(&stk,30-n);
    
	stk += str;

	stk += "\n";

	return;	
}


void Compiler::saveQuad(Token* ip)
{
	if(ip->group == 'w'||ip->group == '&')	//�ƽ�ʱ���ı���״̬��
		bk.push(nextquad);
	if(ip->group == 'e')
	{
		nlist = nextquad;
		ft[nextquad].op = "j";
		ft[nextquad].p1 = "-";
		ft[nextquad].p2 = "-";
		ft[nextquad].res = "-1";
		ft[nextquad].next = -1;
		nextquad ++;

		bk.push(nextquad);
	}

}


void Compiler:: genMaincode(void)
{
	int i = 0;
        log<<"����Ŀ�����....."<<endl;
	for(;i<nextquad;i++)
	{
       if(ft[i].op == "=")
	   {
		 mainCode[i].code += "\tmov ax,"+ft[i].p1+"\n";
		 mainCode[i].code += "\tmov "+ft[i].res+",ax\n";
		 mainCode[i].bNum = -1;							//����Ҫ����
		 mainCode[i].isBack = false;
	   }
	   else if(ft[i].op == "-"||ft[i].op == "+")
	   {
		   mainCode[i].code += "\tmov ax,"+ft[i].p1+"\n";
		   if(ft[i].op == "-")
				mainCode[i].code += "\tsub ax,"+ft[i].p2+"\n";
		   else
			    mainCode[i].code += "\tadd ax,"+ft[i].p2+"\n";

		   mainCode[i].code += "\tmov "+ft[i].res+",ax\n";
		   mainCode[i].bNum = -1;							//����Ҫ����
		   mainCode[i].isBack = false; 
	   }
	   else if(ft[i].op == "*"||ft[i].op =="/")
	   {
		   mainCode[i].code += "\tmov dx, 0\n";
		   mainCode[i].code += "\tmov ax,"+ft[i].p1+"\n";
		   mainCode[i].code += "\tmov bx,"+ft[i].p2+"\n";
		   if(ft[i].op == "*")
				mainCode[i].code += "\tmul bx\n";
		   else 
			    mainCode[i].code += "\tdiv bx\n";

		   mainCode[i].code += "\tmov "+ft[i].res+",ax\n";

		   mainCode[i].bNum = -1;							//����Ҫ����
		   mainCode[i].isBack = false; 
	   }
	   else if(ft[i].op == "j>"||ft[i].op == "j<"||ft[i].op == "j>="||ft[i].op == "j<="
		   ||ft[i].op == "=="||ft[i].op == "!="||ft[i].op == "j")
	   {
		    if(ft[i].op == "j")
			{
				mainCode[i].code += "\tjmp ";
				mainCode[i].bNum = strToint(ft[i].res);

			}
		    else
			{
				mainCode[i].code += "\tmov ax,"+ft[i].p1+"\n";
				mainCode[i].code += "\tmov bx,"+ft[i].p2+"\n";
				mainCode[i].code += "\tcmp ax,bx\n";

			

				if(ft[i].op == "j>")
					mainCode[i].code += "\tjg ";
				else if(ft[i].op == "j<")
					mainCode[i].code += "\tjl ";
				else if(ft[i].op == "j>=")
					mainCode[i].code += "\tjge ";
				else if(ft[i].op == "j<=")
					mainCode[i].code += "\tjle ";
				else if(ft[i].op == "==")
					mainCode[i].code = "\tje ";
				else //if(ft[i].op == "!=")
					ft[i].op = "\tjne ";

				mainCode[i].bNum = strToint(ft[i].res);
			}

			mainCode[i].isBack = false;

	   }

	   else if(ft[i].op == "cal")
	   {
			mainCode[i].code +="\tmov ax,"+ft[i].p2+"\n";
			mainCode[i].code +="\tcall outint\n";
			mainCode[i].isBack = false;
			mainCode[i].bNum = -1;

	   }
      
	}

	backMaincode();
	loadMaincode();
}




void Compiler:: initMaincode(void)
{
	int i = 0;
	for(;i<100;i++)
	{
		mainCode[i].code = "";
		mainCode[i].isBack = false;
	}
}


int Compiler::strToint(string str)
{
	int s;
//	string str="123";
	stringstream ss;
	ss<<str;						//��str����
	ss>>s;
	return s;
}



void Compiler::backMaincode(void)
{
	int i = 0;
	int j = 0;
	Label *l ; 
	string str ;
	for(;i<nextquad;i++)
	{
		j = mainCode[i].bNum;
		if((j != -1))
		{

			if(mainCode[j].isBack == false)
			{
				l = new Label;
				if(j < nextquad)
				{
					mainCode[j].code = l->text+":\n" + mainCode[j].code;

					mainCode[j].isBack = true;
				}
			
				else
				{
					mainCode[nextquad].code = l->text+":"+"\n";
					mainCode[j].isBack = true;
				}

				mainCode[i].code = mainCode[i].code +l->text+"\n";
			}
			else
			{
				int k = mainCode[j].code.find('\n');
				str = mainCode[j].code.substr(0,k+1);
				mainCode[i].code = mainCode[i].code +str;

			}

		}

	}

        Label:: _label  = 0;
}



void Compiler::loadMaincode(void)
{
	int i = 0;
	for(;i<nextquad;i++)
		code1 += mainCode[i].code;
	if(mainCode[nextquad].code != "")
		code1 += mainCode[nextquad].code;
}



void Compiler::creatAsm(void)
{

 int i = 0;
 string ct = "";
//mout.open(("my"+fileName + ".asm").c_str(),ios::out);

if(mout.is_open()){
	//log<<"�����ļ�"<<("my"+fileName + ".asm").c_str()<<"�ɹ�!"<<endl;
	mout<<"\t.model small"<<endl;
	mout<<"\t.stack"<<endl;
	mout<<"\t.data"<<endl;
	while(!symbolList.empty())
	{
		mout<<symbolList.front().word.c_str()<<"\tdw ?"<<endl;
		symbolList.pop_front();
	}
	for(;i<tNum;i++)
	{
		ct = "T"+intTostr(i+1);
		mout<<ct<<"\tdw ?\n";
	}
	mout<<"__end\tdb 13,10,\'Press Any Key To Continue...\',\'$\'"<<endl;
	mout<<"\t.code"<<endl;
	mout<<endl;
	if(needOutSuppose){
	//	log<<"д�뱻����ϵͳ��������."<<endl;
		mout<<"outint proc near"<<endl;
		mout<<"\tmov cx,0"<<endl;
		mout<<"\tmov bx,10"<<endl;
		mout<<"again:\tmov dx,0"<<endl;
		mout<<"\tdiv bx"<<endl;
		mout<<"\tpush dx"<<endl;
		mout<<"\tinc cx"<<endl;
		mout<<"\tcmp ax,0"<<endl;
		mout<<"\tjne again"<<endl;
		mout<<"print:\tpop dx"<<endl;
		mout<<"\tadd dl,30h"<<endl;
		mout<<"\tmov ah,02h"<<endl;
		mout<<"\tint 21h"<<endl;
		mout<<"\tloop print"<<endl;
		mout<<"\tmov dl,20h"<<endl;
		mout<<"\tmov ah,02h"<<endl;
		mout<<"\tint 21h"<<endl;
		mout<<"\tret"<<endl;
		mout<<"outint\tendp"<<endl;
		mout<<endl;
	}
	mout<<"main\tproc near"<<endl;
	mout<<"\t;***CODE START***"<<endl;
	//log<<"��ʼ�Ż�����."<<endl;
	//optimize();
	//log<<"�Ż��������."<<endl;
	mout<<code1;
	//log<<"д��Ŀ�����."<<endl;
	mout<<"\t;***CODE END***"<<endl;
	mout<<"\tret"<<endl;
	mout<<"main endp"<<endl;
	mout<<endl;
	mout<<"start:"<<endl;
	mout<<"\tmov ax,@data"<<endl;
	mout<<"\tmov ds,ax"<<endl;
	mout<<"\tcall main"<<endl;
	mout<<"\tlea dx,__end"<<endl;
	mout<<"\tmov ah,09h"<<endl;
	mout<<"\tint 21h"<<endl;
	mout<<"\tmov ah,08h"<<endl;
	mout<<"\tint 21h"<<endl;
	mout<<"\tmov ah,4ch"<<endl;
	mout<<"\tint 21h"<<endl;
	mout<<"\tend start"<<endl;
	mout.close();
        isAsmClose = true;
	//log<<endl;
	log<<"Ŀ������������!д���ļ�"+fileName+".asm"<<endl;
	//log<<"*******************************************"<<endl;
 }




else
{
	log<<endl;
	log<<"�޷������ļ�!"<<endl;
	log<<"*******************************************"<<endl;
	
 }


}

 

void Compiler::wriStk(void)      //ֻ����һ��
{
	//ofstream stak;
	//stak.open((fileName+".stk").c_str(),ios::out);
	if(fstk.is_open())
	{
		log<<"�﷨ջ��Ϣд��"<<(fileName+ "_stack.txt").c_str()<<"�ļ�"<<endl;
		fstk<<"State Stack" << "\t\t"<<"Symbol Stack" <<"\t\tAction"<<endl;
		fstk<<stk;
		fstk.close();
                isStkClose = true;
	}
	else
		log<<"�����ļ�"<<(fileName + "_stack.txt").c_str()<<"ʧ��!"<<endl;

	

}


 void Compiler::reSet(void)
 {
        hasError = false;
        isClrIn  = false;
        nextquad = 0;
        line=1;

        needOutSuppose=0;
        hasFile=0;

        ss.empty();
        sos.empty();


         code = "";
        code1 = "";
        tNum = 0;
        stk = "";
         ss.empty();
        sos.empty();
        initMaincode();

        //log.close();

   //      if(isClose)
   //      {
   //          log.close();
    //     }

      /*   if(isClrIn)
         {
                in.close();
                in.clear(ios::goodbit);  //��Դ�����ļ���ֻ��һ��
         }*/

         symbolList.clear();   // ?

         while(!ss.empty())
                ss.pop();

        while(!sos.empty())
                sos.pop();
         //sos.pop();

         isLexErrId  = false;

         if(!isTokenClose)
         {
                ftoken.close();
         }

         if(!isFtClose)
         {
                fft.close();
         }

         if(!isStkClose)
         {
               fstk.close();
         }

         if(!isLogClose)
         {
                log.close();
         }

         if(!isAsmClose)
         {
                mout.close();
         }


         while(!symbolList.empty())
        {
                symbolList.pop_front();
        }
 }




 void  Compiler::addBlank(string* pstr,int n)
 {
       while(n != 0)
       {
          (*pstr) += "  ";
          n--;
       }
      return;
 }
