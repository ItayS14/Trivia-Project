using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using Newtonsoft.Json;
using System.Security.Cryptography;
namespace Client
{
    class Utlis
    {
        static public void ShowErrorMessage(string info)
        {
            MainWindow window = (MainWindow)Application.Current.Windows.OfType<Window>().SingleOrDefault(x => x.IsActive);
            if (window != null) // Cannot display dialog if there is no window loaded
            {
                window.ErrorMessageText.Text = info;
                window.ErrorDialog.IsOpen = true;
            }
            else
            {
                string msg = "Error!\nInfo: " + info;
                MessageBox.Show(msg, "Error Message");
            }
        }
        static public List<T> ObjectToList<T>(object data)
        {
            return JsonConvert.DeserializeObject<List<T>>(Convert.ToString(data));
        }
    }
}
