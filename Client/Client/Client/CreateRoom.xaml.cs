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
using System.Windows.Shapes;

namespace Client
{
    /// <summary>
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    public partial class CreateRoom : Window
    {
        public CreateRoom()
        {
            InitializeComponent();
        }
        public CreateRoom(SocketHandler s)
        {
            try
            {
                //CHANGE THIS
                //CHANGE THIS
                //CHANGE THIS
                //CHANGE THIS
                s.CreateRoom(NameTextBox.Text, 10, 10, 10, int.Parse(RoomType.Text)); //not sure if RoomType.Text is the right property, need to check
            }
            
            //Now open the window of the new room
        }
        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
        }
    }
}
