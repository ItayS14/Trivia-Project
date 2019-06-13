using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using System.Net;
using Newtonsoft.Json;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Client
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class SignIn : Window
    {
        public SignIn()
        {
            InitializeComponent();
            //Application.Current.Properties["socket"] = new SocketHandler("127.0.0.1",4422);
            //SocketHandler socket = new SocketHandler("127.0.0.1", 4422);
           
        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
        private void SignInButton_Click(object sender, RoutedEventArgs e)
        {
            
        }
    }
}
