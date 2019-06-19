using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Client
{
    class Utlis
    {
        static public void ShowErrorMessage(string info)
        {
            string msg = "Error!\nInfo: " + info;
            MessageBox.Show(msg, "Error Message");
        }
    }
}
