using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace NightfallEditor.Views;

public partial class WindowBorder : UserControl
{
    public WindowBorder()
    {
        InitializeComponent();
    }

    private void OnCloseClicked(object sender, RoutedEventArgs e)
    {
        if (Window.GetWindow(this) is Window window)
            SystemCommands.CloseWindow(window);
    }

    private void OnMinimizeClicked(object sender, RoutedEventArgs e)
    {
        if (Window.GetWindow(this) is Window window)
            SystemCommands.MinimizeWindow(window);
    }

    private void OnMaximizeClicked(object sender, RoutedEventArgs e)
    {
        if (Window.GetWindow(this) is not Window window)
            return;

        if (window.WindowState == WindowState.Maximized)
            SystemCommands.RestoreWindow(window);
        else
            SystemCommands.MaximizeWindow(window);
    }
}
