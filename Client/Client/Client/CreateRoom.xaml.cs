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
        private SocketHandler socket;

        public CreateRoom(SocketHandler socket)
        {
            InitializeComponent();
            for (int i = 1; i < 6; i++) // check for a better way to init the combo box
                MaxPlayers.Items.Add(i);
            for (int i = 5; i <= 20; i++)
                QuestionCount.Items.Add(i);
            for (int i = 10; i <= 60; i += 5)
                TimePerQuestion.Items.Add(i);
            this.socket = socket;
        }

        private void CreateButton(object sender, RoutedEventArgs e)
        {
           
            Types type;
            try
            {
                Enum.TryParse(RoomType.Text.Replace(' ', '_'), out type);
                string name = NameTextBox.Text;
                int maxPlayers = int.Parse(MaxPlayers.SelectedValue.ToString());
                int questionCount = int.Parse(QuestionCount.SelectedItem.ToString());
                int timePerQuestion = int.Parse(TimePerQuestion.SelectedItem.ToString());
                int roomId = socket.CreateRoom(name, maxPlayers, questionCount, timePerQuestion, (int)type);

                NavigationService.Navigate(new AdminGameLobby(socket, new Room(roomId, name, (int)type, maxPlayers, 1)));
            }
            catch (Exception excep)
            {
                Utlis.ShowErrorMessage(excep.Message);
            }

            
        }

        private void BackButton(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new RoomsMenu(socket));
        }

        private void LogoutButton(object sender, RoutedEventArgs e)
        {
            try
            {
                socket.SignOut();
                NavigationService.Navigate(new SignIn(socket));
            }
            catch (Exception excep)
            {
                Utlis.ShowErrorMessage(excep.Message);
            }
        }
    }
}
