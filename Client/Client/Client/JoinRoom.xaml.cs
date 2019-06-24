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
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Page
    {
        private SocketHandler socket;
        private Room room;
        private bool finished;

        public JoinRoom(SocketHandler socket, Room room) // Should i also display other stuff that belongs to the room?
        {
            InitializeComponent();
            this.socket = socket;
            this.room = room;
            finished = false;
            try
            {
                UpdateRoomData();
            }
            catch (Exception excep)
            {
                Utlis.ShowErrorMessage(excep.Message);
            }
            InitializeComponent();
        }

        private void JoinRoomClick(object sender, RoutedEventArgs e)
        {
            try
            {
                socket.JoinRoom(room.ID);
                finished = true; // here so the async function will only stop if there were no errors
                NavigationService.Navigate(new GameLobby(socket, room,false));
            }
            catch (Exception excep)
            {
                Utlis.ShowErrorMessage(excep.Message);
            }
        }

        private void BackButton(object sender, RoutedEventArgs e)
        {
            finished = true;
            NavigationService.Navigate(new RoomsMenu(socket));
        }

        private void LogoutButton(object sender, RoutedEventArgs e)
        {
            try
            {
                socket.SignOut();
                finished = true; // here so the async function will only stop if there were no errors
                NavigationService.Navigate(new SignIn(socket));
            }
            catch (Exception excep)
            {
                Utlis.ShowErrorMessage(excep.Message);
            }
        }
        private async void UpdateRoomData() // will run once per 5 seconds
        {        
            while (!finished)
            {
                Dictionary<string, object> data = socket.GetRoomState(room.ID);

                List<string> players = Utlis.ObjectToList<string>(data["players"]);
                // Disable the button if the room is full or running
                if (Convert.ToInt32(data["state"]) != (int)State.Joinable || players.Count == Convert.ToInt32(data["max_players"]))
                    JoinRoomButton.IsEnabled = false;
                else
                    JoinRoomButton.IsEnabled = true;
                AdminTextBox.Text = players[0];
                foreach (string player in players.Skip(1))
                    Players.Items.Add(player);
                int type = Convert.ToInt32(data["type"]);
                RoomTypeText.Text = Enum.GetName(typeof(Types), type).Replace('_', ' ');
                QuestionsNumberText.Text = Convert.ToString(room.QuestionCount);
                QuestionTimeText.Text = Convert.ToString(room.TimePerQuestion);

                await Task.Delay(5000);
            }
        }
    }
}
