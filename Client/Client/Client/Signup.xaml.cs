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
        private SocketHandler socket;
        public SignUp()
        {
            InitializeComponent();
        }
        public SignUp(SocketHandler socket)
        {
            InitializeComponent();
            this.socket = socket;
        }

        private void SignUpButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                string password = PasswordBox.Password;
                if (PasswordUtlis.IsTooWeak(password)) //Check that password is strong enough
                    throw new Exception("Password isn't strong enough!"); 
                else
                    password = Utlis.GetHashString(password); //Encrypt the password with SHA-256 before sending     
                socket.SignUp(UsernameTextBox.Text, password, EmailTextBox.Text);
                //Sign in after the sign up automatically
                socket.SignIn(UsernameTextBox.Text, password);
                //Go to rooms menu after sign up is successful
                NavigationService.Navigate(new RoomsMenu(socket));
            }
            catch(Exception excep)
            {
                Utlis.ShowErrorMessage(excep.Message);
            }

            
        }
        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
           
        }

        private void PasswordBoxPasswordChanged(object sender, RoutedEventArgs e)
        {
            PasswordUtlis.PasswordStrength passwordStrength = PasswordUtlis.GetPasswordStrength(PasswordBox.Password);
            PasswordStrengthBar.Value = (int)passwordStrength;
            PasswordStrengthTextBox.Text = passwordStrength.ToString().Replace('_',' ');
        }
    }
}
