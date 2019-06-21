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
using Newtonsoft.Json;
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
        public GameLobby(SocketHandler socket, Room room, bool isAdmin)
        {
            InitializeComponent();
            this.socket = socket;
            this.room = room;
            this.isAdmin = isAdmin;
            Thread thr = new Thread(new ThreadStart(ThreadUpdateRoomData));
            thr.Start();
        }

        private void Leave_Button_Click(object sender, RoutedEventArgs e)
        {
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
        private void Start_Button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                socket.StartGame(room.ID);
            }
            catch (Exception excep)
            {
                Utlis.ShowErrorMessage(excep.Message);
            }
        }
        private void UpdateRoomData()
        {
            Dictionary<string, object> data = null;
            data = socket.GetRoomState(room.ID);

            Players.Items.Clear();
            //Show players in room
            List<string> players = JsonConvert.DeserializeObject<List<string>>(Convert.ToString(data["players"]));
            //List<string> players = new List<string>()
            foreach (string player in players)
                Players.Items.Add(player);

            //Show room data
            int type = Convert.ToInt32(data["type"]);
            RoomTypeText.Text = Enum.GetName(typeof(Types), type).Replace('_', ' ');
            QuestionsNumberText.Text = Convert.ToString(room.QuestionCount);
            QuestionTimeText.Text = Convert.ToString(room.TimePerQuestion);
        }
        private void ThreadUpdateRoomData()
        {
            while (true)
            {
                this.Dispatcher.Invoke(() => //Weird syntax but the point is it lets the current thread change what appears on screen
                {
                    try
                    {
                        UpdateRoomData();
                    }
                    catch
                    {
                        return; //This signals the thread to shut down
                    }
                });
                Thread.Sleep(5000);
            }
        }
    }
}
