using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            //
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();
            saveFileDialog1.Filter = "文本文件(*.txt)|*.txt|CPP文件(*.cpp)|*.cpp|CS文件(*.cs)|*.cs";      //设置文件保存格式，可任意添加
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                ////如果保存对话框打开了
                 FileStream fileStream = new FileStream(saveFileDialog1.FileName,
                    FileMode.Create, FileAccess.Write);
                StreamWriter w = new StreamWriter(fileStream);      //实例化StreamWriter对象，saveFileDialog1.FileName为用户输入的文件名
               
                w.WriteLine(textBox1.Text);
                //写入内容
                w.Close();//关闭写入流
                textBox1.Clear();
            }

        }

        private void Button2_Click(object sender, EventArgs e)
        {
            //OpenFileDialog openFileDialog1 = new OpenFileDialog();
            //openFileDialog1.Filter = "文本文件(*.txt)|*.txt";
            //if (openFileDialog1.ShowDialog() == DialogResult.OK)
            //{
            //    //如果打开对话框打开了
            //    FileStream fs = new FileStream(
            //        openFileDialog1.FileName, FileMode.Open, FileAccess.Read);   //对字节进行读取
            //    StreamReader r = new StreamReader(fs);
            //    //实例化StreamReader对象
            //    textBox1.Text = r.ReadToEnd();

            //    //使用ReadToEnd表示从当前位置一直读到末尾
            //    fs.Close();
            //    r.Close();
            //    //关闭读取流
            //}
            CodeReader();
        }

        public void CodeReader()
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

        private void TextBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
