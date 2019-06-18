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
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    public partial class CreateRoom : Page
    {
        private SocketHandler s;

        public CreateRoom()
        {
          
        }
        public CreateRoom(SocketHandler s)
        {
            InitializeComponent();
            for (int i = 1; i < 6; i++) // check for a better way to init the combo box
                MaxPlayers.Items.Add(i);
            for (int i = 5; i <= 20; i++)
                QuestionCount.Items.Add(i);
            for (int i = 10; i <= 60; i += 5)
                TimePerQuestion.Items.Add(i);
            this.s = s;
        }

        private void CreateButton(object sender, RoutedEventArgs e)
        {
            try //check for a better way to get the elements
            {
                Types type;
                Enum.TryParse(RoomType.Text.Replace(' ', '_'), out type);
                int roomId = s.CreateRoom(NameTextBox.Text, int.Parse(MaxPlayers.SelectedValue.ToString()), int.Parse(QuestionCount.SelectedItem.ToString()),
                    int.Parse(TimePerQuestion.SelectedItem.ToString()), (int)type);
                s.JoinRoom(roomId);
            }
            catch
            {
                //socket error
            }
            //Now open the window of the new room
        }

        private void BackButton(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new RoomsMenu(s));
        }

        private void LogoutButton(object sender, RoutedEventArgs e)
        {
            s.SignOut();
            NavigationService.Navigate(new SignIn(s));
        }
    }
}
