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


        public JoinRoom(SocketHandler socket, Room room) // Should i also display other stuff that belongs to the room?
        {
            InitializeComponent();
            this.socket = socket;
            this.room = room;
            try
            {
                Dictionary<string, object> data = socket.GetRoomState(room.ID);
                foreach(string player in (List<string>)data["players"]) // Consider better way to insert into the listbox
                    Players.Items.Add(player);
                int type = Convert.ToInt32(data["type"]);
                RoomTypeText.Text = Enum.GetName(typeof(Types), type).Replace('_', ' ');
                QuestionsNumberText.Text = Convert.ToString(room.QuestionCount);
                QuestionTimeText.Text = Convert.ToString(room.TimePerQuestion);
            }
            catch (Exception excep)
            {
                Utlis.ShowErrorMessage(excep.Message);
            }
            InitializeComponent();
        }

        private void JoinRoomButton(object sender, RoutedEventArgs e)
        {
            try
            {
                socket.JoinRoom(room.ID);
                NavigationService.Navigate(new GameLobby(socket, room.ID,false));
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
