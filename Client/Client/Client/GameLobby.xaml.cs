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
        private Room room;
        public GameLobby(SocketHandler socket, Room room)
        {
            InitializeComponent();
            this.socket = socket;
            this.room = room;
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
    }
}
