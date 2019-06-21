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
            UpdateRoomData();
        }
        
        private void Leave_Button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                socket.LeaveRoom(room.ID);
                NavigationService.Navigate(new RoomsMenu(socket));
            }
            catch(Exception excep)
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
            Dictionary<string, object> data = socket.GetRoomState(room.ID);

            
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
    }
}
