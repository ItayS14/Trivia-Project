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
    /// Interaction logic for SignUp.xaml
    /// </summary>
    public partial class SignUp : Page
    {
        private SocketHandler s;
        public SignUp()
        {
            InitializeComponent();
        }
        public SignUp(SocketHandler s)
        {
            this.s = s;
        }

        private void SignUpButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                s.SignUp(UsernameTextBox.Text, PasswordBox.Password, EmailTextBox.Text);

            }
            catch
            {
                //Display error message, couldn't sign up
            }

            //Go to rooms menu after sign up is successful
            NavigationService.Navigate(new RoomsMenu(s));
        }
        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
    }
}
