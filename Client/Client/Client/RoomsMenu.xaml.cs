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

        bool finished;

        public RoomsMenu(SocketHandler socket)
        {
            InitializeComponent();
            finished = false;
            this.socket = socket;
            UpdateRoomsList();
        }

        private void NewRoomButton(object sender, RoutedEventArgs e)
        {
            finished = true;
           NavigationService.Navigate(new CreateRoom(socket));
        }
        
  
        private void LogoutButton(object sender, RoutedEventArgs e)
        {
            finished = true;
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

        private void DoubleClickHandler(object sender, System.Windows.Input.MouseEventArgs e)
        {
            finished = true;
            NavigationService.Navigate(new JoinRoom(socket, (Room)Rooms.SelectedItem));
        }

        //The function will update the list of rooms by sending request to the server
        private async void UpdateRoomsList()
        {
            while (!finished)
            {
                try
                {
                    //Get the list in JSON
                    List<Dictionary<string, object>> roomsJson = socket.GetRooms();

                    //Convert the JSON to a list of rooms
                    List<Room> rooms = new List<Room>();
                    if (roomsJson != null)
                    {
                        foreach (Dictionary<string, object> dict in roomsJson)
                            rooms.Add(new Room(Convert.ToInt32(dict["room_id"]), Convert.ToString(dict["room_name"]), Convert.ToInt32(dict["type"]),
                                Convert.ToInt32(dict["max_players"]), Convert.ToInt32(dict["logged_players"]), Convert.ToInt32(dict["state"]),
                                Convert.ToInt32(dict["time_per_question"]), Convert.ToInt32(dict["question_count"])));
                    }

                    //Display all the rooms in the table
                    Rooms.ItemsSource = rooms;
                }
                catch (Exception excep)
                {
                    Utlis.ShowErrorMessage(excep.Message);
                }
                await Task.Delay(3000);
            }

        }

        private void ListView_SelectionChanged_2(object sender, SelectionChangedEventArgs e)
        {

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

    public enum State
    {
        Joinable = 0,
        In_Game
    }


    public class Room
    {
        public Room() { }
        public Room(int id, string name, int type, int maxPlayers, int loggedPlayers, int state, int timePerQuestion, int questionCount)
        {
            ID = id;
            Name = name;
            Players = loggedPlayers + "/" + maxPlayers;
            Type = Enum.GetName(typeof(Types), type).Replace('_', ' ');
            State = Enum.GetName(typeof(State), state).Replace('_', ' ');
            TimePerQuestion = timePerQuestion;
            QuestionCount = questionCount;
        }

        public int ID { set; get; }
        public string Name { set; get; }
        public string Type { set; get; }
        public string Players { set; get; }
        public string State { set; get; }
        public int TimePerQuestion { set; get; }
        public int QuestionCount { set; get; }
    }
}
