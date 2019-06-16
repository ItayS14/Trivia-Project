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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Client
{
    /// <summary>
    /// Interaction logic for SignIn.xaml
    /// </summary>
    public partial class SignIn : Page
    {
        private SocketHandler socket;
        public SignIn(SocketHandler socket)
        {
            
            InitializeComponent();
            this.socket = socket;
        }
        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
        private void SignInButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                socket.SignIn(UsernameTextBox.Text, PasswordBox.Password);
            }
            catch
            {
                //Open error window or tell the user to try to relog and return
            }
            //Main.Content = new RoomsMenu(s);
            //Main.Navigate(new RoomsMenu(s));
            NavigationService.Navigate(new RoomsMenu(socket));
        }

        private void Hyperlink_Click(object sender, RoutedEventArgs e)
        {
            //Main.Navigate(new SignUp(s));
            NavigationService.Navigate(new SignUp(socket));
        }
    }
}
