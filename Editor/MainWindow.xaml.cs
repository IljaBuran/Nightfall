using System.Windows;

namespace NightfallEditor;

public partial class MainWindow : Window
{
    public MainWindow()
    {
        InitializeComponent();
    }

    // https://stackoverflow.com/questions/29391063/wpf-maximized-window-bigger-than-screen
    private void Window_SizeChanged(object sender, SizeChangedEventArgs e)
    {
        if (this.WindowState == WindowState.Maximized)
        {
            this.BorderThickness = new System.Windows.Thickness(8);
        }
        else
        {
            this.BorderThickness = new System.Windows.Thickness(0);
        }
    }
}