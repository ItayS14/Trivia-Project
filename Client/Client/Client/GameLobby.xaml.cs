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
using System.Windows.Threading;
using MaterialDesignThemes.Wpf;

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
        private DispatcherTimer timer;

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
            try
            {
                socket.LeaveRoom(room.ID);
                finished = true;
                NavigationService.Navigate(new RoomsMenu(socket));
            }
            catch (Exception excep)
            {
                Utlis.ShowErrorMessage(excep.Message);
            }
        }

        private void Start_Button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                socket.StartGame();
                finished = true;
                OpenStartGameDialog(5);
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
                foreach (string player in players) 
                    Players.Items.Add(player);

                //Enable Start Game button if user is admin
                if (Convert.ToBoolean(data["is_admin"]))
                    StartButton.IsEnabled = true;

                if (Convert.ToInt32(data["state"]) == (int)State.In_Game)
                {
                    OpenStartGameDialog(Convert.ToInt32(data["start_in"]));
                    finished = true;
                }

                await Task.Delay(5000); // waits for 5 seconds witout stalling the program
            }
        }
        
        private void OpenStartGameDialog(int timeToStart) // will open the dialog and after timeToStart will navigate to the game
        {
            timer = new DispatcherTimer();
            timer.Tick += DialogTimer;
            timer.Interval = TimeSpan.FromSeconds(1);
            timer.Start();
            DialogTimerText.Text = timeToStart.ToString();
            StartGameDialog.IsOpen = true;
        }

        private void DialogTimer(object sender, EventArgs e)
        {
            if (DialogTimerText.Text == "0")
            {
                StartGameDialog.IsOpen = false;
                timer.Stop();
                NavigationService.Navigate(new Game(socket, room));
            }
            else
                DialogTimerText.Text = (int.Parse(DialogTimerText.Text) - 1).ToString();
        }
    }
}
