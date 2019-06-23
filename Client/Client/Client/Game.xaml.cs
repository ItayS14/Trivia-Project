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
        int currQuestion;
        int questionCount;
        public Game()
        {
            InitializeComponent();

            timer = new DispatcherTimer();
            timer.Tick += TimerTick;
            timer.Interval = TimeSpan.FromSeconds(1);
            timer.Start();
            currQuestion = 0;
            timePerQuestion = 5;
            questionCount = 4;
            UpdateQuestionScreen();
        }

        private void TimerTick(object sender, EventArgs e)
        {
            TimerLabel.Text = (int.Parse(TimerLabel.Text) - 1).ToString();
            if (TimerLabel.Text == "-1") // add a function that checks if user clicked on an answer
            {
                timer.Stop();
                if (!IsAnswerPressed())
                {
                    Utlis.ShowErrorMessage("No answer was pressed");
                    foreach (Button b in Answers.Children.OfType<Button>()) // make the buttons unclickable during the sleep
                        b.IsHitTestVisible = false;
                }
                    System.Threading.Thread.Sleep(3000);
                if (questionCount == currQuestion)
                    Utlis.ShowErrorMessage("Finished");
                UpdateQuestionScreen();
                timer.Start();
            }
        }

        private void AnswerButton(object sender, RoutedEventArgs e)
        {
            foreach (Button b in Answers.Children.OfType<Button>())
            {
                if (b == sender)
                    b.IsHitTestVisible = false;
                else
                    b.IsEnabled = false;
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
        private void UpdateQuestionScreen() // the function updates the question screen to next question
        {
            TimerLabel.Text = timePerQuestion.ToString();
            Counter.Text = "Question: " + ++currQuestion;
            foreach (Button b in Answers.Children.OfType<Button>())
            {
                b.IsEnabled = true;
                b.IsHitTestVisible = true;
            }

            //add code that gets next question
        }
    }
}
