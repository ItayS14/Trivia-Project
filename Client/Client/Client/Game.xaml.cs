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
        DispatcherTimer timer;
        int timePerQuestion;
        int questionCount;

        public Game()
        {
            InitializeComponent();

            timer = new DispatcherTimer();
            timer.Tick += TimerTick;
            timer.Interval = TimeSpan.FromSeconds(1);
            timer.Start();
            questionCount = 0;
            timePerQuestion = 5;
            UpdateQuestionScreen();
        }

        private void TimerTick(object sender, EventArgs e)
        {
            TimerLabel.Text = (int.Parse(TimerLabel.Text) - 1).ToString();
            if (TimerLabel.Text == "-1") // add a function that checks if user clicked on an answer
            {
                timer.Stop();
                System.Threading.Thread.Sleep(3000);
                UpdateQuestionScreen();
                timer.Start();
            }
        }

        private void AnswerButton(object sender, RoutedEventArgs e)
        {
            foreach (Button b in Answers.Children.OfType<Button>())
            {
                if (b != sender)
                    b.IsEnabled = false;
            }
        }

        private void UpdateQuestionScreen() // the function updates the question screen to next question
        {
            TimerLabel.Text = timePerQuestion.ToString();
            questionCount++;
            Counter.Text = "Question: " + questionCount;
            foreach (Button b in Answers.Children.OfType<Button>())
                    b.IsEnabled = true;
            
            //add code that gets next question
        }
    }
}
