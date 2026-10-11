using System.Collections.ObjectModel;
using System.Windows.Controls;

namespace NightfallEditor.Views.Panels;
public partial class Hierarchy : UserControl
{
    public Hierarchy()
    {
        InitializeComponent();
        MenuItem root = new MenuItem() { Title = "Menu" };
        MenuItem childItem1 = new MenuItem() { Title = "Child item #1" };
        childItem1.Items.Add(new MenuItem() { Title = "Child item #1.1" });
        childItem1.Items.Add(new MenuItem() { Title = "Child item #1.2" });
        root.Items.Add(childItem1);
        root.Items.Add(new MenuItem() { Title = "Child item #2" });
        trvMenu.Items.Add(root);
    }
}
public class MenuItem
{
    public MenuItem()
    {
        this.Items = new ObservableCollection<MenuItem>();
    }

    public string? Title { get; set; }

    public ObservableCollection<MenuItem> Items { get; set; }
}
