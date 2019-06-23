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
        private SocketHandler socket;
        private DispatcherTimer timer;
        private int timePerQuestion;
        private int currQuestion;
        private int questionCount;
        private int gameId;
        private int index;

        public Game(SocketHandler socket, Room room)
        {
            InitializeComponent();
            this.socket = socket;
            gameId = room.ID;
            timer = new DispatcherTimer();
            timer.Tick += TimerTickAsync;
            timer.Interval = TimeSpan.FromSeconds(1);
            timer.Start();
            currQuestion = 0;
            timePerQuestion = room.TimePerQuestion;
            questionCount = room.QuestionCount;
            UpdateQuestionScreen();
        }

        private async void TimerTickAsync(object sender, EventArgs e)
        {
            TimerLabel.Text = (int.Parse(TimerLabel.Text) - 1).ToString();
            if (TimerLabel.Text == "0") // add a function that checks if user clicked on an answer
            {
                timer.Stop();
                if (!IsAnswerPressed())
                {
                    Utlis.ShowErrorMessage("No answer was pressed");
                    index = 4;
                    foreach (Button b in Answers.Children.OfType<Button>()) // make the buttons unclickable during the sleep
                        b.IsHitTestVisible = false;
                }
                await Task.Delay(2000);
                if (questionCount == currQuestion)
                    Utlis.ShowErrorMessage("Finished");
                SubmitAnswer();
                UpdateQuestionScreen();
                timer.Start();
            }
        }

        private void AnswerButton(object sender, RoutedEventArgs e)
        {
            int count = 0;
            index = 0;
            foreach (Button b in Answers.Children.OfType<Button>())
            {
                if (b == sender) //Will only occur once
                {
                    b.IsHitTestVisible = false;
                    index = count;
                }
                else
                    b.IsEnabled = false;
                count++;
            }
        }

        private bool IsAnswerPressed()
        {
            foreach (Button b in Answers.Children.OfType<Button>())
            {
                if (!b.IsHitTestVisible) // this field would be false if a button is pressed
                    return true;
            }
            return false;
        }
        private void SubmitAnswer()
        {
            Dictionary<string,object> data = socket.SubmitAnswer(index, currQuestion);
            int correctAns = Convert.ToInt32(data["correct_ans"]);
            int count = 0;
            foreach (Button b in Answers.Children.OfType<Button>())
                if (correctAns == count++)
                { }//Temp   
        }

        private void UpdateQuestionScreen() // the function updates the question screen to next question
        {
            TimerLabel.Text = timePerQuestion.ToString();
            Counter.Text = "Question: " + ++currQuestion;
            Dictionary<string, object> data = socket.GetQuestion(currQuestion);
            QuestionText.Text = Convert.ToString(data["question"]);
            List<string> answers = Utlis.ObjectToList<string>(data["answers"]);
            int count = 0;
            foreach (Button b in Answers.Children.OfType<Button>())
            {
                b.Content = answers[count++];
                b.IsEnabled = true;
                b.IsHitTestVisible = true;
            }

        }

        private void LeaveGameButton(object sender, RoutedEventArgs e)
        {
            socket.LeaveGame(gameId);
            NavigationService.Navigate(new RoomsMenu(socket));
        }
    }
}
