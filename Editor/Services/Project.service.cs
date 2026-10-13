using System.IO;

namespace NightfallEditor.Services;

using NightfallEditor.Models;

public static class ProjectService
{
    public static 
    string? ValidateNewProject(string name, string location)
    {
        if (string.IsNullOrWhiteSpace(name)) 
            return "Enter a valid project name.";
        if (name.IndexOfAny(Path.GetInvalidFileNameChars()) >= 0) 
            return "The name contains invalid characters.";
        if (!Directory.Exists(location)) 
            return "The location doesn't exist.";

        var dir = Path.Combine(location, name);
        if (Directory.Exists(dir) && Directory.EnumerateFileSystemEntries(dir).Any())
            return "A non-empty folder with this name already exists.";
        
        // valid
        return null;
    }

    public static
    void Create(string name, string location)
    {
        // validate
        if (ValidateNewProject(name, location) is { } error)
        {
            throw new InvalidOperationException(error);
        }

        // create new folder location + project name
        Directory.CreateDirectory(Path.Combine(location, name));


    }
}

