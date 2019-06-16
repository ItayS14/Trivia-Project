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
        public MainWindow()
        {
            InitializeComponent();
            SocketHandler socket = null;
            try
            {
                socket = new SocketHandler("127.0.0.1", 4422);
            }
            catch
            {
                //Open error window telling the user he has no internet probably
            }
            Main.Navigate(new SignIn(socket));
            
        }
    }
}
