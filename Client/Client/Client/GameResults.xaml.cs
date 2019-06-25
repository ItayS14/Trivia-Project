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
    /// Interaction logic for GameResults.xaml
    /// </summary>
    public partial class GameResults : Page
    {
        private SocketHandler socket;
        private int gameId;
        public GameResults(SocketHandler socket, int gameId)
        {
            InitializeComponent();
            this.socket = socket;
            this.gameId = gameId;
            Dictionary<string,double> players = socket.GetLeaderboard();

            //Change dictionary to list of pairs so we can sort it
            var list = players.ToList();
            list.Sort((pair1, pair2) => pair1.Value.CompareTo(pair2.Value));

            Players.ItemsSource = list;

            //Maybe add start time and end time
        }
        private void LeaveGameButton(object sender, RoutedEventArgs e)
        {
            socket.LeaveGame();
            NavigationService.Navigate(new RoomsMenu(socket));
        }

        private void Players_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }
    }
}
