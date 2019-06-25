using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.DataVisualization.Charting;
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
        private int correctAns;
        private double score;

        bool finished;

        private Button[] answersButtons;

        public Game(SocketHandler socket, Room room)
        {
            InitializeComponent();

            this.socket = socket;
            this.room = room;
            currQuestion = 0;
            answersButtons = new Button[4];
            finished = false;
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


                //update statistics
                //Statistics.Visibility = Visibility.Visible;
                //List<KeyValuePair<string, int>> statistics = new List<KeyValuePair<string, int>>();
                //foreach (int count in socket.GetStatistics())
                //  statistics.Add(new KeyValuePair<string, int>("Answer", count));
                //((ColumnSeries)Statistics.Series[0]).ItemsSource = statistics;

                if (index == NO_ANSWER_PRESSED)
                    SubmitAnswer();

                for (int i = 0; i < answersButtons.Length; i++)
                    if (i != correctAns)
                        answersButtons[i].IsEnabled = false;
                Score.Content = score.ToString();
                await Task.Delay(2000);

                //disable statistics
                //Statistics.Visibility = Visibility.Hidden;

                if (finished)
                    return;

                if (room.QuestionCount == currQuestion)
                {
                    finished = true;
                    NavigationService.Navigate(new GameResults(socket, room.ID)); //room id is the same as game id
                    return;
                }

                UpdateQuestionScreen();
                timer.Start();
            }
        }

        private void AnswerButton(object sender, RoutedEventArgs e)
        {
            for (int i = 0; i < answersButtons.Length; i++)
            {
                answersButtons[i].IsHitTestVisible = false;
                if (answersButtons[i] == sender)
                {
                    answersButtons[i].BorderBrush = System.Windows.Media.Brushes.Black;
                    index = i;
                }
            }
            SubmitAnswer();
        }

        private void SubmitAnswer()
        {
            Dictionary<string,object> data = socket.SubmitAnswer(index);
            correctAns = Convert.ToInt32(data["correct_ans"]);
            score = Convert.ToDouble(data["score"]);
        }

        private void UpdateQuestionScreen() // the function updates the question screen to next question
        {
            index = NO_ANSWER_PRESSED;

            TimerLabel.Text = room.TimePerQuestion.ToString();
            Counter.Text = "Question: " + ++currQuestion;
            
            Dictionary<string, object> data = socket.GetQuestion();
            QuestionText.Text = Convert.ToString(data["question"]);
            List<string> answers = Utlis.ObjectToList<string>(data["answers"]);
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
            finished = true;
            socket.LeaveGame();
            timer.Stop();
            NavigationService.Navigate(new RoomsMenu(socket));
        }
    }
}
