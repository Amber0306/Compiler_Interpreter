using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ComplierUI
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        class Token
        {
            private String t_id;//类型
            private String t_text;//文本
            private int t_row;//行数
            private int t_count;//第几个
            public String T_id
            {
                get { return t_id; }
                set { t_id = value; }
            }
            public String T_text
            {
                get { return t_text; }
                set { t_text = value; }
            }
            public int T_row
            {
                get { return t_row; }
                set { t_row = value; }
            }
            public int T_count
            {
                get { return t_count; }
                set { t_count = value; }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            //执行词法分析
            //运行
            String s = textBox1.Text;
            s = s.Replace(" ", "");
            s = Regex.Replace(s, @"\n", "");
            s = Regex.Replace(s, @"\t", "");
            int len = s.Length;
            if (len == 0)
            {
                Console.WriteLine("进入if");
                MessageBox.Show("输入源代码");
            }
            else
            {
                char[] getChar = getCharArray(textBox1.Text);//获取输入框字符数据
                                                             //Console.WriteLine(getChar);
                                                             //Console.WriteLine(getChar.Length);

                ArrayList arrayList = getTokenArray(getChar);
                foreach (Token t in arrayList)
                {
                    string temp ="("+t.T_id + " " + t.T_text + " " + t.T_row + " " + t.T_count+")";
                    Console.WriteLine(temp);
                    if(textBox2.Text!="")
                    {
                        textBox2.Text = textBox2.Text+ "\r\n"+temp;
                    }
                    else
                    {
                        textBox2.Text = temp;
                    }
                }
            }

        }

        private char[] getCharArray(String str)
        {
            char[] getChar = str.ToCharArray();//将字符串转化为字符数组
            return getChar;
        }
       

        private ArrayList getTokenArray(char[] getChar)
        {
            ArrayList arrToken = new ArrayList();//保存Token

            //int lenChar = getChar.Length;

            //当输入无意义时，弹出对话框
            /*            if (lenChar == 0)
                            MessageBox.Show("请输入源代码");
                        foreach (char a in getChar)
                        {
                            MessageBox.Show("请输入源代码");
                        }*/

            /*if (lenChar == 0)
            {
                MessageBox.Show("请输入源代码");
            }*/



            String temp = "";//保存当前词素的文本
            int row = 1;//初始化行数，从1开始
            int count = 0;//初始化第几个单词，从0开始

            string[] keywords = { "if", "else", "int", "return", "void", "while" };//6个关键字
            string[] op = { "+", "-", "*", "/", "=", "<", "<=", ">", ">=", "==", "!=" };//11个运算符
            string[] diverse = { "(", ")", "[", "]", ",", ";", "{", "}", "/*", "*/" };//10个分隔符

            for (int i = 0; i < getChar.Length; i++)
            {
                char current = getChar[i];
                //Console.WriteLine("循环中，当前字符"+i+" " + current);
                if (current == '\n')
                {
                    row++;//计算当前行
                    count = 0;
                }
                else if (current == ' ' || current == '\t' || current == '\r')//判断空格
                {

                }
                else if (current == '\n')//判断换行符
                {
                    row++;
                }
                else if (char.IsDigit(current))//数字起始，只能是数值，之后是数字时累积
                {
                    temp += current.ToString();
                    while (i != getChar.Length - 1)
                    {
                        if (char.IsDigit(getChar[i + 1]))
                        {
                            temp += getChar[i + 1].ToString();
                            i++;
                        }
                        else
                            break;
                    }
                    count++;

                    Token token = new Token();
                    token.T_id = "digit";
                    token.T_text = temp;
                    token.T_row = row;
                    token.T_count = count;

                    arrToken.Add(token);
                    temp = "";
                }
                else if (char.IsLetter(current))//字母起始，可能是关键字或标识符，遇到空格、制表符、换行符、运算符、分隔符结束
                {
                    temp += current.ToString();
                    while (i != getChar.Length - 1)
                    {
                        if (char.IsLetterOrDigit(getChar[i + 1]))
                        {
                            temp += getChar[i + 1].ToString();
                            i++;
                        }
                        else
                            break;
                    }
                    count++;

                    Token token = new Token();
                    //匹配关键字
                    int flag = 0;
                    foreach (String s in keywords)
                    {
                        if (temp.Equals(s))
                        {
                            flag = 1;
                        }
                        else
                        {

                        }
                    }

                    if (flag == 0)
                    {
                        token.T_id = "identifier";
                        token.T_text = temp;
                        token.T_row = row;
                        token.T_count = count;
                    }
                    else if (flag == 1)
                    {
                        token.T_id = "keywords";
                        token.T_text = temp;
                        token.T_row = row;
                        token.T_count = count;
                    }


                    arrToken.Add(token);
                    temp = "";
                }
                else//运算符或分隔符，或未识别
                {
                    temp += current.ToString();
                    if (i != getChar.Length - 1)
                    {
                        //判断是单目还是双目
                        if (getChar[i + 1] == '=' || getChar[i + 1] == '*' || getChar[i + 1] == '/')
                        {
                            temp += getChar[i + 1].ToString();
                            i++;
                        }
                        else
                        {

                        }
                    }

                    count++;
                    Token token = new Token();
                    int flag = 0;
                    foreach (String s in op)
                    {
                        if (temp.Equals(s))
                        {
                            flag = 1;
                        }
                    }
                    foreach (String s in diverse)
                    {
                        if (temp.Equals(s))
                        {
                            flag = 2;
                        }
                    }
                    if (flag == 1)//运算符
                    {
                        token.T_id = "operater";
                        token.T_text = temp;
                        token.T_row = row;
                        token.T_count = count;
                    }
                    else if (flag == 2)//分隔符
                    {
                        token.T_id = "diverse";
                        token.T_text = temp;
                        token.T_row = row;
                        token.T_count = count;
                    }
                    else if (flag == 0)//未识别
                    {
                        token.T_id = "unKnown";
                        token.T_text = temp;
                        token.T_row = row;
                        token.T_count = count;
                    }
                    arrToken.Add(token);
                    temp = "";
                }
            }

            return arrToken;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //保存为文件
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();
            saveFileDialog1.Filter = "文本文件(*.txt)|*.txt|CPP文件(*.cpp)|*.cpp|CS文件(*.cs)|*.cs";      //设置文件保存格式，可任意添加
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                ////如果保存对话框打开了
                FileStream fileStream = new FileStream(saveFileDialog1.FileName,
                   FileMode.Create, FileAccess.Write);
                StreamWriter w = new StreamWriter(fileStream);      //实例化StreamWriter对象，saveFileDialog1.FileName为用户输入的文件名

                w.WriteLine(textBox2.Text);
                //写入内容
                w.Close();//关闭写入流
                //textBox2.Clear();
            }

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            //显示文件内容

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            //输出结果

        }

        private void button3_Click(object sender, EventArgs e)
        {
            //打开文件
            CodeReader();
        }
        private void CodeReader()
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            openFileDialog1.Filter = "文本文件(*.txt)|*.txt|CPP文件(*.cpp)|*.cpp|CS文件(*.cs)|*.cs";
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    FileStream fileStream = new FileStream(
                        openFileDialog1.FileName, FileMode.Open, FileAccess.Read);

                    StreamReader streamReader = new StreamReader(
                        fileStream);

                    //StreamReader streamReader = new StreamReader(openFileDialog1.FileName, true);

                    //int rowNum = 0;       //行号
                    //string s = streamReader.ReadLine();
                    //while (s != null)
                    //{
                    //    //rowNum++;
                    //    /*s = deleteComments(s);*/
                    //    textBox1.Text = s;//输出
                    //    s = streamReader.ReadLine();
                    //}
                    string s = streamReader.ReadToEnd();
                    textBox1.Text = s;
                    streamReader.Close();
                }
                catch (IOException e1)
                {
                    Console.WriteLine(e1);
                }
            }

            //去掉以//开头的注释          
        }
        private string deleteComments(string s)
        {
            if (s == null)
                return s;
            int pos = s.IndexOf("//");
            if (pos < 0)
                return s;
            return s.Substring(0, pos);
            throw new NotImplementedException();
        }
    }
}
