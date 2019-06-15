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
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class RoomsMenu : Window
    {
        private SocketHandler s;

        public RoomsMenu()
        {
            InitializeComponent();
            //List<Room> rooms = new List<Room>() { new Room(3, "itay", (int)Types.SPORT, 3, 2) };
            // SocketHandler
            // Rooms.ItemsSource = rooms;
        }

        public RoomsMenu(SocketHandler s)
        {
            this.s = s;
            try
            {
                //Get the list in JSON
                List<Dictionary<string, object>> roomsJson = s.GetRooms();

                //Convert the JSON to a list of rooms
                List<Room> rooms = new List<Room>();
                foreach (Dictionary<string, object> dict in roomsJson)
                    rooms.Add(new Room((int)dict["room_id"],(string) dict["room_name"], (int)dict["type"], (int)dict["max_players"], (int)dict["logged_players"]));

                //Display all the rooms in the table
                Rooms.ItemsSource = rooms;
            }
            catch
            {
                //Open an error window with a message
            }

            //Connect the join room function once the user chooses a room
            
        }
    
        private void NewRoomButton(object sender, RoutedEventArgs e)
        {
            //Remember to change
            //Remember to change
            //Remember to change
            //The line should be
            //NavigationService.Navigate(new CreateRoomPage());

            CreateRoom create = new CreateRoom(); 
        }


        private void ListView_SelectionChanged_2(object sender, SelectionChangedEventArgs e)
        {

        }

        private void LogoutButton(object sender, RoutedEventArgs e)
        {
            s.SignOut();
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
        public Room(int id, string name, int type, int max_players, int logged_players)
        {
            ID = id;
            Name = name;
            Players = logged_players + "/" + max_players;
            Type = Enum.GetName(typeof(Types), type).Replace('_', ' ');
        }

        public int ID { set; get; }
        public string Name { set; get; }
        public string Type { set; get; }
        public string Players { set; get; }
    }
}
