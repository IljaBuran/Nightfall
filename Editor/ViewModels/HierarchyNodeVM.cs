using CommunityToolkit.Mvvm.ComponentModel;
using System.Collections.ObjectModel;

namespace NightfallEditor.ViewModels;

public partial class HierarchyNodeVM : ObservableObject
{
    [ObservableProperty] 
    private string _name = "";
    [ObservableProperty] 
    private bool _isSelected;
    
    public ObservableCollection<HierarchyNodeVM> Children { get; set; } = new();
}