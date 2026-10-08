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

        private void DoNothing(object sender, RoutedEventArgs e)
        {
            return;
        }
    }
}
