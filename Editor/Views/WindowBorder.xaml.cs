using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace NightfallEditor.Views;

public partial class WindowBorder : UserControl
{
    public WindowBorder()
    {
        InitializeComponent();

        Loaded += OnLoaded;
    }

    private void OnLoaded(object sender, RoutedEventArgs e)
    {
        if (Window.GetWindow(this) is not Window window)
            return;

        MaximizeButton.IsEnabled =
            window.ResizeMode is ResizeMode.CanResize
                              or ResizeMode.CanResizeWithGrip;
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
        if (Window.GetWindow(this) is not Window window || window.ResizeMode == ResizeMode.NoResize)
            return;

        if (window.WindowState == WindowState.Maximized)
            SystemCommands.RestoreWindow(window);
        else
            SystemCommands.MaximizeWindow(window);
    }
}
