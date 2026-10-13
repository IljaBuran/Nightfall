using CommunityToolkit.Mvvm.ComponentModel;

namespace NightfallEditor.ViewModels;

public partial class HierarchyVM : ObservableObject
{
    public HierarchyVM()
    {
        // TODO: delete later, this is only to test the visuals
        
        Root.Children.Add(new HierarchyNodeVM { Name = "Child1" });
        Root.Children.Add(
            new HierarchyNodeVM 
            { 
                Name = "Child2", 
                Children = [new HierarchyNodeVM { 
                    Name = "Child21",
                    Children = [new HierarchyNodeVM { Name="Child211"}]
                }] 
            }
        );
    }

    [ObservableProperty]
    HierarchyNodeVM _root = new() { Name = "SceneName" };
}