using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using System.IO;

namespace NightfallEditor.ViewModels;

using NightfallEditor.Services;
using System.Windows;

public partial class StartupWindowVM : ObservableObject
{
    [ObservableProperty]
    [NotifyPropertyChangedFor(nameof(NewProjectPathPreview))]
    private string _newProjectName = "";

    [ObservableProperty]
    [NotifyPropertyChangedFor(nameof(NewProjectPathPreview))]
    private string _newProjectLocation =
        Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);

    public string NewProjectPathPreview =>
        Path.Combine(NewProjectLocation, NewProjectName, NewProjectName + ".nf");

    [ObservableProperty]
    private string? _newProjectError;

    [ObservableProperty]
    Visibility _pathPreviewVisibility = Visibility.Hidden;

    public StartupWindowVM()
    {
        Revalidate();
    }

    // ---- Validation (rules live in ProjectPaths, the VM only shows the result) ----

    partial void OnNewProjectNameChanged(string value) => Revalidate();
    partial void OnNewProjectLocationChanged(string value) => Revalidate();

    private void Revalidate()
    {
        NewProjectError = ProjectService.ValidateNewProject(NewProjectName, NewProjectLocation);

        PathPreviewVisibility = 
            NewProjectError == null ? Visibility.Visible : Visibility.Hidden;

        CreateCommand.NotifyCanExecuteChanged();
    }

    // ---- Commands ----

    [RelayCommand(CanExecute = nameof(CanCreate))]
    private void Create()
    {
        // ProjectService.Create(NewProjectName, NewProjectLocation) → then close the window
    }

    private bool CanCreate() => NewProjectError is null;
}