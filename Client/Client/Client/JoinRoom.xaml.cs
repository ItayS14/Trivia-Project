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
        private SocketHandler s;
        private Room room;


        public JoinRoom(SocketHandler s, Room room) // Should i also display other stuff that belongs to the room?
        {
            InitializeComponent();
            this.s = s;
            this.room = room;
            foreach (string player in s.GetPlayersInRoom(room.ID)) // Consider better way to insert into the listbox
                Players.Items.Add(player);
            InitializeComponent();
        }

        private void JoinRoomButton(object sender, RoutedEventArgs e)
        {
            s.JoinRoom(room.ID);
        }

        private void BackButton(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new RoomsMenu(s));
        }

        private void LogoutButton(object sender, RoutedEventArgs e)
        {
            s.SignOut();
        }
    }
}
