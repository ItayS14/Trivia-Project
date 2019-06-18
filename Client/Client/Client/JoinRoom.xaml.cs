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
                foreach (string player in socket.GetPlayersInRoom(room.ID)) // Consider better way to insert into the listbox
                    Players.Items.Add(player);
            }
            catch (Exception excep)
            {
                socket.ShowErrorMessage(excep.Message);
            }
            InitializeComponent();
        }

        private void JoinRoomButton(object sender, RoutedEventArgs e)
        {
            try
            {
                socket.JoinRoom(room.ID);
            }
            catch (Exception excep)
            {
                socket.ShowErrorMessage(excep.Message);
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
            }
            catch (Exception excep)
            {
                socket.ShowErrorMessage(excep.Message);
            }
        }
    }
}
