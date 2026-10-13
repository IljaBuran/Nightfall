using System.Windows.Controls;

using NightfallEditor.ViewModels;

namespace NightfallEditor.Views.Panels;
public partial class Hierarchy : UserControl
{
    public Hierarchy()
    {
        InitializeComponent();

        DataContext = new HierarchyVM();
    }
}
