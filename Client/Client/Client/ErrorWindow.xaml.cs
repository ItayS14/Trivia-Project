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
    /// Interaction logic for ErrorWindow.xaml
    /// </summary>
    public partial class ErrorWindow : Window
    {
        public ErrorWindow()
        {
            InitializeComponent();
        }
        public ErrorWindow(string info)
        {
            InitializeComponent();
            TextBlock tb = new TextBlock();
            tb.Height = 100;
            tb.Width = 200;
            tb.Inlines.Add(info);
            tb.Text = "Error!\nInfo:" + info;
        }
    }
}
