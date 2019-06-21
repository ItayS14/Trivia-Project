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
    /// Interaction logic for AdminGameLobby.xaml
    /// </summary>
    public partial class AdminGameLobby : Page
    {
        private SocketHandler socket;
        private Room room;
        public AdminGameLobby(SocketHandler socket, Room room)
        {
            InitializeComponent();
            this.socket = socket;
            this.room = room;
            Dictionary<string, object> data = socket.GetRoomState(room.ID);
            UpdateRoomData(data);
        }

        private void Start_Button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                socket.StartGame(room.ID);
            }
            catch(Exception excep)
            {
                Utlis.ShowErrorMessage(excep.Message);
            }
        }

        private void Close_Button_Click(object sender, RoutedEventArgs e)
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
        private void UpdateRoomData(Dictionary<string, object> data)
        {
            //Show players in room
            List<string> players = (List<string>)data["players"];
            foreach (string player in players)
                Players.Items.Add(player);

            //Show room data
            int type = Convert.ToInt32(data["type"]);
            RoomTypeText.Text = Enum.GetName(typeof(Types), type).Replace('_', ' ');
            //Need to add time for answer and question count (recieve the data from somewhere)
        }
    }
}
