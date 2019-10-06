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
         isMcode = false;      //语法分析
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

        cc.reSet();           //重置编译器

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
                Label1->Caption = "源程序：";

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
                //初始化token表文件
                cc.log<<"创建"+cc.fileName+"的token表文件"<<endl;
                cc.fft.open((cc.fileName+"_fourTerm.txt").c_str(),ios::out);
                //初始化四元式表
                cc.log<<"创建"+cc.fileName+"的中间代码四元式文件"<<endl;
                cc.fstk.open((cc.fileName+"_stack.txt").c_str(),ios::out);
                // 初始化语法栈
                cc.log<<"创建"+cc.fileName+"的语法栈表文件"<<endl;
                cc.mout.open((cc.fileName + ".asm").c_str(),ios::out);
                cc.log<<"创建"+cc.fileName+"的ASM目标代码文件"<<endl;
                //他们都会清空上一次的内容


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

void __fastcall TForm1::N6Click(TObject *Sender)                //开始词法分析
{

        int i = 0;
        char buffer[10];
        Token *t = new Token;
        int j = 0;
        Form1->ClientHeight = Form1->Memo2->Height + Form1->Memo2->Top;
        cc.cmes.open((cc.fileName+"_cmes.txt").c_str(),ios::out);  //创建文件
        cc.cmes<<"*******************************Minc Compiler Run-Time Report**********************************" <<endl;
        cc.cmes<<"词法分析............"<<endl;
        if(cc.hasFile == false)
        {
           // ShowMessage("不存在源文件.");
            cc.cmes<<"不存在源文件."<<endl;
           goto SHOW;
        }


        cc.line = 1;
        cc.isLexErrId = false;  //避免语法分析时，词法错误。而没有重置
        cc.hasError = false;   //在词法分析，前都是正确的

        cc.preProcess();
        if(cc.hasFile)               // 肯定存在的
                cc.in.open((cc.fileName+".crr").c_str(),ios::in);
        cc.currentChar=cc.nextChar();                          //词法分析器初始化
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
        cc.ftoken<<"单词"<<"\t"<<"种类"<<"\t"<<"行数"<<endl;

        for(;j<=i;j++)
        {
                cc.ftoken<<cc.cct[j].word<<"\t"<<cc.cct[j].group<<"\t"<<itoa(cc.cct[j].line,buffer,10)<<"\n";
        }
        cc.ftoken.close();                              // Token 表形成
        cc.isTokenClose = true;
        //cc.line = 1;
        isLexer = true;
         if(!cc.hasError)
         {
               // ShowMessage("词法分析完毕,正确！");
                cc.cmes<<"词法分析结束,正确."<<endl;
         }
        else
        {
                //ShowMessage("词法分析完毕，有错误！");
                cc.cmes<<"词法分析有错误."<<endl;
        }
        cc.in.close();
        cc.in.clear(ios::goodbit);  //读源程序文件，只有一次


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
                ShowMessage("生成调试信息时，有错误.");
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
   ShowMessage((cc.fileName+".crr"+"文件的Token表，未生成\n不能显示！").c_str());
   return ;
 }        */
 //else
 //{
  //ins.close();

  Form1->ClientHeight = Form1->Memo2->Height + Form1->Memo2->Top;
  cc.cmes.open((cc.fileName+"_cmes.txt").c_str(),ios::out);  //创建文件
  cc.cmes<<"*******************************Minc Compiler Run-Time Report**********************************" <<endl;
  cc.cmes<<"显示Token表............"<<endl;

  string str =    cc.fileName+"_token.txt";
  HFILE hFile = FileOpen(str.c_str(),fmOpenReadWrite);
  if(hFile > -1)
  {

        //char *stemp =  "单词\t类型\t行数\n";
        Label1->Caption = "<Token>表:";
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
        //ShowMessage((cc.fileName+"的Token表未生成.").c_str());
        cc.cmes<<cc.fileName<<"的Token表没有生成不能显示."<<endl;
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
        ShowMessage("生成调试信息时，有错误.");
  }

  return;
 //}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::N8Click(TObject *Sender)
{
   Form1->ClientHeight = Form1->Memo2->Height + Form1->Memo2->Top;
   cc.cmes.open((cc.fileName+"_cmes.txt").c_str(),ios::out);  //创建文件
   cc.cmes<<"*******************************Minc Compiler Run-Time Report**********************************" <<endl;
   cc.cmes<<"语法制导翻译............."<<endl;
   if(!cc.hasFile)
   {
        //ShowMessage("源文件不存在.");
        cc.cmes<<"源文件不存在."<<endl;
        goto SHOW;
   }

   //cc.line = 1;
   if(cc.hasError)
   {
        //ShowMessage((cc.fileName+"代码有错误,不能语法制导翻译").c_str());
        cc.cmes<<cc.fileName+"代码有错误,不能语法制导翻译"<<endl;
        goto SHOW;
   }
   if(isMcode)
   {
        //ShowMessage("已进行语法制导翻译!\n");
        cc.cmes<<"语法制导翻译已经完成."<<endl;
        goto SHOW;
   }
   if(!isLexer)
   {
       // ShowMessage("Token表尚未生成！\n进行一遍式语法语义分析.");
        cc.cmes<<"Token表尚未生成！\n进行一遍式语法语义分析."<<endl;
   }
   else
   {
        //ShowMessage("Token表已经生成!,调用token表进行语法语义分析");
        cc.cmes<<"Token表已经生成!,调用token表进行语法语义分析"<<endl;
   }


   cc.parser(isLexer);    //生成了四元式，语法分析栈

   cc.line = 1;
   //cc.nextquad = 0;  不用因为生成中间代码，只用一次
   if(cc.hasError)
   {
        //ShowMessage("语法分析有错误,不能生成中间代码.\n");
        cc.cmes<<"语法分析有错误,不能生成中间代码" <<endl;
   }

   else
   {
        cc.cmes<<"语法分析正确,成功生成中间代码" <<endl;
        cc.showFterm();   //保存四元式
        cc.wriStk();      //保存符号栈
        //ShowMessage("语法分析完成!");
        isMcode = true;
        isLexer = true;                           //如果没有词法分析
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
        ShowMessage("生成调试信息时，有错误.");
     }
             
     return;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::N9Click(TObject *Sender)
{
/*
 ifstream ins((cc.fileName+".stk").c_str(),ios::in);    //转移的问题


 if(!ins.is_open())
 {
   ShowMessage((cc.fileName+".crr"+"文件的语法栈未生成\n，不能显示！").c_str());
   ins.close();
   return ;
 }
 */
// else
 //{
 // ins.close();
  //Label1->Caption = "语法栈:";
 // Label2->Caption = (cc.fileName+"_stack.txt").c_str();
 Form1->ClientHeight = Form1->Memo2->Height + Form1->Memo2->Top;
  cc.cmes.open((cc.fileName+"_cmes.txt").c_str(),ios::out);  //创建文件
  cc.cmes<<"*******************************Minc Compiler Run-Time Report**********************************" <<endl;
  cc.cmes<<"显示语法分析栈......."<<endl;

  string str;
  str =  cc.fileName+"_stack.txt";
  HFILE hFile = FileOpen(str.c_str(),fmOpenReadWrite);
  if(hFile > - 1)
  {
         //char *stemp =  "单词\t类型\t行数\n";
        Label1->Caption = "语法栈:";
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
       //ShowMessage((cc.fileName+".crr"+"文件的语法栈未生成\n，不能显示！").c_str());
       cc.cmes<<cc.fileName<<".crr"<<"文件的语法栈未生成\n，不能显示！"<<endl;
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
        ShowMessage("生成调试信息时，有错误.");
  }



}
//---------------------------------------------------------------------------


void __fastcall TForm1::N10Click(TObject *Sender)
{
  /*
 ifstream ins((cc.fileName+".ft").c_str(),ios::in);    //对于这种打开文件与FileOpen不一样啊

 if(!ins.is_open())
 {
   ShowMessage((cc.fileName+".crr"+"文件的中间代码不能显示，未生成\n不能显示！").c_str());
   ins.close();
   return ;
 }  */
 //else
 //{
 // ins.close();
 //Label1->Caption = "中间代码:";
 //Label2->Caption = (cc.fileName+"_fourterm.txt").c_str();
  string str =  cc.fileName+"_fourTerm.txt";
  HFILE hFile = FileOpen(str.c_str(),fmOpenReadWrite);

  Form1->ClientHeight = Form1->Memo2->Height + Form1->Memo2->Top;
  cc.cmes.open((cc.fileName+"_cmes.txt").c_str(),ios::out);  //创建文件
  cc.cmes<<"*******************************Minc Compiler Run-Time Report**********************************" <<endl;
  cc.cmes<<"显示中间代码......."<<endl;

  if(hFile > - 1)
  {
        //char *stemp =  "单词\t类型\t行数\n";
        Label1->Caption = "中间代码:";
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
        //ShowMessage((cc.fileName +"的四元式还没有生成.").c_str());
        cc.cmes<<cc.fileName<<"的四元式还没有生成，不能显示中间代码.\n"<<endl;
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
        ShowMessage("生成调试信息时，有错误.");
  }


 
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N17Click(TObject *Sender)
{

        Form1->ClientHeight = Form1->Memo2->Height + Form1->Memo2->Top;
        cc.cmes.open((cc.fileName+"_cmes.txt").c_str(),ios::out);  //创建文件
        cc.cmes<<"*******************************Minc Compiler Run-Time Report**********************************" <<endl;
        cc.cmes<<"显示源程序............."<<endl;
         HFILE hFile;
        if(!cc.hasFile)
        {
                //ShowMessage("源文件不存在.");
                cc.cmes<<"源文件不存在."<<endl;
                goto SHOW;
        }
        Label2->Caption = (cc.fileName+".crr").c_str();
        //ShowMessage(str.c_str());
        Label1->Caption = "源程序：";

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
        ShowMessage("生成调试信息时，有错误.");
         }
      
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N12Click(TObject *Sender)
{
   Form1->ClientHeight = Form1->Memo2->Height + Form1->Memo2->Top;
   cc.cmes.open((cc.fileName+"_cmes.txt").c_str(),ios::out);  //创建文件
   cc.cmes<<"*******************************Minc Compiler Run-Time Report**********************************" <<endl;
   cc.cmes<<"生成目标代码............."<<endl;
   if(!cc.hasFile)
   {
       // ShowMessage("源文件不存在!");
        cc.cmes<<"源文件不存在"<<endl;
        goto SHOW;
   }
   if(cc.hasError)
   {
        cc.cmes<<"源代码已发现错误，不能生成目标代码."<<endl;
        goto SHOW;
   }
   if(isAsmcode)
   {
        //ShowMessage("目标代码文件已经生成.");
        cc.cmes<<"目标代码文件已经生成."<<endl;
        goto SHOW;
   }

   if(!isMcode)
   {
        if(!isLexer)
        {
           //ShowMessage("Token表没有生成，直接生成目标代码.");
           cc.cmes<<"Token表没有生成，直接语法制导翻译"<<endl;
        }
        else
        {
           //ShowMessage("中间代码没有生成，直接生成目标代码.");
           cc.cmes<<"中间代码没有生成，开始生成中间代码，目标代码."<<endl;
        }

        cc.parser(isLexer);
        if(cc.hasError)
        {
            //ShowMessage("词法，语法分析有错误，不能生成中间，目标代码.");
            cc.cmes<<"词法，语法分析有错误，不能生成中间，目标代码."<<endl;
            goto SHOW;
        }
        else
        {
            cc.cmes<<"语法分析完毕，正确生成中间代码,目标代码."<<endl;
            cc.showFterm();   //保存四元式
            cc.wriStk();      //保存符号栈
            //ShowMessage("语法分析完毕，正确生成中间代码,目标代码.");
            cc.genMaincode();  //根据中间代码，生成main函数的目标代码
            cc.creatAsm();    //添加必要的asm代码，生成可编译的asm文件
            isMcode = true;
            isAsmcode = true;
        }
   }
   else
   {
       // ShowMessage("中间代码已经生成，生成目标代码.");
        cc.cmes<<"中间代码已经生成，正确生成目标代码."<<endl;
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
        ShowMessage("生成调试信息时，有错误.");
  }





}
//---------------------------------------------------------------------------

void __fastcall TForm1::N13Click(TObject *Sender)
{

        Form1->ClientHeight = Form1->Memo2->Height + Form1->Memo2->Top;
        cc.cmes.open((cc.fileName+"_cmes.txt").c_str(),ios::out);  //创建文件
        cc.cmes<<"*******************************Minc Compiler Run-Time Report**********************************" <<endl;
        cc.cmes<<"显示目标代码............."<<endl;

        string str = cc.fileName+".asm";
        HFILE hFile = FileOpen(str.c_str(),fmOpenReadWrite);
        if(hFile > - 1)                //不存在源文件
        {
                Label1->Caption = "目标代码ASM:";
                Label2->Caption =  str.c_str();//("my"+cc.fileName+".asm").c_str();
                //char *stemp =  "单词\t类型\t行数\n";
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
               // ShowMessage((str+"文件没有生成，不能显示.").c_str());
                cc.cmes<<str<<"目标文件没有生成，不能显示."<<endl;
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
                 ShowMessage("生成调试信息时，有错误.");
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N15Click(TObject *Sender)
{

        Form1->ClientHeight = Form1->Memo2->Height + Form1->Memo2->Top;
        cc.cmes.open((cc.fileName+"_cmes.txt").c_str(),ios::out);  //创建文件
        cc.cmes<<"*******************************Minc Compiler Run-Time Report**********************************" <<endl;
        cc.cmes<<"显示日志文件............."<<endl;

        string str = cc.fileName+"_log.txt";
        cc.log.close();
        HFILE hFile = FileOpen(str.c_str(),fmOpenReadWrite);
        if(hFile > - 1)
        {
                //char *stemp =  "单词\t类型\t行数\n";
                //cc.log.close();
                Label1->Caption = "日志文件:";
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
                cc.log.open((Label2->Caption).c_str(),ios::app);//继续开启日志文件
        }

        else
        {
                //ShowMessage((cc.fileName+"的日志文件没有生成.").c_str());
                cc.cmes<<cc.fileName+"的日志文件没有生成,不能显示."<<endl;
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
        ShowMessage("生成调试信息时，有错误.");
         }



}
//---------------------------------------------------------------------------

void __fastcall TForm1::N18Click(TObject *Sender)
{
        Form1->ClientHeight = Form1->Memo2->Height + Form1->Memo2->Top;
        cc.cmes.open((cc.fileName+"_cmes.txt").c_str(),ios::out);  //创建文件
        cc.cmes<<"*******************************Minc Compiler Run-Time Report**********************************" <<endl;
        cc.cmes<<"编译目标文件............."<<endl;

        cc.log<<"编译目标文件"<<cc.fileName<<".asm"<<endl;
         if(!isAsmcode)
        {
                //ShowMessage("该文件的目标未生成.");
                cc.cmes<<"该文件的目标未生成,不能编译运行."<<endl;
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
              ShowMessage("生成调试信息时，有错误.");
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





