using System.Windows.Controls;
using AvalonDock;
using AvalonDock.Themes;

namespace NightfallEditor.Views;

/// <summary>
/// Interaction logic for Workspace.xaml
/// </summary>
public partial class Workspace : UserControl
{
    public Workspace()
    {
        InitializeComponent();
        DockManager.Theme = new ArcDarkTheme();
    }
}
