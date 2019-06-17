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
    /// Interaction logic for RoomsMenu.xaml
    /// </summary>
    public partial class RoomsMenu : Page
    {
        private SocketHandler socket;

        public RoomsMenu(SocketHandler socket)
        {
            InitializeComponent();
            this.socket = socket;
            try
            {
                //Get the list in JSON
                List<Dictionary<string, object>> roomsJson = socket.GetRooms();

                //Convert the JSON to a list of rooms
                List<Room> rooms = new List<Room>();
                foreach (Dictionary<string, object> dict in roomsJson)
                    rooms.Add(new Room((int)dict["room_id"], (string)dict["room_name"], (int)dict["type"], (int)dict["max_players"], (int)dict["logged_players"]));

                //Display all the rooms in the table
                Rooms.ItemsSource = rooms;
            }
            catch(Exception excep)
            {
                socket.ShowErrorMessage(excep.Message);
            }

            //Connect the join room function once the user chooses a room

        }
        private void NewRoomButton(object sender, RoutedEventArgs e)
        { 
           NavigationService.Navigate(new CreateRoom(socket));
        }
        
  
        private void LogoutButton(object sender, RoutedEventArgs e)
        {
            socket.SignOut();
        }

        private void DoubleClickHandler(object sender, System.Windows.Input.MouseEventArgs e)
        {
            NavigationService.Navigate(new JoinRoom(socket, (Room)Rooms.SelectedItem));
        }
    }

    public enum Types
    {
        //	Options: all = 0, sport = 1, general = 2, math = 3, tv = 4, geography = 5]
        All = 0,
        Sport,
        General_Knowledge,
        Math,
        TV,
        Geography
    }

    public class Room
    {
        public Room(int id, string name, int type, int maxPlayers, int loggedPlayers)
        {
            ID = id;
            Name = name;
            Players = loggedPlayers + "/" + maxPlayers;
            Type = Enum.GetName(typeof(Types), type).Replace('_', ' ');
        }

        public int ID { set; get; }
        public string Name { set; get; }
        public string Type { set; get; }
        public string Players { set; get; }
    }
}
