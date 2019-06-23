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
using System.Threading;

namespace Client
{
    /// <summary>
    /// Interaction logic for GameLobby.xaml
    /// </summary>
    public partial class GameLobby : Page
    {
        private SocketHandler socket;
        private Room room;
        private bool isAdmin;
        private bool finished;

        public GameLobby(SocketHandler socket, Room room, bool isAdmin)
        {
            InitializeComponent();
            this.socket = socket;
            this.room = room;
            this.isAdmin = isAdmin;
            finished = false;

            //Show room data
            RoomTypeText.Text = room.Type;
            QuestionsNumberText.Text = Convert.ToString(room.QuestionCount);
            QuestionTimeText.Text = Convert.ToString(room.TimePerQuestion);

            UpdateRoomData();
        }

        private void Leave_Button_Click(object sender, RoutedEventArgs e)
        {
            finished = true;
            try
            {
                socket.LeaveRoom(room.ID);
                NavigationService.Navigate(new RoomsMenu(socket));
            }
            catch (Exception excep)
            {
                Utlis.ShowErrorMessage(excep.Message);
            }
        }
        private async void Start_Button_Click(object sender, RoutedEventArgs e)
        {
            finished = true;
            try
            {
                socket.StartGame(room.ID);
                await Task.Delay(5000);
                NavigationService.Navigate(new Game(socket,room));
            }
            catch (Exception excep)
            {
                Utlis.ShowErrorMessage(excep.Message);
            }
        }

        private async void UpdateRoomData()
        {
            while (!finished)
            {
                Dictionary<string, object> data = socket.GetRoomState(room.ID);

                Players.Items.Clear();
                //Show players in room
                List<string> players = Utlis.ObjectToList<string>(data["players"]);
                AdminTextBox.Text = players[0];
                foreach (string player in players.Skip(1)) //Start from second player
                    Players.Items.Add(player);

                //Enable Start Game button if user is admin
                if (Convert.ToBoolean(data["is_admin"]))
                    StartButton.IsEnabled = true;

                if (Convert.ToInt32(data["state"]) == (int)State.In_Game)
                {
                    await Task.Delay(Convert.ToInt32(data["start_in"]) * 1000);
                    //display message that game is about to start
                    NavigationService.Navigate(new Game(socket,room));
                }

                await Task.Delay(5000); // waits for 5 seconds witout stalling the program

            }

        }
    }
}
