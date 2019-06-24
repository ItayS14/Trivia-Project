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
using System.Windows.Threading;

namespace Client
{
    /// <summary>
    /// Interaction logic for Game.xaml
    /// </summary>
    public partial class Game : Page
    {
        static int NO_ANSWER_PRESSED = 4; 

        private SocketHandler socket;
        private DispatcherTimer timer;
        private Room room;
        private int currQuestion;
        private int index;

        private Button[] answersButtons;

        public Game(SocketHandler socket, Room room)
        {
            InitializeComponent();

            this.socket = socket;
            this.room = room;
            currQuestion = 0;
            answersButtons = new Button[4];
            int count = 0;
            foreach (Button b in Answers.Children.OfType<Button>())
                answersButtons[count++] = b;

            timer = new DispatcherTimer();
            timer.Tick += TimerTickAsync;
            timer.Interval = TimeSpan.FromSeconds(1);
            timer.Start();

            UpdateQuestionScreen();
        }

        private async void TimerTickAsync(object sender, EventArgs e)
        {
            TimerLabel.Text = (int.Parse(TimerLabel.Text) - 1).ToString();
            if (TimerLabel.Text == "0") // add a function that checks if user clicked on an answer
            {
                timer.Stop();
                SubmitAnswer();
                if (index == NO_ANSWER_PRESSED)
                {
                    Utlis.ShowErrorMessage("No answer was pressed");
                    foreach (Button b in Answers.Children.OfType<Button>()) // make the buttons unclickable during the sleep
                        b.IsHitTestVisible = false;
                }
                await Task.Delay(2000);
                if (room.QuestionCount == currQuestion)
                    Utlis.ShowErrorMessage("Finished"); // later would navigate to high screen
                UpdateQuestionScreen();
                timer.Start();
            }
        }

        private void AnswerButton(object sender, RoutedEventArgs e)
        {
            index = NO_ANSWER_PRESSED; 
            for (int i = 0; i < answersButtons.Length; i++)
            {
                answersButtons[i].IsHitTestVisible = false;
                if (answersButtons[i] == sender)
                {
                    answersButtons[i].BorderBrush = System.Windows.Media.Brushes.Black;
                    index = i;
                }
            }
        }

        private void SubmitAnswer()
        {
            Dictionary<string,object> data = socket.SubmitAnswer(index, currQuestion);
            int correctAns = Convert.ToInt32(data["correct_ans"]);
            for(int i = 0; i <answersButtons.Length; i++)
            {
                if (i != correctAns)
                    answersButtons[i].IsEnabled = false;
            }
        }

        private void UpdateQuestionScreen() // the function updates the question screen to next question
        {
            TimerLabel.Text = room.TimePerQuestion.ToString();
            Counter.Text = "Question: " + ++currQuestion;
            
            Dictionary<string, object> data = socket.GetQuestion(currQuestion);
            QuestionText.Text = Convert.ToString(data["question"]);
            List<string> answers = Utlis.ObjectToList<string>(data["answersButtons"]);
            for (int i = 0; i < answersButtons.Length; i++)
            {
                answersButtons[i].Content = answers[i];
                answersButtons[i].IsEnabled = true;
                answersButtons[i].IsHitTestVisible = true;
                answersButtons[i].BorderBrush = null;
            }
        }

        private void LeaveGameButton(object sender, RoutedEventArgs e)
        {
            socket.LeaveGame(room.ID);
            NavigationService.Navigate(new RoomsMenu(socket));
        }
    }
}
