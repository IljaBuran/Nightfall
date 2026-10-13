using System.Windows;

using NightfallEditor.ViewModels;

namespace NightfallEditor;

public partial class StartupWindow : Window
{
    public StartupWindow()
    {
        InitializeComponent();

        DataContext = new StartupWindowVM();
    }
}