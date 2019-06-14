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
        public RoomsMenu()
        {
            InitializeComponent();
            //List<Room> rooms = new List<Room>() { new Room(3, "itay", (int)Types.SPORT, 3, 2) };
            SocketHandler
            Rooms.ItemsSource = rooms;
        }
    

        private void NewRoomButton(object sender, RoutedEventArgs e)
        {
            CreateRoom create = new CreateRoom();
            App.Current.MainWindow = create;
            this.Close();
            create.Show();
        }


        private void ListView_SelectionChanged_2(object sender, SelectionChangedEventArgs e)
        {

        }

        public enum Types
        {
            //	Options: all = 0, sport = 1, general = 2, math = 3, tv = 4, geography = 5]
            ALL = 0,
            SPORT,
            GENERAL,
            MATH,
            TV,
            GEOGRAPHY
        }
        
        public class Room
        {
            public Room(int id, string name, int type, int max_players, int logged_players)
            {
                ID = id;
                Name = name;
                Players = logged_players + "/" + max_players;
                switch ((Types)type)
                {
                    case Types.ALL:
                        Type = "All";
                        break;
                    case Types.SPORT:
                        Type = "Sport";
                        break;
                    case Types.GENERAL:
                        Type = "General Knowledge";
                        break;
                    case Types.MATH:
                        Type = "Math";
                        break;
                    case Types.TV:
                        Type = "Tv";
                        break;
                    case Types.GEOGRAPHY:
                        Type = "Geography";
                        break;
                }
            }

            public int ID { set; get; }
            public string Name { set; get; }
            public string Type { set; get; }
            public string Players { set; get; }
        }

    }

}
