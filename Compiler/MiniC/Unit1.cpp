//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
         isLexer = false;
         isMcode = false;      //�﷨����
         isAsmcode = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N2Click(TObject *Sender)
{

       /* cc.hasError = false;
        nextquad = 0;
        line=1;
        hasError=0;
        needOutSuppose=0;
        hasFile=0;*/

        cc.reSet();           //���ñ�����

        isLexer = false;
        isMcode = false;
        isAsmcode = false;

        string str;
        Form1->ClientHeight = 40 + Form1->Memo1->Height;
        OpenDialog1->Filter="Texts files(*.crr)|*.crr*";
        if( OpenDialog1->Execute())
        {

                cc.isClrIn = true;
                cc.hasFile = true;
                //Label2->Caption = OpenDialog1->FileName;
                str =  OpenDialog1->FileName.c_str();
                int end = str.find_last_of('\\');
                str = str.substr(end+1,str.size()-1);
                Label2->Caption = str.c_str();
                //ShowMessage(str.c_str());
                Label1->Caption = "Դ����";

                HFILE hFile = FileOpen(OpenDialog1->FileName.c_str(),fmOpenReadWrite);
	        if(hFile > - 1)
	        {
		        int nSize = FileSeek(hFile,0,2);
		        FileSeek(hFile,0,0);
		        char *pBuf = new char[nSize + 1];
		        FileRead(hFile,pBuf,nSize);
		        pBuf[nSize] = '\0';
		        FileClose(hFile);
		        Memo1->Lines->Text = pBuf;
	        }

                int s = str.find_first_of('.');
                str = str.substr(0,s);
                cc.fileName = str;

                cc.log.open((cc.fileName + "_log.txt").c_str(),ios::out);
                cc.isClose = true;
                cc.ftoken.open((cc.fileName + "_token.txt").c_str(),ios::out);
                //��ʼ��token���ļ�
                cc.log<<"����"+cc.fileName+"��token���ļ�"<<endl;
                cc.fft.open((cc.fileName+"_fourTerm.txt").c_str(),ios::out);
                //��ʼ����Ԫʽ��
                cc.log<<"����"+cc.fileName+"���м������Ԫʽ�ļ�"<<endl;
                cc.fstk.open((cc.fileName+"_stack.txt").c_str(),ios::out);
                // ��ʼ���﷨ջ
                cc.log<<"����"+cc.fileName+"���﷨ջ���ļ�"<<endl;
                cc.mout.open((cc.fileName + ".asm").c_str(),ios::out);
                cc.log<<"����"+cc.fileName+"��ASMĿ������ļ�"<<endl;
                //���Ƕ��������һ�ε�����


                cc.isTokenClose = false;
                cc.isFtClose = false;
                cc.isStkClose = false;
                cc.isAsmClose = false;
                cc.isLogClose = false;
        }
        else
               cc.hasFile = false;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::N6Click(TObject *Sender)                //��ʼ�ʷ�����
{

        int i = 0;
        char buffer[10];
        Token *t = new Token;
        int j = 0;
        Form1->ClientHeight = Form1->Memo2->Height + Form1->Memo2->Top;
        cc.cmes.open((cc.fileName+"_cmes.txt").c_str(),ios::out);  //�����ļ�
        cc.cmes<<"*******************************Minc Compiler Run-Time Report**********************************" <<endl;
        cc.cmes<<"�ʷ�����............"<<endl;
        if(cc.hasFile == false)
        {
           // ShowMessage("������Դ�ļ�.");
            cc.cmes<<"������Դ�ļ�."<<endl;
           goto SHOW;
        }


        cc.line = 1;
        cc.isLexErrId = false;  //�����﷨����ʱ���ʷ����󡣶�û������
        cc.hasError = false;   //�ڴʷ�������ǰ������ȷ��

        cc.preProcess();
        if(cc.hasFile)               // �϶����ڵ�
                cc.in.open((cc.fileName+".crr").c_str(),ios::in);
        cc.currentChar=cc.nextChar();                          //�ʷ���������ʼ��
        t = cc.lexer();
        while(t->word != "$")
        {
                //st[i].word = t->word;
                // st[i].group = t->group;
                //st[i].line =  itoa(t->line,buffer,10);
                cc.cct[i].word = t->word;
                cc.cct[i].group = t->group;
                cc.cct[i].line  = t->line;
                //ct[i].word = t->word;
                //ct[i].group = t->group;
                //ct[i].line  = t->line;
                i++;
                 t = cc.lexer();
        }


         cc.cct[i].word = t->word;
         cc.cct[i].group = t->group;
         cc.cct[i].line  = t->line;

        //cc.ftoken.open((cc.fileName + "_token.txt").c_str(),ios::out);
        cc.ftoken<<"����"<<"\t"<<"����"<<"\t"<<"����"<<endl;

        for(;j<=i;j++)
        {
                cc.ftoken<<cc.cct[j].word<<"\t"<<cc.cct[j].group<<"\t"<<itoa(cc.cct[j].line,buffer,10)<<"\n";
        }
        cc.ftoken.close();                              // Token ���γ�
        cc.isTokenClose = true;
        //cc.line = 1;
        isLexer = true;
         if(!cc.hasError)
         {
               // ShowMessage("�ʷ��������,��ȷ��");
                cc.cmes<<"�ʷ���������,��ȷ."<<endl;
         }
        else
        {
                //ShowMessage("�ʷ�������ϣ��д���");
                cc.cmes<<"�ʷ������д���."<<endl;
        }
        cc.in.close();
        cc.in.clear(ios::goodbit);  //��Դ�����ļ���ֻ��һ��


 SHOW:  cc.cmes.close();
        string str =    cc.fileName+"_cmes.txt";
        HFILE hFile = FileOpen(str.c_str(),fmOpenReadWrite);
        if(hFile > -1)
        {
                int nSize = FileSeek(hFile,0,2);
                FileSeek(hFile,0,0);
                char *pBuf = new char[nSize + 1];
                char *str; //= new char[nSize + 100];
                FileRead(hFile,pBuf,nSize);
                pBuf[nSize] = '\0';
                FileClose(hFile);

                Memo2->Lines->Text = pBuf;
        }

        else
        {
                ShowMessage("���ɵ�����Ϣʱ���д���.");
        }

        return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N4Click(TObject *Sender)
{
        cc.log.close();
        exit(0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Token1Click(TObject *Sender)
{


  /*ifstream ins((cc.fileName+".crr").c_str(),ios::in);


 if(!ins.is_open())
 {
   ShowMessage((cc.fileName+".crr"+"�ļ���Token��δ����\n������ʾ��").c_str());
   return ;
 }        */
 //else
 //{
  //ins.close();

  Form1->ClientHeight = Form1->Memo2->Height + Form1->Memo2->Top;
  cc.cmes.open((cc.fileName+"_cmes.txt").c_str(),ios::out);  //�����ļ�
  cc.cmes<<"*******************************Minc Compiler Run-Time Report**********************************" <<endl;
  cc.cmes<<"��ʾToken��............"<<endl;

  string str =    cc.fileName+"_token.txt";
  HFILE hFile = FileOpen(str.c_str(),fmOpenReadWrite);
  if(hFile > -1)
  {

        //char *stemp =  "����\t����\t����\n";
        Label1->Caption = "<Token>��:";
        Label2->Caption = str.c_str();
        int nSize = FileSeek(hFile,0,2);
        FileSeek(hFile,0,0);
        char *pBuf = new char[nSize + 1];
        char *str; //= new char[nSize + 100];
        FileRead(hFile,pBuf,nSize);
        pBuf[nSize] = '\0';
        FileClose(hFile);
       // str = strcat(stemp,pBuf);
        //Memo1->Lines->Text  = str;
        //Memo1->Lines->Text =  stemp;
        Memo1->Lines->Text = pBuf;
  }

  else
  {
        //ShowMessage((cc.fileName+"��Token��δ����.").c_str());
        cc.cmes<<cc.fileName<<"��Token��û�����ɲ�����ʾ."<<endl;
  }

  cc.cmes.close();
  str =    cc.fileName+"_cmes.txt";
 hFile = FileOpen(str.c_str(),fmOpenReadWrite);
  if(hFile > -1)
  {
        int nSize = FileSeek(hFile,0,2);
        FileSeek(hFile,0,0);
        char *pBuf = new char[nSize + 1];
        char *str; //= new char[nSize + 100];
        FileRead(hFile,pBuf,nSize);
        pBuf[nSize] = '\0';
        FileClose(hFile);
        Memo2->Lines->Text = pBuf;
  }

  else
  {
        ShowMessage("���ɵ�����Ϣʱ���д���.");
  }

  return;
 //}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::N8Click(TObject *Sender)
{
   Form1->ClientHeight = Form1->Memo2->Height + Form1->Memo2->Top;
   cc.cmes.open((cc.fileName+"_cmes.txt").c_str(),ios::out);  //�����ļ�
   cc.cmes<<"*******************************Minc Compiler Run-Time Report**********************************" <<endl;
   cc.cmes<<"�﷨�Ƶ�����............."<<endl;
   if(!cc.hasFile)
   {
        //ShowMessage("Դ�ļ�������.");
        cc.cmes<<"Դ�ļ�������."<<endl;
        goto SHOW;
   }

   //cc.line = 1;
   if(cc.hasError)
   {
        //ShowMessage((cc.fileName+"�����д���,�����﷨�Ƶ�����").c_str());
        cc.cmes<<cc.fileName+"�����д���,�����﷨�Ƶ�����"<<endl;
        goto SHOW;
   }
   if(isMcode)
   {
        //ShowMessage("�ѽ����﷨�Ƶ�����!\n");
        cc.cmes<<"�﷨�Ƶ������Ѿ����."<<endl;
        goto SHOW;
   }
   if(!isLexer)
   {
       // ShowMessage("Token����δ���ɣ�\n����һ��ʽ�﷨�������.");
        cc.cmes<<"Token����δ���ɣ�\n����һ��ʽ�﷨�������."<<endl;
   }
   else
   {
        //ShowMessage("Token���Ѿ�����!,����token������﷨�������");
        cc.cmes<<"Token���Ѿ�����!,����token������﷨�������"<<endl;
   }


   cc.parser(isLexer);    //��������Ԫʽ���﷨����ջ

   cc.line = 1;
   //cc.nextquad = 0;  ������Ϊ�����м���룬ֻ��һ��
   if(cc.hasError)
   {
        //ShowMessage("�﷨�����д���,���������м����.\n");
        cc.cmes<<"�﷨�����д���,���������м����" <<endl;
   }

   else
   {
        cc.cmes<<"�﷨������ȷ,�ɹ������м����" <<endl;
        cc.showFterm();   //������Ԫʽ
        cc.wriStk();      //�������ջ
        //ShowMessage("�﷨�������!");
        isMcode = true;
        isLexer = true;                           //���û�дʷ�����
   }

 SHOW:
    cc.cmes.close();
    string str =    cc.fileName+"_cmes.txt";
    HFILE hFile = FileOpen(str.c_str(),fmOpenReadWrite);
    if(hFile > -1)
    {
        int nSize = FileSeek(hFile,0,2);
        FileSeek(hFile,0,0);
        char *pBuf = new char[nSize + 1];
                //char *str; //= new char[nSize + 100];
        FileRead(hFile,pBuf,nSize);
        pBuf[nSize] = '\0';
        FileClose(hFile);
        Memo2->Lines->Text = pBuf;
     }

     else
     {
        ShowMessage("���ɵ�����Ϣʱ���д���.");
     }
             
     return;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::N9Click(TObject *Sender)
{
/*
 ifstream ins((cc.fileName+".stk").c_str(),ios::in);    //ת�Ƶ�����


 if(!ins.is_open())
 {
   ShowMessage((cc.fileName+".crr"+"�ļ����﷨ջδ����\n��������ʾ��").c_str());
   ins.close();
   return ;
 }
 */
// else
 //{
 // ins.close();
  //Label1->Caption = "�﷨ջ:";
 // Label2->Caption = (cc.fileName+"_stack.txt").c_str();
 Form1->ClientHeight = Form1->Memo2->Height + Form1->Memo2->Top;
  cc.cmes.open((cc.fileName+"_cmes.txt").c_str(),ios::out);  //�����ļ�
  cc.cmes<<"*******************************Minc Compiler Run-Time Report**********************************" <<endl;
  cc.cmes<<"��ʾ�﷨����ջ......."<<endl;

  string str;
  str =  cc.fileName+"_stack.txt";
  HFILE hFile = FileOpen(str.c_str(),fmOpenReadWrite);
  if(hFile > - 1)
  {
         //char *stemp =  "����\t����\t����\n";
        Label1->Caption = "�﷨ջ:";
        Label2->Caption = str.c_str();
        int nSize = FileSeek(hFile,0,2);
        FileSeek(hFile,0,0);
        char *pBuf = new char[nSize + 1];
        //char *str = new char[nSize + 50];
        FileRead(hFile,pBuf,nSize);
        pBuf[nSize] = '\0';
        FileClose(hFile);
        //str = strcat(stemp,pBuf);
        Memo1->Lines->Text  = pBuf;

        //Memo2->Lines->Text += pBuf;
  }
 //}
  else
  {
       //ShowMessage((cc.fileName+".crr"+"�ļ����﷨ջδ����\n��������ʾ��").c_str());
       cc.cmes<<cc.fileName<<".crr"<<"�ļ����﷨ջδ����\n��������ʾ��"<<endl;
  }

  cc.cmes.close();
  str =    cc.fileName+"_cmes.txt";
  hFile = FileOpen(str.c_str(),fmOpenReadWrite);
  if(hFile > -1)
  {
        int nSize = FileSeek(hFile,0,2);
        FileSeek(hFile,0,0);
        char *pBuf = new char[nSize + 1];
        char *str; //= new char[nSize + 100];
        FileRead(hFile,pBuf,nSize);
        pBuf[nSize] = '\0';
        FileClose(hFile);
        Memo2->Lines->Text = pBuf;
  }

  else
  {
        ShowMessage("���ɵ�����Ϣʱ���д���.");
  }



}
//---------------------------------------------------------------------------


void __fastcall TForm1::N10Click(TObject *Sender)
{
  /*
 ifstream ins((cc.fileName+".ft").c_str(),ios::in);    //�������ִ��ļ���FileOpen��һ����

 if(!ins.is_open())
 {
   ShowMessage((cc.fileName+".crr"+"�ļ����м���벻����ʾ��δ����\n������ʾ��").c_str());
   ins.close();
   return ;
 }  */
 //else
 //{
 // ins.close();
 //Label1->Caption = "�м����:";
 //Label2->Caption = (cc.fileName+"_fourterm.txt").c_str();
  string str =  cc.fileName+"_fourTerm.txt";
  HFILE hFile = FileOpen(str.c_str(),fmOpenReadWrite);

  Form1->ClientHeight = Form1->Memo2->Height + Form1->Memo2->Top;
  cc.cmes.open((cc.fileName+"_cmes.txt").c_str(),ios::out);  //�����ļ�
  cc.cmes<<"*******************************Minc Compiler Run-Time Report**********************************" <<endl;
  cc.cmes<<"��ʾ�м����......."<<endl;

  if(hFile > - 1)
  {
        //char *stemp =  "����\t����\t����\n";
        Label1->Caption = "�м����:";
        Label2->Caption = str.c_str();
        int nSize = FileSeek(hFile,0,2);
        FileSeek(hFile,0,0);
        char *pBuf = new char[nSize + 1];
        //char *str = new char[nSize + 50];
        FileRead(hFile,pBuf,nSize);
        pBuf[nSize] = '\0';
        FileClose(hFile);
        //str = strcat(stemp,pBuf);
        Memo1->Lines->Text  = pBuf;

        //Memo2->Lines->Text += pBuf;
  }
 //}
 else
 {
        //ShowMessage((cc.fileName +"����Ԫʽ��û������.").c_str());
        cc.cmes<<cc.fileName<<"����Ԫʽ��û�����ɣ�������ʾ�м����.\n"<<endl;
 }


  cc.cmes.close();
  str =    cc.fileName+"_cmes.txt";
  hFile = FileOpen(str.c_str(),fmOpenReadWrite);
  if(hFile > -1)
  {
        int nSize = FileSeek(hFile,0,2);
        FileSeek(hFile,0,0);
        char *pBuf = new char[nSize + 1];
        char *str; //= new char[nSize + 100];
        FileRead(hFile,pBuf,nSize);
        pBuf[nSize] = '\0';
        FileClose(hFile);
        Memo2->Lines->Text = pBuf;
  }

  else
  {
        ShowMessage("���ɵ�����Ϣʱ���д���.");
  }


 
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N17Click(TObject *Sender)
{

        Form1->ClientHeight = Form1->Memo2->Height + Form1->Memo2->Top;
        cc.cmes.open((cc.fileName+"_cmes.txt").c_str(),ios::out);  //�����ļ�
        cc.cmes<<"*******************************Minc Compiler Run-Time Report**********************************" <<endl;
        cc.cmes<<"��ʾԴ����............."<<endl;
         HFILE hFile;
        if(!cc.hasFile)
        {
                //ShowMessage("Դ�ļ�������.");
                cc.cmes<<"Դ�ļ�������."<<endl;
                goto SHOW;
        }
        Label2->Caption = (cc.fileName+".crr").c_str();
        //ShowMessage(str.c_str());
        Label1->Caption = "Դ����";

        hFile  = FileOpen((cc.fileName+".crr").c_str(),fmOpenReadWrite);
	if(hFile > - 1)
	{
		int nSize = FileSeek(hFile,0,2);
		FileSeek(hFile,0,0);
		char *pBuf = new char[nSize + 1];
		FileRead(hFile,pBuf,nSize);
		pBuf[nSize] = '\0';
		FileClose(hFile);
		Memo1->Lines->Text = pBuf;
	}


SHOW:    cc.cmes.close();
        string str =    cc.fileName+"_cmes.txt";
         hFile = FileOpen(str.c_str(),fmOpenReadWrite);
        if(hFile > -1)
         {
                int nSize = FileSeek(hFile,0,2);
                 FileSeek(hFile,0,0);
                char *pBuf = new char[nSize + 1];
                char *str; //= new char[nSize + 100];
                FileRead(hFile,pBuf,nSize);
                pBuf[nSize] = '\0';
                FileClose(hFile);
                Memo2->Lines->Text = pBuf;
        }

        else
        {
        ShowMessage("���ɵ�����Ϣʱ���д���.");
         }
      
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N12Click(TObject *Sender)
{
   Form1->ClientHeight = Form1->Memo2->Height + Form1->Memo2->Top;
   cc.cmes.open((cc.fileName+"_cmes.txt").c_str(),ios::out);  //�����ļ�
   cc.cmes<<"*******************************Minc Compiler Run-Time Report**********************************" <<endl;
   cc.cmes<<"����Ŀ�����............."<<endl;
   if(!cc.hasFile)
   {
       // ShowMessage("Դ�ļ�������!");
        cc.cmes<<"Դ�ļ�������"<<endl;
        goto SHOW;
   }
   if(cc.hasError)
   {
        cc.cmes<<"Դ�����ѷ��ִ��󣬲�������Ŀ�����."<<endl;
        goto SHOW;
   }
   if(isAsmcode)
   {
        //ShowMessage("Ŀ������ļ��Ѿ�����.");
        cc.cmes<<"Ŀ������ļ��Ѿ�����."<<endl;
        goto SHOW;
   }

   if(!isMcode)
   {
        if(!isLexer)
        {
           //ShowMessage("Token��û�����ɣ�ֱ������Ŀ�����.");
           cc.cmes<<"Token��û�����ɣ�ֱ���﷨�Ƶ�����"<<endl;
        }
        else
        {
           //ShowMessage("�м����û�����ɣ�ֱ������Ŀ�����.");
           cc.cmes<<"�м����û�����ɣ���ʼ�����м���룬Ŀ�����."<<endl;
        }

        cc.parser(isLexer);
        if(cc.hasError)
        {
            //ShowMessage("�ʷ����﷨�����д��󣬲��������м䣬Ŀ�����.");
            cc.cmes<<"�ʷ����﷨�����д��󣬲��������м䣬Ŀ�����."<<endl;
            goto SHOW;
        }
        else
        {
            cc.cmes<<"�﷨������ϣ���ȷ�����м����,Ŀ�����."<<endl;
            cc.showFterm();   //������Ԫʽ
            cc.wriStk();      //�������ջ
            //ShowMessage("�﷨������ϣ���ȷ�����м����,Ŀ�����.");
            cc.genMaincode();  //�����м���룬����main������Ŀ�����
            cc.creatAsm();    //��ӱ�Ҫ��asm���룬���ɿɱ����asm�ļ�
            isMcode = true;
            isAsmcode = true;
        }
   }
   else
   {
       // ShowMessage("�м�����Ѿ����ɣ�����Ŀ�����.");
        cc.cmes<<"�м�����Ѿ����ɣ���ȷ����Ŀ�����."<<endl;
        cc.genMaincode();
        cc.creatAsm();
        isAsmcode = true;
   }
SHOW:

  cc.cmes.close();
  string str =    cc.fileName+"_cmes.txt";
  HFILE hFile = FileOpen(str.c_str(),fmOpenReadWrite);
  if(hFile > -1)
  {
        int nSize = FileSeek(hFile,0,2);
        FileSeek(hFile,0,0);
        char *pBuf = new char[nSize + 1];
        char *str; //= new char[nSize + 100];
        FileRead(hFile,pBuf,nSize);
        pBuf[nSize] = '\0';
        FileClose(hFile);
        Memo2->Lines->Text = pBuf;
  }

  else
  {
        ShowMessage("���ɵ�����Ϣʱ���д���.");
  }





}
//---------------------------------------------------------------------------

void __fastcall TForm1::N13Click(TObject *Sender)
{

        Form1->ClientHeight = Form1->Memo2->Height + Form1->Memo2->Top;
        cc.cmes.open((cc.fileName+"_cmes.txt").c_str(),ios::out);  //�����ļ�
        cc.cmes<<"*******************************Minc Compiler Run-Time Report**********************************" <<endl;
        cc.cmes<<"��ʾĿ�����............."<<endl;

        string str = cc.fileName+".asm";
        HFILE hFile = FileOpen(str.c_str(),fmOpenReadWrite);
        if(hFile > - 1)                //������Դ�ļ�
        {
                Label1->Caption = "Ŀ�����ASM:";
                Label2->Caption =  str.c_str();//("my"+cc.fileName+".asm").c_str();
                //char *stemp =  "����\t����\t����\n";
                int nSize = FileSeek(hFile,0,2);
                FileSeek(hFile,0,0);
                char *pBuf = new char[nSize + 1];
                char *str; //= new char[nSize + 100];
                FileRead(hFile,pBuf,nSize);
                pBuf[nSize] = '\0';
                FileClose(hFile);
                // str = strcat(stemp,pBuf);
                //Memo1->Lines->Text  = str;
                //Memo1->Lines->Text =  stemp;
                Memo1->Lines->Text = pBuf;
        }

        else
        {
               // ShowMessage((str+"�ļ�û�����ɣ�������ʾ.").c_str());
                cc.cmes<<str<<"Ŀ���ļ�û�����ɣ�������ʾ."<<endl;
        }

        cc.cmes.close();
        str = cc.fileName+"_cmes.txt";
        hFile = FileOpen(str.c_str(),fmOpenReadWrite);
        if(hFile > -1)
        {
                int nSize = FileSeek(hFile,0,2);
                FileSeek(hFile,0,0);
                char *pBuf = new char[nSize + 1];
                char *str; //= new char[nSize + 100];
                FileRead(hFile,pBuf,nSize);
                pBuf[nSize] = '\0';
                FileClose(hFile);
                 Memo2->Lines->Text = pBuf;
        }

        else
        {
                 ShowMessage("���ɵ�����Ϣʱ���д���.");
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N15Click(TObject *Sender)
{

        Form1->ClientHeight = Form1->Memo2->Height + Form1->Memo2->Top;
        cc.cmes.open((cc.fileName+"_cmes.txt").c_str(),ios::out);  //�����ļ�
        cc.cmes<<"*******************************Minc Compiler Run-Time Report**********************************" <<endl;
        cc.cmes<<"��ʾ��־�ļ�............."<<endl;

        string str = cc.fileName+"_log.txt";
        cc.log.close();
        HFILE hFile = FileOpen(str.c_str(),fmOpenReadWrite);
        if(hFile > - 1)
        {
                //char *stemp =  "����\t����\t����\n";
                //cc.log.close();
                Label1->Caption = "��־�ļ�:";
                Label2->Caption = str.c_str();
                int nSize = FileSeek(hFile,0,2);
                FileSeek(hFile,0,0);
                char *pBuf = new char[nSize + 1];
                char *str; //= new char[nSize + 100];
                FileRead(hFile,pBuf,nSize);
                pBuf[nSize] = '\0';
                FileClose(hFile);
                // str = strcat(stemp,pBuf);
                //Memo1->Lines->Text  = str;
                //Memo1->Lines->Text =  stemp;
                Memo1->Lines->Text = pBuf;
                cc.log.open((Label2->Caption).c_str(),ios::app);//����������־�ļ�
        }

        else
        {
                //ShowMessage((cc.fileName+"����־�ļ�û������.").c_str());
                cc.cmes<<cc.fileName+"����־�ļ�û������,������ʾ."<<endl;
        }

        cc.cmes.close();
        str =    cc.fileName+"_cmes.txt";
        hFile = FileOpen(str.c_str(),fmOpenReadWrite);
        if(hFile > -1)
         {
                int nSize = FileSeek(hFile,0,2);
                 FileSeek(hFile,0,0);
                char *pBuf = new char[nSize + 1];
                char *str; //= new char[nSize + 100];
                FileRead(hFile,pBuf,nSize);
                pBuf[nSize] = '\0';
                FileClose(hFile);
                Memo2->Lines->Text = pBuf;
        }

        else
        {
        ShowMessage("���ɵ�����Ϣʱ���д���.");
         }



}
//---------------------------------------------------------------------------

void __fastcall TForm1::N18Click(TObject *Sender)
{
        Form1->ClientHeight = Form1->Memo2->Height + Form1->Memo2->Top;
        cc.cmes.open((cc.fileName+"_cmes.txt").c_str(),ios::out);  //�����ļ�
        cc.cmes<<"*******************************Minc Compiler Run-Time Report**********************************" <<endl;
        cc.cmes<<"����Ŀ���ļ�............."<<endl;

        cc.log<<"����Ŀ���ļ�"<<cc.fileName<<".asm"<<endl;
         if(!isAsmcode)
        {
                //ShowMessage("���ļ���Ŀ��δ����.");
                cc.cmes<<"���ļ���Ŀ��δ����,���ܱ�������."<<endl;
        }

         cc.cmes.close();
         string str =    cc.fileName+"_cmes.txt";
         HFILE hFile = FileOpen(str.c_str(),fmOpenReadWrite);
         if(hFile > -1)
         {
                int nSize = FileSeek(hFile,0,2);
                FileSeek(hFile,0,0);
                char *pBuf = new char[nSize + 1];
                char *str; //= new char[nSize + 100];
                FileRead(hFile,pBuf,nSize);
                pBuf[nSize] = '\0';
                FileClose(hFile);
                Memo2->Lines->Text = pBuf;
         }

         else
         {
              ShowMessage("���ɵ�����Ϣʱ���д���.");
         }

        if(isAsmcode)
                system("call cmd");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
        Form1->Memo1->Clear();
        Form1->Memo2->Clear();
     //   Form1->Memo2->Visible=false;
        Form1->ClientHeight = 40 + Form1->Memo1->Height;

}
//---------------------------------------------------------------------------





