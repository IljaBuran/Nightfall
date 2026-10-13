using System.Diagnostics.Metrics;
using System.Windows;
using System.Windows.Controls;

namespace NightfallEditor.Views
{
    /// <summary>
    /// Interaction logic for MenuBar.xaml
    /// </summary>
    public partial class MenuBar : UserControl
    {
        public MenuBar()
        {
            InitializeComponent();
        }

        private uint counter = 0;

        private void Increase(object sender, RoutedEventArgs e)
        {
            counter++;
        }

        private void Decrease(object sender, RoutedEventArgs e)
        { 
            if (counter >= 0)
            {
                counter--;
            }
        }


    }
}