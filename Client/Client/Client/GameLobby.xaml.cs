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
    /// Interaction logic for GameLobby.xaml
    /// </summary>
    public partial class GameLobby : Page
    {
        private SocketHandler socket;
        private int roomId;
        private bool isAdmin;
        public GameLobby(SocketHandler socket, int roomId, bool isAdmin)
        {
            InitializeComponent();
            this.socket = socket;
            this.roomId = roomId;
            this.isAdmin = isAdmin;
            UpdateRoomData();
        }
        
        private void Leave_Button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                socket.LeaveRoom(roomId);
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
                socket.StartGame(roomId);
            }
            catch (Exception excep)
            {
                Utlis.ShowErrorMessage(excep.Message);
            }
        }
        private void UpdateRoomData()
        {
            Dictionary<string, object> data = socket.GetRoomState(roomId);

            //Show players in room
            List<string> players = (List<string>)data["players"];
            foreach (string player in players)
                Players.Items.Add(player);

            //Show room data
            int type = Convert.ToInt32(data["type"]);
            RoomTypeText.Text = Enum.GetName(typeof(Types), type).Replace('_', ' ');
            QuestionsNumberText.Text = Convert.ToString(data["question_count"]);
            QuestionTimeText.Text = Convert.ToString(data["time_per_question"]);
        }
    }
}
