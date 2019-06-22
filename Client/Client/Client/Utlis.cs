using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using Newtonsoft.Json;

namespace Client
{
    class Utlis
    {
        static public void ShowErrorMessage(string info)
        {
            string msg = "Error!\nInfo: " + info;
            MessageBox.Show(msg, "Error Message");
        }
        static public List<string> ObjectToStringList(object data)
        {
            return JsonConvert.DeserializeObject<List<string>>(Convert.ToString(data));
        }
    }
}
