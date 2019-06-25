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

namespace Client
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private SocketHandler socket;
        public MainWindow()
        {
            InitializeComponent();
            SocketHandler socket;
            string ipAddress = "10.0.0.32";
            int port = 4422;
            try
            {
                socket = new SocketHandler(ipAddress,port);
                this.socket = socket;
                Main.Navigate(new SignIn(socket));
            }
            catch(Exception excep)
            {
                //Can't use the ShowErrorMessage function in the SocketHandler class because socket isn't initialized
                Utlis.ShowErrorMessage(excep.Message);
                //Don't continue to use the program because the user isn't connected
                Close();
                return;
            }
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            //Let the server know the user is closing.
            //Need to check: What if the user loses connection when is closing the window?
            if(socket != null)
                socket.Close();
        }
    }
}
