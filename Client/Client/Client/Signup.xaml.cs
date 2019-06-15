using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using Newtonsoft.Json;
using System.Net.Sockets;
using System.Net;

namespace Client
{
    /// <summary>
    /// Interaction logic for Signup.xaml
    /// </summary>
    public partial class Signup : Window
    {
        public Signup()
        {
            InitializeComponent();
        }
        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
        private void SignUpButton_Click(object sender, RoutedEventArgs e)
        {
            string username = UsernameTextBox.Text;
            string password = PasswordBox.Password;
            string email = EmailTextBox.Text;
            string serverAddress = "127.0.0.1";
            int serverPort = 4422;

            Dictionary<string, string> dict = new Dictionary<string, string>();
            dict.Add("username", username);
            dict.Add("password", password);
            dict.Add("email", email);
            //Connect and send to server
            TcpClient client = new TcpClient();
            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse(serverAddress), serverPort);
            client.Connect(serverEndPoint);
            NetworkStream clientStream = client.GetStream();
            List<byte> buffer = new ASCIIEncoding().GetBytes(JsonConvert.SerializeObject(dict)).ToList();
            //Add code of message and length of json message, according to the protocol
            List<byte> prefix = Encoding.ASCII.GetBytes("100" + buffer.Count.ToString().PadLeft(4, '0')).ToList();
            prefix.AddRange(buffer);
            byte[] bytes = prefix.ToArray();
            clientStream.Write(bytes, 0, bytes.Length);
            clientStream.Flush();

            //Check response
            bytes = new byte[3];
            int bytesRead = clientStream.Read(bytes, 0, bytes.Length);
            Console.WriteLine(Encoding.Default.GetString(bytes));
            int code = int.Parse(Encoding.Default.GetString(bytes));
            bytes = new byte[4];
            bytesRead = clientStream.Read(bytes, 0, bytes.Length);
            int size = int.Parse(Encoding.Default.GetString(bytes));
            string msg = "";
            if (size != 0)
            {
                bytes = new byte[size];
                bytesRead += clientStream.Read(bytes, 0, bytes.Length);
                msg = Encoding.Default.GetString(bytes);
            }
            Console.WriteLine(code.ToString() + " " + msg);

        }
    }
}
